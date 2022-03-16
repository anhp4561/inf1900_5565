#define F_CPU 8000000
#include <util/delay.h>
#include "machineVirtuel.h"
const uint8_t POURCENTAGE = 100;
const uint8_t VALEUR_MAX_TIMER0 = 255;
const uint8_t MULTIPLICATEUR_DELAI = 25;


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
// // configuration comme ca, pas final
// Led led1 (&PORTA,0,1);
// Led led2 (&PORTA,2,3);
// Led led3 (&PORTA,4,5);
// Led led4 (&PORTA,6,7);
// Led led5 (&PORTB,0,1);
// Led led6 (&PORTB,6,7); // skip PORTB 2,3,4,5 pour ne pas creer de conflit avec moteurs
// Led led7 (&PORTC,0,1);

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

void initialisationTimer1CtcVm (Timer1& timer1) {
    timer1.setCTC();
    timer1.setCompareToggle();
    timer1.setPrescaler(1); // prescalor = 1, je ne permet d'utiliser un nombre magique puisque c'est egal a 1
    TCNT1 = 0;
}

void jouerSonnerieVm (uint8_t note){
    // justification de mettre :OCR1A = F_CPU / ( 2 * frequencePwm); dans les cases
    // faire ainsi fait que si on donne un parametre non valide (inferieur a 45 ou superieur a 82), cette fonction ne fait rien
    double frequencePwm;
    switch (note){ 
        case 45:
            frequencePwm = 110.0;
            OCR1A = F_CPU / ( 2 * frequencePwm); // Toutes les valeurs de OCR1A ont ete obtenu avec l'equation qui se trouve a la page 96 de la documentation d'atmel
            break;
        case 46:
            frequencePwm = 116.54;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 47:
            frequencePwm = 123.47;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 48:
            frequencePwm = 130.81;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 49:
            frequencePwm = 138.59;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 50:
            frequencePwm = 146.83;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 51:
            frequencePwm = 155.56;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 52:
            frequencePwm = 164.81;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 53:
            frequencePwm = 174.61;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 54:
            frequencePwm = 185.0;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 55:
            frequencePwm = 196.0;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 56:
            frequencePwm = 207.65;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 57:
            frequencePwm = 220.0;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 58:
            frequencePwm = 233.08;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 59:
            frequencePwm = 246.94;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 60:
            frequencePwm = 261.63;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 61:
            frequencePwm = 277.18;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 62:
            frequencePwm = 293.66;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 63:
            frequencePwm = 311.13;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 64:
            frequencePwm = 329.63;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 65:
            frequencePwm = 349.23;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 66:
            frequencePwm = 369.99;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 67:
            frequencePwm = 392.0;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 68:
            frequencePwm = 415.30;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 69:
            frequencePwm = 440.0;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 70:
            frequencePwm = 466.16;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 71:
            frequencePwm = 493.88;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 72:
            frequencePwm = 523.25;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 73:
            frequencePwm = 554.37;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 74:
            frequencePwm = 587.33;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 75:
            frequencePwm = 622.25;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 76:
            frequencePwm = 659.26;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 77:
            frequencePwm = 698.46;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 78:
            frequencePwm = 739.99;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 79:
            frequencePwm = 783.99;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 80:
            frequencePwm = 830.61;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        case 81:
            frequencePwm = 880.0;
            OCR1A = F_CPU / ( 2 * frequencePwm); 
            break;
        default:
            break; 
    }
}
 

void arreterSonnerieVm () {
    OCR1A = 0;
}