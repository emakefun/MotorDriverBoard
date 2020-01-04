#include "Emakefun_MotorDriver.h"

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver(0x60, MOTOR_DRIVER_BOARD_V5);;
RGBLed *rgb = mMotorDriver.getSensor(E_RGB);


void setup()
{
  Serial.begin(9600);
}

void loop()
{
  rgb->setBrightness(20);
  rgb->SetRgbColor(E_RGB_ALL, RGB_WHITE);
  delay(1000);
   rgb->setBrightness(100);
  rgb->SetRgbColor(E_RGB_ALL, RGB_BLUE);
  delay(1000);
  rgb->setBrightness(170);
  rgb->SetRgbColor(E_RGB_ALL, RGB_RED);
  delay(1000);
  rgb->setBrightness(255);
  rgb->SetRgbColor(E_RGB_ALL, RGB_YELLOW);
  delay(1000);
}
