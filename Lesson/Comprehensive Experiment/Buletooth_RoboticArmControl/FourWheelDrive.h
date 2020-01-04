#ifndef _FourWheelDrive_H_
#define _FourWheelDrive_H_
#include <stdint.h>
#include "SPI.h"
#include "Arduino.h"
#include "SmartCar.h"
#include "Emakefun_MotorDriver.h"
#include "ProtocolParser.h"

#define FRONT 0
#define LEFT 1
#define RIGHT 2
#define MIDDLE 3

#define MECANUMCAR 0

typedef enum
{
  E_EFFECT_BREATHING = 0,
  E_EFFECT_ROTATE = 1,
  E_EFFECT_FLASH = 2
} E_RGB_EFFECT;

class FourWheelDrive: public SmartCar {

  private :
    byte ServoPin;
    uint8_t BatteryPin;
    uint8_t ServoBaseDegree;
    ST_PROTOCOL SendData;
    ProtocolParser *mProtocolPackage;
    void DriveSpeed(int s);

  public :
    Emakefun_MotorDriver MotorDriver;
    Emakefun_DCMotor *LeftFoward, *RightFoward, *LeftBackward, *RightBackward;
    IRremote *IR;
    Buzzer *Buzzer;
    RGBLed *Rgb;
    Emakefun_Sensor *Sensors;
    PS2X *Ps2x;
    Nrf24l *Nrf24L01;
    Emakefun_Servo *mServo1, *mServo2, *mServo3, *mServo4, *mServo5, *mServo6;
    FourWheelDrive(ProtocolParser *Package);
    ~FourWheelDrive(void);
    void Move(int directions);
    void init(int leftward, int rightfoward, int leftbackward, int rightbackward);
    void GoForward(void);
    void GoBack(void);
    void TurnLeft(void);
    void TurnRight(void);
    void TurnLeftRotate(void);
    void TurnRightRotate(void);
    void KeepStop(void);
    void Drive(void);
    void Drive(int degree);
    void InitIr(void);
    int GetIrKey(void);
    void InitBuzzer(void);
    void sing(byte songName);
    void PianoSing(ST_MUSIC_TYPE music);
    void InitRgb(void);
    void SetRgbColor(E_RGB_INDEX index , long Color);
    void LightOff(void);
    void InitUltrasonic(void);
    byte GetUltrasonicValue(byte);
    void InitServo(void);
    void SetServoBaseDegree(uint8_t base);
    void SetServoDegree(byte pin, byte Angle);
    void InitPs2x(void);
    int GetPs2xKeyValue(void);
    uint16_t GetPs2xRockerAngle(byte);
    void SendUltrasonicData(void);
    void InitNrf24L01(char *Rxaddr);
};

#endif  /* _AURORARACING_H_ */
