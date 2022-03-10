#include "Bouton.h"
#define F_CPU 800000
#include <avr/io.h>
#include <util/delay.h>

Bouton::Bouton (volatile uint8_t *pin, int boutonPin){
    pin_ = pin;
    boutonPin_ = boutonPin;
    etat_ = Etat::AUCUN;
    // Justification pour la suite de if : switch case ne permettait pas d'utiliser pin_ comme parametre
    if (pin_ == &PINA)
        DDRA &= ~(1<< boutonPin_);

    else if (pin_ == &PINB)
        DDRB &= ~(1<< boutonPin_);

    else if (pin_ == &PINC)
        DDRC &= ~(1<< boutonPin_);
    
    else if (pin_ == &PIND)
        DDRD &= ~(1<< boutonPin_);
}

bool Bouton::estBoutonPresseRappel(){
    uint8_t rebond = 30;
    uint8_t masque = (1 << boutonPin_);
    if (*pin_ & masque){
        _delay_ms(rebond);
        return true;
    }
    return false;
}


void Bouton::actualiserEtat() {
    switch (etat_)
    {
    case Etat::AUCUN:
        if (estBoutonPresseRappel()) {
            etat_ = Etat::PRESSE;
        }
        break;
    case Etat::PRESSE:
        if (estBoutonPresseRappel()) {
            etat_ = Etat::MAINTENU;
        } else {
            etat_ = Etat::RELACHE;
        }
        break;
    case Etat::MAINTENU:
        if (!estBoutonPresseRappel()) {
            etat_ = Etat::RELACHE;
        }
        break;
    case Etat::RELACHE:
        if (estBoutonPresseRappel()) {
            etat_ = Etat::PRESSE;
        } else {
            etat_ = Etat::AUCUN;
        }
        break;
    }
}

bool Bouton::estBoutonPresseTirage(){
    return !(estBoutonPresseRappel());
}
