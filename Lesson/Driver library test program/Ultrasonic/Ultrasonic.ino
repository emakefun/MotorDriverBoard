#include "Emakefun_MotorDriver.h"

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_Sensor *ult = mMotorDriver.getSensor(E_SENSOR_MAX);

void setup()
{
    Serial.begin(9600);
    mMotorDriver.getSensor(E_ULTRASONIC);
}

void loop()
{
    Serial.println(ult->GetUltrasonicDistance());
    delay(1000);
}
