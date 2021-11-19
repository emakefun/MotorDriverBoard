#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver gpio = Emakefun_MotorDriver(0x60);

void setup() {
  Serial.begin(9600);
  Serial.println("GPIO test!");
  gpio.begin(1000);
}

void loop() {
  gpio.setPin(S1, HIGH);
  delay(1000);
  gpio.setPin(S1, LOW);
  delay(1000);
}
