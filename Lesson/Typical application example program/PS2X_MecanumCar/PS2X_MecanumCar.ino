#include "FourWheelDrive.h"
#include "ProtocolParser.h"
#include "BluetoothHandle.h"
#include "debug.h"
#include "KeyMap.h"
ProtocolParser *mProtocol = new ProtocolParser();
FourWheelDrive mMC(mProtocol);

void setup()
{
    Serial.begin(9600);
    Serial.println("PS2X control 4wd");
    mMC.init(M2, M1, M4, M3);
    Serial.println("end");
    mMC.SetControlMode(E_PS2_REMOTE_CONTROL);
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

void HandlePS2(void)
{
    int Ps2xKey;
    mMC.Ps2x->read_gamepad(false, 0);
    if (mMC.Ps2x->ButtonDataByte()) {
        if (mMC.Ps2x->Button(PSB_TRIANGLE)) {
            Serial.print("PS2X PSB_TRIANGLE:");
            mMC.SpeedUp(5);
            Serial.println(mMC.GetSpeed());
            return;
        }
        if (mMC.Ps2x->Button(PSB_CROSS)) {
            Serial.print("PS2X PSB_CROSS:");
            mMC.SpeedDown(5);
            Serial.println(mMC.GetSpeed());
            return;
        }

        if (mMC.Ps2x->Button(PSB_PAD_UP)) {
             Serial.println("PS2X PSB_PAD_UP:");
             mMC.GoForward();
           }
        if (mMC.Ps2x->Button(PSB_PAD_DOWN)) {
            Serial.println("PS2X PSB_PAD_DOWN:");
            mMC.GoBack();
        }
        if (mMC.Ps2x->Button(PSB_PAD_LEFT)) {
            Serial.println("PS2X PSB_PAD_LEFT:");
             mMC.TurnLeft();
           }
        if (mMC.Ps2x->Button(PSB_PAD_RIGHT)) {
            Serial.println("PS2X PSB_PAD_RIGHT:");
            mMC.TurnRight();
        }
        if (mMC.Ps2x->Button(PSB_SQUARE)) {
            Serial.println("PS2X PSB_SQUARE:");
            mMC.TurnLeftRotate();
        }
        if (mMC.Ps2x->Button(PSB_CIRCLE)) {
            Serial.println("PS2X PSB_CIRCLE:");
            mMC.TurnRightRotate();
        }

       }else {
        mMC.KeepStop();
    }
    delay(50);
}


void loop()
{
    if (mMC.GetControlMode() == E_PS2_REMOTE_CONTROL) {
        HandlePS2();
        DEBUG_LOG(DEBUG_LEVEL_INFO, "E_BLUETOOTH_CONTROL \n");
    }

    switch (mMC.GetStatus()) {
        case E_FORWARD:
          mMC.SetRgbColor(E_RGB_ALL, RGB_WHITE);
          break;
        case E_LEFT:
        case E_LEFT_ROTATE:
          mMC.SetRgbColor(E_RGB_LEFT, RGB_WHITE);
          break;
        case E_RIGHT:
        case E_RIGHT_ROTATE:
          mMC.SetRgbColor(E_RGB_RIGHT, RGB_WHITE);
          break;
        case E_BACK:
          mMC.SetRgbColor(E_RGB_ALL, RGB_RED);
          break;
        case E_SPEED_UP:
            mMC.sing(S_connection);
            mMC.SetRgbColor(E_RGB_ALL, RGB_GREEN);
            break;
        case E_SPEED_DOWN:
            mMC.sing(S_disconnection);
            mMC.SetRgbColor(E_RGB_ALL, RGB_BLUE);
            break;
        case E_STOP:
            mMC.LightOff();
            break;
        default:
          break;
    }
}
