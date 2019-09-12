#include "RGBLed.h"
RGBLed rgbled_A3(A1, 2);
void setup()
{
  rgbled_A3.setColor(1,0,0,255);
  rgbled_A3.setColor(2,255,0,0);
  rgbled_A3.show();
}

void loop()
{

}
