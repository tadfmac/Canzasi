// Canzasi_I2CDummySensor
// A simple I2C slave data provider
//   
// with https://github.com/SpenceKonde/ATTinyCore
// 
// License CC by 4.0 2016 D.F.Mac.
//
//                   +----+
//                VCC|    |GND
//        PB0/A11/ D0|    |D10/A0 /PA0
// ERRLED PB1/A10/ D1|    |D9 /A1 /PA1    Button (with pulldown)
//        PB3/ A9/D11|    |D8 /A2 /PA2
//        PB2/ A8/ D2|    |D7 /A3 /PA3
//        PA7/ A7/ D3|    |D6 /A4 /PA4    SCL
// SDA    PA6/ A6/ D4|    |D5 /A5 /PA5
//                   +----+
//
#include "i2c841s2.h"

#define BUTTON_PIN 9

void setup() {
  pinMode(BUTTON_PIN,INPUT);
  // default tx buffer length (per packet size) is 1 byte
  // if slave device specified another size, use i2cs.setTxBuffer()

  // start i2c slave interrupt
  i2cs.init(0x30);            
}

volatile uint8_t tx_data = 0;
#define TX_BUFFER_SIZE 1

void loop() {
  tx_data = (uint8_t)digitalRead(BUTTON_PIN);
  i2cs.setNextTxData(&tx_data, TX_BUFFER_SIZE);
  delay(50);
}
