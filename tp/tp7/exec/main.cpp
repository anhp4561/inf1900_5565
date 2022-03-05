#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include "Led.h"

// tester la fonction LED 
int main() {
    DDRB = 0xff;
    Led test (&PORTB,6,7);
    int nIterations = 2000;
    while (true){
        test.allumerRougeLed();
        _delay_ms(2000);
        test.allumerVertLed();
        _delay_ms(2000);
        test.allumerAmbreLed(nIterations);
        test.eteindreLed();
        _delay_ms(2000);
    } 
}

