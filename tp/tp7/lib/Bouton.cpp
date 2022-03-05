#include "Bouton.h"
#define F_CPU 800000
#include <avr/io.h>
#include <util/delay.h>

Bouton::Bouton (volatile uint8_t *pin, int boutonPin){
    pin_ = pin;
    boutonPin_ = boutonPin;
}

bool Bouton::estBoutonPresseRappel(){
    uint8_t rebond = 10;
    uint8_t masque = (1 << boutonPin_);
    if (*pin_ & masque){
        _delay_ms(rebond);
        return true;
    }
    return false;
}

bool Bouton::estBoutonPresseTirage(){
    return !(estBoutonPresseRappel());
}
