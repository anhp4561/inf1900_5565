#define F_CPU 8000000
#include <util/delay.h>
#include "machineVirtuel.h"

const uint8_t POURCENTAGE = 100;
const uint8_t VALEUR_MAX_TIMER0 = 255;
const uint8_t MULTIPLICATEUR_DELAI = 25;
const uint8_t PRESCALER = 8;


void avancerMoteurVm(int pourcentagePwm, Moteur& moteurs){
    pourcentagePwm = pourcentagePwm * POURCENTAGE / VALEUR_MAX_TIMER0;
    moteurs.avancerMoteur(pourcentagePwm, pourcentagePwm);
}

void reculerMoteurVm (int pourcentagePwm, Moteur& moteurs){
    pourcentagePwm = pourcentagePwm * POURCENTAGE / VALEUR_MAX_TIMER0;
    moteurs.reculerMoteur(pourcentagePwm, pourcentagePwm);
}

void arreter (Moteur& moteurs) {
    moteurs.arreterMoteur();
}


void tournerDroiteMoteurVm (Moteur& moteurs) {
    int pourcentagePwm = 100;
    moteurs.tournerDroiteMoteur (pourcentagePwm);
    _delay_ms(50); // solution band-aid, voir avec equipe quel timer utiliser

    // Section prise du tp6_pb1.cpp : faire qqch comme ca lorsqu'on sait quel timer utiliser
    // initialisationTimer();
    // sei(); 
    // while (isButtonPressed() && gCounter < 120)
    // ; // does nothing while gCounter goes up and button is pressed
    // cli(); 

    moteurs.arreterMoteur(); // pourrais changer a moteurs.avancerMoteurs()
}

void tournerGaucheMoteurVm (Moteur& moteurs) {
    int pourcentagePwm = 100;
    moteurs.tournerGaucheMoteur (pourcentagePwm);
    _delay_ms(50); // voir tournerDroite
    moteurs.arreterMoteur();
}

void allumerLedVm(Led& led){
    led.allumerRougeLed();
}

void allumerLedVm(int operande, Led& led1,Led& led2,Led& led3,Led& led4,Led& led5,Led& led6, Led& led7) { // changer le nom de variable operandes
    switch (operande) {
        case 1 :
            led1.allumerRougeLed();
            break;
        case 2 :
            led2.allumerRougeLed();
            break;
        case 4 :
            led3.allumerRougeLed();
            break;
        case 8 :
            led4.allumerRougeLed();
            break;
        case 16 :
            led5.allumerRougeLed();
            break;
        case 32 :
            led6.allumerRougeLed();
            break;
        case 64 :
            led7.allumerRougeLed();
            break;
        case 127 :
            led1.allumerRougeLed();
            led2.allumerRougeLed();
            led3.allumerRougeLed();
            led4.allumerRougeLed();
            led5.allumerRougeLed();
            led6.allumerRougeLed();
            led7.allumerRougeLed();
            break;
        default:
            break;
    }

}

void eteindreLedVm(Led& led){
    led.eteindreLed();
}

void eteindreLedVm(int operande, Led& led1,Led& led2,Led& led3,Led& led4,Led& led5,Led& led6, Led& led7) {
    switch (operande) {
        case 1 :
            led1.eteindreLed();
            break;
        case 2 :
            led2.eteindreLed();
            break;
        case 4 :
            led3.eteindreLed();
            break;
        case 8 :
            led4.eteindreLed();
            break;
        case 16 :
            led5.eteindreLed();
            break;
        case 32 :
            led6.eteindreLed();
            break;
        case 64 :
            led7.eteindreLed();
            break;
        case 127 :
            led1.eteindreLed();
            led2.eteindreLed();
            led3.eteindreLed();
            led4.eteindreLed();
            led5.eteindreLed();
            led6.eteindreLed();
            led7.eteindreLed();
            break;
        default:
            break;
    }
}

// Delai

void attendreVm (const uint8_t operande) {
    for (int i = 0; i < operande ; i++){
        _delay_ms(MULTIPLICATEUR_DELAI); 
        // solution extremement band-aid
        // je voulais faire const int delai = operande * MULTIPLICATEUR_DELAI;
        // _delay_ms(delai); mais ca ne marche pas puisque operande n'est pas une constante, demander a un charge ?
    }
}

// Sonnerie 

Sonnerie::Sonnerie(){
    initialisationTimer1CtcVm ();
}

Sonnerie::~Sonnerie(){
    cli();
    TCCR1A = TCCR1B = TIMSK1 = 0;
    sei();
}

void Sonnerie::initialisationTimer1CtcVm (/*Timer1& timer1*/) {
    // timer1.setWaveform(Waveform::CTC);
    // timer1.setCompareOutput(CompareOutput::TOGGLE);
    // timer1.setPrescaler(PRESCALER);
    // timer1.setInterupts(true, false, false); // compare A
    // TCNT1 = 0;
     cli();
    TCNT1 = 0;
    TCCR1A = 0; //(1 << COM1A0);
    TCCR1B = (1 << WGM12) | (1 << CS11); // CTC mode with 8 prescaler
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A);
    sei();

}

void Sonnerie::jouerSonnerieVm (uint8_t note){
    // justification de mettdans les cases
    // faire ainsi fait que si on donne un parametre non valide (inferieur a 45 ou superieur a 82), cette fonction ne fait rien
    switch (note){ 
        case 45:
            frequencePwm_ = 110.0; // Toutes les valeurs de OCR1A ont ete obtenu avec l'equation qui se trouve a la page 96 de la documentation d'atmel
            break;
        case 46:
            frequencePwm_ = 116.54;
            break;
        case 47:
            frequencePwm_ = 123.47;
            break;
        case 48:
            frequencePwm_ = 130.81;
            break;
        case 49:
            frequencePwm_ = 138.59;
            break;
        case 50:
            frequencePwm_ = 146.83;
            break;
        case 51:
            frequencePwm_ = 155.56;
            break;
        case 52:
            frequencePwm_ = 164.81;
            break;
        case 53:
            frequencePwm_ = 174.61;
            break;
        case 54:
            frequencePwm_ = 185.0;
            break;
        case 55:
            frequencePwm_ = 196.0;
            break;
        case 56:
            frequencePwm_ = 207.65;
            break;
        case 57:
            frequencePwm_ = 220.0;
            break;
        case 58:
            frequencePwm_ = 233.08;
            break;
        case 59:
            frequencePwm_ = 246.94;
            break;
        case 60:
            frequencePwm_ = 261.63;
            break;
        case 61:
            frequencePwm_ = 277.18;
            break;
        case 62:
            frequencePwm_ = 293.66;
            break;
        case 63:
            frequencePwm_ = 311.13;
            break;
        case 64:
            frequencePwm_ = 329.63;
            break;
        case 65:
            frequencePwm_ = 349.23;
            break;
        case 66:
            frequencePwm_ = 369.99;
            break;
        case 67:
            frequencePwm_ = 392.0;
            break;
        case 68:
            frequencePwm_ = 415.30;
            break;
        case 69:
            frequencePwm_ = 440.0;
            break;
        case 70:
            frequencePwm_ = 466.16;
            break;
        case 71:
            frequencePwm_ = 493.88;
            break;
        case 72:
            frequencePwm_ = 523.25;
            break;
        case 73:
            frequencePwm_ = 554.37;
            break;
        case 74:
            frequencePwm_ = 587.33;
            break;
        case 75:
            frequencePwm_ = 622.25;
            break;
        case 76:
            frequencePwm_ = 659.26;
            break;
        case 77:
            frequencePwm_ = 698.46;
            break;
        case 78:
            frequencePwm_ = 739.99;
            break;
        case 79:
            frequencePwm_ = 783.99;
            break;
        case 80:
            frequencePwm_ = 830.61;
            break;
        case 81:
            frequencePwm_ = 880.0;
            break;
        default:
            break; 
    }
    OCR1A = F_CPU / ( 2 * PRESCALER * frequencePwm_); 
}
 

void Sonnerie::arreterSonnerieVm () {
    OCR1A = 0;
}