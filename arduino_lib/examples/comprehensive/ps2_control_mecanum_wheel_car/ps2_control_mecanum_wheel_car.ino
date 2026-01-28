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
int speed_val = 100;
int LY, LX;
void SetSpeed(int s)
{
    if (s >= 255) {
        speed_val = 255;
        return;
    } else if (s <= 0) {
        speed_val = 0;
        return;
    }
    speed_val = s;
}

int GetSpeed(void)
{
    return speed_val;
}

void SpeedUp(int Duration)
{
    SetSpeed(speed_val + Duration);
}

void SpeedDown(int Duration )
{
    SetSpeed(speed_val - Duration);
}

void Ps2Scan(void)
{
  static char count = 0;
  if (count++ > 20)
  {
   // ps2x.reconfig_gamepad();
    count = 0;
  }
  ps2x.read_gamepad();
  LY = ps2x.Analog(PSS_LY);
  LX = ps2x.Analog(PSS_LX);
}


void setup()
{
  Serial.begin(115200);
  mMotor.begin(50);
  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  MsTimer2::set(50, Ps2Scan);
  MsTimer2::start();
}

void loop()
{
 // ps2x.read_gamepad(); //read controller and set large motor to spin at 'vibrate' speed
  if (ps2x.NewButtonState() == false) {
    if (ps2x.Button(PSB_L1)) {
      Serial.print("Speed up");
      SpeedUp(5);
      Serial.println(GetSpeed());
    }
    if (ps2x.Button(PSB_R1)) {
      Serial.print("Speed donn");
      SpeedDown(5);
      Serial.println(GetSpeed());
    }
    if (ps2x.Button(PSB_PAD_UP) && !ps2x.Button(PSB_PAD_LEFT) && !ps2x.Button(PSB_PAD_RIGHT)) {
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
    } else if (ps2x.Button(PSB_PAD_LEFT) && !ps2x.Button(PSB_PAD_UP) && !ps2x.Button(PSB_PAD_DOWN)){
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
    } else if (ps2x.Button(PSB_PAD_RIGHT) && !ps2x.Button(PSB_PAD_UP) && !ps2x.Button(PSB_PAD_DOWN)){
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
    } else if (ps2x.Button(PSB_PAD_DOWN) && !ps2x.Button(PSB_PAD_LEFT) && !ps2x.Button(PSB_PAD_RIGHT)) {
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
    } else if (ps2x.Button(PSB_PINK)) {  // 右边 紫色色按键
      Serial.println("PINK just pressed");
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
    } else if (ps2x.Button(PSB_RED)) {  //右边 红色按键
      //顺时针
       Serial.println("RED just pressed");
      DCMotor_1->setSpeed(speed_val);
      DCMotor_1->run(BACKWARD);
      DCMotor_2->setSpeed(speed_val);
      DCMotor_2->run(FORWARD);
      DCMotor_3->setSpeed(speed_val);
      DCMotor_3->run(BACKWARD);
      DCMotor_4->setSpeed(speed_val);
      DCMotor_4->run(FORWARD);
    }
    if (ps2x.Button(PSB_PAD_UP) && ps2x.Button(PSB_PAD_RIGHT)) {
      Serial.println("UP and RIHT");
      //右前方45°
      DCMotor_1->setSpeed(speed_val);
      DCMotor_1->run(FORWARD);
      DCMotor_2->run(BRAKE);
      DCMotor_3->run(BRAKE);
      DCMotor_4->setSpeed(speed_val);
      DCMotor_4->run(FORWARD);
    } else if (ps2x.Button(PSB_PAD_LEFT) && ps2x.Button(PSB_PAD_DOWN)) {
      //左后方45°
      Serial.println("LEFT and DOWN");
      DCMotor_1->setSpeed(speed_val);
      DCMotor_1->run(BACKWARD);
      DCMotor_2->run(BRAKE);
      DCMotor_3->run(BRAKE);
      DCMotor_4->setSpeed(speed_val);
      DCMotor_4->run(BACKWARD);
      
    } else if (ps2x.Button(PSB_PAD_UP) && ps2x.Button(PSB_PAD_LEFT)) {
      Serial.println("LEFT and UP");
      //左前方45°
      DCMotor_2->setSpeed(speed_val);
      DCMotor_2->run(FORWARD);
      DCMotor_1->run(BRAKE);
      DCMotor_4->run(BRAKE);
      DCMotor_3->setSpeed(speed_val);
      DCMotor_3->run(FORWARD);
    } else if (ps2x.Button(PSB_PAD_RIGHT) && ps2x.Button(PSB_PAD_DOWN)) {
      Serial.println("RIGHT and DOWN");
      //右后方45°
      DCMotor_2->setSpeed(speed_val);
      DCMotor_2->run(BACKWARD);
      DCMotor_1->run(BRAKE);
      DCMotor_4->run(BRAKE);
      DCMotor_3->setSpeed(speed_val);
      DCMotor_3->run(BACKWARD);
    }
  } else {
    DCMotor_1->run(BRAKE);
    DCMotor_2->run(BRAKE);
    DCMotor_3->run(BRAKE);
    DCMotor_4->run(BRAKE);  
  }
    delay(50);
}
