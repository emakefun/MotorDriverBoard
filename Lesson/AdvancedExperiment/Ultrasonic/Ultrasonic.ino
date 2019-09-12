#include "Emakefun_MotorDriver.h"

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_Sensor *ult = mMotorDriver.getSensor(E_ULTRASONIC);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println(ult->GetUltrasonicDistance());
  delay(100);
}
