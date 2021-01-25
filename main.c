
#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_RESET (0x01 << (1)) //button reset connected to port B pin 1
#define BUTTON_ADD1 (0x01 << (2)) // button switch connected to port B pin 2
#define BUTTON_ADD2 (0x01 << (3)) // button switch connected to port B pin 3

  /*       a PC5
   *        --- 
   *      |     |
   *f PC0 |g PB5| b PC4
   *        ---
   *      |     |
   *e PC1 |     | c PC3
   *        ___
   *      d PC2    
   *
   */
#define LED_a1 (0x01 << (5))
#define LED_b1 (0x01 << (4))
#define LED_c1 (0x01 << (3)) 
#define LED_d1 (0x01 << (2)) 
#define LED_e1 (0x01 << (1))
#define LED_f1 (0x01 << (0))
#define LED_g1 (0x01 << (5))

  /*       a PD0
   *        --- 
   *      |     |
   *f PD5 |g PD6| b PD1
   *        ---
   *      |     |
   *e PD4 |     | c PD2
   *        ___
   *      d PD3    
   *
   */
#define LED_a2 (0x01 << (0))
#define LED_b2 (0x01 << (1))
#define LED_c2 (0x01 << (2)) 
#define LED_d2 (0x01 << (3)) 
#define LED_e2 (0x01 << (4))
#define LED_f2 (0x01 << (5))
#define LED_g2 (0x01 << (6))

#define DEBOUNCE_TIME 25 // time to wait while "de-bouncing" button 
#define LOCK_INPUT_TIME 300 // time to wait after a button press

void init_ports_mcu()
{
  DDRB=0xFFu; // Set all pins of the PORTB as output.
  DDRB &= ~(BUTTON_ADD1); // Makes first pin of PORTB as Input
  DDRB &= ~(BUTTON_ADD2); // Makes first pin of PORTB as Input
  DDRB &= ~(BUTTON_RESET); // Makes first pin of PORTB as Input

  PORTB = 0xFF; // Set all pins of the PORTB as HIGH. Led is turn on, 
              // also the internal Pull Up resistor of first pin PORTB is enable. 

  DDRC=0xFFu; // Set all pins of the PORTC as output.
  PORTC=0x00u; // Set all pins of PORTC low which turns it off.
  
  DDRD=0xFFu; //  Set all pins of the PORTD as output.
  PORTD=0x00u; // Set all pins of PORTD low which turns it off.
}

unsigned char buttons(unsigned char switcher)
{
  /* the button is pressed when BUTTON1 bit is clear */
  if (!(PINB & BUTTON_RESET)) {
    _delay_ms(DEBOUNCE_TIME);
    if (!(PINB & BUTTON_RESET)) return 1;
  }
  
  if (!(PINB & BUTTON_ADD1)) {
    _delay_ms(DEBOUNCE_TIME);
    if (!(PINB & BUTTON_ADD1)) return 2;
  }

  if ((PINB & BUTTON_ADD2)!=switcher) {
    _delay_ms(DEBOUNCE_TIME);
    if ((PINB & BUTTON_ADD2)!=switcher) return 2;
  }
  return 0; 
}

void show (unsigned char count) {
  int digit = count % 10;
  //first number PC5-PC0, PB5. clear all

  /*       a PC5
   *        --- 
   *      |     |
   *f PC0 |g PB5| b PC4
   *        ---
   *      |     |
   *e PC1 |     | c PC3
   *        ___
   *      d PC2    
   *
   */
   
  PORTC &= ~(0b00111111);
  PORTB &= ~(0b00100000);
  switch(digit){
    case 0:
      PORTC |= (LED_a1 | LED_b1 | LED_c1 | LED_d1 | LED_e1 | LED_f1);
    break;
    case 1:
      PORTC |= (LED_b1 | LED_c1);
    break;
    case 2:
      PORTC |= (LED_a1 | LED_b1 | LED_d1 | LED_e1);
      PORTB |= (LED_g1);
    break;
    case 3:
      PORTC |= (LED_a1 | LED_b1 | LED_c1 | LED_d1);
      PORTB |= (LED_g1);
    break;
    case 4:
      PORTC |= (LED_b1 | LED_c1 | LED_f1);
      PORTB |= (LED_g1);
    break;
    case 5:
      PORTC |= (LED_a1 | LED_c1 | LED_d1 | LED_f1);
      PORTB |= (LED_g1);
    break;
    case 6:
      PORTC |= (LED_a1 | LED_c1 | LED_d1 | LED_e1 | LED_f1);
      PORTB |= (LED_g1);
    break;
    case 7:
      PORTC |= (LED_a1 | LED_b1 | LED_c1);
    break;
    case 8:
      PORTC |= (LED_a1 | LED_b1 | LED_c1 | LED_d1 | LED_e1 | LED_f1);
      PORTB |= (LED_g1);
    break;
    case 9:
      PORTC |= (LED_a1 | LED_b1 | LED_c1 | LED_d1 | LED_f1);
      PORTB |= (LED_g1);
    break;
  }
  count /= 10;
  digit = count % 10;
    /*       a PD0
   *        --- 
   *      |     |
   *f PD5 |g PD6| b PD1
   *        ---
   *      |     |
   *e PD4 |     | c PD2
   *        ___
   *      d PD3    
   *
   */
  PORTD &= ~(0b01111111);
  switch(digit){
    case 0:
    break;
      PORTD |= (LED_a2 | LED_b2 | LED_c2 | LED_d2 | LED_e2 | LED_f2);
    case 1:
      PORTD |= (LED_b2 | LED_c2);
    break;
    case 2:
      PORTD |= (LED_a2 | LED_b2 | LED_d2 | LED_e2 | LED_g2);
    break;
    case 3:
      PORTD |= (LED_a2 | LED_b2 | LED_c2 | LED_d2 | LED_g2);
    break;
    case 4:
      PORTD |= (LED_b2 | LED_c2 | LED_f2 | LED_g2);
    break;
    case 5:
      PORTD |= (LED_a2 | LED_c2 | LED_d2 | LED_f2 | LED_g2);
    break;
    case 6:
      PORTD |= (LED_a2 | LED_c2 | LED_d2 | LED_e2 | LED_f2 | LED_g2);
    break;
    case 7:
      PORTD |= (LED_a2 | LED_b2 | LED_c2);
    break;
    case 8:
      PORTD |= (LED_a2 | LED_b2 | LED_c2 | LED_d2 | LED_e2 | LED_f2 | LED_g2);
    break;
    case 9:
      PORTD |= (LED_a2 | LED_b2 | LED_c2 | LED_d2 | LED_f2 | LED_g2);
    break;
  }
}

void reset_animation(unsigned char animation_step) {
  PORTC &= ~(0b00111111);
  PORTB &= ~(0b00100000);
  PORTD &= ~(0b01111111);
  switch(animation_step){
    case 0:
      PORTC |= (LED_a1);
      PORTD |= (LED_a2);
    break;
    case 1:
      PORTC |= (LED_b1);
      PORTD |= (LED_b2);
    break;
    case 2:
      PORTC |= (LED_c1);
      PORTD |= (LED_c2);
    break;
    case 3:
      PORTC |= (LED_d1);
      PORTD |= (LED_d2);
    break;
    case 4:
      PORTC |= (LED_e1);
      PORTD |= (LED_e2);
    break;
    case 5:
      PORTC |= (LED_f1);
      PORTD |= (LED_f2);
    break;
  }
}

int main(void) {
  unsigned char count = 0; // initially count
  unsigned char animation_step = 0;
  unsigned char switcher = PINB & BUTTON_ADD2;
  init_ports_mcu();
  while (1)
  {
    switch(buttons(switcher)){
      case 0:
        show(count);
      break;
      case 1:
        reset_animation(animation_step);
        animation_step++;
        if(animation_step > 5){
          animation_step = 0;
        }
        count=0;
      break;
      case 2:
        switcher = PINB & BUTTON_ADD2;
        count++;
        if(count > 99){
          count = 0;
        }
        show(count);
      break;
    } 
    _delay_ms(LOCK_INPUT_TIME);
  }
  return (0);
}

