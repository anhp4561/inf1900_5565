#include "pwm.h"
#define 	F_CPU   8000000UL
#include <avr/io.h> 
#include <util/delay.h>

void pwm::setPwm(double pourcentage, double freq){
const float TEMPS_UNITAIRE=0.1;
unsigned b = 1/freq;
unsigned a=pourcentage*b/100;
const unsigned TEMPS_D_ACTIVITE_Second=2;
unsigned nbPeriodes = unsigned(TEMPS_D_ACTIVITE_Second/b);
    for(unsigned n=0;n<nbPeriodes;n++){                
        PORTA=0x01;
        for(unsigned i=0;i<a;i++)
            _delay_ms(TEMPS_UNITAIRE);
        PORTA= 0x00;                     
        for(unsigned i=0;i<b-a;i++)
            _delay_ms(TEMPS_UNITAIRE);
    }      
}

// Initialisation du Timer0 pour generer du PWM
void pwm::initialisationTimerPwm()
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
