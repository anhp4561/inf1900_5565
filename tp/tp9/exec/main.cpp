#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
// #include "led.h"
#include "rs232.h"
// #include "bouton.h"
// #include "moteur.h"
#include "debug.h"
#include "machineVirtuel.h"

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
    Timer1 timer1;
    Sonnerie sonnerie = Sonnerie(/*timer1*/);
    Moteur moteurs;
    Led led (&PORTB,0,1);
    eteindreLedVm(led);
    avancerMoteurVm(128, moteurs);
    moteurs.avancerMoteur(50,50);
    
    //sonnerie.initialisationTimer1CtcVm(timer1); Probleme avec init timer, demander a coequipier
    // cli();
    // TCNT1 = 0;
    // TCCR1A = 0; //(1 << COM1A0);
    // TCCR1B = (1 << WGM12) | (1 << CS11); // CTC mode with 8 prescaler
    // TCCR1C = 0;
    // TIMSK1 = (1 << OCIE1A);
    // sei();
    sonnerie.jouerSonnerieVm(65);
    _delay_ms(1000);
    allumerLedVm(led);
    sonnerie.jouerSonnerieVm(75);
    _delay_ms(1000);
    sonnerie.jouerSonnerieVm(81);
    _delay_ms(1000);
    sonnerie.arreterSonnerieVm();
    sonnerie.jouerSonnerieVm(45);
    _delay_ms(1000);
    sonnerie.jouerSonnerieVm(55);
    _delay_ms(1000);
    avancerMoteurVm(128, moteurs);
    _delay_ms(10000);
    

#endif

}

