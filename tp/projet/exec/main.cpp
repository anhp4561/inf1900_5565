#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <can.h>
#include "led.h"
#include "rs232.h"
#include "bouton.h"
#include "debug.h"
#include <memoire_24.h>
#include "sonnerie.h"
#include "interruptions.h"
#include "ecrireMouvements.h"

Moteur moteurs = Moteur();

volatile bool basculeTimer = false;
volatile bool ecrireMouv = true;

Led led (&PORTA,0,1);

// ISR(TIMER1_COMPA_vect)
// {
//     PORTD = basculeTimer ? 0 : 1; // a ameliorer plus tard
//     basculeTimer = !basculeTimer;

//     TIFR1 |= (1 << OCF1A);
// }

// ISR ( INT0_vect ) {

// ecrireMouv = false;
// refaireParcours(moteurs);

// }

// void initialiserInterruption()
// {
//     DDRD = 0x00; // PORT D est en mode entrée
//     //initialiser l'interruption du bouton pour refaire les mouvements
//     initInterruption0();
// }

int main() {

//initialiserInterruption();

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
//initialisationUart();
char mots[] = "Le robot en INF1900\n";
transmissionUartString(mots);
#endif

//tester PWM et Debug
#if false
    initialisationUart();
    int pourcentageOC0A = 100;
    int pourcentageOC0B = 100;
    while (true){
        char tampon[100];
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


#if false
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
    // moteurs.avancerMoteur(100,100);
    // _delay_ms(10000);

    // theme de tetris
    sonnerie.jouerSonnerie(76);
    _delay_ms(450);
    sonnerie.jouerSonnerie(71);
    _delay_ms(250);
    sonnerie.jouerSonnerie(72);
    _delay_ms(250);
    sonnerie.jouerSonnerie(74);
    _delay_ms(450);
    sonnerie.jouerSonnerie(72);
    _delay_ms(250);
    sonnerie.jouerSonnerie(71);
    _delay_ms(250);
    sonnerie.jouerSonnerie(69);
    _delay_ms(450);
    sonnerie.jouerSonnerie(69);
    _delay_ms(250);
    sonnerie.jouerSonnerie(72);
    _delay_ms(250);
    sonnerie.jouerSonnerie(76);
    _delay_ms(450);
    sonnerie.jouerSonnerie(74);
    _delay_ms(250);
    sonnerie.jouerSonnerie(72);
    _delay_ms(300);
    sonnerie.jouerSonnerie(71);
    _delay_ms(550);
    sonnerie.jouerSonnerie(72);
    _delay_ms(450);
    sonnerie.jouerSonnerie(74);
    _delay_ms(450);
    sonnerie.jouerSonnerie(76);
    _delay_ms(450);
    sonnerie.jouerSonnerie(72);
    _delay_ms(550);
    sonnerie.jouerSonnerie(69);
    _delay_ms(250);
    sonnerie.arreterSonnerie();
    _delay_ms(75);
    sonnerie.jouerSonnerie(69);
    _delay_ms(250);
    // moteurs.avancerMoteur(100,100);
    // _delay_ms(2500);
    // moteurs.avancerMoteur(100,100);
    // _delay_ms(2500);
    // moteurs.reculerMoteur(100,100);
    // _delay_ms(2500);
    // moteurs.reculerMoteur(100,100);
    // _delay_ms(2500);
    // moteurs.tournerDroiteMoteur(100);
    // _delay_ms(750);
    // moteurs.arreterMoteur();
    // moteurs.tournerGaucheMoteur(100);
    // _delay_ms(750);
    // moteurs.arreterMoteur();



#endif

#if false
DDRB = 0xff;
DDRA = 0x00;
can converter = can();
initialisationUart();
uint16_t readingLeft = converter.lecture(PA4);
uint16_t readingRight = converter.lecture(PA6);
uint8_t readingLeft8 = readingLeft >> 2 ; // takes out the 2 LSB 
uint8_t readingRight8 = readingRight >> 2 ;
int sommeIntensite = 0;
uint8_t nIterations = 10;
double nLectures = nIterations * 2.0;
uint8_t pourcentageLeft = 0;
uint8_t pourcentageRight = 0;

for (int i = 0; i < nIterations ; i++){
    readingLeft = converter.lecture(PA4);
    readingRight = converter.lecture(PA6);
    readingLeft8 = readingLeft >> 2 ; // takes out the 2 LSB
    readingRight8 = readingRight >> 2 ;
    char tampon2[100];
    int n2= sprintf(tampon2,"readingLeft : %d     readingRight : %d\n\n", readingLeft8, readingRight8);
    DEBUG_PRINT(tampon2,n2);
    sommeIntensite += readingLeft8 +readingRight8;
}
uint8_t intensiteLumiere = sommeIntensite / nLectures; 
char tampon1[100];
int n1 = sprintf(tampon1,"Intesite lumiere est %d\n", intensiteLumiere);
DEBUG_PRINT(tampon1,n1);
while (true){
    readingLeft = converter.lecture(PA4);
    readingRight = converter.lecture(PA6);
    readingLeft8 = (readingLeft >> 2) ; // takes out the 2 LSB
    readingRight8 = (readingRight >> 2) ;
    if (readingLeft8 <= intensiteLumiere)
        pourcentageLeft = 0;
    else 
        pourcentageLeft  = (readingLeft8 - intensiteLumiere) * 100 / (255 - intensiteLumiere);
    
    if (readingRight8 <= intensiteLumiere)
        pourcentageRight = 0;
    else
        pourcentageRight = (readingRight8 - intensiteLumiere) * 100 / (255 - intensiteLumiere);

    moteurs.avancerMoteur(pourcentageLeft, pourcentageRight);
    // if (ecrireMouv) 
    // {
    //     ecrireEnMemoire(pourcentageLeft, pourcentageRight);
    // }
    char tampon[100];
    int n = sprintf(tampon,"pLeft : %d     pRight : %d\n", pourcentageLeft, pourcentageRight);
    DEBUG_PRINT(tampon,n);
}

#endif

#if true
can converter = can();
const uint8_t VINGT_CM = 58;
uint8_t pourcentagePwmGauche = 53;
uint8_t pourcentagePwmDroite = 50;
while (true){
    uint16_t lectureDistance = converter.lecture(PA2);
    uint8_t lectureDistance8Bit = lectureDistance >> 2;
    char tampon1[100];
    int n1 = sprintf(tampon1,"La distance sur 255 est :  %d  \n", lectureDistance8Bit);
    DEBUG_PRINT(tampon1,n1);
    if (lectureDistance8Bit > VINGT_CM+3){
        pourcentagePwmGauche = 0;
    }
    else if (lectureDistance8Bit < VINGT_CM-3){
        pourcentagePwmDroite = 0;
    }
    else {
        pourcentagePwmGauche = 53;
        pourcentagePwmDroite = 50;
    }
    moteurs.avancerMoteur(pourcentagePwmGauche, pourcentagePwmDroite);
    // if (lectureDistance8Bit >  3 + VINGT_CM){ // 5,  100 et 500 valeur aleatoire
    //     moteurs.tournerGaucheMoteur(80);
    //     _delay_ms(600);
    //     moteurs.tournerDroiteMoteur(90);
    //     _delay_ms(700);
    //     moteurs.arreterMoteur();
    // }
    
    // else if (lectureDistance8Bit < VINGT_CM - 3) {
    //     moteurs.tournerDroiteMoteur(80);
    //     _delay_ms(700);
    //     moteurs.tournerGaucheMoteur(80);
    //     _delay_ms(600);
    //     moteurs.arreterMoteur();
    // }
    // else // dans l'intervalle
    //     moteurs.avancerMoteur(pourcentagePwmGauche, pourcentagePwmDroite);
}

#endif

#if false

DDRA = 0x00;
PORTA = 0x01;
uint8_t g = 255;
uint8_t d = 255;
initialisationEcriture();
for (int i=0; i < 20; i++) {
    if (ecrireMouv) {
moteurs.avancerMoteur(g, d);
    ecrireEnMemoire(g, d);
    _delay_ms(100);
}

}

moteurs.arreterMoteur();
_delay_ms(1000);
uint8_t adresseLecture = 0x00;
uint8_t adresseEcriture = getAdresseEcriture();
while(adresseLecture < adresseEcriture) 
	{
    g = getMemoire(adresseLecture);
    adresseLecture += 0x01;
    d = getMemoire(adresseLecture);
    adresseLecture += 0x01;
    moteurs.avancerMoteur(g, d);
    _delay_ms(100);
    }
moteurs.arreterMoteur();
#endif


#if false
DDRB = 0xff;
Bouton bouton = Bouton (&PINA, 0);
while (true) {
    if (bouton.estBoutonPresseTirage())
        PORTB = 1;
    else    
        PORTB = 0;
    char tampon1[100];
    int n1 = sprintf(tampon1,"Valeur de PINA :  %d  \n", PINA);
    DEBUG_PRINT(tampon1,n1);
}
#endif

}
