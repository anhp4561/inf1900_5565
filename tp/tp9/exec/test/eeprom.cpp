#include "eeprom.h"

using namespace std;


Memoire::Memoire(){
    addresse_ = 0;
}  


Memoire::Memoire(uint16_t memoireAdresse){
    address_ = memoireAdresse;
}  

//Set the adress to write in memory
void Memoire::setAddress(uint16_t memoireAdresse){
    address_ = memoireAdresse;
}

//Set the value of address_ with (address_ + uint16_t)
void Memoire::changerAddress(uint16_t numero){
    addresse_ += numero;
}

//If you want to know where you are in the memory
uint16_t Memoire::getAddress(){
    return addresse_;
}

/****************************************************************************************************************************************************
 * Nom:	ecricreEeprom
 * Description: Permet d'ecricre un char buffer dans un eeprom
 * Parametres:	char message[]:table de carctére a ecricre, uint8_t taille:nombre de bite qu'on veut ecricre
 * Retour:		void
 ***************************************************************************************************************************************************/

void Memoire::ecricreEeprom(unsigned char message[], uint8_t taille){
  
    eeprom_write_block((void*)message, (void*)addresse_, taille);
    addresse_ += taille;
}

/****************************************************************************************************************************************************
 * Nom:	lireEeprom
 * Description: Permet de lire un char buffer passé par reference  dans un eeprom
 * Parametres:	unsigned char &buffer: le message a lire, uint8_t taille: nombre de bit qu'on veut lire
 * Retour:		void
 ***************************************************************************************************************************************************/

void Memory::lireEeprom(unsigned char &buffer, uint8_t taille){

    eeprom_read_block((void*)&buffer, (const void*)addresse_, taille);
    addresse_ += taille;
}

