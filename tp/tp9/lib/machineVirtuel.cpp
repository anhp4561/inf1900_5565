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

void allumerLedVm(int operande, Led& led0, Led& led1,Led& led2,Led& led3,Led& led4,Led& led5,Led& led6, Led& led7) { // changer le nom de variable operandes
if ((operande & 0x01) == 0x01) {
    led0.allumerRougeLed();
}

if ((operande & 0x02) == 0x02) {
    led1.allumerRougeLed();
}

if ((operande & 0x04) == 0x04) {
    led2.allumerRougeLed();
}

if ((operande & 0x08) == 0x08) {
    led3.allumerRougeLed();
}

if ((operande & 0x10) == 0x10) {
    led4.allumerRougeLed();
}

if ((operande & 0x20) == 0x20) {
    led5.allumerRougeLed();
}

if ((operande & 0x40) == 0x40) {
    led6.allumerRougeLed();
}

if ((operande & 0x80) == 0x80) {
    led7.allumerRougeLed();
}

}

void eteindreLedVm(Led& led){
    led.eteindreLed();
}

void eteindreLedVm(int operande, Led& led0, Led& led1,Led& led2,Led& led3,Led& led4,Led& led5,Led& led6, Led& led7) {
if ((operande & 0x01) == 0x01) {
    led0.eteindreLed();
}

if ((operande & 0x02) == 0x02) {
    led1.eteindreLed();
}

if ((operande & 0x04) == 0x04) {
    led2.eteindreLed();
}

if ((operande & 0x08) == 0x08) {
    led3.eteindreLed();
}

if ((operande & 0x10) == 0x10) {
    led4.eteindreLed();
}

if ((operande & 0x20) == 0x20) {
    led5.eteindreLed();
}

if ((operande & 0x40) == 0x40) {
    led6.eteindreLed();
}

if ((operande & 0x80) == 0x80) {
    led7.eteindreLed();
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

void Sonnerie::initialisationTimer1CtcVm () {
     cli();
    TCNT1 = 0;
    TCCR1A = (1 << COM1A0);
    TCCR1B = (1 << WGM12) | (1 << CS11); // CTC mode with 8 prescaler
    TCCR1C = 0;
    sei();

}

void Sonnerie::jouerSonnerieVm (uint8_t note){ 
uint8_t constante2Equation = 2;
    if (note >= 45 && note <= 81){
        uint16_t frequenceDefaut = 440;
        double constanteSoustractionEquation = 69.0;
        uint8_t constanteDivisionEquation = 12;
        frequencePwm_ = frequenceDefaut * pow(constante2Equation, (note-constanteSoustractionEquation) / constanteDivisionEquation);
    }
    OCR1A = F_CPU / ( constante2Equation * PRESCALER * frequencePwm_);  
}
 

void Sonnerie::arreterSonnerieVm () {
    OCR1A = 0;
}
