#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
const int delay =2000;


void initialisationTimerPwm()
{
    cli();
    DDRB |= (1 << PB2) | (1 << PB3);
    TCNT0 = 0; // Set timer 0 to 0
    // In SimulIde use the Fast PWM, but with the robot you must use the PWM Phase Correct 8-bit
    TCCR0A =
        (1 << WGM00) | // WGM03 WGM02 WGM01 WGM00 = 0 0 1 1 PWM, Phase correct , 10-bit
        (1 << WGM01) | // Comment this line when you are in the robot to obtain the PWM Phase Correct 8-bit
        (1 << COM0A1); // Clear OCnA/OCnB on Compare Match when upcounting. Set OCnA/OCnB on Compare Match when downcounting.
    TCCR0B = (1 << CS01); // prescalor / 8
    sei();
}

void set(int percentage){ //  change the name to set speed ?
    double percentage1 = percentage / 100.0;
    OCR0A = 254 * percentage1; // where we compare timer 0
}

// make a function called setDirection() which has a parameter (uint8_t motorPort) and parameter (uint8_t direction) not sure about type for variable direction

int main (){
    initialisationTimerPwm();
    int percentage = 0;
    while (true){
        set(percentage);
        percentage += 25;
        percentage = percentage % 125;
        _delay_ms (delay);
        if (percentage ==0)
            PORTB ^= (1 << PB2);

    }
}
    