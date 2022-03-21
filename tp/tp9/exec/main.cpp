#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "led.h"
#include "rs232.h"
#include "bouton.h"
#include "moteur.h"
#include "debug.h"
#include "sonnerie.h"

volatile bool basculeTimer = false;

// ISR(TIMER1_COMPA_vect)
// {
//     PORTD = basculeTimer ? 0 : 1; // a ameliorer plus tard
//     basculeTimer = !basculeTimer;

//     TIFR1 |= (1 << OCF1A);
// }

int main() {

// tester Bouton et Led
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
initialisationUart();
char mots[] = "Le robot en INF1900\n";
transmissionUartString(mots);
#endif

//tester PWM et Debug
#if false
    initialisationUart();
    Moteur moteurs;
    int pourcentageOC0A = 100;
    int pourcentageOC0B = 100;
    while (true){
        char tampon[50];
        int n = sprintf(tampon,"La valeur de pourcentage0C0B est : %d\n", pourcentageOC0B);
        moteurs.avancerMoteur(pourcentageOC0A, pourcentageOC0B);
        _delay_ms(2000);
        moteurs.tournerDroiteMoteur(pourcentageOC0B);
        DEBUG_PRINT(tampon, n);
        _delay_ms(2000);
        moteurs.tournerGaucheMoteur(pourcentageOC0A);
        _delay_ms(2000);
        moteurs.reculerMoteur(pourcentageOC0A, pourcentageOC0B);
        _delay_ms(2000);
        moteurs.arreterMoteur();
        _delay_ms(2000);
        pourcentageOC0B = pourcentageOC0B - 1;
    }
#endif 


#if true
    initialisationUart();
    DDRD = 0xff;
    Sonnerie sonnerie = Sonnerie();
    Moteur moteurs;
    // Led led (&PORTB,0,1);
    // moteurs.avancerMoteur(100,100);
    // sonnerie.jouerSonnerie(65);
    // _delay_ms(1000);
    // sonnerie.jouerSonnerie(75);
    // _delay_ms(1000);
    // sonnerie.jouerSonnerie(81);
    // _delay_ms(1000);
    // sonnerie.arreterSonnerie();
    // sonnerie.jouerSonnerie(45);
    // _delay_ms(1000);
    // sonnerie.jouerSonnerie(55);
    // _delay_ms(1000);
    // moteurs.avancerMoteur(50,50);
    // _delay_ms(10000);

    // theme de tetris
    // sonnerie.jouerSonnerie(76);
    // _delay_ms(450);
    // sonnerie.jouerSonnerie(71);
    // _delay_ms(250);
    // sonnerie.jouerSonnerie(72);
    // _delay_ms(250);
    // sonnerie.jouerSonnerie(74);
    // _delay_ms(450);
    // sonnerie.jouerSonnerie(72);
    // _delay_ms(250);
    // sonnerie.jouerSonnerie(71);
    // _delay_ms(250);
    // sonnerie.jouerSonnerie(69);
    // _delay_ms(450);
    // sonnerie.jouerSonnerie(69);
    // _delay_ms(250);
    // sonnerie.jouerSonnerie(72);
    // _delay_ms(250);
    // sonnerie.jouerSonnerie(76);
    // _delay_ms(450);
    // sonnerie.jouerSonnerie(74);
    // _delay_ms(250);
    // sonnerie.jouerSonnerie(72);
    // _delay_ms(300);
    // sonnerie.jouerSonnerie(71);
    // _delay_ms(550);
    // sonnerie.jouerSonnerie(72);
    // _delay_ms(450);
    // sonnerie.jouerSonnerie(74);
    // _delay_ms(450);
    // sonnerie.jouerSonnerie(76);
    // _delay_ms(450);
    // sonnerie.jouerSonnerie(72);
    // _delay_ms(550);
    // sonnerie.jouerSonnerie(69);
    // _delay_ms(250);
    // sonnerie.arreterSonnerie();
    // _delay_ms(75);
    // sonnerie.jouerSonnerie(69);
    // _delay_ms(250);
    moteurs.avancerMoteur(50,50);
    _delay_ms(2500);
    moteurs.avancerMoteur(100,100);
    _delay_ms(2500);
    moteurs.reculerMoteur(25,25);
    _delay_ms(2500);
    moteurs.reculerMoteur(50,50);
    _delay_ms(2500);
    moteurs.tournerDroiteMoteur(100);
    _delay_ms(333);
    moteurs.arreterMoteur();
    moteurs.tournerGaucheMoteur(100);
    _delay_ms(333);
    moteurs.arreterMoteur();



#endif

}

