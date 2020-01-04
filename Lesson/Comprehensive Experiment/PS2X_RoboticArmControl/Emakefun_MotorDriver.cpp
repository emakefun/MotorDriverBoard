#if (ARDUINO >= 100)
#include "PinChangeInt.h"
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Wire.h>

#include "Emakefun_MotorDriver.h"
#include "Emakefun_MS_PWMServoDriver.h"
#if defined(ARDUINO_SAM_DUE)
#define WIRE Wire1
#else
#define WIRE Wire
#endif

#if (MICROSTEPS == 8)
uint8_t microstepcurve[] = {0, 50, 98, 142, 180, 212, 236, 250, 255};
#elif (MICROSTEPS == 16)
uint8_t microstepcurve[] = {0, 25, 50, 74, 98, 120, 141, 162, 180, 197, 212, 225, 236, 244, 250, 253, 255};
#endif

Emakefun_MotorDriver::Emakefun_MotorDriver(uint8_t addr, uint8_t version) {
  _version = version;
  _addr = addr;
  _pwm = Emakefun_MS_PWMServoDriver(_addr);
}

void Emakefun_MotorDriver::begin(uint16_t freq) {
  // init PWM w/_freq
  WIRE.begin();
  _pwm.begin();
  _freq = freq;
  _pwm.setPWMFreq(_freq);  // This is the maximum PWM frequency
  for (uint8_t i = 0; i < 16; i++)
    _pwm.setPWM(i, 0, 0);
}

void Emakefun_MotorDriver::setPWM(uint8_t pin, uint16_t value) {
  if (value > 4095) {
    _pwm.setPWM(pin, 4096, 0);
  } else
    _pwm.setPWM(pin, 0, value);
}
void Emakefun_MotorDriver::setPin(uint8_t pin, boolean value) {
  if (value == LOW)
    _pwm.setPWM(pin, 0, 0);
  else
    _pwm.setPWM(pin, 4096, 0);
}

Emakefun_DCMotor *Emakefun_MotorDriver::getMotor(uint8_t num) {
  if (num > 4) return NULL;
  num--;
  if (dcmotors[num].motornum == 0) {
    // not init'd yet!
    dcmotors[num].motornum = num;
    dcmotors[num].MC = this;
    uint8_t pwm, in1, in2;
    if (num == 0) {
      if (_version == MOTOR_DRIVER_BOARD_V3) {
        pwm = 8; in2 = 9; in1 = 10;
      } else if (_version == MOTOR_DRIVER_BOARD_V4) {
        pwm = 8; in1 = 10;
      } else if (_version == MOTOR_DRIVER_BOARD_V5) {
        in1 = 8; in2 = 10;
      }
    } else if (num == 1) {
      if (_version == MOTOR_DRIVER_BOARD_V3) {
        pwm = 13; in2 = 12; in1 = 11;
      } else if (_version == MOTOR_DRIVER_BOARD_V4) {
        pwm = 13; in1 = 11;
      } else if (_version == MOTOR_DRIVER_BOARD_V5) {
        in1 = 11; in2 = 13;
      }
    } else if (num == 2) {
      if (_version == MOTOR_DRIVER_BOARD_V3) {
        pwm = 2; in2 = 3; in1 = 4;
      } else if (_version == MOTOR_DRIVER_BOARD_V4) {
        pwm = 2; in1 = 4;
      } else if (_version == MOTOR_DRIVER_BOARD_V5) {
        in1 = 4; in2 = 2;
      }
    } else if (num == 3) {
      if (_version == MOTOR_DRIVER_BOARD_V3) {
        pwm = 7; in2 = 6; in1 = 5;
      } else if (_version == MOTOR_DRIVER_BOARD_V4) {
        pwm = 7; in1 = 5;
      } else if (_version == MOTOR_DRIVER_BOARD_V5) {
        in1 = 5; in2 = 7;
      }
    }
    dcmotors[num].PWMpin = pwm;
    dcmotors[num].IN1pin = in1;
    dcmotors[num].IN2pin = in2;
  }

  return &dcmotors[num];
}


void Emakefun_EncoderMotor::EncoderCallback1(void)
{
  (CallBack[0])();
}

void Emakefun_EncoderMotor::EncoderCallback2(void)
{
  (CallBack[1])();
}

Emakefun_EncoderMotor::Emakefun_EncoderMotor(void) {
  MC = NULL;
  encodernum = 0;
  ENCODER1pin = ENCODER2pin = 0;
  PWMpin = IN1pin = IN2pin = 0;

}

void Emakefun_EncoderMotor::init(FuncPtr encoder_fun) {
  pinMode(ENCODER1pin, INPUT);
  CallBack[encodernum] = encoder_fun;
  if (encodernum == 0) {
#if ARDUINO > 10609
    attachPinChangeInterrupt(ENCODER1pin, *(FuncPtr )(&EncoderCallback1), CHANGE);
#else
    attachPinChangeInterrupt(ENCODER1pin, *(FuncPtr )(&Emakefun_EncoderMotor::EncoderCallback1), CHANGE);
#endif
  } else if (encodernum == 1) {
#if ARDUINO > 10609
    attachPinChangeInterrupt(ENCODER1pin, *(FuncPtr )(&EncoderCallback2), CHANGE);
#else
    attachPinChangeInterrupt(ENCODER1pin, *(FuncPtr )(&Emakefun_EncoderMotor::EncoderCallback2), CHANGE);
#endif
  }
}

Emakefun_EncoderMotor *Emakefun_MotorDriver::getEncoderMotor(uint8_t num) {
  if (num > 2) return NULL;
  num--;
  if (encoder[num].encodernum == 0) {
    // not init'd yet!
    encoder[num].encodernum = num;
    encoder[num].MC = this;
    uint8_t pwm, in1, in2;
    uint8_t encoder1pin, encoder2pin;
    if (num == 0) {
      if (_version == MOTOR_DRIVER_BOARD_V3) {
        pwm = 8; in2 = 9; in1 = 10;
      } else if (_version == MOTOR_DRIVER_BOARD_V4) {
        pwm = 8; in1 = 10;
      } else if (_version == MOTOR_DRIVER_BOARD_V5) {
        in1 = 8; in2 = 10;
      }
      encoder1pin = 3; encoder2pin = 2;

    } else if (num == 1) {
      if (_version == MOTOR_DRIVER_BOARD_V3) {
        pwm = 13; in2 = 12; in1 = 11;
      } else if (_version == MOTOR_DRIVER_BOARD_V4) {
        pwm = 13; in1 = 11;
      } else if (_version == MOTOR_DRIVER_BOARD_V5) {
        in1 = 11; in2 = 13;
      }
      encoder1pin = 7; encoder2pin = 4;
    }
    // for mega2560
    /* else if (num == 2) {
       if (_version == MOTOR_DRIVER_BOARD_V3) {
         pwm = 2; in2 = 3; in1 = 4;
       } else if (_version == MOTOR_DRIVER_BOARD_V4) {
         pwm = 2; in1 = 4;
       } else if (_version == MOTOR_DRIVER_BOARD_V5) {
         in1 = 4; in2 = 2;
       }
      } else if (num == 3) {
       if (_version == MOTOR_DRIVER_BOARD_V3) {
         pwm = 7; in2 = 6; in1 = 5;
       } else if (_version == MOTOR_DRIVER_BOARD_V4) {
         pwm = 7; in1 = 5;
       } else if (_version == MOTOR_DRIVER_BOARD_V5) {
         in1 = 5; in2 = 7;
       }
      }
    */
    encoder[num].PWMpin = pwm;
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
      if (MC->_version != MOTOR_DRIVER_BOARD_V4) MC->setPin(IN2pin, LOW);
      if (MC->_version == MOTOR_DRIVER_BOARD_V5) {
        MC->setPWM(IN1pin, DcSpeed);
      } else {
        MC->setPin(IN1pin, HIGH);
      }
      break;
    case BACKWARD:
      MC->setPin(IN1pin, LOW);
      if (MC->_version == MOTOR_DRIVER_BOARD_V5) {
        MC->setPWM(IN2pin, DcSpeed);
      } else if (MC->_version == MOTOR_DRIVER_BOARD_V3) {
        MC->setPin(IN2pin, HIGH);
      }
      break;
    case BRAKE:
      if (MC->_version != MOTOR_DRIVER_BOARD_V5) {
        MC->setPWM(PWMpin, 0);
      }
      if (MC->_version != MOTOR_DRIVER_BOARD_V4) MC->setPin(IN2pin, HIGH);
      MC->setPin(IN1pin, HIGH);
      break;
    case RELEASE:
      if (MC->_version == 4) {
        MC->setPin(IN1pin, LOW);
      } else {
        MC->setPin(IN1pin, LOW);
        MC->setPin(IN2pin, LOW);
      }
      break;
  }
}

void Emakefun_EncoderMotor::setSpeed(uint8_t speed) {
  if (MC->_version == 5) {
    DcSpeed = (speed * 16);
  } else {
    MC->setPWM(PWMpin, speed * 16);
  }
}

Emakefun_StepperMotor *Emakefun_MotorDriver::getStepper(uint16_t steps, uint8_t num) {
  if (num > 2) return NULL;

  num--;

  if (steppers[num].steppernum == 0) {
    // not init'd yet!
    steppers[num].steppernum = num;
    steppers[num].revsteps = steps;
    steppers[num].MC = this;
    uint8_t pwma, pwmb, ain1, ain2, bin1, bin2;
    if (num == 0) {
      if (_version == MOTOR_DRIVER_BOARD_V3) {
        pwma = 8; ain2 = 9; ain1 = 10;
        pwmb = 13; bin2 = 12; bin1 = 11;
      } else if (_version == MOTOR_DRIVER_BOARD_V4) {
        pwma = 8;  ain1 = 10;
        pwmb = 13; bin1 = 11;
      } else if (_version == MOTOR_DRIVER_BOARD_V5) {
        ain1 = 8; ain2 = 10;
        bin1 = 13; bin2 = 11;
      }
    } else if (num == 1) {
      if (_version == MOTOR_DRIVER_BOARD_V3) {
        pwma = 2; ain2 = 3; ain1 = 4;
        pwmb = 7; bin2 = 6; bin1 = 5;
      } else if (_version == MOTOR_DRIVER_BOARD_V4) {
        pwma = 2; ain1 = 4;
        pwmb = 7; bin1 = 5;

      } else if (_version == MOTOR_DRIVER_BOARD_V5) {
        ain1 = 2; ain2 = 4;
        bin1 = 7; bin2 = 5;
      }
    }
    steppers[num].PWMApin = pwma;
    steppers[num].PWMBpin = pwmb;
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
      if (_version == MOTOR_DRIVER_BOARD_V4) {
        pwm = 3;
      } else {
        pwm = 14;
      }
    } else if (num == 3) {
      if (_version == MOTOR_DRIVER_BOARD_V4) {
        pwm = 6;
      } else {
        pwm = 15;
      }
    }
    if (_version == MOTOR_DRIVER_BOARD_V4 || _version == MOTOR_DRIVER_BOARD_V5) {
      if (num == 4) {
        pwm = 9;
      } else if (num == 5) {
        pwm = 12;
      } else if (num == 6) {
        if (_version == MOTOR_DRIVER_BOARD_V4) {
          pwm = 14;
        } else if (_version == MOTOR_DRIVER_BOARD_V5) {
          pwm = 3;
        }
      } else if (num == 7) {
        if (_version == MOTOR_DRIVER_BOARD_V4) {
          pwm = 15;
        } else if (_version == MOTOR_DRIVER_BOARD_V5) {
          pwm = 6;
        }
      }
      servos[num].PWMpin = pwm;
    }
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

/******************************************
               MOTORS
******************************************/

Emakefun_DCMotor::Emakefun_DCMotor(void) {
  MC = NULL;
  motornum = 0;
  PWMpin = IN1pin = IN2pin = 0;
}

void Emakefun_DCMotor::run(uint8_t cmd) {
#ifdef MOTORDEBUG
#endif
  switch (cmd) {
    case FORWARD:
      if (MC->_version != MOTOR_DRIVER_BOARD_V4) MC->setPin(IN2pin, LOW);
      if (MC->_version == MOTOR_DRIVER_BOARD_V5) {
        MC->setPWM(IN1pin, DcSpeed);
      } else {
        MC->setPin(IN1pin, HIGH);
      }
      break;
    case BACKWARD:
      MC->setPin(IN1pin, LOW);
      if (MC->_version == MOTOR_DRIVER_BOARD_V5) {
        MC->setPWM(IN2pin, DcSpeed);
      }  else if(MC->_version == MOTOR_DRIVER_BOARD_V3) {
        MC->setPin(IN2pin, HIGH);
      }
      break;
    case BRAKE:
      if (MC->_version != MOTOR_DRIVER_BOARD_V5) {
        MC->setPWM(PWMpin, 0);
      }
      if (MC->_version != MOTOR_DRIVER_BOARD_V4) MC->setPin(IN2pin, HIGH);
      MC->setPin(IN1pin, HIGH);
      break;
    case RELEASE:
      if (MC->_version == 4) {
        MC->setPin(IN1pin, LOW);
      } else {
        MC->setPin(IN1pin, LOW);
        MC->setPin(IN2pin, LOW);
      }
      break;
  }
}

void Emakefun_DCMotor::setSpeed(uint8_t speed) {
  if (MC->_version == 5) {
    DcSpeed = (speed * 16);
  } else {
    MC->setPWM(PWMpin, speed * 16);
  }
}

/******************************************
               STEPPERS
******************************************/
Emakefun_StepperMotor::Emakefun_StepperMotor(void) {
  revsteps = steppernum = currentstep = 0;
}
void Emakefun_StepperMotor::setSpeed(uint16_t rpm) {
  //Serial.println("steps per rev: "); Serial.println(revsteps);
  //Serial.println("RPM: "); Serial.println(rpm);
  usperstep = 60000000 / ((uint32_t)revsteps * (uint32_t)rpm);
}

void Emakefun_StepperMotor::release(void) {

  MC->setPin(AIN1pin, LOW);
  MC->setPin(BIN1pin, LOW);
  if (MC->_version != 4) {
    MC->setPin(AIN2pin, LOW);
    MC->setPin(BIN2pin, LOW);
  }
  if (MC->_version != 5) {
    MC->setPWM(PWMApin, 0);
    MC->setPWM(PWMBpin, 0);
  }
}

void Emakefun_StepperMotor::step(uint16_t steps, uint8_t dir,  uint8_t style) {
  uint32_t uspers = usperstep;
  uint8_t ret = 0;
  if (MC->_version == 4) style = DOUBLE;
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
  if (MC->_version != 5) {
    MC->setPWM(PWMApin, ocra * 16);
    MC->setPWM(PWMBpin, ocrb * 16);
  }
  // release all
  uint8_t latch_state = 0; // all motor pins to 0
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
    switch (currentstep / (MICROSTEPS / 2)) {
      case 0:
        latch_state |= 0x1; // energize coil 1 only
        break;
      case 1:
        latch_state |= 0x3; // energize coil 1+2
        break;
      case 2:
        latch_state |= 0x2; // energize coil 2 only
        break;
      case 3:
        latch_state |= 0x6; // energize coil 2+3
        break;
      case 4:
        latch_state |= 0x4; // energize coil 3 only
        break;
      case 5:
        latch_state |= 0xC; // energize coil 3+4
        break;
      case 6:
        latch_state |= 0x8; // energize coil 4 only
        break;
      case 7:
        latch_state |= 0x9; // energize coil 1+4
        break;
    }
  }
#ifdef MOTORDEBUG
  Serial.print("Latch: 0x"); Serial.println(latch_state, HEX);
#endif
  if (MC->_version == 3) {
    if (latch_state & 0x1) {
      MC->setPin(AIN2pin, HIGH);
    } else {
      MC->setPin(AIN2pin, LOW);
    }
    if (latch_state & 0x2) {
      MC->setPin(BIN1pin, HIGH);
    } else {
      MC->setPin(BIN1pin, LOW);
    }
    if (latch_state & 0x4) {
      MC->setPin(AIN1pin, HIGH);
    } else {
      MC->setPin(AIN1pin, LOW);
    }
    if (latch_state & 0x8) {
      MC->setPin(BIN2pin, HIGH);
    } else {
      MC->setPin(BIN2pin, LOW);
    }
  } else if (MC->_version == 4) {
    if (latch_state & 0x1) {
      MC->setPin(AIN1pin, HIGH);
    }
    if (latch_state & 0x2) {
      MC->setPin(BIN1pin, HIGH);
    }
    if (latch_state & 0x4) {
      MC->setPin(AIN1pin, LOW);
    }
    if (latch_state & 0x8) {
      MC->setPin(BIN1pin, LOW);
    }
  } else if (MC->_version == 5) {
    if (latch_state & 0x1) {
      MC->setPin(AIN2pin, LOW);
    } else {
      MC->setPWM(AIN2pin, ocra * 16);
    }
    if (latch_state & 0x2) {
      MC->setPin(BIN1pin, LOW);
    } else {
      MC->setPWM(BIN1pin, ocrb * 16);
    }
    if (latch_state & 0x4) {
      MC->setPin(AIN1pin, LOW);
    } else {
      MC->setPWM(AIN1pin, ocra * 16);
    }
    if (latch_state & 0x8) {
      MC->setPin(BIN2pin, LOW);
    } else {
      MC->setPWM(BIN2pin, ocrb * 16);
    }
  }
  return currentstep;
}

/******************************************
               SENSOR
******************************************/

Emakefun_Sensor::Emakefun_Sensor(void) {
  MC = NULL;
  mIrRecv = NULL;
  mPs2x = NULL;
  mBuzzer = NULL;
  mRgb = NULL;
  mNrf24L01 = NULL;
  IrPin = BuzzerPin = RgbPin = EchoPin = TrigPin = 0;
  Ps2xClkPin = Ps2xCmdPin = Ps2xAttPin = Ps2xDatPin = 0;
  P1 = P2 = P3 = P4 = P5 = 0;
}

void Emakefun_Sensor::SetRgbColor(E_RGB_INDEX index , long Color)
{
  if (index == E_RGB_ALL) {
    mRgb->setColor(0, Color);
  } else {
    mRgb->setColor(index, Color);
  }
  mRgb->show();
}

void Emakefun_Sensor::Sing(byte songName)
{
  switch (songName) {
    case S_connection:
      mBuzzer->_tone(note_E5, 50, 30);
      mBuzzer->_tone(note_E6, 55, 25);
      mBuzzer->_tone(note_A6, 60, 10);
      //  _tone(9, 394);
      break;

    case S_disconnection:
      mBuzzer->_tone(note_E5, 50, 30);
      mBuzzer->_tone(note_A6, 55, 25);
      mBuzzer->_tone(note_E6, 50, 10);
      break;

    case S_buttonPushed:
      mBuzzer->bendTones (note_E6, note_G6, 1.03, 20, 2);
      delay(30);
      mBuzzer->bendTones (note_E6, note_D7, 1.04, 10, 2);
      break;

    case S_mode1:
      mBuzzer->bendTones (note_E6, note_A6, 1.02, 30, 10);  //1318.51 to 1760
      break;

    case S_mode2:
      mBuzzer->bendTones (note_G6, note_D7, 1.03, 30, 10);  //1567.98 to 2349.32
      break;

    case S_mode3:
      mBuzzer->_tone(note_E6, 50, 100); //D6
      mBuzzer->_tone(note_G6, 50, 80); //E6
      mBuzzer->_tone(note_D7, 300, 0); //G6
      break;

    case S_surprise:
      mBuzzer->bendTones(800, 2150, 1.02, 10, 1);
      mBuzzer->bendTones(2149, 800, 1.03, 7, 1);
      break;

    case S_OhOoh:
      mBuzzer->bendTones(880, 2000, 1.04, 8, 3); //A5 = 880
      delay(200);

      for (int i = 880; i < 2000; i = i * 1.04) {
        mBuzzer->_tone(note_B5, 5, 10);
      }
      break;

    case S_OhOoh2:
      mBuzzer->bendTones(1880, 3000, 1.03, 8, 3);
      delay(200);

      for (int i = 1880; i < 3000; i = i * 1.03) {
        mBuzzer->_tone(note_C6, 10, 10);
      }
      break;

    case S_cuddly:
      mBuzzer->bendTones(700, 900, 1.03, 16, 4);
      mBuzzer->bendTones(899, 650, 1.01, 18, 7);
      break;

    case S_sleeping:
      mBuzzer->bendTones(100, 500, 1.04, 10, 10);
      delay(500);
      mBuzzer->bendTones(400, 100, 1.04, 10, 1);
      break;

    case S_happy:
      mBuzzer->bendTones(1500, 2500, 1.05, 20, 8);
      mBuzzer->bendTones(2499, 1500, 1.05, 25, 8);
      break;

    case S_superHappy:
      mBuzzer->bendTones(2000, 6000, 1.05, 8, 3);
      delay(50);
      mBuzzer->bendTones(5999, 2000, 1.05, 13, 2);
      break;

    case S_happy_short:
      mBuzzer->bendTones(1500, 2000, 1.05, 15, 8);
      delay(100);
      mBuzzer->bendTones(1900, 2500, 1.05, 10, 8);
      break;

    case S_sad:
      mBuzzer->bendTones(880, 669, 1.02, 20, 200);
      break;

    case S_confused:
      mBuzzer->bendTones(1000, 1700, 1.03, 8, 2);
      mBuzzer->bendTones(1699, 500, 1.04, 8, 3);
      mBuzzer->bendTones(1000, 1700, 1.05, 9, 10);
      break;

    case S_fart1:
      mBuzzer->bendTones(1600, 3000, 1.02, 2, 15);
      break;

    case S_fart2:
      mBuzzer->bendTones(2000, 6000, 1.02, 2, 20);
      break;

    case S_fart3:
      mBuzzer->bendTones(1600, 4000, 1.02, 2, 20);
      mBuzzer->bendTones(4000, 3000, 1.02, 2, 20);
      break;

    case S_didi:
      mBuzzer->_tone(note_C7, 50, 100);
      delay(110);
      mBuzzer->_tone(note_C6, 50, 100);
      break;
  }

}

uint16_t Emakefun_Sensor::GetUltrasonicDistance(void)
{
  uint16_t FrontDistance;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  FrontDistance = pulseIn(EchoPin, HIGH) / 58.00;
  return FrontDistance;
}

/*
  Nrf24l Emakefun_MotorDriver::GetNrf24L01() {
    Serial.println("E_NRF24L01 in");
    if (sensors.mNrf24L01 == NULL) {
      sensors.mNrf24L01 = new Nrf24l(NRF24L01_CE, NRF24L01_CSN);
      sensors.mNrf24L01->spi = &MirfHardwareSpi;
      sensors.mNrf24L01->init();
      sensors.mNrf24L01->setRADDR((byte *)"MotorDriver");
      sensors.mNrf24L01->payload = 1;
      sensors.mNrf24L01->channel = 90;             //Set the used channel
      sensors.mNrf24L01->config();
    }
    Serial.println("Got E_NRF24L01");
    return sensors.mNrf24L01;

  } */


int Emakefun_Sensor::GetNrf24L01(char *RxaddrName) {
  mNrf24L01->setRADDR((byte *)RxaddrName);
  delay(10);
  if (mNrf24L01->dataReady()) {
    mNrf24L01->getData((byte *) &GetNrfData);
    return GetNrfData;
  } else {
    return NULL;
  }
}

void Emakefun_Sensor::sendNrf24l01(char *TxaddrName, int SendNrfData) {
  mNrf24L01->setTADDR((byte *)TxaddrName);
  mNrf24L01->send((byte *)&SendNrfData);
  while (mNrf24L01->isSending()) delay(1);        //Until you send successfully, exit the loop
#ifdef MOTORDEBUG
  Serial.print("Send success:");
  Serial.println(SendNrfData);
#endif
  delay(1000);
}

void *Emakefun_MotorDriver::getSensor(E_SENSOR_INDEX n)
{
  //Serial.print("E_SENSOR_INDEX is ");
  //Serial.println(n);
  if (n == E_RGB) {
    if (sensors.mRgb == NULL) {
      sensors.RgbPin = RGB_PIN;
      pinMode(RGB_PIN, OUTPUT);
      sensors.mRgb = new RGBLed(RGB_PIN, 2);
    }
    return sensors.mRgb;
  }
  if (n == E_IR) {
    if (sensors.mIrRecv == NULL) {
      sensors.IrPin = IR_PIN;
      pinMode(IR_PIN, INPUT);
      sensors.mIrRecv = new IRremote (IR_PIN);
      sensors.mIrRecv->begin();  // Initialize the infrared receiver
    }
    return sensors.mIrRecv;
  }
  if (n == E_BUZZER) {
    if (sensors.mBuzzer == NULL) {
      sensors.BuzzerPin = BUZZER_PIN;
      if (_version == 3) sensors.BuzzerPin = 9;
      sensors.mBuzzer = new Buzzer(sensors.BuzzerPin);
    }
    return sensors.mBuzzer;
  }
  if (n == E_PS2X) {
    // Serial.println("E_PS2X in");
    int error = 0;
    if (sensors.mPs2x == NULL) {
      sensors.mPs2x = new PS2X();
      sensors.Ps2xClkPin = PS2_CLK;
      sensors.Ps2xCmdPin = PS2_CMD;
      sensors.Ps2xAttPin = PS2_SEL;
      sensors.Ps2xDatPin = PS2_DAT;
      error = sensors.mPs2x->config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
      if (error == 0) {
        Serial.println("Found Controller, configured successful");
      } else {
        Serial.println("Connect Faile");
      }
    }
    return sensors.mPs2x;
  }
  if (n == E_NRF24L01) {

    if (sensors.mNrf24L01 == NULL) {
     
      sensors.mNrf24L01 = new Nrf24l(NRF24L01_CE, NRF24L01_CSN);
      sensors.mNrf24L01->init();
      sensors.mNrf24L01->setRADDR((byte *)"MotorDriver");
      sensors.mNrf24L01->payload = 12;
      sensors.mNrf24L01->channel = 90;             //Set the used channel
      sensors.mNrf24L01->config();
    }
    // Serial.println("Got E_NRF24L01");
    return sensors.mNrf24L01;
  }
  if (n == E_ULTRASONIC) {
    // Serial.println("E_ULTRASONIC");
    sensors.EchoPin = ECHO_PIN;
    sensors.TrigPin = TRIG_PIN;
    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);
    return NULL;
  }
  sensors.MC = this;
  return &sensors;
}

/*
  Emakefun_Sensor *Emakefun_MotorDriver::getSensor()
  {
    sensors.MC = this;
    return &sensors;
  } */
