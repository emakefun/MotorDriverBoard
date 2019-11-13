#include "FourWheelDrive.h"
#include "ProtocolParser.h"
#include "BluetoothHandle.h"
#include "debug.h"
#include "KeyMap.h"
ProtocolParser *mProtocol = new ProtocolParser();
FourWheelDrive mMC(mProtocol);
static byte count = 0;
void setup()
{
  Serial.begin(9600);
  Serial.println("PS2X control 4wd");
  mMC.init(M2, M1, M4, M3);
  Serial.println("end");
  mMC.SetControlMode(E_BLUETOOTH_CONTROL);
  mMC.InitServo();
  mMC.InitRgb();
  mMC.InitBuzzer();
  mMC.SetSpeed(100);
  mMC.SetServoBaseDegree(90);
  mMC.SetServoDegree(1, 90);
  mMC.InitPs2x();
  Serial.println("init ok");
  mMC.sing(S_connection);
}

void HandleBluetoothRemote(bool recv_flag)
{
  if (recv_flag) {
    switch (mProtocol->GetRobotControlFun()) {
      case E_BUTTON:
        switch (mProtocol->GetBluetoothButton())
        {
          case BT_PAD_UP:
            mMC.GoForward();
            break;
          case BT_PAD_DOWN:
            mMC.GoBack();
            break;
          case BT_PAD_LEFT:
            mMC.TurnLeft();
            break;
          case BT_PAD_RIGHT:
            mMC.TurnRight();
            break;
          case BT_PINK:
            mMC.TurnLeftRotate();
            break;
          case BT_RED:
            mMC.TurnRightRotate();
            break;
          case BT_GREEN:
            mMC.sing(S_connection);
            mMC.SetRgbColor(E_RGB_ALL, mMC.GetSpeed() * 2.5);
            mMC.SpeedUp(10);
            break;
          case BT_BLUE:
            mMC.sing(S_disconnection);
            mMC.SetRgbColor(E_RGB_ALL, mMC.GetSpeed() * 2.5);
            mMC.SpeedDown(10);
            break;
        }
        break;
      case E_ROBOT_CONTROL_DIRECTION:
        mMC.Drive(mProtocol->GetRobotDegree());
        break;
      case E_ROBOT_CONTROL_SPEED:
        mMC.SetSpeed(mProtocol->GetRobotSpeed());
        break ;
      case E_LED:
        mMC.SetRgbColor(E_RGB_ALL, mProtocol->GetRgbValue());
        break;
      case E_SERVER_DEGREE:
        mMC.SetServoDegree(mProtocol->GetServoDegreeNum(), mProtocol->GetServoDegree());
        break;
      case E_BUZZER_MODE:
        if (mProtocol->GetBuzzerMode() == E_SOUND) {
          mMC.sing(mProtocol->GetBuzzerSound());
        }
        break;
    }
    mMC.LightOff();
  }
}

void loop()
{
  static byte mode;
  static bool recv_flag;
  mProtocol->RecevData();
  if (recv_flag = mProtocol->ParserPackage()) {
    if (mProtocol->GetRobotControlFun() == E_CONTROL_MODE) {
      mMC.SetControlMode(mProtocol->GetControlMode());
      return;
    }
  }
  switch (mMC.GetControlMode()) {
    case E_BLUETOOTH_CONTROL:
      HandleBluetoothRemote(recv_flag);
      DEBUG_LOG(DEBUG_LEVEL_INFO, "E_BLUETOOTH_CONTROL \n");
      break;
    default:
      break;
  }
  switch (mMC.GetStatus()) {
    case E_FORWARD:
      mMC.SetRgbColor(E_RGB_ALL, RGB_WHITE);
      break;
    case E_LEFT:
      mMC.SetRgbColor(E_RGB_LEFT, RGB_WHITE);
      break;
    case E_RIGHT:
      mMC.SetRgbColor(E_RGB_RIGHT, RGB_WHITE);
      break;
    case E_BACK:
      mMC.SetRgbColor(E_RGB_ALL, RGB_RED);
      break;
    case E_STOP:
      mMC.LightOff();
      break;
    default:
      break;
  }
}
