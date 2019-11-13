#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
PS2X *ps2x;
RGBLed *rgb;

void setup()
{
    Serial.begin(9600);
    ps2x = mMotorDriver.getSensor(E_PS2X);
    rgb = mMotorDriver.getSensor(E_RGB);
}

void loop()
{
  static int vibrate = 0;
  byte PSS_X = 0, PSS_Y = 0;
  ps2x->read_gamepad(false, vibrate); // read controller and set large motor to spin at 'vibrate' speed
  if (ps2x->ButtonDataByte()) {
    if (ps2x->Button(PSB_PAD_UP)) {     //will be TRUE as long as button is pressed
      rgb->SetRgbColor(E_RGB_ALL, RGB_WHITE);
      Serial.println("PSB_PAD_UP");
    }
    if (ps2x->Button(PSB_PAD_RIGHT)) {
      Serial.println("PSB_PAD_RIGHT");
      rgb->SetRgbColor(E_RGB_RIGHT, RGB_WHITE);
    }
    if (ps2x->Button(PSB_PAD_LEFT)) {
      rgb->SetRgbColor(E_RGB_LEFT, RGB_WHITE);
      Serial.println("PSB_PAD_LEFT");
    }
    if (ps2x->Button(PSB_PAD_DOWN)) {
      rgb->SetRgbColor(E_RGB_ALL, RGB_RED);
      Serial.println("PSB_PAD_DOWN");
    }
    vibrate = ps2x->Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
    if (ps2x->Button(PSB_CROSS)) {             //will be TRUE if button was JUST pressed OR released
      rgb->SetRgbColor(E_RGB_LEFT, RGB_GREEN);
      Serial.println("PSB_CROSS");
    }
    if (ps2x->Button(PSB_TRIANGLE)) {
      rgb->SetRgbColor(E_RGB_RIGHT, RGB_GREEN);
      Serial.println("PSB_TRIANGLE");
    }
    if (ps2x->Button(PSB_CIRCLE)) {
      rgb->SetRgbColor(E_RGB_LEFT, RGB_BLUE);
      Serial.println("PSB_CIRCLE");
    }
    if (ps2x->Button(PSB_SQUARE)) {
      rgb->SetRgbColor(E_RGB_RIGHT, RGB_BLUE);
      Serial.println("PSB_SQUARE");
    }
    if (ps2x->Button(PSB_L1) || ps2x->Button(PSB_R1)) {
      Serial.print("Stick Values:");
      Serial.print(ps2x->Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
      Serial.print(",");
      Serial.print(ps2x->Analog(PSS_LX), DEC); 
      Serial.print(",");
      Serial.print(ps2x->Analog(PSS_RY), DEC); 
      Serial.print(",");
      Serial.println(ps2x->Analog(PSS_RX), DEC); 
    }
  } 
  delay(50);
}
