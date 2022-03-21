
#include "sonnerie.h"
const uint8_t PRESCALER = 8;
// Sonnerie 

Sonnerie::Sonnerie(){
    initialisationTimer1Ctc ();
}

Sonnerie::~Sonnerie(){
    cli();
    TCCR1A = TCCR1B = TIMSK1 = 0;
    sei();
}

void Sonnerie::initialisationTimer1Ctc () {
    cli();
    TCNT1 = 0;
    TCCR1A = (1 << COM1A0);
    TCCR1B = (1 << WGM12) | (1 << CS11); // CTC mode with 8 prescaler
    TCCR1C = 0;
    sei();

}

void Sonnerie::jouerSonnerie (uint8_t note){ 
uint8_t constante2Equation = 2;
    if (note >= 45 && note <= 81){
        uint16_t frequenceDefaut = 440;
        double constanteSoustractionEquation = 69.0;
        uint8_t constanteDivisionEquation = 12;
        frequencePwm_ = frequenceDefaut * pow(constante2Equation, (note-constanteSoustractionEquation) / constanteDivisionEquation);
    }
    OCR1A = F_CPU / ( constante2Equation * PRESCALER * frequencePwm_);  
}
 

void Sonnerie::arreterSonnerie () {
    OCR1A = 0;
}