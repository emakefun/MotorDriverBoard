#include "Emakefun_MotorDriver.h"
#include "MsTimer2.h"
#include "PID_v1.h"

double Setpoint, Input, Output;
double Kp=1, Ki=5, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);//速度为正值时：DIRECT 负值时：REVERSE

static volatile int Encoder1Pulse = 0, Encoder2Pulse = 0;
int ratio = 1.5;//电机减速比

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_EncoderMotor *EncodeMotor_1 = mMotorDriver.getEncoderMotor(E1);

void EncoderSpeed()
{
  Input = EncodeMotor_1->EncoderPulse*ratio;
  EncodeMotor_1->EncoderPulse = 0;
  Serial.println(Input);   
}

static void encoder1(void)
{
  if (digitalRead(EncodeMotor_1->ENCODER2pin) == LOW) {
    EncodeMotor_1->EncoderPulse++;
  } else {
    EncodeMotor_1->EncoderPulse--;
  }
}

void setup()
{
    Serial.begin(9600);
    mMotorDriver.begin();
    EncodeMotor_1->init(encoder1);
    MsTimer2::set(100, EncoderSpeed); // 500ms period
    MsTimer2::start();
    Setpoint = 100;
    myPID.SetOutputLimits(-255, 255);
    myPID.SetSampleTime(100);
    myPID.SetMode(AUTOMATIC);
      
}

void loop()
{
  myPID.Compute();
  EncodeMotor_1->setSpeed(abs(Output));
  if(Output > 0) {
    EncodeMotor_1->run(FORWARD);
  } else {
    EncodeMotor_1->run(BACKWARD);
  }
}
