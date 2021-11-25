#include "Emakefun_MotorDriver.h"

#define ONE_CIRCLE_PULSE  1080  //90*12=1080

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_EncoderMotor *EncodeMotor_1 = mMotorDriver.getEncoderMotor(E1);
Emakefun_EncoderMotor *EncodeMotor_2 = mMotorDriver.getEncoderMotor(E2);
Emakefun_EncoderMotor *EncodeMotor_3 = mMotorDriver.getEncoderMotor(E3);
Emakefun_EncoderMotor *EncodeMotor_4 = mMotorDriver.getEncoderMotor(E4);

void encoder1(void)
{
  if (digitalRead(EncodeMotor_1->ENCODER2pin) == LOW) {
    EncodeMotor_1->EncoderPulse++;
  } else {
    EncodeMotor_1->EncoderPulse--;
  }
}

void encoder2(void)
{
  if (digitalRead(EncodeMotor_2->ENCODER2pin) == LOW) {
    EncodeMotor_2->EncoderPulse++;
  } else {
    EncodeMotor_2->EncoderPulse--;
  }
}

void encoder3(void)
{
  if (digitalRead(EncodeMotor_3->ENCODER2pin) == LOW) {
    EncodeMotor_3->EncoderPulse++;
  } else {
    EncodeMotor_3->EncoderPulse--;
  }
}

void encoder4(void)
{
  if (digitalRead(EncodeMotor_4->ENCODER2pin) == LOW) {
    EncodeMotor_4->EncoderPulse++;
  } else {
    EncodeMotor_4->EncoderPulse--;
  }
}

void setup()
{
    Serial.begin(9600);
    mMotorDriver.begin();
    delay(100);
    Serial.println("start");
    EncodeMotor_1->init(encoder1);
    EncodeMotor_2->init(encoder2);
    EncodeMotor_3->init(encoder3);
    EncodeMotor_4->init(encoder4);
    EncodeMotor_1->setSpeed(200);
    EncodeMotor_2->setSpeed(200);
    EncodeMotor_3->setSpeed(200);
    EncodeMotor_4->setSpeed(200);
    EncodeMotor_1->run(FORWARD);
    EncodeMotor_2->run(FORWARD);
    EncodeMotor_3->run(BACKWARD);
    EncodeMotor_4->run(BACKWARD);
    EncodeMotor_1->run(BACKWARD, 200, ONE_CIRCLE_PULSE);
    while(1);
}

void loop()
{

  Serial.print("Encoder1Pulse:");
  Serial.println(EncodeMotor_1->EncoderPulse);
  Serial.print("Encoder2Pulse:");
  Serial.println(EncodeMotor_2->EncoderPulse);
  Serial.print("Encoder3Pulse:");
  Serial.println(EncodeMotor_3->EncoderPulse);
  Serial.print("Encoder4Pulse:");
  Serial.println(EncodeMotor_4->EncoderPulse);
  while(1) {
      
      if (EncodeMotor_1->EncoderPulse > 180*12) {
        //  Serial.println("STOP");
          EncodeMotor_1->run(BRAKE);
      } else {
        Serial.println(EncodeMotor_1->EncoderPulse);
      }
     //delay(10);
  }
}
