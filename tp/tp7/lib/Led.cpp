#include "Led.h"
#define F_CPU 800000
#include <avr/io.h>
#include <util/delay.h>
const uint8_t AMBRE_DELAI = 5;

Led::Led (volatile uint8_t *port, int premierPin, int deuxiemePin){
    port_ = port;
    premierPin_ = premierPin;
    deuxiemePin_ = deuxiemePin;
}
void Led::allumerRougeLed (){
    *port_ &= ~(1<<premierPin_ | 1<<deuxiemePin_);
    *port_ |= 1 << premierPin_;
}

void Led::allumerVertLed(){
    *port_ &= ~(1<<premierPin_ | 1<<deuxiemePin_);
    *port_ |= 1 << deuxiemePin_;

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
    *port_ &= ~(1<<premierPin_ | 1<<deuxiemePin_);
}

