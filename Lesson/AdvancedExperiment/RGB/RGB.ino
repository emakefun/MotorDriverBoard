#include "Emakefun_MotorDriver.h"

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_Sensor *rgb = mMotorDriver.getSensor(E_RGB);


void setup()
{
  Serial.begin(9600);
}

void loop()
{
  rgb->SetRgbColor(E_RGB_ALL, RGB_WHITE);
  delay(1000);
  rgb->SetRgbColor(E_RGB_ALL, RGB_BLUE);
  delay(1000);
  rgb->SetRgbColor(E_RGB_ALL, RGB_RED);
  delay(1000);
  rgb->SetRgbColor(E_RGB_ALL, RGB_YELLOW);
  delay(1000);
  rgb->SetRgbColor(E_RGB_ALL, RGB_BLACK);
  delay(1000);
}
