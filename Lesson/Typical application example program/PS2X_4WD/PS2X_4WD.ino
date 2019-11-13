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
    m4wd.SetControlMode(E_PS2_REMOTE_CONTROL);
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

void HandlePS2(void)
{
    int Ps2xKey;
    m4wd.Ps2x->read_gamepad(false, 0);
    if (m4wd.Ps2x->ButtonDataByte()) {
        if (m4wd.Ps2x->Button(PSB_TRIANGLE)) {
            Serial.print("PS2X PSB_TRIANGLE:");
            m4wd.SpeedUp(5);
            Serial.println(m4wd.GetSpeed());
            return;
        }
        if (m4wd.Ps2x->Button(PSB_CROSS)) {
            Serial.print("PS2X PSB_CROSS:");
            m4wd.SpeedDown(5);
            Serial.println(m4wd.GetSpeed());
            return;
        }

        if (m4wd.Ps2x->Button(PSB_PAD_UP)) {
             Serial.println("PS2X PSB_PAD_UP:");
             m4wd.GoForward();
           }
        if (m4wd.Ps2x->Button(PSB_PAD_DOWN)) {
            Serial.println("PS2X PSB_PAD_DOWN:");
            m4wd.GoBack();
        }
        if (m4wd.Ps2x->Button(PSB_PAD_LEFT)) {
            Serial.println("PS2X PSB_PAD_LEFT:");
             m4wd.TurnLeft();
           }
        if (m4wd.Ps2x->Button(PSB_PAD_RIGHT)) {
            Serial.println("PS2X PSB_PAD_RIGHT:");
            m4wd.TurnRight();
        }
        if (m4wd.Ps2x->Button(PSB_SQUARE)) {
            Serial.println("PS2X PSB_SQUARE:");
            m4wd.TurnLeftRotate();
        }
        if (m4wd.Ps2x->Button(PSB_CIRCLE)) {
            Serial.println("PS2X PSB_CIRCLE:");
            m4wd.TurnRightRotate();
        }

       }else {
        m4wd.KeepStop();
    }
    delay(50);
}


void loop()
{
    if (m4wd.GetControlMode() == E_PS2_REMOTE_CONTROL) {
        HandlePS2();
        DEBUG_LOG(DEBUG_LEVEL_INFO, "E_BLUETOOTH_CONTROL \n");
    }

    switch (m4wd.GetStatus()) {
        case E_FORWARD:
          m4wd.SetRgbColor(E_RGB_ALL, RGB_WHITE);
          break;
        case E_LEFT:
        case E_LEFT_ROTATE:
          m4wd.SetRgbColor(E_RGB_LEFT, RGB_WHITE);
          break;
        case E_RIGHT:
        case E_RIGHT_ROTATE:
          m4wd.SetRgbColor(E_RGB_RIGHT, RGB_WHITE);
          break;
        case E_BACK:
          m4wd.SetRgbColor(E_RGB_ALL, RGB_RED);
          break;
        case E_SPEED_UP:
            m4wd.sing(S_connection);
            m4wd.SetRgbColor(E_RGB_ALL, RGB_GREEN);
            break;
        case E_SPEED_DOWN:
            m4wd.sing(S_disconnection);
            m4wd.SetRgbColor(E_RGB_ALL, RGB_BLUE);
            break;
        case E_STOP:
            m4wd.LightOff();
            break;
        default:
          break;
    }
}
