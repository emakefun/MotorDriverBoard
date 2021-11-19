#include "Emakefun_MotorDriver.h"
#include "MsTimer2.h"
#include "PID_v1.h"

double Setpoint, Input, Output;
double Kp=3, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);//速度为正值时：DIRECT 负值时：REVERSE

static volatile int Encoder1Pulse = 0, Encoder2Pulse = 0;
int raduction_ratio = 45;//电机减速比

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
FuncPtr Emakefun_EncoderMotor::CallBack[4] = {NULL, NULL};
Emakefun_EncoderMotor *EncodeMotor_1 = mMotorDriver.getEncoderMotor(1);
Emakefun_EncoderMotor *EncodeMotor_2 = mMotorDriver.getEncoderMotor(2);

void EncoderSpeed()
{
  Input = Encoder1Pulse / raduction_ratio;
  Encoder1Pulse = 0;
  Serial.println(Input);   
}

static void encoder1(void)
{
  if (digitalRead(EncodeMotor_1->ENCODER2pin) == LOW) {
    Encoder1Pulse++;
  } else {
    Encoder1Pulse--;
  }
//  Serial.print("Encoder1Pulse");
//  Serial.println(Encoder1Pulse);
}

 void encoder2(void)
{
  if (digitalRead(EncodeMotor_2->ENCODER2pin) == LOW) {
    Encoder2Pulse++;
  } else {
    Encoder2Pulse--;
  }
//  Serial.print("Encoder1Pulse");
//  Serial.println(Encoder1Pulse);
}
 
void setup()
{
    Serial.begin(9600);
    mMotorDriver.begin();
    EncodeMotor_1->init(encoder1);
    EncodeMotor_2->init(encoder2);
    MsTimer2::set(500, EncoderSpeed); // 500ms period
    MsTimer2::start();
    Setpoint = 20;
    myPID.SetSampleTime(500);
    myPID.SetMode(AUTOMATIC);
      
}

void loop()
{
  myPID.Compute();
  EncodeMotor_1->setSpeed(abs(Output));
  EncodeMotor_1->run(FORWARD);
}
