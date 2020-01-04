
#define BUZZER_PIN A0 //buzzer pin A0
#define RGB A1      //RGB pin A1

#define Do 262
#define Re 294
#define Mi 330
#define Fa 349
#define Sol 392
#define La 440
#define Si 494
#define Do_h 523
#define Re_h 587
#define Mi_h 659
#define Fa_h 698
#define Sol_h 784
#define La_h 880
#define Si_h 988
#include "RGBLed.h"

RGBLed rgbled_A3(RGB, 2);
int length;
// happy birthday Music score
int scale[] = {Sol, Sol, La, Sol, Do_h, Si, Sol, Sol,
               La, Sol, Re_h, Do_h, Sol, Sol, Sol_h, Mi_h,
               Do_h, Si, La, Fa_h, Fa_h, Mi_h, Do_h, Re_h, Do_h
              };

// Beats time
float durt[] =
{
  0.5, 0.5, 1, 1, 1, 1 + 1, 0.5, 0.5,
  1, 1, 1, 1 + 1, 0.5, 0.5, 1, 1,
  1, 1, 1, 0.5, 0.5, 1, 1, 1, 1 + 1
};


void setup()
{
  pinMode(BUZZER_PIN, OUTPUT);
  // get scale length
  length = sizeof(scale) / sizeof(scale[0]);
  Serial.begin(9600);
}

void loop()
{
  for (int x = 0; x < length; x++) {
    // Serial.println(scale[x]);
    tone(BUZZER_PIN, scale[x]);
    rgbled_A3.setColor(1, scale[x] - 425, scale[x] - 500, scale[x] - 95);
    rgbled_A3.setColor(2, scale[x] - 425, scale[x] - 500, scale[x] - 95);
    rgbled_A3.show();
    // 1= 3/4F so one Beats is  187*4 = 748ms
    delay(748 * durt[x]);
    noTone(BUZZER_PIN);
  }
  delay(3000);
}
