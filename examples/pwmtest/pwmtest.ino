#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver pwm = Emakefun_MotorDriver(0x60);

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
