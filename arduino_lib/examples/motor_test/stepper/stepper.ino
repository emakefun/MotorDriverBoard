#include "Emakefun_MotorDriver.h"

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver(0x60);

Emakefun_StepperMotor *StepperMotor_1 = mMotorDriver.getStepper(STEPPER1, 200);
Emakefun_StepperMotor *StepperMotor_2 = mMotorDriver.getStepper(STEPPER2, 200);

void setup()
{
    Serial.begin(9600);
    mMotorDriver.begin(1600);
    StepperMotor_1->setSpeed(400);
    StepperMotor_2->setSpeed(400);
}

void loop()
{
    StepperMotor_1->step(200, FORWARD, DOUBLE); //电机1正转1圈 200步
    StepperMotor_1->release();
    StepperMotor_2->step(200, FORWARD, SINGLE); //电机2正转1圈 200步
    StepperMotor_2->release();
    delay(1000);
    StepperMotor_1->step(200, BACKWARD, DOUBLE); //电机1反转1圈 200步
    StepperMotor_1->release();
    StepperMotor_2->step(200, BACKWARD, SINGLE); //电机2反转1圈 200步
    StepperMotor_2->release();
    delay(1000);
}
