#include "Emakefun_MotorDriver.h"
#include "PS2X_lib.h"  //for v1.6
#include "MsTimer2.h"

#define PS2_DAT     12
#define PS2_CMD     11
#define PS2_SEL     10
#define PS2_CLK     13

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x; // create PS2 Controller Class
Emakefun_MotorDriver mMotor = Emakefun_MotorDriver(0x60);
Emakefun_DCMotor *DCMotor_1 = mMotor.getMotor(1);
Emakefun_DCMotor *DCMotor_2 = mMotor.getMotor(2);
Emakefun_DCMotor *DCMotor_3 = mMotor.getMotor(3);
Emakefun_DCMotor *DCMotor_4 = mMotor.getMotor(4);

void Ps2Scan(void)
{
  static char count = 0;
  if (count++ > 20)
  {
    ps2x.reconfig_gamepad();
    count = 0;
  }
  ps2x.read_gamepad();
}

int speed_val = 100;
void setup()
{
  Serial.begin(9600);
  mMotor.begin(50);
  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  MsTimer2::set(50, Ps2Scan);
  MsTimer2::start();
}

void loop()
{
 // ps2x.read_gamepad(); //read controller and set large motor to spin at 'vibrate' speed
  if(ps2x.NewButtonState() == false){
    if(ps2x.Button(PSB_START))         //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");      
  
    if(ps2x.Button(PSB_PAD_UP)) {      //will be TRUE as long as button is pressed
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      //前进
      DCMotor_1->setSpeed(speed_val);
      DCMotor_1->run(FORWARD);
      DCMotor_2->setSpeed(speed_val);
      DCMotor_2->run(FORWARD);
      DCMotor_3->setSpeed(speed_val);
      DCMotor_3->run(FORWARD);
      DCMotor_4->setSpeed(speed_val);
      DCMotor_4->run(FORWARD);
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      //左平移
      DCMotor_1->setSpeed(speed_val);
      DCMotor_1->run(BACKWARD);
      DCMotor_2->setSpeed(speed_val);
      DCMotor_2->run(FORWARD);
      DCMotor_3->setSpeed(speed_val);
      DCMotor_3->run(FORWARD);
      DCMotor_4->setSpeed(speed_val);
      DCMotor_4->run(BACKWARD);
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      //右平移
      DCMotor_1->setSpeed(speed_val);
      DCMotor_1->run(FORWARD);
      DCMotor_2->setSpeed(speed_val);
      DCMotor_2->run(BACKWARD);
      DCMotor_3->setSpeed(speed_val);
      DCMotor_3->run(BACKWARD);
      DCMotor_4->setSpeed(speed_val);
      DCMotor_4->run(FORWARD);
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      //后退
      DCMotor_1->setSpeed(speed_val);
      DCMotor_1->run(BACKWARD);
      DCMotor_2->setSpeed(speed_val);
      DCMotor_2->run(BACKWARD);
      DCMotor_3->setSpeed(speed_val);
      DCMotor_3->run(BACKWARD);
      DCMotor_4->setSpeed(speed_val);
      DCMotor_4->run(BACKWARD);
    }
  }else {
    DCMotor_1->run(BRAKE);
    DCMotor_2->run(BRAKE);
    DCMotor_3->run(BRAKE);
    DCMotor_4->run(BRAKE);  
  }
    if(ps2x.ButtonPressed(PSB_CIRCLE)){
      Serial.println("Circle just pressed");
      //原地旋转
      //逆时针
      DCMotor_1->setSpeed(speed_val);
      DCMotor_1->run(FORWARD);
      DCMotor_2->setSpeed(speed_val);
      DCMotor_2->run(BACKWARD);
      DCMotor_3->setSpeed(speed_val);
      DCMotor_3->run(FORWARD);
      DCMotor_4->setSpeed(speed_val);
      DCMotor_4->run(BACKWARD);
      //顺时针
  //    DCMotor_1->setSpeed(speed_val);
  //    DCMotor_1->run(BACKWARD);
  //    DCMotor_2->setSpeed(speed_val);
  //    DCMotor_2->run(FORWARD);
  //    DCMotor_3->setSpeed(speed_val);
  //    DCMotor_3->run(BACKWARD);
  //    DCMotor_4->setSpeed(speed_val);
  //    DCMotor_4->run(FORWARD);
    }
    if(ps2x.ButtonPressed(PSB_CROSS)){
      Serial.println("X just changed");
      // 刹车
      DCMotor_1->run(BRAKE);
      DCMotor_2->run(BRAKE);
      DCMotor_3->run(BRAKE);
      DCMotor_4->run(BRAKE);
    }
    if(ps2x.ButtonPressed(PSB_SQUARE)){
      Serial.println("Square just released");
      DCMotor_1->setSpeed(speed_val);
      DCMotor_1->run(BACKWARD);
      DCMotor_2->setSpeed(speed_val);
      DCMotor_2->run(FORWARD);
      DCMotor_3->setSpeed(speed_val);
      DCMotor_3->run(BACKWARD);
      DCMotor_4->setSpeed(speed_val);
      DCMotor_4->run(FORWARD);
    }
    if(ps2x.ButtonPressed(PSB_TRIANGLE)){
      Serial.println("Triangle pressed");
      //右前方45°
      DCMotor_1->setSpeed(speed_val);
      DCMotor_1->run(FORWARD);
      DCMotor_2->run(BRAKE);
      DCMotor_3->run(BRAKE);
      DCMotor_4->setSpeed(speed_val);
      DCMotor_4->run(FORWARD);
      //左后方45°
  //    DCMotor_1->setSpeed(speed_val);
  //    DCMotor_1->run(BACKWARD);
  //    DCMotor_2->run(BRAKE);
  //    DCMotor_3->run(BRAKE);
  //    DCMotor_4->setSpeed(speed_val);
  //    DCMotor_4->run(BACKWARD);
      //左前方45°
  //    DCMotor_2->setSpeed(speed_val);
  //    DCMotor_2->run(FORWARD);
  //    DCMotor_1->run(BRAKE);
  //    DCMotor_4->run(BRAKE);
  //    DCMotor_3->setSpeed(speed_val);
  //    DCMotor_3->run(FORWARD);
      //右后方45°
  //    DCMotor_2->setSpeed(speed_val);
  //    DCMotor_2->run(BACKWARD);
  //    DCMotor_1->run(BRAKE);
  //    DCMotor_4->run(BRAKE);
  //    DCMotor_3->setSpeed(speed_val);
  //    DCMotor_3->run(BACKWARD);
    }
}
