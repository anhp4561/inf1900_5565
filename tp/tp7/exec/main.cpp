#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include "Led.h"
#include "RS232.h"
int main() {
#if defined(OFF)
// tester la fonction LED 

    DDRA = 0xff;
    Led test (&PORTA,0,1);
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

#endif

// Tester RS232 
//#if defined(ON)
initialisationUART();
char mots[] = "Le robot en INF1900\n";
UARTTranmissionMot(mots,21);
//#endif
}