#include "IRremote.h"
#define IR_PIN 8

IRremote ir(IR_PIN);
unsigned char keycode;
char str[128];
void setup()
{
  Serial.begin(9600);
  ir.begin();
}

void loop()
{
  if (keycode = ir.getCode()) {
    String key_name = ir.getKeyMap(keycode);
    sprintf(str, "Get ir code: 0x%x key name: %s \n", keycode, (char *)key_name.c_str());
    Serial.println(str);
  } else {
    //   Serial.println("no key");
  }
  delay(110);
}
