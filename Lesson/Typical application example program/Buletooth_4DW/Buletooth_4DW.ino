#include "FourWheelDrive.h"
#include "ProtocolParser.h"
#include "BluetoothHandle.h"
#include "debug.h"
#include "KeyMap.h"
ProtocolParser *mProtocol = new ProtocolParser();
FourWheelDrive m4wd(mProtocol);

void setup()
{
  Serial.begin(9600);
  Serial.println("PS2X control 4wd");
  m4wd.init(M2, M1, M4, M3);
  Serial.println("end");
  m4wd.SetControlMode(E_BLUETOOTH_CONTROL);
  m4wd.InitServo();
  m4wd.InitRgb();
  m4wd.InitBuzzer();
  m4wd.SetSpeed(100);
  m4wd.SetServoBaseDegree(90);
  m4wd.SetServoDegree(1, 90);
  m4wd.InitPs2x();
  Serial.println("init ok");
  m4wd.sing(S_connection);
}

void HandleBluetoothRemote(bool recv_flag)
{
  if (recv_flag) {
    switch (mProtocol->GetRobotControlFun()) {
      case E_BUTTON:
        switch (mProtocol->GetBluetoothButton())
        {
          case BT_PAD_UP:
            m4wd.GoForward();
            break;
          case BT_PAD_DOWN:
            m4wd.GoBack();
            break;
          case BT_PAD_LEFT:
            m4wd.Drive(160);
            break;
          case BT_PAD_RIGHT:
            m4wd.Drive(20);
            break;
          case BT_PINK:
            m4wd.TurnLeft();
            break;
          case BT_RED:
            m4wd.TurnRight();
            break;
          case BT_GREEN:
            m4wd.sing(S_connection);
            m4wd.SetRgbColor(E_RGB_ALL, m4wd.GetSpeed() * 2.5);
            m4wd.SpeedUp(10);
            break;
          case BT_BLUE:
            m4wd.sing(S_disconnection);
            m4wd.SetRgbColor(E_RGB_ALL, m4wd.GetSpeed() * 2.5);
            m4wd.SpeedDown(10);
            break;
          case BT_L1:
            m4wd.sing(S_connection);
            m4wd.SetRgbColor(E_RGB_ALL, m4wd.GetSpeed() * 2.5);
            m4wd.SpeedUp(10);
            break;
          case BT_R1:
            m4wd.sing(S_disconnection);
            m4wd.SetRgbColor(E_RGB_ALL, m4wd.GetSpeed() * 2.5);
            m4wd.SpeedDown(10);
            break;
        }
        break;
      case E_ROBOT_CONTROL_DIRECTION:
        m4wd.Drive(mProtocol->GetRobotDegree());
        break;
      case E_ROBOT_CONTROL_SPEED:
        m4wd.SetSpeed(mProtocol->GetRobotSpeed());
        break ;
      case E_LED:
        m4wd.SetRgbColor(E_RGB_ALL, mProtocol->GetRgbValue());
        break;
      case E_SERVER_DEGREE:
        m4wd.SetServoDegree(mProtocol->GetServoDegreeNum(), mProtocol->GetServoDegree());
        break;
      case E_BUZZER_MODE:
        if (mProtocol->GetBuzzerMode() == E_SOUND) {
          m4wd.sing(mProtocol->GetBuzzerSound());
        }
        break;
    }
    m4wd.LightOff();
  }
}

void loop()
{
  static byte mode;
  static bool recv_flag;
  mProtocol->RecevData();
  if (recv_flag = mProtocol->ParserPackage()) {
    if (mProtocol->GetRobotControlFun() == E_CONTROL_MODE) {
      m4wd.SetControlMode(mProtocol->GetControlMode());
      return;
    }
  }
  switch (m4wd.GetControlMode()) {
    case E_BLUETOOTH_CONTROL:
      HandleBluetoothRemote(recv_flag);
      DEBUG_LOG(DEBUG_LEVEL_INFO, "E_BLUETOOTH_CONTROL \n");
      break;
    default:
      break;
  }
  switch (m4wd.GetStatus()) {
    case E_FORWARD:
      m4wd.SetRgbColor(E_RGB_ALL, RGB_WHITE);
      break;
    case E_LEFT:
      m4wd.SetRgbColor(E_RGB_LEFT, RGB_WHITE);
      break;
    case E_RIGHT:
      m4wd.SetRgbColor(E_RGB_RIGHT, RGB_WHITE);
      break;
    case E_BACK:
      m4wd.SetRgbColor(E_RGB_ALL, RGB_RED);
      break;
    case E_STOP:
      m4wd.LightOff();
      break;
    default:
      break;
  }
}
