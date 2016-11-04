// Canzasi_I2CAnalogDevice
// multi functional Analog Device
//   
// with https://github.com/SpenceKonde/ATTinyCore
// 
// License CC by 4.0 2016 D.F.Mac.
//
//                   +----+
//                VCC|    |GND
//        PB0/A11/ D0|    |D10/A0 /PA0
// ERRLED PB1/A10/ D1|    |D9 /A1 /PA1    Func1ADC
//        PB3/ A9/D11|    |D8 /A2 /PA2    Func2ADC
//        PB2/ A8/ D2|    |D7 /A3 /PA3    Func3ADC
//        PA7/ A7/ D3|    |D6 /A4 /PA4    SCL
// SDA    PA6/ A6/ D4|    |D5 /A5 /PA5
//                   +----+
//
#include "i2c841s2.h"

#define ANALOG_PIN_1 1
#define ANALOG_PIN_2 2
#define ANALOG_PIN_3 3
#define REGISTER_1 0x10
#define REGISTER_2 0x20
#define REGISTER_3 0x30

volatile uint16_t tx_data = 0;
#define TX_BUFFER_SIZE 2

int analogPin = 0;

int checkFuncs(uint8_t reg){
  int Pin = 0;
  if(reg == REGISTER_1){
    Pin = ANALOG_PIN_1;
  }else if(reg == REGISTER_2){
    Pin = ANALOG_PIN_2;
  }else if(reg == REGISTER_3){
    Pin = ANALOG_PIN_3;
  }
  return Pin;
}

void onI2CWrite(volatile uint8_t *pbuf, uint8_t size){
  analogPin = checkFuncs((uint8_t)(*pbuf));
}

void setup() {
  i2cs.setTxBuffer((uint8_t *)&tx_data,TX_BUFFER_SIZE);
  i2cs.setOnWriteEnd(onI2CWrite);
  // start i2c slave interrupt
  i2cs.init(0x30);            
}

void loop() {
  if(analogPin){
    tx_data = analogRead(analogPin);
  }else{
    tx_data = 0;
  }
  delay(50);
}
