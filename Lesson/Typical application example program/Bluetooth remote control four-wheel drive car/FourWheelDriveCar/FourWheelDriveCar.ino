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
    m4wd.SetControlMode(E_NRF24L01_CONTROL);
    
    m4wd.InitServo();
    m4wd.InitRgb();
    m4wd.InitBuzzer();
    m4wd.SetSpeed(100);
    m4wd.SetServoBaseDegree(90);
    m4wd.SetServoDegree(1, 90);
    m4wd.InitNrf24L01("MotorDriver");
    Serial.println("init ok");
    m4wd.sing(S_connection);
}

void HandleNrf24L01Remote()
{
    byte value[12] = {0};
    bool godata = false;
    while (m4wd.Nrf24L01->dataReady()) { //When the program is received, the received data is output from the serial port
        m4wd.Nrf24L01->getData(value);
        mProtocol->RecevData(value, 12);
       /*  for (int i = 0; i < 12; i++) {
            Serial.print(value[i], HEX); Serial.print(" ");
        }
            Serial.println("");
       */
    }
    if (mProtocol->ParserPackage())
    {
        Serial.println("got rf package");
        E_CONTOROL_FUNC fun = mProtocol->GetRobotControlFun();
        if ( fun == E_ROBOT_CONTROL_DIRECTION) {
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ROBOT_CONTROL_DIRECTION \n");
            int degree = mProtocol->GetRobotDegree();
            Serial.println(degree);
            m4wd.Drive(degree);
        }
        if (fun == E_ROBOT_CONTROL_SPEED) {
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ROBOT_CONTROL_SPEED \n");
            m4wd.SetSpeed(mProtocol->GetRobotSpeed());
        }
        if (fun == E_BUTTON) {
            Serial.println("Button: ");
            Serial.println(mProtocol->GetBluetoothButton());
            switch (mProtocol->GetBluetoothButton()) {
            case BT_L1:
                Serial.println("BT_L:");
                m4wd.SpeedDown(5);
                break;
            case BT_R1:
                Serial.println("BT_R:");
                m4wd.SpeedUp(5);
                break;                
            case BT_PAD_UP:
                Serial.println("BT_PAD_UP:");
                m4wd.GoForward();
                break;
            case BT_PAD_DOWN:
                Serial.println("BT_PAD_DOWN:");
                m4wd.GoBack();
                break;                
            case BT_PAD_LEFT:
                Serial.println("BT_PAD_LEFT:");
                m4wd.TurnLeftRotate();
                break; 
            case BT_PAD_RIGHT:
                Serial.println("BT_PAD_RIGHT:");
                m4wd.TurnRightRotate();
                break; 
                default:
                break;
            } 
        }
    }
}

void loop()
{
    if (m4wd.GetControlMode() == E_NRF24L01_CONTROL) {
        HandleNrf24L01Remote();
        DEBUG_LOG(DEBUG_LEVEL_INFO, "E_NRF24L01_CONTROL \n");
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
