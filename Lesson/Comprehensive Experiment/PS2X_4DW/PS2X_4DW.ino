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
  mTank.SetSpeed(100);
  mTank.init();
  mTank.SetServoBaseDegree(90);
  mTank.SetServoDegree(1, 90);
}

void HandlePS2(int Ps2xKey, uint16_t Ps2xRightAngle, uint16_t Ps2xLeftAngle)
{
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
      if (mode != E_PS2_REMOTE_CONTROL) {
        mTank.InitPs2xPin();
        mode = E_PS2_REMOTE_CONTROL;
      }
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
