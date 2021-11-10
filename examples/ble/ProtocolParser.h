#ifndef   _PROTOCOLPARSER_H_
#define   _PROTOCOLPARSER_H_
#include "Arduino.h"
#include "Protocol.h"
#include <stdint.h>
#include<stdint.h>

#define BUFFER_SIZE 32

typedef enum
{
    E_BLUETOOTH_CONTROL = 0,
    E_INFRARED_REMOTE_CONTROL,
    E_INFRARED_TRACKING_MODE,
    E_INFRARED_AVOIDANCE_MODE,
    E_ULTRASONIC_AVOIDANCE,
    E_PS2_REMOTE_CONTROL,
    E_NRF24L01_CONTROL,
    E_ULTRASONIC_INFRARED_AVOIDANCE,
    E_PIANO_MODE,
    E_RGB_MODE,
    E_LED_MAXTRIX_MODE,
    E_CMD_LINE_MODE,
    E_LIGHT_SEEKING_MODE,
    E_ULTRASONIC_FOLLOW_MODE,
    E_SMARTCAR_CONTROL_MAX,
} E_SMARTCAR_CONTROL_MODE;

typedef enum
{
    E_FORWARD = 0,
    E_BACK,
    E_LEFT,
    E_RIGHT,
    E_RIGHT_ROTATE,
    E_LEFT_ROTATE,
    E_STOP,
    E_RUNNING,
    E_SPEED_UP,
    E_SPEED_DOWN,
    E_LOW_POWER,
} E_SMARTCAR_STATUS;

class ProtocolParser
{
  public:
    ProtocolParser(byte header = PROTOCOL_START_CODE, byte end = PROTOCOL_END_CODE);
    ~ProtocolParser();
    bool RecevData(byte *data, size_t len);
    bool RecevData(void);
    bool ParserPackage(byte *data = NULL);
    E_TYPE GetRobotType(void);
    uint8_t GetRobotAddr(void);
    E_CONTOROL_FUNC GetRobotControlFun(void);
    int GetRobotSpeed(void);
    int GetRobotDegree(void);
    int GetServoDegree(void);
    int GetServoDegreeNum(void);
    uint16_t GetBluetoothButton();
    bool GetBluetoothButton(uint16_t Button);
//    E_BUZZER_TYPE GetBuzzerMode(void);
    uint16_t GetBuzzerNote(void);
    uint8_t GetBuzzerSound(void);
//    ST_MUSIC_TYPE GetBuzzerMusic(void);
    long GetRgbValue(void);
    byte GetRgbEffect(void);
    byte GetRgbMode(void);
    byte* GetCmdLine(void);
    bool SendPackage(ST_PROTOCOL *send_dat, int len);
    E_SMARTCAR_CONTROL_MODE GetControlMode(void);
    uint8_t GetProtocolDataLength(void);

  private:
    byte buffer[BUFFER_SIZE];
    byte m_StartCode, m_EndCode;
    ST_PROTOCOL *recv;
    uint8_t protocol_data_len;
    bool m_recv_flag, m_send_success;   // recevive flag
    byte *m_pHeader;                    // protocol header
    uint8_t m_PackageLength;            // recevie package length
    uint16_t m_CheckSum;
    uint8_t m_RecvDataIndex;            // get recevie data index
    char GetHeader(size_t index);
    uint8_t GetPackageLength(void);
    uint16_t GetCheckSum(void);             // get package check sum
};

#endif // _PROTOCOLPARSER_H_
