#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include <stdio.h>
// #include "led.h"
#include "rs232.h"
// #include "bouton.h"
// #include "moteur.h"
#include "debug.h"
#include "machineVirtuel.h"
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
    moteurs.initialisationTimer0Pwm();
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
    //initialisationTimer1CtcVm(timer1);

    cli();
    TCNT1 = 0;
    TCCR1A = (1 << COM1A0);
    TCCR1B = (1 << WGM12) | (1 << CS10); // CTC mode with 1024 prescalor
    TIMSK1 = (1 << OCIE1A);
    sei();


    // for (int i = 45; i < 81 ; i++){
    //     sei();
    //     char tampon[50];
    //     int n = sprintf(tampon,"La valeur de i est : %d\n", i);
    //     DEBUG_PRINT(tampon, n);
    //     jouerSonnerieVm(i);
    //     _delay_ms(100);
    //     cli();
    // }
    Led led (&PORTA,0,1);
    allumerLedVm(led);
    char tampon[50];
    char tampon1[50];
    int n = sprintf(tampon,"Avant 1ere fonction \n");
    DEBUG_PRINT(tampon, n);
    jouerSonnerieVm(65);
    int o = sprintf(tampon1,"Apres 1ere fonction \n");
    DEBUG_PRINT(tampon, o);
    _delay_ms(100);
    allumerLedVm(led);
    jouerSonnerieVm(75);
    _delay_ms(100);
    jouerSonnerieVm(81);
    _delay_ms(100);
    arreterSonnerieVm();
    jouerSonnerieVm(45);
    _delay_ms(100);
    jouerSonnerieVm(55);
    _delay_ms(100);
    

#endif

}

