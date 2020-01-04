#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver(0x60, MOTOR_DRIVER_BOARD_V5);
Emakefun_Sensor *buzzer = mMotorDriver.getSensor(E_SENSOR_MAX);

void setup()
{
    Serial.begin(9600);
    mMotorDriver.getSensor(E_BUZZER);
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
