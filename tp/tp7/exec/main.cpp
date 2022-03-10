#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include "led.h"
#include "rs232.h"
#include "bouton.h"
#include "moteur.h"
#include "debug.h"
int main() {

#if false 
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
#if false  
initialisationUART();
char mots[] = "Le robot en INF1900\n";
UARTTranmissionMot(mots);
#endif

//tester PMW 
#if true
    Moteur moteurs;
    moteurs.initialisationTimer0Pwm();
    int pourcentageOC0A = 100;
    int pourcentageOC0B = 100;
    while (true){
        moteurs.avancerMoteur(pourcentageOC0A, pourcentageOC0B);
        _delay_ms(2000);
        moteurs.tournerDroiteMoteur(pourcentageOC0B);
        DEBUG_PRINT((pourcentageOC0B));
        _delay_ms(2000);
        moteurs.tournerGaucheMoteur(pourcentageOC0A);
        _delay_ms(2000);
        moteurs.reculerMoteur(pourcentageOC0A, pourcentageOC0B);
        _delay_ms(2000);
        moteurs.arreterMoteur();
        _delay_ms(2000);
    }
#endif 
}
