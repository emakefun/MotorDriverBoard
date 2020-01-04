#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver(0x60, MOTOR_DRIVER_BOARD_V5);
Emakefun_Sensor *Nrf = mMotorDriver.getSensor(E_SENSOR_MAX);

void setup()
{
    Serial.begin(9600);
    mMotorDriver.getSensor(E_NRF24L01);
    Serial.println("nRF24L01+ module reveive test");
}

void loop()
{
  int NrfData;
  NrfData = Nrf->GetNrf24L01((char *)"MotorDriver");
  if (NrfData != NULL) {
      Serial.print("i'm Got MotorDriver data: ");
      Serial.println(NrfData);
  }
}
