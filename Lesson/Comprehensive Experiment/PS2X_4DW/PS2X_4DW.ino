#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_Sensor *ps2x;
Emakefun_Sensor *rgb = mMotorDriver.getSensor(E_RGB);
Emakefun_DCMotor *DCMotor_1 = mMotorDriver.getMotor(1);
Emakefun_DCMotor *DCMotor_2 = mMotorDriver.getMotor(2);
Emakefun_DCMotor *DCMotor_3 = mMotorDriver.getMotor(3);
Emakefun_DCMotor *DCMotor_4 = mMotorDriver.getMotor(4);
Emakefun_Sensor *buzzer = mMotorDriver.getSensor(E_BUZZER);
static uint8_t Speed = 100;

void setup()
{
  Serial.begin(9600);
  mMotorDriver.begin(50);
  ps2x = mMotorDriver.getSensor(E_PS2X);
}

void loop()
{
  static int vibrate = 0;
  byte PSS_X = 0, PSS_Y = 0;
  ps2x->mPs2x->read_gamepad(false, vibrate); // read controller and set large motor to spin at 'vibrate' speed
  if (ps2x->mPs2x->ButtonDataByte()) {
    if (ps2x->mPs2x->Button(PSB_PAD_UP)) {     //will be TRUE as long as button is pressed
      rgb->SetRgbColor(E_RGB_ALL, RGB_WHITE);
      DCMotor_1->setSpeed(Speed);
      DCMotor_2->setSpeed(Speed);
      DCMotor_3->setSpeed(Speed);
      DCMotor_4->setSpeed(Speed);
      DCMotor_1->run(1);
      DCMotor_2->run(1);
      DCMotor_3->run(1);
      DCMotor_4->run(1);
      rgb->SetRgbColor(E_RGB_ALL, RGB_WHITE);
    }
    if (ps2x->mPs2x->Button(PSB_PAD_RIGHT)) {
      DCMotor_1->setSpeed(Speed);
      DCMotor_2->setSpeed(Speed);
      DCMotor_3->setSpeed(Speed);
      DCMotor_4->setSpeed(Speed);
      DCMotor_1->run(2);
      DCMotor_2->run(1);
      DCMotor_3->run(2);
      DCMotor_4->run(1);
      rgb->SetRgbColor(E_RGB_RIGHT, RGB_WHITE);
      Serial.println("PSB_PAD_RIGHT");
    }
    if (ps2x->mPs2x->Button(PSB_PAD_LEFT)) {
      rgb->SetRgbColor(E_RGB_LEFT, RGB_WHITE);
      DCMotor_1->setSpeed(Speed);
      DCMotor_2->setSpeed(Speed);
      DCMotor_3->setSpeed(Speed);
      DCMotor_4->setSpeed(Speed);
      DCMotor_1->run(1);
      DCMotor_2->run(2);
      DCMotor_3->run(1);
      DCMotor_4->run(2);
      Serial.println("PSB_PAD_LEFT");
    }
    if (ps2x->mPs2x->Button(PSB_PAD_DOWN)) {
      DCMotor_1->setSpeed(Speed);
      DCMotor_2->setSpeed(Speed);
      DCMotor_3->setSpeed(Speed);
      DCMotor_4->setSpeed(Speed);
      DCMotor_1->run(2);
      DCMotor_2->run(2);
      DCMotor_3->run(2);
      DCMotor_4->run(2);
      rgb->SetRgbColor(E_RGB_ALL, RGB_RED);
    }
    vibrate = ps2x->mPs2x->Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
    if (ps2x->mPs2x->Button(PSB_CROSS)) {             //will be TRUE if button was JUST pressed OR released
      buzzer->Sing(S_disconnection);
      if (Speed >= 20)
        Speed -= 20;
      else
        Speed = 0;
      rgb->SetRgbColor(E_RGB_ALL, Speed * 2.5);
      Serial.println("PSB_CROSS");
    }
    if (ps2x->mPs2x->Button(PSB_TRIANGLE)) {
      buzzer->Sing(S_connection);
      if (Speed <= 230)
        Speed += 20;
      else
        Speed = 255;
      rgb->SetRgbColor( E_RGB_ALL, Speed * 2.5);
      Serial.println("PSB_TRIANGLE");
    }
    if (ps2x->mPs2x->Button(PSB_CIRCLE)) {
      DCMotor_1->setSpeed(Speed);
      DCMotor_2->setSpeed(Speed);
      DCMotor_3->setSpeed(Speed);
      DCMotor_4->setSpeed(Speed);
      DCMotor_1->run(2);
      DCMotor_2->run(1);
      DCMotor_3->run(2);
      DCMotor_4->run(1);
      rgb->SetRgbColor(E_RGB_LEFT, RGB_BLUE);
      Serial.println("PSB_CIRCLE");
    }
    if (ps2x->mPs2x->Button(PSB_SQUARE)) {
      DCMotor_1->setSpeed(Speed);
      DCMotor_2->setSpeed(Speed);
      DCMotor_3->setSpeed(Speed);
      DCMotor_4->setSpeed(Speed);
      DCMotor_1->run(1);
      DCMotor_2->run(2);
      DCMotor_3->run(1);
      DCMotor_4->run(2);
      rgb->SetRgbColor(E_RGB_RIGHT, RGB_WHITE);
      Serial.println("PSB_SQUARE");
    }
  } else {
    DCMotor_1->setSpeed(0);
    DCMotor_1->run(3);
    DCMotor_2->setSpeed(0);
    DCMotor_2->run(3);
    DCMotor_3->setSpeed(0);
    DCMotor_3->run(3);
    DCMotor_4->setSpeed(0);
    DCMotor_4->run(3);
    rgb->SetRgbColor(E_RGB_ALL, RGB_WHITE);
  }
  delay(50);
}
