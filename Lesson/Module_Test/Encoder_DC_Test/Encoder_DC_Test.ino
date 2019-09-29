#include "Emakefun_MotorDriver.h"

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_EncoderMotor *EncodeMotor_1 = mMotorDriver.getEncoderMotor(1);
Emakefun_EncoderMotor *EncodeMotor_2 = mMotorDriver.getEncoderMotor(2);

void setup()
{
    Serial.begin(9600);
    mMotorDriver.begin(50);
}

void loop()
{
  EncodeMotor_1->setSpeed(100);
  EncodeMotor_2->setSpeed(100);
  EncodeMotor_1->run(FORWARD);
  EncodeMotor_2->run(FORWARD);
  delay(1000);
  EncodeMotor_1->run(BACKWARD);
  EncodeMotor_2->run(BACKWARD);
  delay(1000);
  EncodeMotor_1->setSpeed(0);
  EncodeMotor_2->setSpeed(0);
  EncodeMotor_1->run(RELEASE);
  EncodeMotor_2->run(RELEASE);
  delay(1000);
}
