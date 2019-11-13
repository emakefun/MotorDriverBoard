#include "RGBLed.h"

const int RgbPin = A1;
RGBLed mRgb(RgbPin, 2);

void setup() {
    Serial.begin(9600);
    Serial.println("RGB Test");
    mRgb.SetRgbColor(E_RGB_RIGHT, RGB_ORANGE);
    mRgb.SetRgbColor(E_RGB_LEFT, RGB_PURPLE);
    delay(1000);
}

void loop() {
    mRgb.setBrightness(10);
    mRgb.SetRgbColor(E_RGB_ALL, RGB_RED);
    delay(1000);
    mRgb.setBrightness(50);
    mRgb.SetRgbColor(E_RGB_ALL, RGB_GREEN);
    delay(1000);
    mRgb.setBrightness(100);
    mRgb.SetRgbColor(E_RGB_ALL, RGB_BLUE);
    delay(1000);
    mRgb.setBrightness(150);
    mRgb.SetRgbColor(E_RGB_ALL, RGB_YELLOW);
    delay(1000);
    mRgb.setBrightness(250);
    mRgb.SetRgbColor(E_RGB_ALL, RGB_WHITE);
    delay(1000);
    mRgb.setBrightness(255);
    mRgb.SetRgbColor(E_RGB_ALL, RGB_BLACK);
    delay(1000);
}
