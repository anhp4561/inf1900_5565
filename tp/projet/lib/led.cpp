/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : TRAVAIL_PRATIQUE 7
* Section # : 3
* Ã‰quipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
* date : 13-03-2022
 *
 * Description : Classe permet le controle d'une LED
 */

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

const uint8_t AMBRE_DELAI = 5;
/* Methode permet d'utiliser n'importe quel port et pin du microcontrolleur
entrée: port LEdPin1,LedPin2
*/
Led::Led(volatile uint8_t *port, int ledPin1, int ledPin2){
    port_ = port;
    ledPin1_ = ledPin1;
    ledPin2_ = ledPin2;
    // Justification pour la suite de if : switch case ne permettait pas d'utiliser port_ comme parametre
    if (port_ == &PORTA)
        DDRA |= (1 << ledPin1_) | (1 << ledPin2_);

    else if (port_ == &PORTB)
        DDRB |= (1 << ledPin1_) | (1 << ledPin2_);

    else if (port_ == &PORTC)
        DDRC |= (1 << ledPin1_) | (1 << ledPin2_);

    else if (port_ == &PORTD)
        DDRD |= (1 << ledPin1_) | (1 << ledPin2_);
}
/*
Methode permet d'allumer le led en rouge
*/
void Led::allumerRougeLed(){
    *port_ &= ~(1 << ledPin1_ | 1 << ledPin2_);
    *port_ |= 1 << ledPin1_;
}
/*
Methode permet d'allumer le led en vert
*/
void Led::allumerVertLed()
{
    *port_ &= ~(1 << ledPin1_ | 1 << ledPin2_);
    *port_ |= 1 << ledPin2_;
}
/*
Methode permet d'allumer le led en ambré
*/
void Led::allumerAmbreLed(int nIterations){
    for (int i = 0; i < nIterations; i++){
        allumerRougeLed();
        _delay_ms(AMBRE_DELAI);
        allumerVertLed();
        _delay_ms(AMBRE_DELAI);
    }
}
/*
Methode permet d'eteincre le led
*/
void Led::eteindreLed(){
    *port_ &= ~(1 << ledPin1_ | 1 << ledPin2_);
}
