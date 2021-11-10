#include "Emakefun_MotorDriver.h"
#include "ProtocolParser.h"
#include "BluetoothHandle.h"

#define M1 1
#define M2 2
#define M3 3
#define M4 4

ProtocolParser *mProtocol = new ProtocolParser();
Emakefun_MotorDriver mMotor = Emakefun_MotorDriver(0x60);
Emakefun_DCMotor *LeftFoward, *RightFoward, *LeftBackward, *RightBackward;

int Speed;

void moto_init(int leftward, int rightfoward, int leftbackward, int rightbackward)
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

void Drive(int degree)
{
  byte value = (Speed / 10) * 25.5;   //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
  float f;
  if (degree >= 0 && degree <= 90) {
    f = (float)(degree) / 90;
    LeftFoward->setSpeed(value);
    RightFoward->setSpeed((float)(value * f));
    LeftBackward->setSpeed(value);
    RightBackward->setSpeed((float)(value * f));
    LeftFoward->run(FORWARD);
    RightFoward->run(FORWARD);
    LeftBackward->run(FORWARD);
    RightBackward->run(FORWARD);
  } else if (degree > 90 && degree <= 180) {
    f = (float)(180 - degree) / 90;
    LeftFoward->setSpeed((float)(value * f));
    RightFoward->setSpeed(value);
    LeftBackward->setSpeed((float)(value * f));
    RightBackward->setSpeed(value);
    LeftFoward->run(FORWARD);
    RightFoward->run(FORWARD);
    LeftBackward->run(FORWARD);
    RightBackward->run(FORWARD);
  } else if (degree > 180 && degree <= 270) {
    f = (float)(degree - 180) / 90;
    LeftFoward->setSpeed((float)(value * f));
    RightFoward->setSpeed(value);
    LeftBackward->setSpeed((float)(value * f));
    RightBackward->setSpeed(value);
    LeftFoward->run(BACKWARD);
    RightFoward->run(BACKWARD);
    LeftBackward->run(BACKWARD);
    RightBackward->run(BACKWARD);
  } else if (degree > 270 && degree <= 360) {
    f = (float)(360 - degree) / 90;
    LeftFoward->setSpeed(value);
    RightFoward->setSpeed((float)(value * f));
    LeftBackward->setSpeed(value);
    RightBackward->setSpeed((float)(value * f));
    LeftFoward->run(BACKWARD);
    RightFoward->run(BACKWARD);
    LeftBackward->run(BACKWARD);
    RightBackward->run(BACKWARD);
  }
  else {
    KeepStop();
    return;
  }
}

void HandleBluetoothRemote(bool recv_flag)
{
  if (recv_flag) {
    switch (mProtocol->GetRobotControlFun()) {
     case E_BUTTON:
        switch (mProtocol->GetBluetoothButton())
        {
          case BT_PAD_UP:
            GoForward();
            break;
          case BT_PAD_DOWN:
            GoBack();
            break;
          case BT_PAD_LEFT:
            Drive(160);
            break;
          case BT_PAD_RIGHT:
            Drive(20);
            break;
          case BT_PINK:
            TurnLeft();
            break;
          case BT_RED:
            TurnRight();
            break;
          case BT_GREEN:
            SpeedUp(10);
            break;
          case BT_BLUE:
            SpeedDown(10);
            break;
          case BT_L1:
            SpeedUp(10);
            break;
          case BT_R1:
            SpeedDown(10);
            break;
        }
        break;
      case E_ROBOT_CONTROL_DIRECTION:
        Drive(mProtocol->GetRobotDegree());
        break;
      case E_ROBOT_CONTROL_SPEED:
        SetSpeed(mProtocol->GetRobotSpeed());
        break ;
      default:
        break;
    }
  }
}

void setup()
{
  Serial.begin(9600);
  moto_init(M2, M1, M4, M3);
  SetSpeed(100);
}

void loop()
{
  static byte mode;
  static bool recv_flag;
  mProtocol->RecevData();
      
  if (recv_flag = mProtocol->ParserPackage()) {
    if (mProtocol->GetRobotControlFun() == E_CONTROL_MODE) {
      Serial.print("GetControlMode: ");
      Serial.println(mProtocol->GetControlMode());
      return;
    }
  }
  switch (mProtocol->GetControlMode()) {
    case E_BLUETOOTH_CONTROL:
      HandleBluetoothRemote(recv_flag);
      break;
    default:
      break;
  }
}
