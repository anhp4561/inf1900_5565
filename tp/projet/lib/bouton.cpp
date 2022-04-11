/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : TRAVAIL_PRATIQUE 7
* Section # : 3
* Ã‰quipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
date : 13-03-2022
 *
 * Description : 
 Cette classe permet le controle et les interactions avec un bouton poussoir
 */
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "bouton.h"

 /****************************************************************************************************************************************************
  * Nom :         Bouton
  * Description:  Methode permet l`utilisation du n'importe quel port du microcontrolleur
  * entree:       pin , boutonPin
  * Retour:       bouton
  ***************************************************************************************************************************************************/

Bouton::Bouton(volatile uint8_t *pin, int boutonPin){
    pin_ = pin;
    boutonPin_ = boutonPin;
    etat_ = Etat::AUCUN;
    // Justification pour la suite de if : switch case ne permettait pas d'utiliser pin_ comme parametre
    if (pin_ == &PINA)
        DDRA &= ~(1 << boutonPin_);

    else if (pin_ == &PINB)
        DDRB &= ~(1 << boutonPin_);

    else if (pin_ == &PINC)
        DDRC &= ~(1 << boutonPin_);

    else if (pin_ == &PIND)
        DDRD &= ~(1 << boutonPin_);
}

 /****************************************************************************************************************************************************
  * Nom :         estBoutonPresseRappel
  * Description:  Methode permet de savoir si le bouton est encore pressé
  * entree:       
  * Retour:       true ou false
  ***************************************************************************************************************************************************/
bool Bouton::estBoutonPresseRappel(){
    uint8_t rebond = 30;
    uint8_t masque = (1 << boutonPin_);
    uint8_t lectureBouton1 = *pin_ & masque;
    _delay_ms(rebond);
    uint8_t lectureBouton2 = *pin_ & masque;
    if (*pin_ & masque & (lectureBouton1 == lectureBouton2)){
        return true;
    }
    return false;
}
 /****************************************************************************************************************************************************
  * Nom :         actualiserEtat
  * Description:  Methode permet d'actualiser etat du bouton
  * entree:       
  * Retour:       void
  ***************************************************************************************************************************************************/
void Bouton::actualiserEtat()
{
    switch (etat_){
    case Etat::AUCUN:
        if (estBoutonPresseRappel()){
            etat_ = Etat::PRESSE;
        }
        break;
    case Etat::PRESSE:
        if (estBoutonPresseRappel()){
            etat_ = Etat::MAINTENU;
        }
        else {
            etat_ = Etat::RELACHE;
        }
        break;
    case Etat::MAINTENU:
        if (!estBoutonPresseRappel())
        {
            etat_ = Etat::RELACHE;
        }
        break;
    case Etat::RELACHE:
        if (estBoutonPresseRappel()){
            etat_ = Etat::PRESSE;
        }
        else{
            etat_ = Etat::AUCUN;
        }
        break;
    }
}
 /****************************************************************************************************************************************************
  * Nom :         estBoutonPresseTirage
  * Description:  Methode permet de savoir si le bouton est relacher 
  * entree:       
  * Retour:       bool
  ***************************************************************************************************************************************************/
bool Bouton::estBoutonPresseTirage(){
    return !(estBoutonPresseRappel());
}
