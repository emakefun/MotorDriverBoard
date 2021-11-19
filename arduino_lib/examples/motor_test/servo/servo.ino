#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver(0x60);

Emakefun_Servo *mServo1 = mMotorDriver.getServo(1);
Emakefun_Servo *mServo2 = mMotorDriver.getServo(2);
Emakefun_Servo *mServo3 = mMotorDriver.getServo(3);
Emakefun_Servo *mServo4 = mMotorDriver.getServo(4);
Emakefun_Servo *mServo5 = mMotorDriver.getServo(5);
Emakefun_Servo *mServo6 = mMotorDriver.getServo(6);
Emakefun_Servo *mServo7 = mMotorDriver.getServo(7);
Emakefun_Servo *mServo8 = mMotorDriver.getServo(8);

void setup()
{
    Serial.begin(9600);
    mMotorDriver.begin(50);
}

void loop()
{
    mServo1->writeServo(0);
    mServo2->writeServo(0);
    mServo3->writeServo(0);
    mServo4->writeServo(0);
    mServo5->writeServo(0);
    mServo6->writeServo(0);
    mServo7->writeServo(0);
    mServo8->writeServo(0);
    delay(1000);
    mServo1->writeServo(90);
    mServo2->writeServo(90);
    mServo3->writeServo(90);
    mServo4->writeServo(90);
    mServo5->writeServo(90);
    mServo6->writeServo(90);
    mServo7->writeServo(90);
    mServo8->writeServo(90);
    delay(1000);
    mServo1->writeServo(180);
    mServo2->writeServo(180);
    mServo3->writeServo(180);
    mServo4->writeServo(180);
    mServo5->writeServo(180);
    mServo6->writeServo(180);
    mServo7->writeServo(180);
    mServo8->writeServo(180);
    delay(1000);
}
