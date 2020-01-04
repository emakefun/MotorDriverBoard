#ifndef _WIRELESS_HANDLE_H_
#define _WIRELESS_HANDLE_H_
#include "Arduino.h"
#include "Protocol.h"
#include "ProtocolParser.h"
#include "Wire.h"
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"
#include "nRF24L01.h"

#define BUTTON_BIT_BMASK 0b00000001
#define BUTTON_BIT_CMASK 0b00001001
#define BUTTON_BIT_DMASK 0b11111100

//These are our button constantst
#define BT_SELECT      0x0100
#define BT_START       0x0002
#define BT_L1          0x0080 
#define BT_R1          0x0040 
#define BT_PAD_DOWN    0x0020
#define BT_PAD_LEFT    0x0010
#define BT_PAD_UP      0x0008
#define BT_PAD_RIGHT   0x0004

#define PIN_ANALOG_X A6
#define PIN_ANALOG_Y A7
#define BT_X 1
#define BT_Y 2
#define BT_Z 3


#define MODE_GREEN_LED A2
#define SELEC_BLUE_LED A1

#define NRF24L01_CE 10
#define NRF24L01_CSN 9

typedef enum {
    E_BLUTOOTH_MODE = 0,
    E_NRF24L01_MODE,
    E_WIFI_MODE
} E_CONTROL_MODE;

typedef enum {
    E_WIRELESS_CONTROL_MODE = 0,
    E_GRAVITY_CONTROL_MODE,
} E_CONTROL_SELECT;

struct RAW_type {
    uint8_t x;
    uint8_t y;
    uint8_t z;
};

class WirelessHandle {
  private :
    E_CONTROL_MODE control_mode;
    E_CONTROL_SELECT control_select;

    MPU6050 accelgyro;
    float roll = 0, pitch = 0, yaw = 0;
    float RwAcc[3], Gyro[3];            // ACC raw data
    float RwGyro[3], Awz[2], RwEst[3];  // Gyro raw dat
    float tmpf = 0.0;
    int signRzGyro;
    uint32_t currentTime = 0, lastTime = 0, interval = 0;
    const float pi = 3.1415926;
    const float Rad = 57.3;             //180.0/pi;
    const float wGyro = 10.0;
    const float AcceRatio = 16384.0;
    const float GyroRatio = 131.0 * 57.3;

    int16_t ax, ay, az, gx, gy, gz;
    struct RAW_type accel_zero_offsent, gyro_zero_offsent;

    volatile uint8_t *Bbutton_reg, *Bmode_reg, *Cbutton_reg, *Cmode_reg, *Dbutton_reg, *Dmode_reg;
    uint16_t last_buttons, buttons;
    uint16_t buttonsB, buttonsC, buttonsD;

  public :
    Nrf24l *mNrf24L01;
    ProtocolParser *mProtocolPackage;
    WirelessHandle(E_CONTROL_MODE mode);
    void SetControlMode(E_CONTROL_MODE mode);
    E_CONTROL_MODE GetControlMode(void);
    void SetControlSelect(E_CONTROL_SELECT mode);
    E_CONTROL_SELECT GetControlSelect(void);
    boolean Button(uint16_t);                //will be TRUE if button is being pressed
    unsigned int ButtonDataByte();
    boolean NewButtonState();
    boolean NewButtonState(uint16_t);       //will be TRUE if button was JUST pressed OR released
    boolean ButtonPressed(uint16_t);        //will be TRUE if button was JUST pressed
    boolean ButtonReleased(uint16_t);       //will be TRUE if button was JUST released
    uint16_t ScanKeyPad(void);
    int Analog(byte);
    float GetGravity(byte direction);
    void normalize3DVec(float vector[3]);
    float squared(float x);
    void readSensors(void);
    void getInclination(void);
    float GetRoll(void);
    float GetPitch(void);
    int GetDegree(void);
    void InitMpu6050(void);
    void InitNrf24l01(byte CE, byte CSN);
};
#endif
