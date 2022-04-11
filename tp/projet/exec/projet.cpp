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
bool estPresseD2(); // Classe Bouton ne marche pas avec Port D
uint8_t lectureCan(uint8_t pin);
void faireDemiTour();

const uint8_t N_ITERATIONS = 10;
const double N_LECTURES = N_ITERATIONS * 2.0;
const uint8_t VINGT_CM = 58;
const uint8_t INTERVALLE_VINGT_CM = 2;
const uint8_t PWM_MAXIMAL = 98;
const uint8_t DELAI_BOUTON = 30;
const uint8_t PWN_MAXIMAL = 255;
const uint8_t POURCENTAGE = 100;
const uint16_t DELAI_DEMI_TOUR = 5500;

enum class Etat {
    INIT,
    MODE_SUIVEUR_MUR,
    MODE_SUIVEUR_LUMIERE,
    ATTENTE,
    MODE_TOURNER,
    FIN_PARCOURS
};

Etat etatPresent = Etat::INIT;

int main () {
    initialisationUart();
    can can;
    Bouton boutonBlanc (&PINA,0);
    DDRA &= ~((1 << PA4) | (1 << PA6) | (1 << PA1));
    Led led(&PORTB, 0, 1);
    int sommeIntensite = 0;
    uint8_t lecturePhotoresistanceGauche = 0; 
    uint8_t lecturePhotoresistanceDroite = 0;


    for (int i = 0; i < N_ITERATIONS ; i++) {
        lecturePhotoresistanceGauche = lectureCan(PA4);
        lecturePhotoresistanceDroite = lectureCan(PA6);
        sommeIntensite += lecturePhotoresistanceGauche +lecturePhotoresistanceDroite;
    }
    uint8_t intensiteLumiere = sommeIntensite / N_LECTURES; 

    while (true){
        switch (etatPresent){
            case Etat::INIT:
                if (estPresseD2()){
                    for (int i = 0; i < 15; i++){ // 15 pour que LED clignote pour 3 secondes
                    led.allumerVertLed();
                    _delay_ms(100);
                    led.eteindreLed();
                    _delay_ms(100);
                    }
                    etatPresent = Etat::MODE_SUIVEUR_MUR;
                }
                break;

            case Etat::MODE_SUIVEUR_MUR:
                suivreMur();
                etatPresent = Etat::ATTENTE;
                break;

            case Etat::MODE_SUIVEUR_LUMIERE:
                suivreLumiere(intensiteLumiere);
                etatPresent = Etat::MODE_SUIVEUR_MUR;
                break;

            case Etat::ATTENTE: {
                uint8_t lectureDistance = lectureCan(PA1);
                uint8_t lecturePhotoresistanceGauche = lectureCan(PA4);
                uint8_t lecturePhotoresistanceDroite = lectureCan(PA6);

                // if (lectureDistance > 20 & lectureDistance < 80)
                //     etatPresent = Etat::MODE_SUIVEUR_MUR;

                if (lecturePhotoresistanceGauche > (intensiteLumiere + 30) | lecturePhotoresistanceDroite > (intensiteLumiere + 30))
                    etatPresent = Etat::MODE_SUIVEUR_LUMIERE;

                else if (estPresseD2())
                    etatPresent = Etat::FIN_PARCOURS;

                else if (boutonBlanc.estBoutonPresseTirage())
                    etatPresent = Etat::MODE_TOURNER;
                break;
                }

            case Etat::MODE_TOURNER:
                led.allumerVertLed();
                faireDemiTour();
                led.eteindreLed();
                etatPresent = Etat::MODE_SUIVEUR_MUR;
                break;

            case Etat::FIN_PARCOURS:
                led.allumerRougeLed();
                break;
        }
    }
}

bool estPresseD2 (){
    uint8_t d2BoutonLecture1 = PIND;
    _delay_ms(DELAI_BOUTON);
    uint8_t d2BoutonLecture2 = PIND;
    return ((d2BoutonLecture1 & (1<<PD2)) && d2BoutonLecture1 == d2BoutonLecture2);
}

uint8_t lectureCan(uint8_t pin){
    can can;
    uint16_t lectureCan16Bit = can.lecture(pin);
    return lectureCan16Bit >> 2;
}

void suivreMur() {
    can can;
    Moteur moteurs = Moteur();
    uint8_t pourcentagePwmGauche = 51;
    uint8_t pourcentagePwmDroite = 50;
    uint8_t lectureDistance = lectureCan(PA1);
    while (lectureDistance > 20) { // 20 est une valeur arbitraire (sert a voir si on est pres d'un mur)
        if (lectureDistance > VINGT_CM + INTERVALLE_VINGT_CM){
            pourcentagePwmGauche = 0; 
        }
        else if (lectureDistance < VINGT_CM - INTERVALLE_VINGT_CM){
            pourcentagePwmDroite = 0;
        }
        else {
            pourcentagePwmGauche = 51;
            pourcentagePwmDroite = 50;
        }
        moteurs.avancerMoteur(pourcentagePwmGauche, pourcentagePwmDroite);
        lectureDistance = lectureCan(PA1);
        char tampon4[50];
        int n4 = sprintf(tampon4,"La distance sur 255 est :  %d  \n", lectureDistance);
        DEBUG_PRINT(tampon4,n4);
    }
}

void suivreLumiere (int intensiteLampe) {
    char tampon[50];
    // int n = sprintf(tampon,"pLeft : %d     pRight : %d\n", pourcentagePwmGauche, pourcentagePwmDroite);
    int n  = sprintf (tampon, "in suivreLumiere\n");
    DEBUG_PRINT(tampon,n);
    can can;
    Moteur moteurs = Moteur();
    uint8_t pourcentagePwmGauche = 0;
    uint8_t pourcentagePwmDroite = 0;
    uint8_t lecturePhotoresistanceGauche = 0; 
    uint8_t lecturePhotoresistanceDroite = 0;
    uint8_t lectureDistance = lectureCan(PA1);

    while (lectureDistance <= 50 | lectureDistance > 63) { // 30 est une valeur arbitraire (sert a voir si on est pres d'un mur)
        lecturePhotoresistanceGauche = lectureCan(PA4);
        lecturePhotoresistanceDroite = lectureCan(PA6);
        if (lecturePhotoresistanceGauche <= intensiteLampe)
            pourcentagePwmGauche = 0;

        else 
            pourcentagePwmGauche  = (lecturePhotoresistanceGauche - intensiteLampe) * POURCENTAGE / (PWM_MAXIMAL - intensiteLampe);
        
        if (lecturePhotoresistanceDroite <= intensiteLampe)
            pourcentagePwmDroite = 0;

        else
            pourcentagePwmDroite = (lecturePhotoresistanceDroite - intensiteLampe) * POURCENTAGE / (PWM_MAXIMAL - intensiteLampe);

        moteurs.avancerMoteur(pourcentagePwmGauche, pourcentagePwmDroite);
        lectureDistance = lectureCan(PA1);
    }
}

void faireDemiTour () {
    Moteur moteurs = Moteur();
    uint8_t pourcentagePwmGauche = 88;
    uint8_t pourcentagePwmDroite = 65;
    
    moteurs.avancerMoteur(pourcentagePwmGauche,pourcentagePwmDroite);
    _delay_ms(DELAI_DEMI_TOUR);
    pourcentagePwmGauche = 0;
    pourcentagePwmDroite = 0;
}