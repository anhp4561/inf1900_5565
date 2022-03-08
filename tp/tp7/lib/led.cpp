#include "led.h"
#define F_CPU 800000
#include <avr/io.h>
#include <util/delay.h>
const uint8_t AMBRE_DELAI = 5;

Led::Led (volatile uint8_t *port, int ledPin1, int ledPin2){
    port_ = port;
    ledPin1_ = ledPin1;
    ledPin2_ = ledPin2;
    // Justification pour la suite de if : switch case ne permettait pas d'utiliser port_ comme parametre
    if (port_ == &PORTA)
        DDRA |= (1<< ledPin1_) | (1<< ledPin2_);
    
    else if (port_ == &PORTB)
        DDRB |= (1<< ledPin1_) | (1<< ledPin2_);

    else if (port_ == &PORTC)
        DDRC |= (1<< ledPin1_) | (1<< ledPin2_);
    
    else if (port_ == &PORTD)
        DDRD |= (1<< ledPin1_) | (1<< ledPin2_);
}
void Led::allumerRougeLed (){
    *port_ &= ~(1<<ledPin1_ | 1<<ledPin2_);
    *port_ |= 1 << ledPin1_;
}

void Led::allumerVertLed(){
    *port_ &= ~(1<<ledPin1_ | 1<<ledPin2_);
    *port_ |= 1 << ledPin2_;

}
void Led::allumerAmbreLed(int nIterations){
    for (int i = 0; i < nIterations ; i++){
        allumerRougeLed();
        _delay_ms(AMBRE_DELAI);
        allumerVertLed();
        _delay_ms(AMBRE_DELAI);
    }
    
}

void Led::eteindreLed(){
    *port_ &= ~(1<<ledPin1_ | 1<<ledPin2_);
}

