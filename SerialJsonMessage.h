#include <Arduino.h>
#include <ArduinoJson.h>
#include <string>

#define BUFFER_SIZE 256
#define RECV_TIMEOUT_MS 100

class SerialJsonMessage{
public:
    void begin(Stream &stream,unsigned long recvTimeOut = RECV_TIMEOUT_MS);
    void setValue(String key,bool value);
    void setValue(String key,int value);
    void setValue(String key,float value);
    void setValue(String key,double value);
    void setValue(String key,String value);
    void setValue(String key,char* value);
    void send();
    bool recv();
    bool getValueBool(String key);
    int getValueInt(String key);
    float getValueFloat(String key);
    String getValueString(String key);

private:
    Stream *_serial;
    StaticJsonDocument<BUFFER_SIZE> _send_buff;
    StaticJsonDocument<BUFFER_SIZE> _recv_buff;
    int _recvBufferCount;
    char _recvBuffer[BUFFER_SIZE];
    unsigned long _beforTime;
    unsigned long _recvTimeOut;
    void clerRecvBuffer();
};
