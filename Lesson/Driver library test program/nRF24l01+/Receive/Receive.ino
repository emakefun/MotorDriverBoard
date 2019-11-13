#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_Sensor *Nrf = mMotorDriver.getSensor(E_NRF24L01);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
  int NrfData;
  NrfData = Nrf->GetNrf24L01((char *)"Emakefun");
  if(NrfData != NULL){
  Serial.print("Got MotorDriver data: ");
  Serial.println(NrfData);
  }
}
