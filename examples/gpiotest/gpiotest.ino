#include "pca9685.h"
Pca9685 gpio = Pca9685(0x40);

void setup() {
  Serial.begin(9600);
  Serial.println("GPIO test!");
  gpio.begin(1000);
}

void loop() {
  gpio.setPin(1, HIGH);
  delay(1000);
  gpio.setPin(1, LOW);
  delay(1000);
}
