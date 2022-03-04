/* 
Authors: Oussaada Mohamed Adlane && Anh pham

Description:
A program which turns an LED red while slowly decreasing its intensity. It will then do the same with the LED lit green.

Material identification: 2x 5 volts rail , 2x 10kOhm resistor,2x 1 MOhm resistor,
2x Ground (0V) , 1x 1,5 KOhm, 1x DEL bicolore and 1x atmega324a. 
Used Pins : D2 , D3 on input and A0 , A1 on output.
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>
volatile uint8_t gState = 0; 
uint8_t ON = 1 << PA1;
uint8_t OFF = 0;

ISR (INT0_vect) {
    _delay_ms ( 30 );
    uint8_t reading = PIND;
    uint8_t mask = 1 << PD2;
    if (reading && mask)
        gState = !gState;
    EIFR |= (1 << INTF0) ;// Setting bit INTF0 clears the external interrupt flag for INT0
}

void initialisation ( void ) {
    cli (); // clear interrupt
    DDRA = 0xff;
    EIMSK |= (1 << INT0) ; // Enables external interrupt pin INT0
    EICRA = (1 << ISC00) || ( 1<< ISC01); // ISC00 = ISC01 = 1 -> The rising edge of INT0 generates asynchronously an interrupt request (from microchip documentation)
    // sets interrupt sense control
    sei (); // set interrupt
}

int main () {
    initialisation();
    while (true){
        if  (gState ==1){
            PORTA = ON;
        }
        else {
            PORTA = OFF;
        }
    }
}
