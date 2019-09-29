#include "Adafruit_NeoPixel.h"
#define RGB_PIN A1
#define MAX_LED 2  
 
int RGB1_val = 0;
int RGB2_val = 255;
bool trig_flag = false;
Adafruit_NeoPixel strip = Adafruit_NeoPixel( MAX_LED, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    strip.begin();  //default close all led
    strip.show();
    Serial.begin(9600);
}

void loop()
{
    // write 0 ~ 255  ~ 0 value to RGB1
    strip.setPixelColor(0, strip.Color(RGB1_val, 0, 0));
    // write 255 ~ 0 ~ 255 value to RGB2
    strip.setPixelColor(1, strip.Color(0, 0, RGB2_val));
    strip.show();
    if (trig_flag == 1) {
        RGB1_val--;
        RGB2_val++;
    } else {
        RGB1_val++;
        RGB2_val--;
    }
    if (RGB1_val >= 255 || RGB1_val <= 0 ) {
        trig_flag =  !trig_flag;
        Serial.print(trig_flag);
    }
     Serial.print(RGB1_val);
     Serial.print(" ");
    delay(30);
}
