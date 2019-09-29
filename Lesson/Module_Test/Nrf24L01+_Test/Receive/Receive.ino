//Receiver program
#include <SPI.h>
#include "nRF24L01.h"

#define NRF24L01_CE 10
#define NRF24L01_CSN 9


Nrf24l Mirf = Nrf24l(NRF24L01_CE, NRF24L01_CSN);
String SmartCarName = "MotorDrive";
int value;

void setup()
{
    Serial.begin(9600);
    Mirf.spi = &MirfHardwareSpi;
    Mirf.init();
    Mirf.setRADDR((byte *)"MotorDrive"); //Set your own address (receiver address) 
    Mirf.payload = sizeof(value);
    Mirf.channel = 90;             //Set the used channel
    Mirf.config();
    Serial.println("Listening...");  //Start listening to received data
}

void loop()
{
  if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData((byte *) &value);
    Serial.print("Got data: ");
    Serial.println(value);
  }
}
