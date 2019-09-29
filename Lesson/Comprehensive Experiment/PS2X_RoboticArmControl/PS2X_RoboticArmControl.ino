#include<Arduino.h>
#include<Wire.h>
#include "Panther_Tank.h"
#include "ProtocolParser.h"
#include "BluetoothHandle.h"
#include "debug.h"
#include "KeyMap.h"
ProtocolParser *mProtocol = new ProtocolParser();
Tank mTank(mProtocol);
void setup()
{
  Serial.begin(9600);
  mTank.SetControlMode(E_PS2_REMOTE_CONTROL);
  mTank.InitServoPin();
  mTank.InitPs2xPin();
  mTank.InitRgbPin();
  mTank.InitBuzzerPin();
  mTank.SetSpeed(60);
  mTank.init();
  mTank.SetServoBaseDegree(90);
  mTank.SetServoDegree(1, 90);
}

void HandlePS2(int Ps2xKey, uint16_t Ps2xRightAngle, uint16_t Ps2xLeftAngle)
{
  static byte UpServo = 90;
  static byte DownServo = 90;
  static byte LeftServo = 140;
  static byte RightServo = 90;
  switch (Ps2xKey) {
    case PSB_PAD_UP:
      mTank.GoForward();
      break;
    case PSB_PAD_DOWN:
      mTank.GoBack();
      break;
    case PSB_PAD_LEFT:
      mTank.Drive(160);
      break;
    case PSB_PAD_RIGHT:
      mTank.Drive(20);
      break;
    case PSB_CROSS:
      mTank.sing(S_disconnection);
      mTank.SetRgbColor(E_RGB_ALL, mTank.GetSpeed() * 2.5);
      mTank.SpeedDown(5);
      break;
    case PSB_TRIANGLE:
      mTank.sing(S_connection);
      mTank.SetRgbColor(E_RGB_ALL, mTank.GetSpeed() * 2.5);
      mTank.SpeedUp(5);
      break;
    case PSB_SQUARE:
      mTank.TurnLeft();
      break;
    case PSB_CIRCLE:
      mTank.TurnRight();
      break;
    case PSB_L1:
      if (UpServo < 140) {
        UpServo += 4;
      }
      break;
    case PSB_R1:
      if (UpServo > 47) {
        UpServo -= 4;
      }
      break;
  }
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
      }  else {
        mTank.sing(S_connection);
        delay(1000);
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
    mTank.SetServoDegree(1, DownServo);
    mTank.SetServoDegree(2, LeftServo);
    mTank.SetServoDegree(3, RightServo);
  }
  mTank.SetServoDegree(4, UpServo);
}

void loop()
{
  static byte mode;
  static bool recv_flag;
  mProtocol->RecevData();
  if (recv_flag = mProtocol->ParserPackage()) {
    if (mProtocol->GetRobotControlFun() == E_CONTROL_MODE) {
      mTank.SetControlMode(mProtocol->GetControlMode());
      return;
    }
  }
  switch (mTank.GetControlMode()) {
    case E_PS2_REMOTE_CONTROL:
      int Ps2xKey;
      uint16_t Ps2xLeftAngle, Ps2xRightAngle;
      Ps2xKey = mTank.GetPs2xKeyValue();
      Ps2xLeftAngle = mTank.GetPs2xRockerAngle(1);
      Ps2xRightAngle = mTank.GetPs2xRockerAngle(2);
      if ((Ps2xKey != NULL) || (Ps2xRightAngle != 0xFFF) || (Ps2xLeftAngle != 0xFFF)) {
        HandlePS2(Ps2xKey, Ps2xRightAngle, Ps2xLeftAngle);
        delay(20);
      }
      else {
        mTank.KeepStop();
      }
      break;
    default:
      break;
  }
  switch (mTank.GetStatus()) {
    case E_FORWARD:
      mTank.SetRgbColor(E_RGB_ALL, RGB_WHITE);
      break;
    case E_LEFT:
      mTank.SetRgbColor(E_RGB_LEFT, RGB_WHITE);
      break;
    case E_RIGHT:
      mTank.SetRgbColor(E_RGB_RIGHT, RGB_WHITE);
      break;
    case E_BACK:
      mTank.SetRgbColor(E_RGB_ALL, RGB_RED);
      break;
    case E_STOP:
      mTank.LightOff();
      break;
    default:
      break;
  }
}
