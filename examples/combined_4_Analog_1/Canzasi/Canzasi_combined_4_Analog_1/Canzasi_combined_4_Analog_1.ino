// Canzasi_I2CAnalogDevice
// 4 Analog Pot (read8 version)
//   
// with https://github.com/SpenceKonde/ATTinyCore
// 
// License CC by 4.0 2016 D.F.Mac.
//
//                   +----+
//                VCC|    |GND
//        PB0/A11/ D0|    |D10/A0 /PA0    ANALOG_CH_1
//        PB1/A10/ D1|    |D9 /A1 /PA1    ANALOG_CH_2
//        PB3/ A9/D11|    |D8 /A2 /PA2    ANALOG_CH_3
//        PB2/ A8/ D2|    |D7 /A3 /PA3    ANALOG_CH_4
//        PA7/ A7/ D3|    |D6 /A4 /PA4    SCL
// SDA    PA6/ A6/ D4|    |D5 /A5 /PA5
//                   +----+
//
#include "i2c841s2.h"

// Constants
#define ANALOG_CH1 0
#define ANALOG_CH2 1
#define ANALOG_CH3 2
#define ANALOG_CH4 3
#define REGISTER_MIN 0x10
#define REGISTER_MAX 0x13
#define ADC_CHANNELS 4
#define TX_BUFFER_SIZE 1
const int analog_pins[ADC_CHANNELS] = {ANALOG_CH1,ANALOG_CH2,ANALOG_CH3,ANALOG_CH4};

// Global Valiables
static uint8_t tx_data[ADC_CHANNELS] = {0x20,0x21,0x22,0x23};
static int currentCh = 0;

static void onI2CWrite(uint8_t *pbuf, uint8_t len){
  uint8_t data = *(pbuf + (len -1));
  if((data >= REGISTER_MIN)&&(data <= REGISTER_MAX)){
    currentCh = data- 0x10;
    i2cs.setTxBuffer(&tx_data[currentCh],TX_BUFFER_SIZE);
  }  
}

void setup() {
  i2cs.setTxBuffer(&tx_data[currentCh],TX_BUFFER_SIZE);
  i2cs.setOnWriteEnd(onI2CWrite);
  i2cs.init(0x30);            
}

void loop() {
  int cnt,adc;
  uint8_t data;

  for(cnt = 0;cnt < ADC_CHANNELS;cnt ++){
    adc = analogRead(analog_pins[cnt]);
    data = (uint8_t)(adc >> 2);
    tx_data[cnt] += (data - tx_data[cnt]) / 2;
  }
  delay(30);
}
