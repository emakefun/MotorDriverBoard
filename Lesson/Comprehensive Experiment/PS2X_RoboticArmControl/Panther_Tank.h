#ifndef _PANTHER_TANK_H_
#define _PANTHER_TANK_H_
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
typedef enum
{
  E_EFFECT_BREATHING = 0,
  E_EFFECT_ROTATE = 1,
  E_EFFECT_FLASH = 2
} E_RGB_EFFECT;



class Tank: public SmartCar {

  private :
    byte ServoPin;
    uint8_t BatteryPin;
    uint8_t ServoBaseDegree;
    ST_PROTOCOL SendData;
    ProtocolParser *mProtocolPackage;

  public :
    Emakefun_MotorDriver *mMotorDriver;
    Emakefun_DCMotor *DCMotor_1;
    Emakefun_DCMotor *DCMotor_2;
    Emakefun_DCMotor *DCMotor_3;
    Emakefun_DCMotor *DCMotor_4;
    Emakefun_Sensor *IR;
    Emakefun_Sensor *Buzzer;
    Emakefun_Sensor *Rgb;
    Emakefun_Sensor *UT;
    Emakefun_Sensor  *Ps2x;
    Emakefun_Sensor *Nrf;
    Emakefun_Servo *mServo1, *mServo2, *mServo3, *mServo4, *mServo5, *mServo6;
    Tank(ProtocolParser *Package);
    ~Tank(void);
    void Move(int directions);
    void init(void);
    void SetSpeed(int s);
    void GoForward(void);
    void GoBack(void);
    void TurnLeft(void);
    void TurnRight(void);
    void LeftLateral(void);
    void RightLateral(void);
    void KeepStop(void);
    void Drive(void);
    void Drive(int degree);
    void InitIrPin(void);
    int GetIrKey(void);
    void InitBuzzerPin(void);
    void sing(byte songName);
    void PianoSing(ST_MUSIC_TYPE music);
    void InitRgbPin(void);
    void SetRgbColor(E_RGB_INDEX index , long Color);
    void LightOff(void);
    void SetRgbEffect(E_RGB_INDEX index, long Color, uint8_t effect);
    void InitUltrasonicPin(void);
    byte GetUltrasonicValue(byte);
    void InitServoPin(void);
    void SetServoBaseDegree(uint8_t base);
    void SetServoDegree(byte pin, byte Angle);
    void InitPs2xPin(void);
    int GetPs2xKeyValue(void);
    uint16_t GetPs2xRockerAngle(byte);
    //void SetBatteryCheckPin(uint8_t pin);
    //uint16_t GetBatteryValue(void);
    //void SendBatteryPackage(uint16_t battery_value);
    void SendUltrasonicData(void);
    //    void SendUltrasonicData();
    //    void PianoSing(ST_MUSIC_TYPE music);
    //    int SetPs2xPin(uint8_t clk = TA_PS2X_CLK, uint8_t cmd = TA_PS2X_CMD, uint8_t att = TA_PS2X_CS, uint8_t dat = TA_PS2X_DAT);
    //    int ResetPs2xPin(void);
    //    void SetBatteryCheckPin(uint8_t pin);
    //    uint16_t GetBatteryValue(void);
    //    void SendBatteryPackage(uint16_t battery_value);
    //    void SendVersionPackage(void);

    //    void SetUltrasonicPin(uint8_t Trig_Pin = TA_TRIG_PIN, uint8_t Echo_Pin = TA_ECHO_PIN, uint8_t Sevo_Pin = TA_SERVO_PIN);
    //    #if (EM_MOTOR_SHIELD_BOARD_VERSION > 2)
    //    void SetNRF24L01Pin(uint8_t CE_Pin = TA_CE_PIN, uint8_t CSN_Pin = TA_CSN_PIN);
    //    void InitNrf24L01(char *Raddr);
    //    int  GetNrf24L01(void);
    //    #endif
};

#endif  /* _AURORARACING_H_ */
