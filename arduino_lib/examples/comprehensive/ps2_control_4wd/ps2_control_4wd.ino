#include "Emakefun_MotorDriver.h"
#include "PS2X_lib.h"  //for v1.6
#include "MsTimer2.h"

#define PS2_DAT     12
#define PS2_CMD     11
#define PS2_SEL     10
#define PS2_CLK     13

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x; // create PS2 Controller Class
Emakefun_MotorDriver mMotor = Emakefun_MotorDriver(0x60);
Emakefun_DCMotor *LeftFoward, *RightFoward, *LeftBackward, *RightBackward;

int Speed;

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

void MotorInit(int leftward, int rightfoward, int leftbackward, int rightbackward)
{
    LeftFoward = mMotor.getMotor(leftward);
    RightFoward = mMotor.getMotor(rightfoward);
    LeftBackward = mMotor.getMotor(leftbackward);
    RightBackward = mMotor.getMotor(rightbackward);
    delay(200);
    mMotor.begin(50);
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
  LeftBackward->run(BACKWARD);
  RightBackward->run(BACKWARD);
}

void GoBack(void)
{
  DriveSpeed(Speed);
  LeftFoward->run(BACKWARD);
  RightFoward->run(BACKWARD);
  LeftBackward->run(FORWARD);
  RightBackward->run(FORWARD);
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

void setup()
{
  Serial.begin(9600);
  MotorInit(M2, M1, M4, M3);
  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
    pinMode(A0, OUTPUT);
  tone(A0,131);
  delay(200);
    noTone(A0);
//  MsTimer2::set(50, Ps2Scan);
//  MsTimer2::start();
}

void loop()
{
  ps2x.read_gamepad(false, 0);
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
  } else {
    KeepStop();
  }
}
