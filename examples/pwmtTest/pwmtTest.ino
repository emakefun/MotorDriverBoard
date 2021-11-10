#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver pwm = Emakefun_MotorDriver(0x60);

void setup() {
  Serial.begin(9600);
  Serial.println("GPIO test!");
  pwm.begin(1500);
}

void loop() {
  pwm.setPin(S1, 0);
  delay(1000);
  pwm.setPin(S1, 1024);
  delay(1000);
  pwm.setPin(S1, 4096);
  delay(1000);
}
