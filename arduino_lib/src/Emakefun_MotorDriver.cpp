/*!
 * @file Emakefun_MotorDriver.cpp
 *
 * @mainpage Emakefun FXOS8700 accel/mag sensor driver
 *
 * @section intro_sec Introduction
 *
 * This is the library for the Emakefun Motor Shield V2 for Arduino.
 * It supports DC motors & Stepper motors with microstepping as well
 * as stacking-support. It is *not* compatible with the V1 library!
 * For use with the Motor Shield https://www.emakefun.com/
 * and Motor FeatherWing https://www.emakefun.com/
 *
 * This shield/wing uses I2C to communicate, 2 pins (SCL+SDA) are required
 * to interface.
 *
 * Emakefun invests time and resources providing this open source code,
 * please support Emakefun and open-source hardware by purchasing
 * products from Emakefun!
 *
 * @section author Author
 *
 *
 * @section license License
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */
#include "PinChangeInt.h"
#include "Emakefun_MotorDriver.h"
#include "Arduino.h"
#include "Emakefun_MS_PWMServoDriver.h"
#include <Wire.h>

#if (MICROSTEPS == 8)
///! A sinusoial microstepping curve for the PWM output (8-bit range) with 9
/// points - last one is start of next step.
static uint8_t microstepcurve[] = {0, 50, 98, 142, 180, 212, 236, 250, 255};
#elif (MICROSTEPS == 16)
///! A sinusoial microstepping curve for the PWM output (8-bit range) with 17
/// points - last one is start of next step.
static uint8_t microstepcurve[] = {0,   25,  50,  74,  98,  120, 141, 162, 180,
                                   197, 212, 225, 236, 244, 250, 253, 255};
#endif

/**************************************************************************/
/*!
    @brief  Create the Motor Shield object at an I2C address, default is 0x60
    @param  addr Optional I2C address if you've changed it
*/
/**************************************************************************/
Emakefun_MotorDriver::Emakefun_MotorDriver(uint8_t addr) {
  _addr = addr;
  _pwm = Emakefun_MS_PWMServoDriver(_addr);
}

/**************************************************************************/
/*!
    @brief  Initialize the I2C hardware and PWM driver, then turn off all pins.
    @param    freq
    The PWM frequency for the driver, used for speed control and microstepping.
    By default we use 1600 Hz which is a little audible but efficient.
    @param    theWire
    A pointer to an optional I2C interface. If not provided, we use Wire or
   Wire1 (on Due)
*/
/**************************************************************************/
void Emakefun_MotorDriver::begin(uint16_t freq, TwoWire *theWire) {
  if (!theWire) {
#if defined(ARDUINO_SAM_DUE)
    _i2c = &Wire1;
#else
    _i2c = &Wire;
#endif
  } else {
    _i2c = theWire;
  }

  // init PWM w/_freq
  _i2c->begin();
  _pwm.begin();
  _freq = freq;
  _pwm.setPWMFreq(_freq); // This is the maximum PWM frequency
  for (uint8_t i = 0; i < 16; i++)
    _pwm.setPWM(i, 0, 0);
}

/**************************************************************************/
/*!
    @brief  Helper that sets the PWM output on a pin and manages 'all on or off'
    @param  pin The PWM output on the driver that we want to control (0-15)
    @param  value The 12-bit PWM value we want to set (0-4095) - 4096 is a
   special 'all on' value
*/
/**************************************************************************/
void Emakefun_MotorDriver::setPWM(uint8_t pin, uint16_t value) {
  if (value > 4095) {
    _pwm.setPWM(pin, 4096, 0);
  } else
    _pwm.setPWM(pin, 0, value);
}

/**************************************************************************/
/*!
    @brief  Helper that sets the PWM output on a pin as if it were a GPIO
    @param  pin The PWM output on the driver that we want to control (0-15)
    @param  value HIGH or LOW depending on the value you want!
*/
/**************************************************************************/
void Emakefun_MotorDriver::setPin(uint8_t pin, boolean value) {
  if (value == LOW)
    _pwm.setPWM(pin, 0, 0);
  else
    _pwm.setPWM(pin, 4096, 0);
}

/**************************************************************************/
/*!
    @brief  Mini factory that will return a pointer to an already-allocated
    Emakefun_DCMotor object. Initializes the DC motor and turns off all pins
    @param  num The DC motor port we want to use: 1 thru 4 are valid
    @returns NULL if something went wrong, or a pointer to a Emakefun_DCMotor
*/
/**************************************************************************/
Emakefun_DCMotor *Emakefun_MotorDriver::getMotor(uint8_t num) {
  if (num > 4)
    return NULL;
  num--;
  if (dcmotors[num].motornum == 0) {
    dcmotors[num].motornum = num;
    dcmotors[num].MC = this;
    uint8_t in1, in2;
    if (num == 0) {
      in2 = 10; in1 = 8;      
    } else if (num == 1) {
      in2 = 13; in1 = 11;
    } else if (num == 2) {
      in2 = 2; in1 = 4;
    } else if (num == 3) {
      in2 = 7; in1 = 5;
    } 
    dcmotors[num].IN1pin = in1;
    dcmotors[num].IN2pin = in2;
  }
  return &dcmotors[num];
}

/**************************************************************************/
/*!
    @brief  Mini factory that will return a pointer to an already-allocated
    Emakefun_StepperMotor object with a given 'steps per rotation.
    Then initializes the stepper motor and turns off all pins.
    @param  steps How many steps per revolution (used for RPM calculation)
    @param  num The stepper motor port we want to use: only 1 or 2 are valid
    @returns NULL if something went wrong, or a pointer to a
   Emakefun_StepperMotor
*/
/**************************************************************************/
Emakefun_StepperMotor *Emakefun_MotorDriver::getStepper(uint8_t num, uint16_t steps) {
  if (num > 2) return NULL;

  num--;

  if (steppers[num].steppernum == 0) {
    // not init'd yet!
    steppers[num].steppernum = num;
    steppers[num].revsteps = steps;
    steppers[num].MC = this;
    uint8_t ain1, ain2, bin1, bin2;
    if (num == 0) {
        ain1 = 8; ain2 = 10;
#ifdef MOTOR_DRIVER_V5_2
        bin1 = 11; bin2 = 13;
#else
		bin1 = 13; bin2 = 11;
#endif

    } else if (num == 1) {
        ain1 = 5; ain2 = 7;
#ifdef MOTOR_DRIVER_V5_2

        bin1 = 4; bin2 = 2;
#else
		bin1 = 2; bin2 = 4;
#endif
    }
    steppers[num].AIN1pin = ain1;
    steppers[num].AIN2pin = ain2;
    steppers[num].BIN1pin = bin1;
    steppers[num].BIN2pin = bin2;
  }
  return &steppers[num];
}

Emakefun_Servo *Emakefun_MotorDriver::getServo(uint8_t num) {
  if (num > 8) return NULL;

  num--;

  if (servos[num].servonum == 0) {
    // not init'd yet!
    servos[num].servonum = num;
    servos[num].MC = this;
    uint8_t pwm;
    if (num == 0) {
      pwm = 0;
    } else if (num == 1) {
      pwm = 1;
    } else if (num == 2) {
      pwm = 14;
    } else if (num == 3) {
      pwm = 15;
    } else if (num == 4) {
      pwm = 3;
    } else if (num == 5) {
      pwm = 6;
    } else if (num == 6) {
      pwm = 9;
    } else if (num == 7) {
      pwm = 12;
    }
      servos[num].PWMpin = pwm;
    }
  return &servos[num];
}

/******************************************
               SERVOS
******************************************/

Emakefun_Servo::Emakefun_Servo(void) {
  MC = NULL;
  servonum = 0;
  PWMpin = 0;
  currentAngle = 0;
}

void Emakefun_Servo::setServoPulse(double pulse) {
  double pulselength;
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 50;   // 50 Hz
  pulselength /= 4096;  // 12 bits of resolution
  pulse *= 1000;
  pulse /= pulselength;
  MC->setPWM(PWMpin, pulse);
}
void Emakefun_Servo::writeServo(uint8_t angle) {
  double pulse;
  pulse = 0.5 + angle / 90.0;
  setServoPulse(pulse);
  currentAngle = angle;
  /* if (n > 1) {
     currentAngle[n-12]=angle;
    }else{
     currentAngle[n]=angle;
    } */
}

uint8_t Emakefun_Servo::readDegrees() {
  return currentAngle;
}

void Emakefun_Servo::writeServo(uint8_t angle, uint8_t speed) {
    double pulse;
    if (speed == 10) {
        pulse=0.5+angle/90.0;
        setServoPulse(pulse);
    } else {
        if (angle < currentAngle){
            for (int i = currentAngle; i > angle; i--)
            {
                delay(4 * (10 - speed));
                pulse = 0.5+i/90.0;
                setServoPulse(pulse);
            }
        } else {
            for (int i = currentAngle; i < angle; i++)
            {
                delay(4 * (10 - speed));
                pulse = 0.5+i/90.0;
                setServoPulse(pulse);
            }
        }
    }
    currentAngle = angle;
}
/******************************************
               MOTORS
******************************************/

/**************************************************************************/
/*!
    @brief  Create a DCMotor object, un-initialized!
    You should never call this, instead have the {@link Emakefun_MotorDriver}
    give you a DCMotor object with {@link Emakefun_MotorDriver.getMotor}
*/
/**************************************************************************/
Emakefun_DCMotor::Emakefun_DCMotor(void) {
  MC = NULL;
  motornum = 0;
  IN1pin = IN2pin = 0;
}

/**************************************************************************/
/*!
    @brief  Control the DC Motor direction and action
    @param  cmd The action to perform, can be FORWARD, BACKWARD or RELEASE
*/
/**************************************************************************/
void Emakefun_DCMotor::run(uint8_t cmd) {
    switch (cmd) {
        case FORWARD:
            MC->setPin(IN2pin, LOW);
            MC->setPin(IN1pin, MC->DcSpeed);
            break;
        case BACKWARD:
            MC->setPin(IN1pin, LOW);
            MC->setPin(IN2pin, MC->DcSpeed);
            break;
        case RELEASE:
            MC->setPin(IN1pin, LOW);
            MC->setPin(IN2pin, LOW);
            break;
        case BRAKE:
            MC->setPin(IN2pin, HIGH);
            MC->setPin(IN1pin, HIGH);
            break;
    }
}

/**************************************************************************/
/*!
    @brief  Control the DC Motor speed/throttle
    @param  speed The 8-bit PWM value, 0 is off, 255 is on
*/
/**************************************************************************/
void Emakefun_DCMotor::setSpeed(uint8_t speed) {
    MC->DcSpeed = (speed * 16);
}

/******************************************
               ENCODER MOTOR
******************************************/

Emakefun_EncoderMotor::Emakefun_EncoderMotor(void) {
  MC = NULL;
  encodernum = 0;
  IN2pin = IN1pin = ENCODER1pin = ENCODER2pin = 0;
  EncoderPulse = 0;
}

void Emakefun_EncoderMotor::init(PCIntvoidFuncPtr encoder_fun) {
  pinMode(ENCODER1pin, INPUT);
  pinMode(ENCODER2pin, INPUT);
  EncoderCallback = encoder_fun;
  attachPinChangeInterrupt(ENCODER1pin, encoder_fun, RISING);
}

Emakefun_EncoderMotor *Emakefun_MotorDriver::getEncoderMotor(uint8_t num) {
  if (num > 4) return NULL;
  num--;
  if (encoder[num].encodernum == 0) {
    // not init'd yet!
    encoder[num].encodernum = num;
    encoder[num].MC = this;

    uint8_t in1, in2, encoder1pin , encoder2pin;
    if (num == 0) {
     in1 = 8; in2 = 10; encoder1pin = 3; encoder2pin = 2;
    } else if (num == 1) {
      in1 = 11; in2 = 13; encoder1pin = 7; encoder2pin = 4;
    }else if (num == 2) {
      in1 = 4; in2 = 2; encoder1pin = 6; encoder2pin = 5;
    }else if (num == 3) {
      in1 = 5; in2 = 7; encoder1pin = 10; encoder2pin = 9;
    }    
    encoder[num].IN1pin = in1;
    encoder[num].IN2pin = in2;
    encoder[num].ENCODER1pin = encoder1pin;
    encoder[num].ENCODER2pin = encoder2pin;
  }
  return &encoder[num];
}

void Emakefun_EncoderMotor::run(uint8_t cmd) {
  switch (cmd) {
    case FORWARD:
      MC->setPin(IN2pin, LOW);
      MC->setPWM(IN1pin, MC->DcSpeed);
      break;
    case BACKWARD:
      MC->setPin(IN1pin, LOW);
      MC->setPWM(IN2pin, MC->DcSpeed);
      break;
    case RELEASE:
      MC->setPin(IN1pin, LOW);
      MC->setPin(IN2pin, LOW);
      break;
     case BRAKE:
      MC->setPin(IN2pin, HIGH);
      MC->setPin(IN1pin, HIGH);
      break;
  }
}

void Emakefun_EncoderMotor::setSpeed(uint8_t speed) {
     MC->DcSpeed = speed*16;
}

void Emakefun_EncoderMotor::run(uint8_t cmd, uint8_t speed, int pluse) {
    //int point_pluse = 0;
    setSpeed(speed);
    run(cmd);
    //Serial.println(":run end");
    if (cmd == FORWARD) {
      pluse = EncoderPulse + pluse;
      while (EncoderPulse < pluse) {
          //Serial.println(EncoderPulse);
      }
      run(BRAKE);
    } else if (cmd == BACKWARD) {
      pluse = EncoderPulse - pluse;
      while (EncoderPulse > pluse);
      run(BRAKE);
    }
}


/******************************************
               STEPPERS
******************************************/

/**************************************************************************/
/*!
    @brief  Create a StepperMotor object, un-initialized!
    You should never call this, instead have the {@link Emakefun_MotorDriver}
    give you a StepperMotor object with {@link Emakefun_MotorDriver.getStepper}
*/
/**************************************************************************/
Emakefun_StepperMotor::Emakefun_StepperMotor(void) {
  revsteps = steppernum = currentstep = 0;
}

/**************************************************************************/
/*!
    @brief  Set the delay for the Stepper Motor speed in RPM
    @param  rpm The desired RPM, we will do our best to reach it!
*/
/**************************************************************************/
// 设定一分钟旋转的圈速
void Emakefun_StepperMotor::setSpeed(uint16_t rpm) {
  // Serial.println("steps per rev: "); Serial.println(revsteps);
  // Serial.println("RPM: "); Serial.println(rpm);

  usperstep = 60000000 / ((uint32_t)revsteps * (uint32_t)rpm);
}

/**************************************************************************/
/*!
    @brief  Release all pins of the stepper motor so it free-spins
*/
/**************************************************************************/
void Emakefun_StepperMotor::release(void) {
  MC->setPin(AIN1pin, LOW);
  MC->setPin(AIN2pin, LOW);
  MC->setPin(BIN1pin, LOW);
  MC->setPin(BIN2pin, LOW);
}

/**************************************************************************/
/*!
    @brief  Move the stepper motor with the given RPM speed, don't forget to
   call
    {@link Emakefun_StepperMotor.setSpeed} to set the speed!
    @param  steps The number of steps we want to move
    @param  dir The direction to go, can be FORWARD or BACKWARD
    @param  style How to perform each step, can be SINGLE, DOUBLE, INTERLEAVE or
   MICROSTEP
*/
/**************************************************************************/
void Emakefun_StepperMotor::step(uint16_t steps, uint8_t dir,  uint8_t style) {
  uint32_t uspers = usperstep;
  uint8_t ret = 0;
  if (style == INTERLEAVE) {
    uspers /= 2;
  }
  else if (style == MICROSTEP) {
    uspers /= MICROSTEPS;
    steps *= MICROSTEPS;
#ifdef MOTORDEBUG
    Serial.print("steps = "); Serial.println(steps, DEC);
#endif
  }
  while (steps--) {
    //Serial.println("step!"); Serial.println(uspers);
    ret = onestep(dir, style);
    delayMicroseconds(uspers);
    //yield(); // required for ESP8266
  }
}

/**************************************************************************/
/*!
    @brief  Move the stepper motor one step only, with no delays
    @param  dir The direction to go, can be FORWARD or BACKWARD
    @param  style How to perform each step, can be SINGLE, DOUBLE, INTERLEAVE or
   MICROSTEP
    @returns The current step/microstep index, useful for
   Emakefun_StepperMotor.step to keep track of the current location, especially
   when microstepping
*/
/**************************************************************************/
uint8_t chang_state = 0xF;
uint8_t chang_interleave_arr[8] = {4, 1, 8, 2, 1, 4, 2, 8};

uint8_t Emakefun_StepperMotor::onestep(uint8_t dir, uint8_t style) {
  uint8_t a, b, c, d;
  uint8_t ocrb, ocra;

  ocra = ocrb = 255;

  // next determine what sort of stepping procedure we're up to
  if (style == SINGLE) {
    if ((currentstep / (MICROSTEPS / 2)) % 2) { // we're at an odd step, weird
      if (dir == FORWARD) {
        currentstep += MICROSTEPS / 2;
      }
      else {
        currentstep -= MICROSTEPS / 2;
      }
    } else {           // go to the next even step
      if (dir == FORWARD) {
        currentstep += MICROSTEPS;
      }
      else {
        currentstep -= MICROSTEPS;
      }
    }
  } else if (style == DOUBLE) {
    if (! (currentstep / (MICROSTEPS / 2) % 2)) { // we're at an even step, weird
      if (dir == FORWARD) {
        currentstep += MICROSTEPS / 2;
      } else {
        currentstep -= MICROSTEPS / 2;
      }
    } else {           // go to the next odd step
      if (dir == FORWARD) {
        currentstep += MICROSTEPS;
      } else {
        currentstep -= MICROSTEPS;
      }
    }
  } else if (style == INTERLEAVE) {
    if (dir == FORWARD) {
      currentstep += MICROSTEPS / 2;
    } else {
      currentstep -= MICROSTEPS / 2;
    }
  }
  if (style == MICROSTEP) {
    if (dir == FORWARD) {
      currentstep++;
    } else {
      // BACKWARDS
      currentstep--;
    }
    currentstep += MICROSTEPS * 4;
    currentstep %= MICROSTEPS * 4;

    ocra = ocrb = 0;
    if ( (currentstep >= 0) && (currentstep < MICROSTEPS)) {
      ocra = microstepcurve[MICROSTEPS - currentstep];
      ocrb = microstepcurve[currentstep];
    } else if  ( (currentstep >= MICROSTEPS) && (currentstep < MICROSTEPS * 2)) {
      ocra = microstepcurve[currentstep - MICROSTEPS];
      ocrb = microstepcurve[MICROSTEPS * 2 - currentstep];
    } else if  ( (currentstep >= MICROSTEPS * 2) && (currentstep < MICROSTEPS * 3)) {
      ocra = microstepcurve[MICROSTEPS * 3 - currentstep];
      ocrb = microstepcurve[currentstep - MICROSTEPS * 2];
    } else if  ( (currentstep >= MICROSTEPS * 3) && (currentstep < MICROSTEPS * 4)) {
      ocra = microstepcurve[currentstep - MICROSTEPS * 3];
      ocrb = microstepcurve[MICROSTEPS * 4 - currentstep];
    }
  }
  currentstep += MICROSTEPS * 4;
  currentstep %= MICROSTEPS * 4;
#ifdef MOTORDEBUG
  Serial.print("current step: "); Serial.println(currentstep, DEC);
  Serial.print(" pwmA = "); Serial.print(ocra, DEC);
  Serial.print(" pwmB = "); Serial.println(ocrb, DEC);
#endif

  // release all
  uint8_t latch_state = 0, stp = 0;; // all motor pins to 0
  //Serial.println(step, DEC);
  if (style == MICROSTEP) {
    if ((currentstep >= 0) && (currentstep < MICROSTEPS))
      latch_state |= 0x03;
    if ((currentstep >= MICROSTEPS) && (currentstep < MICROSTEPS * 2))
      latch_state |= 0x06;
    if ((currentstep >= MICROSTEPS * 2) && (currentstep < MICROSTEPS * 3))
      latch_state |= 0x0C;
    if ((currentstep >= MICROSTEPS * 3) && (currentstep < MICROSTEPS * 4))
      latch_state |= 0x09;
  } else {
    stp = currentstep / (MICROSTEPS / 2);
    switch (stp) {
      case 0:
        latch_state |= 0x1; // energize coil 1 only
        chang_state = 0xc;
        break;
      case 1:
        latch_state |= 0x3; // energize coil 1+2
        chang_state = 0x4;
        break;
      case 2:
        latch_state |= 0x2; // energize coil 2 only
        chang_state = 0x08;
        break;
      case 3:
        latch_state |= 0x6; // energize coil 2+3
        chang_state = 0x8;
        break;
      case 4:
        latch_state |= 0x4; // energize coil 3 only
        chang_state = 0x03;
        break;
      case 5:
        latch_state |= 0xC; // energize coil 3+4
        chang_state = 0x5;
        break;
      case 6:
        latch_state |= 0x8; // energize coil 4 only
        chang_state = 0x06;
        break;
      case 7:
        latch_state |= 0x9; // energize coil 1+4
        chang_state = 0xA;
        break;
    }
    if (style == INTERLEAVE) {
        chang_state = chang_interleave_arr[stp];
    }
  }
#ifdef MOTORDEBUG
  Serial.print("chang_state: 0x"); Serial.println(chang_state, HEX);
  Serial.print("Latch: 0x"); Serial.println(latch_state, HEX);
#endif
 F1_LOOP:
    if (chang_state&0x1) {
        if (latch_state & 0x2) {
          //Serial.println("AIN1 1");
          MC->setPWM(AIN1pin, 4096);
        } else {
          //Serial.println("AIN1 0");
          MC->setPin(AIN1pin, LOW);
        }
    }
    if (chang_state&0x2) {
        if (latch_state & 0x4) {
          //Serial.println("BIN1 1");
          MC->setPWM(BIN1pin, 4096);
        } else {
          //Serial.println("BIN1 0");
          MC->setPin(BIN1pin, LOW);
        }
    }
    if (chang_state&0x4) {
        if (latch_state & 0x8) {
          //Serial.println("AIN2 1");
          MC->setPWM(AIN2pin, 4096);
        } else {
          //Serial.println("AIN2 0");
          MC->setPin(AIN2pin, LOW);
          if (style == DOUBLE) {
            chang_state = 1;
            goto F1_LOOP;
          }
        }
    }
    if (chang_state&0x8) {
        if (latch_state & 0x1) {
          //Serial.println("BIN2 1");
          MC->setPWM(BIN2pin, 4096);
        } else {
          //Serial.println("BIN2 0");
          MC->setPin(BIN2pin, LOW);
          if (style == SINGLE) {
            chang_state = 1;
            goto F1_LOOP;
          } else if (style == DOUBLE) {
            chang_state = 2;
            goto F1_LOOP;
          }
        }
    }
    return currentstep;
}
