#include "Emakefun_MotorDriver.h"
#include "debug.h"
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_Sensor *ps2x;
//Emakefun_Sensor *Nrf = mMotorDriver.getSensor(E_NRF24L01);
Emakefun_Servo *mServo1 = mMotorDriver.getServo(1);
Emakefun_Servo *mServo2 = mMotorDriver.getServo(2);
Emakefun_Servo *mServo3 = mMotorDriver.getServo(3);
Emakefun_Servo *mServo4 = mMotorDriver.getServo(4);
Emakefun_Sensor *buzzer = mMotorDriver.getSensor(E_BUZZER);
static byte RightServo = 90;
static byte LeftServo = 110;
static byte PliersServo = 90;
static byte TurnServo = 90;

void setup()
{
  Serial.begin(9600);
  mMotorDriver.begin(50);
  ps2x = mMotorDriver.getSensor(E_PS2X);
  delay(500);
}

void loop()
{
  static int vibrate = 0;
  byte PSS_X = 0, PSS_Y = 0;
  ps2x->mPs2x->read_gamepad(false, vibrate); // read controller and set large motor to spin at 'vibrate' speed
  if (ps2x->mPs2x->ButtonDataByte()) {
    if (ps2x->mPs2x->Button(PSB_L2))
    {
      if (PliersServo < 145) {
        PliersServo += 1;
      } else {
        PliersServo = 145;
      }
    } else if (ps2x->mPs2x->Button(PSB_R2)) {
      if (PliersServo > 60) {
        PliersServo -= 1;
      } else {
        PliersServo = 60;
      }
    }
    delay(10);
    mServo4->writeServo(PliersServo);
  } else {
    uint16_t RightValue = ps2x->mPs2x->RightHart();
    uint16_t LeftValue = ps2x->mPs2x->LeftHart();
    if (LeftValue <= 360)
    {
      if ((90 < LeftValue) && (LeftValue <= 270))
      {
        if (TurnServo < 180) { 
          TurnServo += 1;
        } else {
          TurnServo = 180;
        }
      } else if ((270 < LeftValue) && (LeftValue <= 360) || (0 <= LeftValue) && (LeftValue <= 90)) {
        if (TurnServo != 0) {
          TurnServo -= 1;
        } else {
          TurnServo = 0;
        }
      }
      if ((TurnServo <= 180) && (TurnServo >= 0)) {
        mServo1->writeServo(TurnServo);
      }
    } else if (RightValue <= 360) {
      if ((45 <= RightValue) && (RightValue < 135)) {
        if ((RightServo < 140)) {
          RightServo += 3;
        } 
      } else if ((225 <= RightValue) && (RightValue < 315)) {
        if (((RightServo != 0) && (100 < LeftServo)) && (RightServo > 60)) {
          RightServo -= 3;
        } else if (RightServo == 0) {
          RightServo = 0;
        } else {
          buzzer->Sing(S_connection);
        }
      }  else if ((135 <= RightValue) && (RightValue < 225)) {
        if (LeftServo < 180) {
          LeftServo += 3;
        } else {
          LeftServo = 180;
        }
      } else if ((225 <= RightValue <= 360) && (0 <= RightValue < 45)) {
        if (LeftServo >= 92) {
          LeftServo -= 3;
        } else {
          LeftServo = 90;
        }
      }
      delay(10);
      Serial.println(RightServo);
      if ((RightServo != 140) && (RightServo != 0)) {
        mServo2->writeServo(RightServo);
      } if ((LeftServo != 180) && (90 != LeftServo)) {
        mServo3->writeServo(LeftServo);
      }
    }
    delay(20);
  }
}
