/*
 * Nom : Ben Jemaa Manel (1871842)
 * Travail : TRAVAIL_PRATIQUE 4
 * Section # : 3
 * Ã‰quipe # : 65
*/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

void ajustementPwm ( uint8_t pourcentage ) {

// mise à un des sorties OC1A et OC1B sur comparaison

// réussie en mode PWM 8 bits, phase correcte

// et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5

// page 130 de la description technique du ATmega324PA)

double pmw = (pourcentage / 100) * 254;

OCR1A = pmw;
OCR1B = pmw  ;// 2^8-1=255-1=254


// division d'horloge par 8 - implique une fréquence de PWM fixe

TCCR1A = (1 << WGM10) | (1 << COM1B1) | (1 << WGM11) | (1 << COM1A1);
//TCCR1A |= (1 << WGM11) | (1 << COM1A1);

TCCR1B = (1 << CS11);

TCCR1C = 0;

}
int main() {

  DDRB=0xff;
  DDRD=0xff;
  while (true){
  ajustementPwm(100);
  _delay_ms(2000);
  ajustementPwm(75);
  _delay_ms(2000);
    ajustementPwm(50);
  _delay_ms(2000);
    ajustementPwm(25);
  _delay_ms(2000);
  
  
    
  }


}
