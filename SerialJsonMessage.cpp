#include "SerialJsonMessage.h"

void SerialJsonMessage::begin(Stream &stream,unsigned long recvTimeOut) {
    _serial = &stream;
    clerRecvBuffer();
    _beforTime = millis();
    _recvTimeOut = recvTimeOut;
}

void SerialJsonMessage::setValue(String key,bool value) {
    _send_buff[key] = value;
}

void SerialJsonMessage::setValue(String key,int value) {
    _send_buff[key] = value;
}

void SerialJsonMessage::setValue(String key,float value) {
    _send_buff[key] = value;
}

void SerialJsonMessage::setValue(String key,double value) {
    float _value = (float)value;
    _send_buff[key] = _value;
}

void SerialJsonMessage::setValue(String key,String value) {
    _send_buff[key] = value;
}

void SerialJsonMessage::setValue(String key,char* value) {
    _send_buff[key] = value;
}

void SerialJsonMessage::send() {
    if(!_send_buff.isNull()) {
        String output;
        serializeJson(_send_buff, output);
        _serial->println(output);
        _send_buff.clear();
    }
}

bool SerialJsonMessage::recv() {
    bool ret = false;
    if(_serial->available()) {
        unsigned long time = millis();
        if(time >= (_beforTime + _recvTimeOut)){
            clerRecvBuffer();
        }
        while(_serial->available() && _recvBufferCount < BUFFER_SIZE) {
            _recvBuffer[_recvBufferCount++] = _serial->read();
        }
        DeserializationError error = deserializeJson(_recv_buff, _recvBuffer);

        if(!error) {
            ret = true;
        }
        _beforTime = millis();
    }
    return ret;
}

bool SerialJsonMessage::getValueBool(String key) {
    return (bool)_recv_buff[key];
}

int SerialJsonMessage::getValueInt(String key) {
    return (int)_recv_buff[key];
}

float SerialJsonMessage::getValueFloat(String key) {
    return (float)_recv_buff[key];
}

String SerialJsonMessage::getValueString(String key) {
    return (String)_recv_buff[key];
}

void SerialJsonMessage::clerRecvBuffer() {
    _recvBufferCount = 0;
    memset( _recvBuffer , 0 , BUFFER_SIZE);
    _recv_buff.clear();
}