#include "Emakefun_MotorDriver.h"
//#include "PinChangeInt.h"

volatile int Encoder1Pulse = 0, Encoder2Pulse = 0;
float Velocity_KP =1.05, Velocity_KI =0.015; //PI参数
int Flag_Way = 1, Flag_Direction;            //遥控模式标志与蓝牙窜口通信相关标志

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
FuncPtr Emakefun_EncoderMotor::CallBack[2] = {NULL, NULL};
Emakefun_EncoderMotor *EncodeMotor_1 = mMotorDriver.getEncoderMotor(1);
Emakefun_EncoderMotor *EncodeMotor_2 = mMotorDriver.getEncoderMotor(2);

static void encoder1(void)
{
    if (digitalRead(EncodeMotor_1->EncoderBpin) == LOW)  {    //根据另外一相电平判定方向
        Encoder1Pulse--;
    } else {
        Encoder1Pulse++;
    }
  //Serial.print("Encoder1Pulse");
  Serial.println(Encoder1Pulse);
}

 void encoder2(void)
{
    if (digitalRead(EncodeMotor_2->EncoderBpin) == LOW)  {    //根据另外一相电平判定方向
        Encoder2Pulse--;
    } else {
        Encoder2Pulse++;
    }
  //Serial.print("Encoder2Pulse");
  Serial.println(Encoder2Pulse);
}

int Incremental_PI_M1 (int Encoder,int Target)
{  float Bias;
   static float PWM,Last_bias;
   Bias=Encoder-Target;                                  //计算偏差
   PWM+=Velocity_KP/Multiple*(Bias-Last_bias)+Velocity_KI/Multiple/1.314*Bias;   //增量式PI控制器
   if(PWM>155)PWM=155;                                   //限幅
   if(PWM<-155)PWM=-155;                                 //限幅  
   Last_bias=Bias;                                       //保存上一次偏差 
   if(Flag_Way == 1){if (Flag_Direction == 0){if(Target>0)PWM = -2,Last_bias = 0;if(Target<0)PWM = 2,Last_bias = 0;}}//APP模式停止时，重置相关的变量，反向赋值降低小车惯性移动距离
   else if(Flag_Way == 0){if (abs(PS2_Velocity)<=51){if(Target>0)PWM = -2,Last_bias = 0;if(Target<0)PWM = 2,Last_bias = 0;}}//手柄停止时，重置相关的变量，反向赋值降低小车惯性移动距离
   return PWM;                                           //增量输出
}

int Incremental_PI_M2 (int Encoder,int Target)
{  float Bias; 
   static float PWM,Last_bias;
   Bias=Encoder-Target;                                   //计算偏差
   PWM+=Velocity_KP/Multiple*(Bias-Last_bias)+Velocity_KI/Multiple/1.314*Bias;   //增量式PI控制器
   if(PWM>155)PWM=155;                                    //限幅
   if(PWM<-155)PWM=-155;                                  //限幅 
   Last_bias=Bias;                                        //保存上一次偏差
   if(Flag_Way == 1){if (Flag_Direction == 0){if(Target>0)PWM = -2,Last_bias = 0;if(Target<0)PWM = 2,Last_bias = 0;}}//APP模式停止时，重置相关的变量，反向赋值降低小车惯性移动距离
   else if(Flag_Way == 0){if (abs(PS2_Velocity)<=51){if(Target>0)PWM = -2,Last_bias = 0;if(Target<0)PWM = 2,Last_bias = 0;}}//手柄停止时，重置相关的变量，反向赋值降低小车惯性移动距离
   return PWM;                                            //增量输出
}

void setup()
{
    Serial.begin(9600);
    mMotorDriver.begin(50);
    delay(500);
    Serial.println("start");
    EncodeMotor_1->init(encoder1);
    EncodeMotor_2->init(encoder2);
    EncodeMotor_1->run(FORWARD);
    EncodeMotor_2->run(FORWARD);
}

void loop()
{
  /*
    EncodeMotor_1->setSpeed(255);
    EncodeMotor_2->setSpeed(255);
    EncodeMotor_1->run(FORWARD);
    EncodeMotor_2->run(FORWARD);
    Serial.print("FORWARD");
    delay(1000);
    EncodeMotor_1->run(BRAKE);
    EncodeMotor_2->run(BRAKE);
    delay(1000);
    EncodeMotor_1->setSpeed(255);
    EncodeMotor_2->setSpeed(255);
    EncodeMotor_1->run(BACKWARD);
    EncodeMotor_2->run(BACKWARD);
    Serial.print("BACKWARD");
    delay(1000);
    EncodeMotor_1->run(BRAKE);
    EncodeMotor_2->run(BRAKE);
    delay(1000);
    */
}
