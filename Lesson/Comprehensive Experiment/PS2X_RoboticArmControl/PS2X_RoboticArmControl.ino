#include "FourWheelDrive.h"
#include "ProtocolParser.h"
#include "BluetoothHandle.h"
#include "debug.h"
#include "KeyMap.h"
ProtocolParser *mProtocol = new ProtocolParser();
FourWheelDrive mARM(mProtocol);
byte UpServo = 90;
byte DownServo = 90;
byte LeftServo = 140;
byte RightServo = 90;

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
  mARM.InitPs2x();
  Serial.println("init ok");
  mARM.sing(S_connection);
}

void HandlePS2(void)
{
  int Ps2xRightAngle, Ps2xLeftAngle;
  mARM.Ps2x->read_gamepad(false, 0);
  if (mARM.Ps2x->ButtonDataByte()) {
    if (mARM.Ps2x->Button(PSB_TRIANGLE)) {
      Serial.print("PS2X PSB_TRIANGLE:");
      mARM.SpeedUp(5);
      Serial.println(mARM.GetSpeed());
      return;
    }
    if (mARM.Ps2x->Button(PSB_CROSS)) {
      Serial.print("PS2X PSB_CROSS:");
      mARM.SpeedDown(5);
      Serial.println(mARM.GetSpeed());
      return;
    }
    if (mARM.Ps2x->Button(PSB_PAD_UP)) {
      Serial.println("PS2X PSB_PAD_UP:");
      mARM.GoForward();
    }
    if (mARM.Ps2x->Button(PSB_PAD_DOWN)) {
      Serial.println("PS2X PSB_PAD_DOWN:");
      mARM.GoBack();
    }
    if (mARM.Ps2x->Button(PSB_PAD_LEFT)) {
      Serial.println("PS2X PSB_PAD_LEFT:");
      mARM.TurnLeft();
    }
    if (mARM.Ps2x->Button(PSB_PAD_RIGHT)) {
      Serial.println("PS2X PSB_PAD_RIGHT:");
      mARM.TurnRight();
    }
    if (mARM.Ps2x->Button(PSB_SQUARE)) {
      Serial.println("PS2X PSB_SQUARE:");
      mARM.TurnLeftRotate();
    }
    if (mARM.Ps2x->Button(PSB_CIRCLE)) {
      Serial.println("PS2X PSB_CIRCLE:");
      mARM.TurnRightRotate();
    }
    if (mARM.Ps2x->Button(PSB_L1)) {
      if (UpServo < 140)
        UpServo += 4;
    }
    if (mARM.Ps2x->Button(PSB_R1)) {
      if (UpServo > 47)
        UpServo -= 4;
    }
  } else {
    mARM.KeepStop();
    Ps2xRightAngle = mARM.Ps2x->RightHart();
    Ps2xLeftAngle = mARM.Ps2x->LeftHart();
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
          mARM.sing(S_connection);
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
      mARM.SetServoDegree(1, DownServo);
      mARM.SetServoDegree(2, LeftServo);
      mARM.SetServoDegree(3, RightServo);
    }
  }
  mARM.SetServoDegree(4, UpServo);
  delay(50);
}

void loop()
{
  if (mARM.GetControlMode() == E_PS2_REMOTE_CONTROL) {
    HandlePS2();
    DEBUG_LOG(DEBUG_LEVEL_INFO, "E_BLUETOOTH_CONTROL \n");
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
