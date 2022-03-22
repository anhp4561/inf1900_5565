/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : TRAVAIL_PRATIQUE 7
* Section # : 3
* Equipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
* date : 21-03-2022
* Description : Cette classe permet de jouer une sonnerie
 */

#include "sonnerie.h"
const uint8_t PRESCALER = 8;


 /****************************************************************************************************************************************************
  * Nom :         Sonnerie()
  * Description:  constructeur
  * entree:       
  * Retour:       sonnerie
  ***************************************************************************************************************************************************/
Sonnerie::Sonnerie(){
    initialisationTimer1Ctc ();
}


 /****************************************************************************************************************************************************
  * Nom :         ~Sonnerie()
  * Description:  destructeur
  * entree:       
  * Retour:       sonnerie
  ***************************************************************************************************************************************************/
Sonnerie::~Sonnerie(){
    cli();
    TCCR1A = TCCR1B = TIMSK1 = 0;
    sei();
}

 /****************************************************************************************************************************************************
  * Nom :         initialisationTimer1Ctc()
  * Description:  initialiser le CTC du timer1
  * entree:       
  * Retour:       void
  ***************************************************************************************************************************************************/
void Sonnerie::initialisationTimer1Ctc () {
    cli();
    TCNT1 = 0;
    TCCR1A = (1 << COM1A0);
    TCCR1B = (1 << WGM12) | (1 << CS11); // CTC mode with 8 prescaler
    TCCR1C = 0;
    sei();
}
 /****************************************************************************************************************************************************
  * Nom :         jouerSonnerie()
  * Description:  permet de jouer une note
  * entree:       note
  * Retour:       void
  ***************************************************************************************************************************************************/
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
  /****************************************************************************************************************************************************
  * Nom :         arreterSonnerie()
  * Description:  permet d'arreter une sonnerie
  * entree:       
  * Retour:       void
  ***************************************************************************************************************************************************/

void Sonnerie::arreterSonnerie () {
    OCR1A = 0;
}