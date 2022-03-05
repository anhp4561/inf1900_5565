#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include "Led.h"
#include "Bouton.h"

// tester la fonction LED 
int main() {
    DDRA = 0xff;
    Led led (&PORTA,0,1);
    Bouton bouton (&PIND,2);

    while (true){
        if (bouton.estBoutonPresseRappel())
            led.allumerRougeLed();
        
        else 
            led.allumerVertLed();
    } 
}

