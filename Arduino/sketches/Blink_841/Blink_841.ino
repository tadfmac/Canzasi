// Simple Blink for ATtiny841
// PB2 : LED

#define LEDPORT PORTB
#define LEDDDR  DDRB
#define LEDBIT  2

void setup() {
  LEDDDR |= (1 << LEDBIT);
}

void loop() {
  LEDPORT |= (1 << LEDBIT);
  delay(1000);
  LEDPORT &= ~(1 << LEDBIT);
  delay(1000);
}
