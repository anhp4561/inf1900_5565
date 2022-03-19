
/**************************************************************************************************************************************************
 * Nom:	lireByteCode.cpp
 * Auteurs: Manel Ben Jemaa, Oscar Arcand, Anh Phan 
 * Description: Le code qui suit permet d'écrire notre bytecode dans la mémoire externe dela carte mère en utilisant la classe memoire_24 et uart
 * Date: 17 mars 2022
 **************************************************************************************************************************************************/


#include <avr/io.h>
#include <util/delay.h>
#include "rs232.h"
#include <memoire_24.h>

#define DERNIERE_ADRESSE_MEMOIRE 0x3E8 //1KB

int main()
{
	Memoire24CXXX notreMemoire = Memoire24CXXX();
    initialisationUart();
	uint8_t donnee;
	uint16_t adresseEcriture = 0x00;//initialisation pour écrire à la premère adresse mémoire
	//DDRB = 0xff;//PORB en sortie

	while (adresseEcriture < DERNIERE_ADRESSE_MEMOIRE) {
		donnee = receptionUart();//reception des données à écrire (un octet à la fois)
		notreMemoire.ecriture(adresseEcriture, donnee);//écriture de la donnée reçu à l'adresse actuelle
		adresseEcriture += 0x01;//adresse actuelle +1
	}
}