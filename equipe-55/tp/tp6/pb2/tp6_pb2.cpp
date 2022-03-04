/* 
Author: Anh pham

Description:
A program which turns an LED green, amber or red depending on the luminosity.
 
Used Pins : B0 , B1 on output and A0 on input mode.
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <can.h>

void initialisationUART ( void ) {
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A = 0;
    UCSR0B |= ( 1 << RXEN0) | ( 1<< TXEN0);
    UCSR0C = 0;
}

// FROM USART to the  PC
void transmissionUART ( uint8_t donnee ) {
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) )
    ;
    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

int main () {
    DDRB = 0xff;
    DDRA = 0x00;
    const uint8_t GREEN = 1 << PB1;
    const uint8_t RED = 1 << PB0;
    const uint8_t OFF = 0;
    can converter = can();
    initialisationUART();
    while (true){
        uint16_t readingAdc = converter.lecture(PA0);
        uint8_t readingAdcEightBit = readingAdc >> 2 ; // takes out the 2 LSB
        uint8_t redUpperLimit = 255;
        uint8_t redLowerLimit = 220;
        uint8_t amberLowerLimit = 100;
        uint8_t delay = 10;

        if (readingAdcEightBit > redLowerLimit && readingAdcEightBit <= redUpperLimit)
            PORTB = RED;
        else if (readingAdcEightBit > amberLowerLimit && readingAdcEightBit <= redLowerLimit){
            PORTB = GREEN;
            _delay_ms (delay-4);
            PORTB = OFF;
            _delay_ms (delay);
            PORTB = RED;
            _delay_ms (delay-8);
        }
        else 
            PORTB = GREEN;
        transmissionUART(readingAdcEightBit);
    }
}