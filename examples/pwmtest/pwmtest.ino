#include "pca9685.h"
Pca9685 pwm = Pca9685(0x40);

void setup() {
  Serial.begin(9600);
  Serial.println("GPIO test!");
  pwm.begin(1600);
}

void loop() {
  pwm.setPin(1, 0);
  delay(1000);
  pwm.setPin(1, 1024);
  delay(1000);
  pwm.setPin(1, 4096);
  delay(1000);
}
