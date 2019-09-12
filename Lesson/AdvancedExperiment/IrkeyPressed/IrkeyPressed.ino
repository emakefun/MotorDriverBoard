#include "Emakefun_MotorDriver.h"
#include "KeyMap.h"
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_Sensor *ir = mMotorDriver.getSensor(E_IR);
Emakefun_Sensor *rgb = mMotorDriver.getSensor(E_RGB);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
  byte irKeyCode;
  if (irKeyCode = ir->mIrRecv->getCode()){
    Serial.print("key name:");
    switch ((E_IR_KEYCODE)ir->mIrRecv->getIrKey(irKeyCode)){
      case IR_KEYCODE_STAR:
        Serial.println("STAR");
        rgb->SetRgbColor(E_RGB_ALL,RGB_GREEN);
        break;
      case IR_KEYCODE_POUND:
        Serial.println("POUND");
        rgb->SetRgbColor(E_RGB_ALL,RGB_GREEN);
        break;
      case IR_KEYCODE_UP:
        Serial.println("UP");
        rgb->SetRgbColor(E_RGB_ALL,RGB_WHITE);
        break;
      case IR_KEYCODE_DOWN:
        Serial.println("DOWN");
        rgb->SetRgbColor(E_RGB_ALL,RGB_RED);
        break;
      case IR_KEYCODE_OK:
        Serial.println("OK");
        rgb->SetRgbColor(E_RGB_ALL,RGB_BLACK);
        break;
      case IR_KEYCODE_LEFT:
        Serial.println("LEFT");
        rgb->SetRgbColor(E_RGB_LEFT,RGB_WHITE);
        break;
      case IR_KEYCODE_RIGHT:
        Serial.println("RIGHT");
        rgb->SetRgbColor(E_RGB_RIGHT,RGB_WHITE);
        break;
      default:
        break;
    }
    rgb->SetRgbColor(E_RGB_ALL,RGB_BLACK);
  }
}
