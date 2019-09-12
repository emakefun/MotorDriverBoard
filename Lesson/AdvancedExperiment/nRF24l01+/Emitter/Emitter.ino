#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_Sensor *Nrf = mMotorDriver.getSensor(E_NRF24L01);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
  Nrf->sendNrf24l01((char *)"Emakefun",123);
  
}
