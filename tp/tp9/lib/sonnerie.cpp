
#include "sonnerie.h"
//#include <util/delay.h>
const uint8_t PRESCALER = 8;
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
    TCNT1 = 0;
    TCCR1A = 0; //(1 << COM1A0);
    TCCR1B = (1 << WGM12) | (1 << CS11); // CTC mode with 8 prescaler
    TCCR1C = 0;
    sei();

}

void Sonnerie::jouerSonnerieVm (uint8_t note){
    if (note >= 45 && note <= 81){
        uint16_t frequenceDefaut = 440;
        uint8_t constante2Equation = 2;
        uint8_t constanteSoustractionEquation = 69;
        uint8_t constanteDivisionEquation = 12;
        frequencePwm_ = frequenceDefaut * pow(constante2Equation, (note-constanteSoustractionEquation) / constanteDivisionEquation);
    }
    OCR1A = F_CPU / ( 2 * PRESCALER * frequencePwm_); 
}
 

void Sonnerie::arreterSonnerieVm () {
    OCR1A = 0;
}