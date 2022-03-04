#include <avr/io.h> 
#include "LED.h"
DDRB=0xff;

// tester la fonction LED 
int main() {
    choisirPort('B');
    allumerLedRouge(2);
}

