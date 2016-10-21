// I2C Master Writer for Arduino (UNO or Pro Micro)
// License CC by 4.0 2016 D.F.Mac.
#include "Wire.h"

#define I2CSLAVE_ADDR 0x30

#define LED_PIN 13 // For UNO D13
// #define LED_PIN 15 // For Pro Micro D15

void setup() {
  Wire.begin();
  pinMode(LED_PIN,OUTPUT);
}

uint8_t flg = 0;

void loop() {
  Wire.beginTransmission(I2CSLAVE_ADDR);
  Wire.write(flg);
  Wire.endTransmission();
  flg ^= 1;
  if(flg){
    digitalWrite(LED_PIN,HIGH);
  }else{
    digitalWrite(LED_PIN,LOW);
  }
  delay(1000);
}
