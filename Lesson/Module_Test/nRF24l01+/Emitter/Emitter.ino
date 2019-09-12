//Transmitter program

#include <SPI.h>
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"


#define NRF24L01_CE 10
#define NRF24L01_CSN 9

Nrf24l Mirf = Nrf24l(NRF24L01_CE, NRF24L01_CSN);
int value;


const uint64_t pipe = 0xE8E8F0F0E1LL;
void setup()
{
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  //Set your own address (sender address) using 5 characters
  Mirf.setRADDR((byte *)"ABCDE");
  Mirf.payload = sizeof(value);
  Mirf.channel = 90;              //Set the channel used
  Mirf.config();
}

void loop()
{
  Mirf.setTADDR((byte *)"MotorDrive");           //Set the receiver address
  value = random(255);                      //0-255 random number
  Mirf.send((byte *)&value);                //Send instructions, send random number value
	Serial.print("Wait for sending.....");
  while (Mirf.isSending()) delay(1);        //Until you send successfully, exit the loop
  Serial.print("Send success:");
  Serial.println(value);
  delay(1000);
}
