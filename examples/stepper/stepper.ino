#include "Emakefun_MotorShield.h"

Emakefun_MotorShield mMotorShield = Emakefun_MotorShield(0x60);
Emakefun_StepperMotor *StepperMotor_1 = mMotorShield.getStepper(200, 1);
Emakefun_StepperMotor *StepperMotor_2 = mMotorShield.getStepper(200, 2);

void setup()
{
  Serial.begin(9600);
  mMotorShield.begin(50);
  StepperMotor_1->setSpeed(200);
  StepperMotor_2->setSpeed(200);
}

void loop()
{
    StepperMotor_1->step(200, FORWARD,DOUBLE); //电机1正转1圈 200步
    StepperMotor_1->release();
    StepperMotor_2->step(200, FORWARD,DOUBLE); //电机2正转1圈 200步
    StepperMotor_2->release();
//    delay(1000);
//    StepperMotor_1->step(200, BACKWARD,DOUBLE); //电机1反转1圈 200步
//    StepperMotor_1->release();
//    StepperMotor_2->step(200, BACKWARD,DOUBLE); //电机2反转1圈 200步
//    StepperMotor_2->release();
//    delay(1000);
}
