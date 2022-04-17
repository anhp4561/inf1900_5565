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
void suivreLumiere(int intensiteLumiereGauche, int intensiteLumiereDroite);
bool estPresseD2(); // Classe Bouton ne marche pas avec Port D
uint8_t lectureCan(uint8_t pin);
void faireDemiTour();
void allumerLed5hz3secondes (char couleur);

const uint8_t N_ITERATIONS = 20;
const double N_LECTURES = N_ITERATIONS * 2.0;
const uint8_t VINGT_CM = 58;
const uint8_t INTERVALLE_VINGT_CM = 2; // marge d'erreur pour 20 cm
const uint8_t PWM_MAXIMAL = 98;
const uint8_t DELAI_BOUTON = 30;
const uint8_t PWN_MAXIMAL = 255;
const uint8_t POURCENTAGE = 100;
const uint16_t DELAI_DEMI_TOUR = 5600;

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
    Led led(&PORTB, 0, 1);
    Bouton boutonBlanc (&PINA,0);
    DDRA &= ~((1 << PA4) | (1 << PA6) | (1 << PA1));

    int sommeIntensiteGauche = 0;
    int sommeIntensiteDroite = 0;
    uint8_t lecturePhotoresistanceGauche = 0;
    uint8_t lecturePhotoresistanceDroite = 0;

    for (int i = 0; i < N_ITERATIONS ; i++){
        lecturePhotoresistanceGauche = lectureCan(PA4);
        lecturePhotoresistanceDroite = lectureCan(PA6);
        sommeIntensiteGauche += lecturePhotoresistanceGauche;
        sommeIntensiteDroite += lecturePhotoresistanceDroite;
    }
    uint8_t intensiteLumiereGauche = (sommeIntensiteGauche / N_ITERATIONS) + 10; 
    uint8_t intensiteLumiereDroite = (sommeIntensiteDroite / N_ITERATIONS) + 10; 

    if (intensiteLumiereGauche < 180 || intensiteLumiereDroite < 180)
        intensiteLumiereGauche = intensiteLumiereDroite = 180;

    else if (intensiteLumiereGauche > 255 || intensiteLumiereDroite > 255)
        intensiteLumiereGauche = intensiteLumiereDroite = 140;

    while (true){
        switch (etatPresent){
            case Etat::INIT:
                if (estPresseD2()){
                    allumerLed5hz3secondes('v');
                    etatPresent = Etat::MODE_SUIVEUR_MUR;
                }
                break;

            case Etat::MODE_SUIVEUR_MUR:
                suivreMur();
                etatPresent = Etat::ATTENTE;
                break;

            case Etat::MODE_SUIVEUR_LUMIERE:
                suivreLumiere(intensiteLumiereGauche, intensiteLumiereDroite);
                etatPresent = Etat::MODE_SUIVEUR_MUR;
                break;

            case Etat::ATTENTE: {
                uint8_t lectureDistance = lectureCan(PA1);
                lecturePhotoresistanceGauche = lectureCan(PA4);
                lecturePhotoresistanceDroite = lectureCan(PA6);

                

                if (lecturePhotoresistanceGauche > (intensiteLumiereGauche + 30) | lecturePhotoresistanceDroite > (intensiteLumiereDroite + 30))
                    etatPresent = Etat::MODE_SUIVEUR_LUMIERE;

                // else if (estPresseD2()) // mis en commentaire pour tester sans le vrai robot
                //     etatPresent = Etat::FIN_PARCOURS;

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
    uint8_t pourcentagePwmGauche = 54;
    uint8_t pourcentagePwmDroite = 53;
    uint8_t lectureDistance = lectureCan(PA1);
    while (/*lectureDistance > 20*/!estPresseD2()) { // 20 est une valeur arbitraire (sert a voir si on est pres d'un mur)
        if (lectureDistance > VINGT_CM + INTERVALLE_VINGT_CM){
            pourcentagePwmGauche = 0; 
        }
        else if (lectureDistance < VINGT_CM - INTERVALLE_VINGT_CM){
            pourcentagePwmDroite = 0;
        }
        else {
            pourcentagePwmGauche = 54;
            pourcentagePwmDroite = 53;
        }
        moteurs.avancerMoteur(pourcentagePwmGauche, pourcentagePwmDroite);
        lectureDistance = lectureCan(PA1);
        char tampon4[50];
        int n4 = sprintf(tampon4,"La distance sur 255 est :  %d  \n", lectureDistance);
        DEBUG_PRINT(tampon4,n4);
    }
}

void suivreLumiere (int intensiteLumiereGauche, int intensiteLumiereDroite) {

    can converter = can();
    Moteur moteurs;
    initialisationUart();
    uint8_t lecturePhotoresistanceGauche = /*readingLeft >> 2*/0 ; // takes out the 2 LSB 
    uint8_t lecturePhotoresistanceDroite = /*readingRight >> 2*/0 ;
    uint8_t pourcentageLeft = 0;
    uint8_t pourcentageRight = 0;

    while (true/*lectureDistance <= 50 || lectureDistance > 63*/){
        lecturePhotoresistanceGauche = lectureCan(PA4);
        lecturePhotoresistanceDroite = lectureCan(PA6);
        if (lecturePhotoresistanceGauche <= intensiteLumiereGauche)
            pourcentageLeft = 0;
        else if ( lecturePhotoresistanceGauche > 235)
            pourcentageLeft = 90; // correction pour equilibrer moteurs
        
        else {
            pourcentageLeft  = (lecturePhotoresistanceGauche - intensiteLumiereGauche) * 100 / (255 - intensiteLumiereGauche);
            pourcentageLeft -= 20;
        }
        
        if (lecturePhotoresistanceDroite <= intensiteLumiereDroite)
            pourcentageRight = 0;
        
        else if (lecturePhotoresistanceDroite > 235 )
            pourcentageRight = 100;

        else {
            pourcentageRight = (lecturePhotoresistanceDroite - intensiteLumiereDroite) * 100 / (255 - intensiteLumiereDroite);
        }

        if (!(pourcentageLeft < 5 && pourcentageRight > 30) && !(pourcentageLeft > 30 && pourcentageRight < 5))
            moteurs.avancerMoteur(pourcentageLeft, pourcentageRight);

        else if (pourcentageLeft < 5 && pourcentageRight > 30)
            moteurs.tournerSurPlaceDroite(pourcentageRight-10, pourcentageRight);

        else if (pourcentageLeft > 30 && pourcentageRight < 5)
            moteurs.tournerSurPlaceGauche(pourcentageLeft-10, pourcentageLeft);
    
    }
}

void faireDemiTour () {
    _delay_ms(1000);
    Moteur moteurs = Moteur();
    Led led(&PORTB, 0, 1);
    uint8_t pourcentagePwmGauche = 88;
    uint8_t pourcentagePwmDroite = 65;
    
    moteurs.avancerMoteur(pourcentagePwmGauche,pourcentagePwmDroite);
    for (int i = 0; i < 500 ; i++){
        led.allumerRougeLed();
        _delay_ms(5);
        led.allumerVertLed();
        _delay_ms(5);
    }
}

void allumerLed5hz3secondes (char couleur) {
    Led led(&PORTB, 0, 1);
    if (couleur == 'v'){
        for (int i = 0; i < 15; i++){ // 15 pour que LED clignote pour 3 secondes
            led.allumerVertLed();
            _delay_ms(100);
            led.eteindreLed();
            _delay_ms(100);
        } 
    }
    else if (couleur == 'r'){
       for (int i = 0; i < 15; i++){ // 15 pour que LED clignote pour 3 secondes
            led.allumerRougeLed();
            _delay_ms(100);
            led.eteindreLed();
            _delay_ms(100);
        } 
    }             
}