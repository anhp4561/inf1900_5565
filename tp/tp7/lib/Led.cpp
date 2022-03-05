#include "Led.h"
#define F_CPU 800000
#include <avr/io.h>
#include <util/delay.h>

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
void Led::allumerAmbreLed(){
    allumerRougeLed();
    _delay_ms(5);
    allumerVertLed();
    _delay_ms(5);
}

void Led::eteindreLed(){
    *port_ &= ~(1<<premierPin_ | 1<<deuxiemePin_);
}

