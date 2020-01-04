#include "Emakefun_MotorDriver.h"

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver(0x60, MOTOR_DRIVER_BOARD_V5);;
Emakefun_Sensor *ult = mMotorDriver.getSensor(E_SENSOR_MAX);

void setup()
{
  Serial.begin(9600);
  mMotorDriver.getSensor(E_ULTRASONIC);
  Serial.println("Start ranging");
}

void loop()
{
  Serial.print("distance:");
  Serial.println(ult->GetUltrasonicDistance());
  delay(1000);
}
