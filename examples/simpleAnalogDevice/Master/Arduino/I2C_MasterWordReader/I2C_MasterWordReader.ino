// I2C Master Reader for Arduino (UNO or Pro Micro)
// License CC by 4.0 2016 D.F.Mac.
#include "Wire.h"

#define I2CSLAVE_ADDR 0x30

#define LED_PIN 13 // For UNO D13
// #define LED_PIN 15 // For Pro Micro D15

void setup() {
  Wire.begin();
  Serial.begin(19200);
  pinMode(LED_PIN,OUTPUT);
}

uint8_t flg = 0;
uint16_t val = 0;
int cnt = 0;

void loop() {
  Wire.requestFrom(I2CSLAVE_ADDR, 2);
  val = 0;
  cnt = 0;
  while (Wire.available()) {
    uint16_t c = Wire.read();    // receive 2byte data
    if(cnt == 1){
      c <<= 8;
    }
    val |= c;
    cnt++;
  }
  Serial.println(val,DEC);      // print the number

  flg ^= 1;
  if(flg){
    digitalWrite(LED_PIN,HIGH);
  }else{
    digitalWrite(LED_PIN,LOW);
  }
  delay(100);
}
