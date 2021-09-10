#include "Emakefun_MotorShield.h"
Emakefun_MotorShield mMotorShield = Emakefun_MotorShield(0x60);
Emakefun_DCMotor *DCMotor_1 = mMotorShield.getMotor(1);
Emakefun_DCMotor *DCMotor_2 = mMotorShield.getMotor(2);
Emakefun_DCMotor *DCMotor_3 = mMotorShield.getMotor(3);
Emakefun_DCMotor *DCMotor_4 = mMotorShield.getMotor(4);

void setup()
{
    Serial.begin(9600);
    mMotorShield.begin(50);
}

void loop()
{
  // 前进
  DCMotor_1->setSpeed(200);
  DCMotor_1->run(FORWARD);
  DCMotor_2->setSpeed(200);
  DCMotor_2->run(FORWARD);
  DCMotor_3->setSpeed(200);
  DCMotor_3->run(FORWARD);
  DCMotor_4->setSpeed(200);
  DCMotor_4->run(FORWARD);
  delay(4000);
  // 后退
  DCMotor_1->setSpeed(100);
  DCMotor_1->run(BACKWARD);
  DCMotor_2->setSpeed(100);
  DCMotor_2->run(BACKWARD);
  DCMotor_3->setSpeed(100);
  DCMotor_3->run(BACKWARD);
  DCMotor_4->setSpeed(100);
  DCMotor_4->run(BACKWARD);
  delay(4000);
  // 刹车
  DCMotor_1->run(BRAKE);
  DCMotor_2->run(BRAKE);
  DCMotor_3->run(BRAKE);
  DCMotor_4->run(BRAKE);
  delay(4000);
}
