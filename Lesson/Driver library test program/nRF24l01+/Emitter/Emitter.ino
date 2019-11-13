#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_Sensor *Nrf = mMotorDriver.getSensor(E_NRF24L01);
byte value;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
  value = random(255);                      //0-255 random number
  Nrf->sendNrf24l01((char *)"Emakefun",value);
  Serial.print("Send success:");
  Serial.println(value);
  delay(1000);
}
