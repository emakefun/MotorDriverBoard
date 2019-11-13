#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_Sensor *buzzer = mMotorDriver.getSensor(E_BUZZER);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
   buzzer->Sing(S_connection);
   delay(1000);
   buzzer->Sing(S_disconnection);
   delay(1000);
   buzzer->Sing(S_buttonPushed);
   delay(1000);
   buzzer->Sing(S_surprise);
   delay(1000);
   buzzer->Sing(S_happy);
   delay(1000);
   buzzer->Sing(S_sad);
   delay(1000);
}
