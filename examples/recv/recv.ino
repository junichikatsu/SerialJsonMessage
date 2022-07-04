#include "SerialJsonMessage.h"

SerialJsonMessage recvJson;

void setup() {
  Serial.begin(115200);
  recvJson.begin(Serial);
}

void loop() {
  // test data { "BoolValue":true, "IntValue":128, "FloatValue":3.14, "StringValue":"abcdef" }
  if(recvJson.recv()){
      Serial.println("JSON Recived");
      bool b = recvJson.getValueBool("BoolValue");
      int i = recvJson.getValueInt("IntValue");
      float f = recvJson.getValueFloat("FloatValue");
      String s = recvJson.getValueString("StringValue");
      Serial.print("BoolValue:");
      Serial.println(b==true ? "true" : "false");
      Serial.print("IntValue:");
      Serial.println(i);
      Serial.print("FloatValue:");
      Serial.println(f);
      Serial.print("StringValue:");
      Serial.println(s);
  }
  delay(100);
}