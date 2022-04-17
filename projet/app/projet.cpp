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
#include "ecrireMouvements.h"

void suivreMur();
void suivreLumiere(int intensiteLampe);
bool estPresseD2(); // Classe Bouton ne marche pas avec Port D
uint8_t lectureCan(uint8_t pin);
void faireDemiTour();
void allumerLed5hz3secondes (char couleur);
void refaireParcours();
void configurerTimer();

const uint8_t N_ITERATIONS = 20;
const double N_LECTURES = N_ITERATIONS * 2.0;
const uint8_t VINGT_CM = 58;
const uint8_t INTERVALLE_VINGT_CM = 2; // marge d'erreur pour 20 cm
const uint8_t PWM_MAXIMAL = 98;
const uint8_t DELAI_BOUTON = 30;
const uint8_t PWN_MAXIMAL = 255;
const uint8_t POURCENTAGE = 100;
const uint16_t DELAI_DEMI_TOUR = 5600;
const uint16_t DELAI_DEPASER_MUR = 800;
const uint8_t LIMITE_TOURNER_SUR_PLACE = 10;
const uint8_t INTESITE_MINIMAL = 150;

volatile bool ecrireMouv = true;
volatile bool enregistrer = true;
bool uTurnFait = false;

Moteur moteurs = Moteur();

enum class Etat {
    INIT,
    MODE_SUIVEUR_MUR,
    MODE_SUIVEUR_LUMIERE,
    ATTENTE,
    MODE_TOURNER,
    FIN_PARCOURS,
    MODE_REPRISE
};

Etat etatPresent = Etat::INIT;




int main () 
{
    initialisationUart();
    initialisationEcriture();
    configurerTimer();

    can can;
    Led led(&PORTB, 0, 1);
    Bouton boutonBlanc (&PINA,0);
    DDRA &= ~((1 << PA4) | (1 << PA6) | (1 << PA1));
    int sommeIntensite = 0;
    uint8_t lecturePhotoresistanceGauche = 0; 
    uint8_t lecturePhotoresistanceDroite = 0;


    for (int i = 0; i < N_ITERATIONS ; i++) {
        lecturePhotoresistanceGauche = lectureCan(PA4);
        lecturePhotoresistanceDroite = lectureCan(PA6);
        sommeIntensite += lecturePhotoresistanceGauche +lecturePhotoresistanceDroite;
    }
    uint8_t intensiteLumiere = (sommeIntensite / N_LECTURES); // Ajouter + 10  a l'intensite pour que ca soit plus restrictive ?

    if (intensiteLumiere > INTESITE_MINIMAL)
        intensiteLumiere = INTESITE_MINIMAL;

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
                suivreLumiere(intensiteLumiere);
                etatPresent = Etat::MODE_SUIVEUR_MUR;
                break;

            case Etat::ATTENTE: {
                uint8_t lectureDistance = lectureCan(PA1);
                uint8_t lecturePhotoresistanceGauche = lectureCan(PA4);
                uint8_t lecturePhotoresistanceDroite = lectureCan(PA6);


                if (lecturePhotoresistanceGauche > (intensiteLumiere + 30) || lecturePhotoresistanceDroite > (intensiteLumiere + 30))
                    etatPresent = Etat::MODE_SUIVEUR_LUMIERE;

                else if (estPresseD2())
                    etatPresent = Etat::FIN_PARCOURS;

                else if (boutonBlanc.estBoutonPresseTirage()) {
                    if (!(uTurnFait)){
                        uTurnFait = true;
                        etatPresent = Etat::MODE_TOURNER;
                    } else {
                        etatPresent = Etat::MODE_REPRISE;
                    }
                }

                break;
                }

            case Etat::MODE_TOURNER:
                enregistrer = false;
                led.allumerVertLed();
                faireDemiTour();
                led.eteindreLed();
                etatPresent = Etat::MODE_SUIVEUR_MUR;
                break;

            case Etat::MODE_REPRISE:
                refaireParcours();
                etatPresent = Etat::FIN_PARCOURS;
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
    uint8_t pourcentagePwmGauche = 58;
    uint8_t pourcentagePwmDroite = 57;

    moteurs.avancerMoteur(pourcentagePwmGauche, pourcentagePwmDroite);
    _delay_ms(DELAI_DEPASER_MUR);

    uint8_t lectureDistance = lectureCan(PA1);
    while (lectureDistance > 20) { // 20 est une valeur arbitraire (sert a voir si on est pres d'un mur)
        if (lectureDistance > VINGT_CM + INTERVALLE_VINGT_CM){
            pourcentagePwmGauche = 0; 
        }
        else if (lectureDistance < VINGT_CM - INTERVALLE_VINGT_CM){
            pourcentagePwmDroite = 0;
        }
        else {
            pourcentagePwmGauche = 58;
            pourcentagePwmDroite = 57;
        }
        moteurs.avancerMoteur(pourcentagePwmGauche, pourcentagePwmDroite);
        if (ecrireMouv) 
        {
            ecrireEnMemoire(pourcentagePwmGauche, pourcentagePwmDroite);
            ecrireMouv = false;
            transmissionUart(pourcentagePwmGauche);
            transmissionUart(pourcentagePwmDroite);
        }
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
    
    uint8_t pourcentagePwmGauche = 0;
    uint8_t pourcentagePwmDroite = 0;
    uint8_t lecturePhotoresistanceGauche = 0; 
    uint8_t lecturePhotoresistanceDroite = 0;
    uint8_t lectureDistance = lectureCan(PA1);

    while (lectureDistance <= 50 | lectureDistance > 63) { // 63 pour une distancce de 15cm et 50 pour une distance de 25 cm.
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

        if (pourcentagePwmGauche >  LIMITE_TOURNER_SUR_PLACE && pourcentagePwmDroite <  LIMITE_TOURNER_SUR_PLACE)
            moteurs.tournerSurPlaceGauche(pourcentagePwmGauche, pourcentagePwmGauche); 
        
        else if (pourcentagePwmGauche <  LIMITE_TOURNER_SUR_PLACE && pourcentagePwmDroite >  LIMITE_TOURNER_SUR_PLACE)
            moteurs.tournerSurPlaceDroite(pourcentagePwmDroite, pourcentagePwmDroite);

        lectureDistance = lectureCan(PA1);
    }
}

void faireDemiTour () {
    Moteur moteurs = Moteur();
    uint8_t pourcentagePwmGauche = 88;
    uint8_t pourcentagePwmDroite = 65;
    
    moteurs.avancerMoteur(pourcentagePwmGauche, pourcentagePwmDroite);
    _delay_ms(DELAI_DEMI_TOUR);
    pourcentagePwmGauche = 0;
    pourcentagePwmDroite = 0;
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

ISR(TIMER1_COMPA_vect)
{
    if (enregistrer) {
        ecrireMouv = true;
    }
}

void configurerTimer() {
    
    cli();
    TCNT1 = 0; // sets the timer to 0
    TCCR1A = 0; // We don't need OCnA or OCnB here (not generating PWM or outputting something when output compare) (WGM11 and WGM10 = 0, since we want CTC mode)
    // for CTC mode - > WGM13 WGM12 WGM11 WGM10  = 0 1 0 0 
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode and (CS12 and CS10 = 1, since we want /1024 prescalor)
    // for 1024 prescalor -> CS12 CS11 CS10 = 1 0 1
    TIMSK1 = (1 << OCIE1A); // Timer/Counter 1 output compare match A enabled
    OCR1A = 781; // where we compare timer 1
    sei();
}

void refaireParcours() {
    moteurs.arreterMoteur();
    _delay_ms(1000);
    uint8_t adresseLecture = 0x00;
    uint8_t adresseEcriture = getAdresseEcriture();
    uint8_t pourcentageGauche;
    uint8_t pourcentageDroite;
    while(adresseLecture < adresseEcriture) 
	{
        pourcentageGauche = getMemoire(adresseLecture);
        adresseLecture += 0x01;
        pourcentageDroite = getMemoire(adresseLecture);
        adresseLecture += 0x01;

        if (pourcentageGauche > 110) 
        {
            pourcentageGauche -= 120;
            moteurs.tournerSurPlaceGauche(pourcentageGauche, pourcentageDroite);
        } else if (pourcentageDroite > 110) 
        {
            pourcentageDroite -= 120;
            moteurs.tournerSurPlaceGauche(pourcentageGauche, pourcentageDroite);
        } else {
            moteurs.avancerMoteur(pourcentageGauche, pourcentageDroite);
        }

        _delay_ms(100);
    }
    moteurs.arreterMoteur();
}