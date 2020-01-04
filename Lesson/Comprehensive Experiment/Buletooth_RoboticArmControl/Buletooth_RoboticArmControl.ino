#include "FourWheelDrive.h"
#include "ProtocolParser.h"
#include "BluetoothHandle.h"
#include "debug.h"
#include "KeyMap.h"
ProtocolParser *mProtocol = new ProtocolParser();
FourWheelDrive mARM(mProtocol);
static byte count = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("PS2X control 4wd");
  mARM.init(M2, M1, M4, M3);
  Serial.println("end");
  mARM.SetControlMode(E_PS2_REMOTE_CONTROL);
  mARM.InitServo();
  mARM.InitRgb();
  mARM.InitBuzzer();
  mARM.SetSpeed(100);
  mARM.SetServoBaseDegree(90);
  mARM.SetServoDegree(1, 90);
  mARM.SetServoDegree(2, 90);
  mARM.SetServoDegree(3, 90);
  mARM.SetServoDegree(4, 90);
  mARM.InitPs2x();
  Serial.println("init ok");
  mARM.sing(S_connection);
}

void HandleBluetoothRemote(bool recv_flag)
{
  if (recv_flag) {
    switch (mProtocol->GetRobotControlFun()) {
      case E_BUTTON:
        switch (mProtocol->GetBluetoothButton())
        {
          case BT_PAD_UP:
            mARM.GoForward();
            break;
          case BT_PAD_DOWN:
            mARM.GoBack();
            break;
          case BT_PAD_LEFT:
            mARM.Drive(160);
            break;
          case BT_PAD_RIGHT:
            mARM.Drive(20);
            break;
          case BT_PINK:
            mARM.TurnLeft();
            break;
          case BT_RED:
            mARM.TurnRight();
            break;
          case BT_GREEN:
            mARM.sing(S_connection);
            mARM.SetRgbColor(E_RGB_ALL, mARM.GetSpeed() * 2.5);
            mARM.SpeedUp(10);
            break;
          case BT_BLUE:
            mARM.sing(S_disconnection);
            mARM.SetRgbColor(E_RGB_ALL, mARM.GetSpeed() * 2.5);
            mARM.SpeedDown(10);
            break;
        }
        break;
      case E_ROBOT_CONTROL_DIRECTION:
        mARM.Drive(mProtocol->GetRobotDegree());
        break;
      case E_ROBOT_CONTROL_SPEED:
        mARM.SetSpeed(mProtocol->GetRobotSpeed());
        break ;
      case E_LED:
        mARM.SetRgbColor(E_RGB_ALL, mProtocol->GetRgbValue());
        break;
      case E_SERVER_DEGREE:
        mARM.SetServoDegree(mProtocol->GetServoDegreeNum(), mProtocol->GetServoDegree());
        break;
      case E_BUZZER_MODE:
        if (mProtocol->GetBuzzerMode() == E_SOUND) {
          mARM.sing(mProtocol->GetBuzzerSound());
        }
        break;
    }
    mARM.LightOff();
  }
}

void loop()
{
  static byte mode;
  static bool recv_flag;
  mProtocol->RecevData();
  if (recv_flag = mProtocol->ParserPackage()) {
    if (mProtocol->GetRobotControlFun() == E_CONTROL_MODE) {
      mARM.SetControlMode(mProtocol->GetControlMode());
      return;
    }
  }
  switch (mARM.GetControlMode()) {
    case E_BLUETOOTH_CONTROL:
      HandleBluetoothRemote(recv_flag);
      DEBUG_LOG(DEBUG_LEVEL_INFO, "E_BLUETOOTH_CONTROL \n");
      break;
    default:
      break;
  }
  switch (mARM.GetStatus()) {
    case E_FORWARD:
      mARM.SetRgbColor(E_RGB_ALL, RGB_WHITE);
      break;
    case E_LEFT:
      mARM.SetRgbColor(E_RGB_LEFT, RGB_WHITE);
      break;
    case E_RIGHT:
      mARM.SetRgbColor(E_RGB_RIGHT, RGB_WHITE);
      break;
    case E_BACK:
      mARM.SetRgbColor(E_RGB_ALL, RGB_RED);
      break;
    case E_STOP:
      mARM.LightOff();
      break;
    default:
      break;
  }
}
