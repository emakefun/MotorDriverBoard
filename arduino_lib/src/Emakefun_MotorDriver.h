
/******************************************************************
 This is the library for the Emakefun Motor Shield V2 for Arduino.
 It supports DC motors & Stepper motors with microstepping as well
 as stacking-support. It is *not* compatible with the V1 library!

 It will only work with https://www.Emakefun.com/products/1483

 Emakefun invests time and resources providing this open
 source code, please support Emakefun and open-source hardware
 by purchasing products from Emakefun!

 Written by Limor Fried/Ladyada for Emakefun Industries.
 BSD license, check license.txt for more information.
 All text above must be included in any redistribution.
 ******************************************************************/

#ifndef _Emakefun_MotorDriver_h_
#define _Emakefun_MotorDriver_h_

#include "Emakefun_MS_PWMServoDriver.h"
#include <Wire.h>
#include <inttypes.h>

//#define MOTORDEBUG
#define MOTOR_DRIVER_V5_2

#define MICROSTEPS 8 // 8 or 16

#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4
#define MOTOR4_A 0
#define MOTOR4_B 6
#define MOTOR3_A 5
#define MOTOR3_B 7

#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

#define SINGLE 1
#define DOUBLE 2
#define INTERLEAVE 3
#define MICROSTEP 4

#define S1 0
#define S2 1
#define S3 14
#define S4 15
#define S5 9
#define S6 12
#define S7 3
#define S8 6

#define M1 1
#define M2 2
#define M3 3
#define M4 4

#define E1 1
#define E2 2
#define E3 3
#define E4 4

#define STEPPER1 1
#define STEPPER2 2

class Emakefun_MotorDriver;
/** Object that controls and keeps state for a Servo */
class Emakefun_Servo
{
public:
  Emakefun_Servo(void);
  friend class Emakefun_MotorDriver;
  void setServoPulse(double pulse);
  void writeServo(uint8_t angle);
  void writeServo(uint8_t angle, uint8_t speed);
  uint8_t readDegrees();
private:
  uint8_t PWMpin;
  uint16_t PWMfreq;
  Emakefun_MotorDriver *MC;
  uint8_t servonum, currentAngle;
};


/** Object that controls and keeps state for a single DC motor */
class Emakefun_DCMotor {
public:
  Emakefun_DCMotor(void);
  friend class Emakefun_MotorDriver; ///< Let MotorShield create DCMotors
  void run(uint8_t);
  void setSpeed(uint8_t);

private:
  uint8_t IN1pin, IN2pin;
  Emakefun_MotorDriver *MC;
 // int DcSpeed;
  uint8_t motornum;
};

/** Object that controls and keeps state for a single stepper motor */
class Emakefun_StepperMotor {
public:
  Emakefun_StepperMotor(void);
  void setSpeed(uint16_t);

  void step(uint16_t steps, uint8_t dir, uint8_t style = SINGLE);
  uint8_t onestep(uint8_t dir, uint8_t style);
  void release(void);

  friend class Emakefun_MotorDriver; ///< Let MotorShield create StepperMotors

private:
  uint32_t usperstep;

  uint8_t AIN1pin, AIN2pin;
  uint8_t BIN1pin, BIN2pin;
  uint16_t revsteps; // # steps per revolution
  uint8_t currentstep;
  Emakefun_MotorDriver *MC;
  uint8_t steppernum;
};

typedef void (*FuncPtr)(void);

class Emakefun_EncoderMotor {
 public:
  Emakefun_EncoderMotor(void);
  friend class Emakefun_MotorDriver;
  void run(uint8_t);
  void run(uint8_t cmd, uint8_t speed, int pluse);
  void setSpeed(uint8_t);
  //void release(void);
  void init(FuncPtr encoder_fun);
  FuncPtr EncoderCallback;
// private:
  uint8_t IN1pin, IN2pin;
  uint8_t ENCODER1pin, ENCODER2pin;
  volatile int EncoderPulse;
private:
  Emakefun_MotorDriver *MC;
  uint8_t encodernum;
};

/** Object that controls and keeps state for the whole motor shield.
    Use it to create DC and Stepper motor objects! */
class Emakefun_MotorDriver {
public:
  Emakefun_MotorDriver(uint8_t addr = 0x60);

  void begin(uint16_t freq = 1600, TwoWire *theWire = NULL);
  Emakefun_DCMotor *getMotor(uint8_t n);
  Emakefun_StepperMotor *getStepper(uint8_t num, uint16_t steps);
  Emakefun_EncoderMotor *getEncoderMotor(uint8_t num);
  Emakefun_Servo *getServo(uint8_t num);
  friend class Emakefun_DCMotor;  //< Let DCMotors control the Shield
  friend class Emakefun_EncoderMotor;
  
  void setPWM(uint8_t pin, uint16_t val);
  void setPin(uint8_t pin, boolean val);
  int DcSpeed;

private:
  TwoWire *_i2c;
  uint8_t _addr;
  uint16_t _freq;

  Emakefun_Servo servos[8];
  Emakefun_DCMotor dcmotors[4];
  Emakefun_StepperMotor steppers[2];
  Emakefun_EncoderMotor encoder[4];
  Emakefun_MS_PWMServoDriver _pwm;
};

#endif
