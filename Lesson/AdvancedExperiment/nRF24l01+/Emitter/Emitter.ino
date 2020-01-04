#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver(0x60, MOTOR_DRIVER_BOARD_V5);
Emakefun_Sensor *Nrf = mMotorDriver.getSensor(E_SENSOR_MAX);
byte value;

void setup()
{
    Serial.begin(9600);
	  mMotorDriver.getSensor(E_NRF24L01);
}

void loop()
{
  value = random(255);                      //0-255 random number
  Nrf->sendNrf24l01((char *)"MotorDriver", value);
  Serial.print("I'm send success:");
  Serial.println(value);
  delay(1000);
}
