#ifndef   _PROTOCOLPARSER_H_
#define   _PROTOCOLPARSER_H_
#include "Arduino.h"
#include "Protocol.h"
#include <stdint.h>

#define BUFFER_SIZE 64
typedef byte (*p_read)(void);
typedef int (*p_write)(byte buf[], int);

class ProtocolParser
{
  public:
    ProtocolParser(byte startcode = PROTOCOL_START_CODE, byte endcode = PROTOCOL_END_CODE, p_read pread = NULL, p_write pwrite = NULL);
    ~ProtocolParser();
    bool RecevData(byte *data, size_t len);
    bool RecevData(void);
    bool ParserPackage(byte *data = NULL);

    int GetRobotSpeed(void);
    int GetRobotDegree(void);

    uint16_t GetBluetoothButton();
    bool GetBluetoothButton(uint16_t Button);
    void SendButton(uint16_t button);
    bool SendPackage(ST_PROTOCOL *send_dat, int len);
    void SendDirection(uint16_t degree);
    void SendSpeed(byte speed);
    uint8_t GetProtocolDataLength(void);
  private:
    p_read mRead;
    p_write mWrite;
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
