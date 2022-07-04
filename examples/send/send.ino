#include "SerialJsonMessage.h"

SerialJsonMessage sendJson;

void setup() {
  Serial.begin(115200);
  sendJson.begin(Serial);
  
  sendJson.setValue("BoolValue",true);
  sendJson.setValue("IntValue",128);
  sendJson.setValue("FloatValue",3.14);
  sendJson.setValue("StringValue",(String)"abcdef");

  sendJson.send();
}

void loop(){

}