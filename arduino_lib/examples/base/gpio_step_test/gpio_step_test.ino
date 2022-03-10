#include "Emakefun_MotorDriver.h"

#define IN1 5  //A+
#define IN2 7  //A-
#define IN3 4  //B+
#define IN4 2  //B-
#define TIME 1000
Emakefun_MotorDriver gpio = Emakefun_MotorDriver(0x60);

Emakefun_MotorDriver gpio = Emakefun_MotorDriver(0x60);

void setup() {
  Serial.begin(9600);
  Serial.println("GPIO test!");
  gpio.begin(1600);
}

void onesteps()
{
  gpio.setPin(IN1, HIGH);
  // gpio.setPin(IN2, LOW);
  // gpio.setPin(IN3, LOW);
  gpio.setPin(IN4, LOW);
  delayMicroseconds(TIME);

  gpio.setPin(IN1, LOW);
  // gpio.setPin(IN2, LOW);
  gpio.setPin(IN3, HIGH);
  // gpio.setPin(IN4, LOW);
  delayMicroseconds(TIME);

  gpio.setPin(IN3, LOW);
  gpio.setPin(IN2, HIGH);
  // gpio.setPin(IN1, LOW);
  // gpio.setPin(IN4, LOW);
  delayMicroseconds(TIME);

  gpio.setPin(IN2, LOW);
  // gpio.setPin(IN1, LOW);
  // gpio.setPin(IN3, LOW);
  gpio.setPin(IN4, HIGH);
  delayMicroseconds(TIME);
}

void StepStop()
{
  gpio.setPin(IN1, LOW);
  gpio.setPin(IN2, LOW);
  gpio.setPin(IN3, LOW);
  gpio.setPin(IN4, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 200; i++) {
    onesteps();
  }
  StepStop();
  delay(2000);
}
