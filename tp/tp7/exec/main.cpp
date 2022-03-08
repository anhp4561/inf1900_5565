#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include "led.h"
#include "rs232.h"
#include "bouton.h"
int main() {
#if defined(OFF)
    Led led (&PORTA,0,1);
    Bouton bouton (&PIND,2);

    while (true){
        if (bouton.estBoutonPresseRappel())
            led.allumerRougeLed();
        
        else 
            led.allumerVertLed();
    } 

#endif

// Tester RS232 
//#if defined(ON)
initialisationUART();
char mots[] = "Le robot en INF1900\n";
UARTTranmissionMot(mots,21);
//#endif
}