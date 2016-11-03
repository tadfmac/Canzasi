// i2c841s2.h
//
// I2C Slave Library for mi:muz:expr
//
// CC 2016 by D.F.Mac.
//
// base : http://www.mikrocontroller.net/topic/353654 (Autor Zepp 2014-12-31 21:01)
// base2 : i2c841s.h (https://github.com/tadfmac/mi-muz/tree/master/avr/arduino/libraries/HybridMidiAttiny)

#ifndef __I2C841S2_h__
#define __I2C841S2_h__

#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef __cplusplus
extern "C"{
#endif 

// Callback
void (*onWriteEnd)(volatile uint8_t *pbuf, uint8_t size);

// Global Vals
#define _TX_BUF_SIZE 1  // default TX buffer size
#define _RX_BUF_SIZE 1  // default RX buffer size

volatile uint8_t _txBufSize = _TX_BUF_SIZE;
volatile uint8_t _rxBufSize = _RX_BUF_SIZE;
volatile uint8_t _defaultTxBuf = 0xff;
volatile uint8_t _defaultRxBuf = 0xff;
volatile uint8_t *_txBufp = &_defaultTxBuf;
volatile uint8_t *_rxBufp = &_defaultRxBuf;
volatile uint8_t _txBufIndex = 0;
volatile uint8_t _rxBufIndex = 0;

ISR( TWI_SLAVE_vect )
{  
  uint8_t status = TWSSRA & ((1 << TWDIF)|(1<< TWASIF));
  // TWDIF:  TWI Data Interrupt Flag
  // TWASIF: TWI Address/Stop Interrupt Flag 

  // When TWI Data Interruption is exist
  if(status & (1 << TWDIF)){
    if(TWSSRA & (1 << TWDIR)){  // TWDIR: (1: a master read operation is in progress)
      TWSD = *(_txBufp + _txBufIndex);
      _txBufIndex++;
      _txBufIndex = _txBufIndex % _txBufSize;
    }else{                      // TWDIR: (0: a master write operation is in progress)
      *(_rxBufp + (_rxBufIndex % _rxBufSize)) = TWSD;
      _rxBufIndex ++;
    }
    TWSCRB = (uint8_t) ((1<<TWCMD1)|(1<<TWCMD0));
  // When TWI Address/Stop Interruption is exist
  }else if (status & (1 << TWASIF)){    
    if (TWSSRA & (1<<TWC)){   // TWC: TWI Collision
      TWSCRB = (uint8_t) (1<<TWCMD1);
    }else{    
      if(TWSSRA & (1<<TWAS)){  // Start Condition
        if(_rxBufIndex != 0){  // For SR Condition
          if(onWriteEnd != 0){
            (*onWriteEnd)(_rxBufp, _rxBufIndex);
          }
        }
        _rxBufIndex = 0;
        _txBufIndex = 0;
        TWSCRB = (uint8_t) ((1<<TWCMD1)|(1<<TWCMD0)); // ACK   
      }else{                    // Stop Condition
        if(TWSSRA & (1 << TWDIR)){ // Read End
        }else{  // Write End
          if(onWriteEnd != 0){
            (*onWriteEnd)(_rxBufp, _rxBufIndex);
          }
          _rxBufIndex = 0;
        }
        TWSCRB = (uint8_t) (1<<TWCMD1);
      }
    }
  }    
}

class i2c841slave {
public:
  i2c841slave(){
    onWriteEnd = 0;
  }

  void init(uint8_t addr){
    DDRA |= 0x50; // SCL,SDA
    TWSA = addr << 1;  // set to slaveaddr << 1; 
    TWSD = 0xFF;

    // enable twi slave    
    TWSCRA = (1<<TWSHE)|(1<<TWDIE)|(1<<TWASIE)|(1<<TWEN)|(1<<TWSIE);
    // × TWSHE  (0x80): TWI SDA Hold Time Enable
    // TWDIE  (0x20): TWI Data Interrupt Enable
    // TWASIE (0x10): TWI Address/Stop Interrupt Enable
    // TWEN   (0x08): Two-Wire Interface Enable
    // TWSIE  (0x04): TWI Stop Interrupt Enable

//    TWSCRA |= (1<<TWPME);  // for Debugging
  }

  void setOnWriteEnd(void (*fptr)(volatile uint8_t *pbuf, uint8_t size)){
    cli();
    onWriteEnd = fptr;
    sei();
  }

  void setTxBuffer(volatile uint8_t *pBuf, uint8_t size){
    cli();
    _txBufp = pBuf;
    _txBufSize = size;
    sei();
  }

  void setRxBuffer(volatile uint8_t *pBuf, uint8_t size){
    cli();
    _rxBufp = pBuf;
    _rxBufSize = size;
    sei();
  }

  void setNextTxByte(uint8_t data){
    cli();
    *(_txBufp) = data;
    sei();
  }

};

#ifdef __cplusplus
} // extern "C"
#endif

i2c841slave i2cs;

#endif // __I2C841S2_h__

