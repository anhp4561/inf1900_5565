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
void suivreLumiere(int intensiteLumiereGauche, int intensiteLumiereDroite);
bool estPresseD2(); // Classe Bouton ne marche pas avec Port D
uint8_t lectureCan(uint8_t pin);
void faireDemiTour();
void allumerLed5hz3secondes (char couleur);
void refaireParcours();
void configurerTimer();

const uint8_t N_ITERATIONS = 20;
const uint8_t VINGT_CM = 70/*58*/;
const uint8_t INTERVALLE_VINGT_CM = 10; // marge d'erreur pour 20 cm
const uint8_t PWM_MAXIMAL = 98;
const uint8_t DELAI_BOUTON = 30;
const uint8_t PWN_MAXIMAL = 255;
const uint8_t POURCENTAGE = 100;
const uint8_t DISTANCE_MUR_MINIMAL = 40;
const uint16_t DELAI_UNE_SECONDE = 1000;
const uint16_t DELAI_DEMI_SECONDE = 500;

volatile bool ecrireMouv = true;
volatile bool enregistrer = true;

enum class Etat {
    INIT,
    MODE_SUIVEUR_MUR,
    MODE_SUIVEUR_LUMIERE,
    ATTENTE,
    MODE_TOURNER,
    MODE_REPRISE,
    FIN_PARCOURS
};

Etat etatPresent = Etat::INIT;

int main () {
    initialisationUart();
    initialisationEcriture();
    configurerTimer();

    can can;
    Led led(&PORTB, 0, 1);
    Bouton boutonBlanc (&PINA,0);
    DDRA &= ~((1 << PA4) | (1 << PA6) | (1 << PA1));

    int sommeIntensiteGauche = 0;
    int sommeIntensiteDroite = 0;
    uint8_t lecturePhotoresistanceGauche = 0;
    uint8_t lecturePhotoresistanceDroite = 0;

    _delay_ms(DELAI_UNE_SECONDE);

    for (int i = 0; i < N_ITERATIONS ; i++){
        lecturePhotoresistanceGauche = lectureCan(PA4);
        lecturePhotoresistanceDroite = lectureCan(PA6);
        sommeIntensiteGauche += lecturePhotoresistanceGauche;
        sommeIntensiteDroite += lecturePhotoresistanceDroite;
    }
    uint8_t intensiteLumiereGauche = (sommeIntensiteGauche / N_ITERATIONS); 
    uint8_t intensiteLumiereDroite = (sommeIntensiteDroite / N_ITERATIONS); 

    if (intensiteLumiereGauche < 150 || intensiteLumiereDroite < 150)
        intensiteLumiereGauche = intensiteLumiereDroite = 150;

    else if (intensiteLumiereGauche > 255 || intensiteLumiereDroite > 255)
        intensiteLumiereGauche = intensiteLumiereDroite = 150;

    while (true){
        switch (etatPresent){
            case Etat::INIT:
                if (estPresseD2()){
                    allumerLed5hz3secondes('v');
                    etatPresent = Etat::MODE_SUIVEUR_MUR;
                } else if (boutonBlanc.estBoutonPresseTirage()) {
                    etatPresent = Etat::MODE_REPRISE;
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

                

                if (lecturePhotoresistanceGauche > (intensiteLumiereGauche) || lecturePhotoresistanceDroite > (intensiteLumiereDroite))
                    etatPresent = Etat::MODE_SUIVEUR_LUMIERE;

                 else if (estPresseD2())
                     etatPresent = Etat::FIN_PARCOURS;

                else if (boutonBlanc.estBoutonPresseTirage())
                    etatPresent = Etat::MODE_TOURNER;
                break;
                }

            case Etat::MODE_TOURNER:
                enregistrer = false;
                faireDemiTour();
                etatPresent = Etat::MODE_SUIVEUR_MUR;
                break;

            case Etat::MODE_REPRISE:
                refaireParcours();
                etatPresent = Etat::FIN_PARCOURS;
                break;

            case Etat::FIN_PARCOURS:
                led.allumerRougeLed();
                while (estPresseD2()) {}
                etatPresent = Etat::INIT;
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
    uint8_t pourcentagePwmGauche = 53;
    uint8_t pourcentagePwmDroite = 56;
    moteurs.avancerMoteur(pourcentagePwmGauche, pourcentagePwmDroite);
    _delay_ms(DELAI_UNE_SECONDE);
    uint8_t lectureDistance = lectureCan(PA1);    
    while (lectureDistance >= DISTANCE_MUR_MINIMAL/*20*/ ){ // 20 est une valeur arbitraire (sert a voir si on est pres d'un mur)
        if (lectureDistance > VINGT_CM + 3){
            if (pourcentagePwmGauche > 5) 
                pourcentagePwmGauche--;   
        }
        else if (lectureDistance < VINGT_CM-1){
            if (pourcentagePwmDroite > 5) {
                pourcentagePwmDroite --;
                _delay_ms(10);
            }
        }
        else {
            pourcentagePwmGauche = 53;
            pourcentagePwmDroite = 56;
        }
        moteurs.avancerMoteur(pourcentagePwmGauche, pourcentagePwmDroite);
        if (ecrireMouv) 
        {
            ecrireEnMemoire(pourcentagePwmGauche, pourcentagePwmDroite);
            ecrireMouv = false;
            // transmissionUart(pourcentagePwmGauche);
            // transmissionUart(pourcentagePwmDroite);
        }
        lectureDistance = lectureCan(PA1);
        char tampon4[50];
        int n4 = sprintf(tampon4,"La distance sur 255 est :  %d  \n", lectureDistance);
        DEBUG_PRINT(tampon4,n4);
    }
}

void suivreLumiere (int intensiteLumiereGauche, int intensiteLumiereDroite) {

    can can;
    Moteur moteurs;
    initialisationUart();
    uint8_t lecturePhotoresistanceGauche = /*readingLeft >> 2*/0 ; // takes out the 2 LSB 
    uint8_t lecturePhotoresistanceDroite = /*readingRight >> 2*/0 ;
    uint8_t pourcentageLeft = 0;
    uint8_t pourcentageRight = 0;
    uint8_t lectureDistance = lectureCan(PA1);

    while (/*lectureDistance <= 55 || lectureDistance > 63*/ /*lectureDistance != VINGT_CM*/ !(lectureDistance < VINGT_CM + INTERVALLE_VINGT_CM && lectureDistance > VINGT_CM - 5)){ // trouver bonne valeur min et max pour faire une bonne transition entre lumiere et mur
        lecturePhotoresistanceGauche = lectureCan(PA4);
        lecturePhotoresistanceDroite = lectureCan(PA6);
        if (lecturePhotoresistanceGauche <= intensiteLumiereGauche)
            pourcentageLeft = 0;
        else if ( lecturePhotoresistanceGauche > 215)
            pourcentageLeft = 98; // correction pour equilibrer moteurs
        
        else 
            pourcentageLeft  = (lecturePhotoresistanceGauche - intensiteLumiereGauche) * 100 / (255 - intensiteLumiereGauche);
           
        
        if (lecturePhotoresistanceDroite <= intensiteLumiereDroite)
            pourcentageRight = 0;
        
        else if (lecturePhotoresistanceDroite > 215 )
            pourcentageRight = 100;

        else {
            pourcentageRight = (lecturePhotoresistanceDroite - intensiteLumiereDroite) * 100 / (255 - intensiteLumiereDroite);
        }

        if (!(pourcentageLeft < 5 && pourcentageRight > 30) && !(pourcentageLeft > 30 && pourcentageRight < 5)) {
            moteurs.avancerMoteur(pourcentageLeft, pourcentageRight);
            if (ecrireMouv) 
            {
                ecrireEnMemoire(pourcentageLeft, pourcentageRight);
                ecrireMouv = false;
                // transmissionUart(pourcentageLeft);
                // transmissionUart(pourcentageRight);
            }

        } else if (pourcentageLeft < 5 && pourcentageRight > 30) {
            moteurs.tournerSurPlaceDroite(pourcentageRight, pourcentageRight);
            if (ecrireMouv) 
            {
                ecrireEnMemoire(pourcentageLeft, pourcentageRight + 120);
                ecrireMouv = false;
                // transmissionUart(pourcentageLeft);
                // transmissionUart(pourcentageRight);
            }

        } else if (pourcentageLeft > 30 && pourcentageRight < 5) {
            moteurs.tournerSurPlaceGauche(pourcentageLeft, pourcentageLeft);
            if (ecrireMouv) 
            {
                ecrireEnMemoire(pourcentageLeft + 120, pourcentageRight);
                ecrireMouv = false;
                // transmissionUart(pourcentageLeft);
                // transmissionUart(pourcentageRight);
            }
        }

        lectureDistance = lectureCan(PA1);
    }
}

void faireDemiTour () {
    can can;
    Moteur moteurs = Moteur();
    Led led(&PORTB, 0, 1);
    uint8_t pourcentagePwmGauche = 88;
    uint8_t pourcentagePwmDroite = 63;

    _delay_ms(DELAI_UNE_SECONDE);
    moteurs.avancerMoteur(pourcentagePwmGauche,pourcentagePwmDroite);
    for (int i = 0; i < 350; i++){
        led.allumerRougeLed();
        _delay_ms(5);
        led.allumerVertLed();
        _delay_ms(5);
    }
    uint8_t lectureDistance = lectureCan(PA1);
    while (lectureDistance < DISTANCE_MUR_MINIMAL){
        led.allumerRougeLed();
        _delay_ms(5);
        led.allumerVertLed();
        _delay_ms(5);
        lectureDistance = lectureCan(PA1);
    }
    led.eteindreLed(); 
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
    Moteur moteurs;
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
        } 
        else if (pourcentageDroite > 110) 
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