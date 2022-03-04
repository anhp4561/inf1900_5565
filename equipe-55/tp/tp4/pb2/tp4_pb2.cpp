#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile bool toggleButton = false;
volatile bool toggleTimer = false;

ISR(TIMER1_COMPA_vect)
{
   toggleTimer=1;
}

ISR (INT0_vect) {
    _delay_ms ( 30 );
    uint8_t reading = PIND;
    uint8_t mask = 1 << PD2;
    if (reading && mask)
        toggleButton = 1;
    EIFR |= (1 << INTF0) ;// Setting bit INTF0 clears the external interrupt flag for INT00
}

void initialisationTimer()
{
    cli();
    DDRA |= (1 << PA2) | (1 << PA3);

    TCNT1 = 0; // sets the timer to 0
    TCCR1A = 0; // We don't need OCnA or OCnB here (not generating PWM or outputting something when output compare) (WGM11 and WGM10 = 0, since we want CTC mode)
    // for CTC mode - > WGM13 WGM12 WGM11 WGM10  = 0 1 0 0 
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode and (CS12 and CS10 = 1, since we want /1024 prescalor)
    // for 1024 prescalor -> CS12 CS11 CS10 = 1 0 1
    TIMSK1 = (1 << OCIE1A); // Timer/Counter 1 output compare match A enabled
    OCR1A = 7000; // where we compare timer 1
    sei();
}

void initialisationInt0()
{

    cli();
    DDRA |= (1 << PA0) | (1 << PA1);
    DDRD = 0;
    EIMSK |= (1 << INT0); // Enables external interrupt pin INT0
    EICRA = (1 << ISC00) || ( 1<< ISC01); // ISC00 = ISC01 = 1 -> The rising edge of INT0 generates asynchronously an interrupt request (from microchip documentation

    sei();
}

int main () {
    initialisationInt0();
    cli();
    PORTA = 0;
    _delay_ms(10000);
    PORTA = 1;
    _delay_ms(100);
    PORTA = 0;
    sei();
    initialisationTimer();
    do {

    }
    while (toggleTimer==0 && toggleButton ==0);
    cli();
    if (toggleButton)
        PORTA = 1;
    else if (toggleTimer)
        PORTA = 2;
}
