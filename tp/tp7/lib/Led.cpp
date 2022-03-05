#include "Led.h"
#define F_CPU 800000
#include <avr/io.h>
#include <util/delay.h>
const uint8_t AMBRE_DELAI = 5;

Led::Led (volatile uint8_t *port, int LedPin1, int LedPin2){
    port_ = port;
    LedPin1_ = LedPin1;
    LedPin2_ = LedPin2;
}
void Led::allumerRougeLed (){
    *port_ &= ~(1<<LedPin1_ | 1<<LedPin2_);
    *port_ |= 1 << LedPin1_;
}

void Led::allumerVertLed(){
    *port_ &= ~(1<<LedPin1_ | 1<<LedPin2_);
    *port_ |= 1 << LedPin2_;

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
    *port_ &= ~(1<<LedPin1_ | 1<<LedPin2_);
}

