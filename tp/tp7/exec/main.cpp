#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include "Led.h"
<<<<<<< HEAD
#include "RS232.h"
int main() {
#if defined(OFF)
// tester la fonction LED 

    DDRA = 0xff;
    Led test (&PORTA,0,1);
    int nIterations = 2000;
=======
#include "Bouton.h"

// tester la fonction LED 
int main() {
    //DDRA = 0x00; // pour verifier si a la construction on modifie bien le registre de direction
    //DDRD = 0xff; // pour verifier si a la construction on modifie bien le registre de direction
    Led led (&PORTA,0,1);
    Bouton bouton (&PIND,2);

>>>>>>> 5167a067fda0ddf717647e166229751f6f58c700
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