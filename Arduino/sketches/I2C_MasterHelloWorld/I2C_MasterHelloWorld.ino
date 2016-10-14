#include "Wire.h"

#define I2CSLAVE_ADDR 0x30

void setup() {
  Wire.begin();
  pinMode(13,OUTPUT);
}

uint8_t flg = 0;

void loop() {
  Wire.beginTransmission(I2CSLAVE_ADDR);
  Wire.write(1);
  Wire.endTransmission();
  flg ^= 1;
  if(flg){
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
  }
  delay(1000);
}
