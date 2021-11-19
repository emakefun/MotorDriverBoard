#include "Emakefun_MotorDriver.h"
#include "PS2X_lib.h"  //for v1.6
#include "MsTimer2.h"

#define M1 1
#define M2 2
#define M3 3
#define M4 4

#define PS2_DAT     12
#define PS2_CMD     11
#define PS2_SEL     10
#define PS2_CLK     13

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x; // create PS2 Controller Class
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver(0x60);
Emakefun_DCMotor *LeftFoward, *RightFoward, *LeftBackward, *RightBackward;
Emakefun_Servo *mServo1, *mServo2, *mServo3, *mServo4, *mServo5, *mServo6;

int Speed ;

float LY, LX, RY, RX, LeftAngle, RightAngle;
uint8_t ServoBaseDegree;
byte ServoPin;
byte UpServo = 90;
byte DownServo = 90;
byte LeftServo = 140;
byte RightServo = 90;

void moto_init(int leftward, int rightfoward, int leftbackward, int rightbackward)
{
    
    LeftFoward = mMotorDriver.getMotor(leftward);
    RightFoward = mMotorDriver.getMotor(rightfoward);
    LeftBackward = mMotorDriver.getMotor(leftbackward);
    RightBackward = mMotorDriver.getMotor(rightbackward);
}

void SetSpeed(int8_t s)
{
    if (s > 100) {
        Speed = 100;
        return;
    } else if (s < 0) {
        Speed = 0;
        return;
    }
    Speed = s;
}

int GetSpeed(void)
{
    return Speed;
}

void SpeedUp(int8_t Duration)
{
    SetSpeed(Speed + Duration);
}

void SpeedDown(int8_t Duration )
{
    SetSpeed(Speed - Duration);
}

void DriveSpeed(int s)
{
  if (s >= 0 && s <= 100) {
    LeftFoward->setSpeed((s / 10) * 25.5);
    RightFoward->setSpeed((s / 10) * 25.5);
    LeftBackward->setSpeed((s / 10) * 25.5);
    RightBackward->setSpeed((s / 10) * 25.5);
  }
}

void GoForward(void)
{
  DriveSpeed(Speed);
  LeftFoward->run(FORWARD);
  RightFoward->run(FORWARD);
  LeftBackward->run(FORWARD);
  RightBackward->run(FORWARD);
}

void GoBack(void)
{
  DriveSpeed(Speed);
  LeftFoward->run(BACKWARD);
  RightFoward->run(BACKWARD);
  LeftBackward->run(BACKWARD);
  RightBackward->run(BACKWARD);
}
void KeepStop(void)
{
  DriveSpeed(0);
  LeftFoward->run(BRAKE);
  RightFoward->run(BRAKE);
  LeftBackward->run(BRAKE);
  RightBackward->run(BRAKE);
}

void TurnLeft(void)
{
  int s;
  s = (Speed / 10) * 25.5;
  LeftFoward->setSpeed(s/2);
  LeftBackward->setSpeed(s/2);
  RightFoward->setSpeed(s);
  RightBackward->setSpeed(s);
  LeftFoward->run(FORWARD);
  RightFoward->run(FORWARD);
  LeftBackward->run(FORWARD);
  RightBackward->run(FORWARD);
}

void TurnRight(void)
{
    int s;
    s = (Speed / 10) * 25.5;
    LeftFoward->setSpeed(s);
    LeftBackward->setSpeed(s);
    RightFoward->setSpeed(s/2);
    RightBackward->setSpeed(s/2);
    LeftFoward->run(FORWARD);
    RightFoward->run(FORWARD);
    LeftBackward->run(FORWARD);
    RightBackward->run(FORWARD);
}

void TurnLeftRotate(void)
{
    DriveSpeed(Speed);
    LeftFoward->run(BACKWARD);
    LeftBackward->run(BACKWARD);
    RightFoward->run(FORWARD);
    RightBackward->run(FORWARD);
}

void TurnRightRotate(void)
{
    DriveSpeed(Speed);
    LeftFoward->run(FORWARD);
    LeftBackward->run(FORWARD);
    RightFoward->run(BACKWARD);
    RightBackward->run(BACKWARD);
}

void InitServo(void)
{
    mServo1 = mMotorDriver.getServo(1);
    mServo2 = mMotorDriver.getServo(2);
    mServo3 = mMotorDriver.getServo(3);
    mServo4 = mMotorDriver.getServo(4);
    mServo5 = mMotorDriver.getServo(5);
    mServo6 = mMotorDriver.getServo(6);
}

void SetServoBaseDegree(uint8_t base)
{
  ServoBaseDegree = base;
}

void SetServoDegree(byte pin , byte Angle)
{
  int Degree = Angle;
  int servo_degree;
  ServoPin = pin;
  if (Degree > 360) {
    return;
  }
  if (Degree == 90 || Degree == 270) {
    servo_degree = ServoBaseDegree;
  } else if (Degree >= 0 && Degree <= 180) {
    servo_degree = ServoBaseDegree - 90 + Degree;   // 180-degree-diff
  }
  if (ServoPin == 1)
    mServo1->writeServo(servo_degree);
  else if (ServoPin == 2)
    mServo2->writeServo(Angle);
  else if (ServoPin == 3)
    mServo3->writeServo(Angle);
  else if (ServoPin == 4)
    mServo4->writeServo(Angle);
  else if (ServoPin == 5)
    mServo5->writeServo(Angle);
  else if (ServoPin == 6)
    mServo6->writeServo(Angle);
}

uint16_t LeftHart(void)
{
  LY = float((ps2x.Analog(PSS_LY)) - 127) / 127;
  LX = float((ps2x.Analog(PSS_LX)) - 127) / 127;
  if ((-0.1 <= LX) && (LX <= 0.1) && (-0.1 <= LY) && (LY <= 0.1)) {
    return 0xFFF;
  } else {
    if ((LX > 0) && (LY > 0)) {
      LeftAngle = 360 - (atan(LY / LX) * 58);
    } else if ((LX < 0) && (LY > 0)) {
      LeftAngle = 180 + (abs(atan(LY / LX) * 58));
    } else if ((LX < 0) && (LY < 0)) {
      LeftAngle = 180 - (abs(atan(LY / LX) * 58)) ;
    } else if ((LX > 0) && (LY < 0)) {
      LeftAngle = abs(atan(LY / LX) * 58);
    }
    return LeftAngle;
  }
}
uint16_t RightHart(void)
{
  RY = float((ps2x.Analog(PSS_RY)) - 127) / 127;
  RX = float((ps2x.Analog(PSS_RX)) - 127) / 127;
  if ((-0.1 <= RX) && (RX <= 0.1) && (-0.1 <= RY) && (RY <= 0.1)) {
    return 0xFFF;
  } else {
    if ((RX > 0) && (RY > 0)) {
      RightAngle = 360 - (atan(RY / RX) * 58);
    } else if ((RX < 0) && (RY > 0)) {
      RightAngle = 180 + (abs(atan(RY / RX) * 58));
    } else if ((RX < 0) && (RY < 0)) {
      RightAngle = 180 - (abs(atan(RY / RX) * 58)) ;
    } else if ((RX > 0) && (RY < 0)) {
      RightAngle = abs(atan(RY / RX) * 58);
    }
    return RightAngle;
  }
}

void Ps2Scan(void)
{
  static char count = 0;
  if (count++ > 20)
  {
    ps2x.reconfig_gamepad();
    count = 0;
  }
  ps2x.read_gamepad();
}

void setup()
{
  Serial.begin(9600);
  mMotorDriver.begin(50);
  InitServo();
  moto_init(M2, M1, M4, M3);
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  SetServoBaseDegree(90);
  SetServoDegree(1, 90);
  MsTimer2::set(50, Ps2Scan);
  MsTimer2::start();
}

void HandlePS2(void)
{
  int Ps2xRightAngle, Ps2xLeftAngle;
  //ps2x.read_gamepad(false, 0);
  if (ps2x.ButtonDataByte()) {
    if (ps2x.Button(PSB_TRIANGLE)) {
      Serial.print("PS2X PSB_TRIANGLE:");
      SpeedUp(5);
      Serial.println(GetSpeed());
      return;
    }
    if (ps2x.Button(PSB_CROSS)) {
      Serial.print("PS2X PSB_CROSS:");
      SpeedDown(5);
      Serial.println(GetSpeed());
      return;
    }
    if (ps2x.Button(PSB_PAD_UP)) {
      Serial.println("PS2X PSB_PAD_UP:");
      GoForward();
    }
    if (ps2x.Button(PSB_PAD_DOWN)) {
      Serial.println("PS2X PSB_PAD_DOWN:");
      GoBack();
    }
    if (ps2x.Button(PSB_PAD_LEFT)) {
      Serial.println("PS2X PSB_PAD_LEFT:");
      TurnLeft();
    }
    if (ps2x.Button(PSB_PAD_RIGHT)) {
      Serial.println("PS2X PSB_PAD_RIGHT:");
      TurnRight();
    }
    if (ps2x.Button(PSB_SQUARE)) {
      Serial.println("PS2X PSB_SQUARE:");
      TurnLeftRotate();
    }
    if (ps2x.Button(PSB_CIRCLE)) {
      Serial.println("PS2X PSB_CIRCLE:");
      TurnRightRotate();
    }
    if (ps2x.Button(PSB_L1)) {
      if (UpServo < 140)
        UpServo += 4;
    }
    if (ps2x.Button(PSB_R1)) {
      if (UpServo > 47)
        UpServo -= 4;
    }
  } else {
    KeepStop();
    Ps2xRightAngle = RightHart();
    Ps2xLeftAngle = LeftHart();
    if ((Ps2xRightAngle != 0xFFF) || (Ps2xLeftAngle != 0xFFF)) {
      if ((90 < Ps2xLeftAngle) && (Ps2xLeftAngle <= 270))
      {
        if (DownServo < 180) {
          DownServo += 2;
        }
      } else if ((270 < Ps2xLeftAngle) && (Ps2xLeftAngle <= 360) || (0 <= Ps2xLeftAngle) && (Ps2xLeftAngle <= 90)) {
        if (DownServo != 0) {
          DownServo -= 2;
        }
      }
      if ((45 <= Ps2xRightAngle) && (Ps2xRightAngle < 135)) {
        if ((RightServo < 175)) {
          RightServo += 2;
        }
      } else if ((225 <= Ps2xRightAngle) && (Ps2xRightAngle < 315)) {
        if (((RightServo != 0) && (100 < LeftServo)) && (RightServo > 70)) {
          RightServo -= 2;
        }
      }  else if ((135 <= Ps2xRightAngle) && (Ps2xRightAngle < 225)) {
        if (LeftServo < 160) {
          LeftServo += 2;
        }
      } else if ((315 <= Ps2xRightAngle) && (Ps2xRightAngle <= 360) || (0 <= Ps2xRightAngle) && (Ps2xRightAngle < 45)) {
        if (LeftServo >= 92) {
          LeftServo -= 2;
        }
      }
      SetServoDegree(1, DownServo);
      SetServoDegree(2, LeftServo);
      SetServoDegree(3, RightServo);
    }
  }
  SetServoDegree(4, UpServo);
  delay(50);
}

void loop()
{
  HandlePS2();
}
