#include "FourWheelDrive.h"
#include "ProtocolParser.h"
#include "BluetoothHandle.h"
#include "debug.h"
#include "KeyMap.h"
ProtocolParser *mProtocol = new ProtocolParser();
FourWheelDrive mARM(mProtocol);

void setup()
{
  Serial.begin(9600);
  Serial.println("PS2X control 4wd");
  mARM.init(M2, M1, M4, M3);
  Serial.println("end");
  mARM.SetControlMode(E_NRF24L01_CONTROL);

  mARM.InitServo();
  mARM.InitRgb();
  mARM.InitBuzzer();
  mARM.SetSpeed(100);
  mARM.SetServoBaseDegree(90);
  mARM.SetServoDegree(1, 90);
  mARM.InitNrf24L01("MotorDriver");
  Serial.println("init ok");
  mARM.sing(S_connection);
}

void HandleNrf24L01Remote()
{
  static byte UpServo = 90;
  static byte DownServo = 90;
  static byte LeftServo = 140;
  static byte RightServo = 90;
  byte value[12] = {0};
  bool godata = false;
  while (mARM.Nrf24L01->dataReady()) { //When the program is received, the received data is output from the serial port
    mARM.Nrf24L01->getData(value);
    mProtocol->RecevData(value, 12);
    //      for (int i = 0; i < 12; i++) {
    //         Serial.print(value[i], HEX); Serial.print(" ");
    //      }
    //         Serial.println("");
  }
  if (mProtocol->ParserPackage())
  {
    Serial.println("got rf package");
    E_CONTOROL_FUNC fun = mProtocol->GetRobotControlFun();
    if ( fun == E_ROBOT_CONTROL_DIRECTION) {
      DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ROBOT_CONTROL_DIRECTION \n");
      int degree = mProtocol->GetRobotDegree();
      if ((90 < degree) && (degree <= 270))
      {
        if (DownServo < 180) {
          DownServo += 2;
        }
      } else if ((270 < degree) && (degree <= 360) || (0 <= degree) && (degree <= 90)) {
        if (DownServo != 0) {
          DownServo -= 2;
        }
      }
    }
    mARM.SetServoDegree(1, DownServo);
    if (fun == E_ROBOT_CONTROL_SPEED) {
      DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ROBOT_CONTROL_SPEED \n");
      mARM.SetSpeed(mProtocol->GetRobotSpeed());
    }
    if (fun == E_BUTTON) {
      switch (mProtocol->GetBluetoothButton()) {
        case BT_L1:
          Serial.println("BT_L:");
          if (UpServo < 140)
            UpServo += 4;
          break;
        case BT_R1:
          Serial.println("BT_R:");
          if (UpServo > 47)
            UpServo -= 4;
          break;
        case BT_PAD_UP:
          Serial.println("BT_PAD_UP:");
          if ((RightServo < 175))
            RightServo += 2;
          break;
        case BT_PAD_DOWN:
          Serial.println("BT_PAD_DOWN:");
          if (((RightServo != 0) && (100 < LeftServo)) && (RightServo > 70)) {
            RightServo -= 2;
          }  else {
            mARM.sing(S_connection);
            delay(1000);
          }
          break;
        case BT_PAD_LEFT:
          Serial.println("BT_PAD_LEFT:");
          if (LeftServo < 160)
            LeftServo += 2;
          break;
        case BT_PAD_RIGHT:
          Serial.println("BT_PAD_RIGHT:");
          if (LeftServo >= 92)
            LeftServo -= 2;
          break;
        default:
          break;
      }
      mARM.SetServoDegree(4, UpServo);
      mARM.SetServoDegree(2, LeftServo);
      mARM.SetServoDegree(3, RightServo);
    }
  }
}

void loop()
{
  if (mARM.GetControlMode() == E_NRF24L01_CONTROL) {
    HandleNrf24L01Remote();
    DEBUG_LOG(DEBUG_LEVEL_INFO, "E_NRF24L01_CONTROL \n");
  }

  switch (mARM.GetStatus()) {
    case E_FORWARD:
      mARM.SetRgbColor(E_RGB_ALL, RGB_WHITE);
      break;
    case E_LEFT:
    case E_LEFT_ROTATE:
      mARM.SetRgbColor(E_RGB_LEFT, RGB_WHITE);
      break;
    case E_RIGHT:
    case E_RIGHT_ROTATE:
      mARM.SetRgbColor(E_RGB_RIGHT, RGB_WHITE);
      break;
    case E_BACK:
      mARM.SetRgbColor(E_RGB_ALL, RGB_RED);
      break;
    case E_SPEED_UP:
      mARM.sing(S_connection);
      mARM.SetRgbColor(E_RGB_ALL, RGB_GREEN);
      break;
    case E_SPEED_DOWN:
      mARM.sing(S_disconnection);
      mARM.SetRgbColor(E_RGB_ALL, RGB_BLUE);
      break;
    case E_STOP:
      mARM.LightOff();
      break;
    default:
      break;
  }
}
