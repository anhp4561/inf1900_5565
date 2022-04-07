#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <can.h>
#include "led.h"
#include "rs232.h"
#include "bouton.h"
#include "moteur.h"
#include "debug.h"
#include "sonnerie.h"

void suivreMur();
void suivreLumiere(int intensiteLampe);

const uint8_t N_ITERATIONS = 10;
const double N_LECTURES = N_ITERATIONS * 2.0;
const uint8_t VINGT_CM = 58;
const uint8_t INTERVALLE_VINGT_CM = 3;
const uint8_t PWM_MAXIMAL = 98;

int main () {
    initialisationUart();
    can can;
    Bouton bouton = Bouton (&PINA, 0); // estBoutonPresseRappel();
    DDRA &= ~((1 << PA4) | (1 << PA6) | (1 << PA2));
    int sommeIntensite = 0;
    uint16_t readingLeft;
    uint16_t readingRight;
    uint8_t readingLeft8; 
    uint8_t readingRight8;
    bool sortirLoop = false;

    for (int i = 0; i < N_ITERATIONS ; i++) {
        readingLeft = can.lecture(PA4);
        readingRight = can.lecture(PA6);
        readingLeft8 = readingLeft >> 2 ; // takes out the 2 LSB
        readingRight8 = readingRight >> 2 ;
        sommeIntensite += readingLeft8 +readingRight8;
    }
    uint8_t intensiteLumiere = sommeIntensite / N_LECTURES; 
    
    while (true){
        char tampon2[50];
        // int n2= sprintf(tampon2,"readingLeft : %d     readingRight : %d\n\n", readingLeft8, readingRight8);
        int n2 = sprintf (tampon2, "in main\n");
        DEBUG_PRINT(tampon2,n2);
        suivreMur();
        char tampon8[50];
        int n8 = sprintf (tampon8, "retour dans le main\n");
        DEBUG_PRINT(tampon8, n8);
        readingLeft = can.lecture(PA4);
        readingRight = can.lecture(PA6);
        readingLeft8 = readingLeft >> 2 ; // takes out the 2 LSB
        readingRight8 = readingRight >> 2 ;
        char tampon6[100];
        int n6 = sprintf (tampon6, "juste avant loop\n");
        //int n6 = sprintf(tampon6,"rLeft %d, rRight %d, intesite %d et bouton %d\n", readingLeft8, readingRight8, intensiteLumiere, bouton.estBoutonPresseTirage());
        DEBUG_PRINT(tampon6,n6);
        while (readingLeft8 < intensiteLumiere | readingRight8 | intensiteLumiere | !(bouton.estBoutonPresseTirage())){
            readingLeft = can.lecture(PA4);
            readingRight = can.lecture(PA6);
            readingLeft8 = readingLeft >> 2 ; // takes out the 2 LSB
            readingRight8 = readingRight >> 2 ;
            if (bouton.estBoutonPresseTirage())
                sortirLoop = true;
            char tampon5[50];
            int n5 = sprintf(tampon5,"rLeft %d, rRight %d, intesite %d et bouton %d\n", readingLeft8, readingRight8, intensiteLumiere, bouton.estBoutonPresseTirage());
            DEBUG_PRINT(tampon5,n5);
        }
        if (sortirLoop) {
            sortirLoop = false;
            break;
        }
        suivreLumiere(intensiteLumiere);
    }
} 

// faire une fonction pour lire, puis convertir

void suivreMur() {
    char tampon1[50];
    // int n1 = sprintf(tampon1,"La distance sur 255 est :  %d  \n", lectureDistance8Bit);
    int n1 = sprintf (tampon1, "in suivreMur\n");
    DEBUG_PRINT(tampon1,n1);
    can can;
    Moteur moteurs = Moteur();
    uint8_t pourcentagePwmGauche = 55;
    uint8_t pourcentagePwmDroite = 50;
    uint16_t lectureDistance = can.lecture(PA2);
    uint8_t lectureDistance8Bit = lectureDistance >> 2;
    while (lectureDistance8Bit > 20) { // 20 est une valeur arbitraire (sert a voir si on est pres d'un mur)
        if (lectureDistance8Bit > VINGT_CM + INTERVALLE_VINGT_CM){
            pourcentagePwmGauche = 0; 
        }
        else if (lectureDistance8Bit < VINGT_CM - INTERVALLE_VINGT_CM){
            pourcentagePwmDroite = 0;
        }
        else {
            pourcentagePwmGauche = 55;
            pourcentagePwmDroite = 50;
        }
        moteurs.avancerMoteur(pourcentagePwmGauche, pourcentagePwmDroite);
        lectureDistance = can.lecture(PA2);
        lectureDistance8Bit = lectureDistance >> 2;
        char tampon4[50];
        int n4 = sprintf(tampon4,"La distance sur 255 est :  %d  \n", lectureDistance8Bit);
        DEBUG_PRINT(tampon4,n4);
    }
    char tampon7[50];
    int n7 = sprintf(tampon7,"fin loop de suivreMur\n");
    DEBUG_PRINT(tampon7, n7);

}

void suivreLumiere (int intensiteLampe) {
    char tampon[50];
    // int n = sprintf(tampon,"pLeft : %d     pRight : %d\n", pourcentageLeft, pourcentageRight);
    int n  = sprintf (tampon, "in suivreLumiere\n");
    DEBUG_PRINT(tampon,n);
    can can;
    Moteur moteurs = Moteur();
    uint8_t pourcentageLeft = 0;
    uint8_t pourcentageRight = 0;
    uint16_t readingLeft;
    uint16_t readingRight;
    uint8_t readingLeft8; 
    uint8_t readingRight8;

    uint16_t lectureDistance = can.lecture(PA2);
    uint8_t lectureDistance8Bit = lectureDistance >> 2;
    while (lectureDistance8Bit < 20) { // 20 est une valeur arbitraire (sert a voir si on est pres d'un mur)
        readingLeft = can.lecture(PA4);
        readingRight = can.lecture(PA6);
        readingLeft8 = (readingLeft >> 2) ; // takes out the 2 LSB
        readingRight8 = (readingRight >> 2) ;
        if (readingLeft8 <= intensiteLampe)
            pourcentageLeft = 0;
        else 
            pourcentageLeft  = (readingLeft8 - intensiteLampe) * 100 / (255 - intensiteLampe);
        
        if (readingRight8 <= intensiteLampe)
            pourcentageRight = 0;
        else
            pourcentageRight = (readingRight8 - intensiteLampe) * 100 / (255 - intensiteLampe);

        moteurs.avancerMoteur(pourcentageLeft, pourcentageRight);
        uint16_t lectureDistance = can.lecture(PA2);
        uint8_t lectureDistance8Bit = lectureDistance >> 2;
    }

}