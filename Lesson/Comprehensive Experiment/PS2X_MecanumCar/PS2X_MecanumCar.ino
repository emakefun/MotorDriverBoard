#include<Arduino.h>
#include<Wire.h>
#include "Panther_Tank.h"
#include "ProtocolParser.h"
#include "BluetoothHandle.h"
#include "debug.h"
#include "KeyMap.h"
ProtocolParser *mProtocol = new ProtocolParser();
Tank mTank(mProtocol);
static byte count = 0;
void setup()
{
  Serial.begin(9600);
  mTank.SetControlMode(E_PS2_REMOTE_CONTROL);
  mTank.InitServoPin();
  mTank.InitRgbPin();
  mTank.InitBuzzerPin();
  mTank.SetSpeed(60);
  mTank.init();
  mTank.SetServoBaseDegree(90);
}

void HandlePS2(int Ps2xKey)
{
  switch (Ps2xKey) {
    case PSB_PAD_UP:
      mTank.GoForward();
      break;
    case PSB_PAD_DOWN:
      mTank.GoBack();
      break;
    case PSB_PAD_LEFT:
      mTank.TurnLeft();
      break;
    case PSB_PAD_RIGHT:
      mTank.TurnRight();
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
      mTank.LeftLateral();
      break;
    case PSB_CIRCLE:
      mTank.RightLateral();
      break;
  }
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
      Ps2xKey = mTank.GetPs2xKeyValue();
      if (Ps2xKey != NULL) {
        HandlePS2(Ps2xKey);
        delay(20);
      } else {
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
