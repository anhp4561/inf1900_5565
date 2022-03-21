
/**************************************************************************************************************************************************
 * Nom:	lireByteCode.cpp
 * Auteurs: Manel Ben Jemaa, Oscar Arcand, Anh Phan 
 * Description: Le code qui suit permet d'écrire notre bytecode dans la mémoire externe dela carte mère en utilisant la classe memoire_24 et uart
 * Date: 17 mars 2022
 **************************************************************************************************************************************************/


#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "rs232.h"
#include "debug.h"
#include <memoire_24.h>
//#define DERNIERE_ADRESSE_MEMOIRE 0x10 //1KB

int main()
   {
	 DDRA=0XFF;

 	PORTA=0x01;
	Memoire24CXXX notreMemoire = Memoire24CXXX();
	
    initialisationUart();
	
	uint8_t donnee;
	uint16_t adresseEcriture = 0x00;//initialisation pour écrire à la premère adresse mémoire
	//DDRB = 0xff;//PORB en sortie
	uint8_t tailleMoitie1 = receptionUart();

    uint8_t tailleMoitie2 = receptionUart();
     uint16_t tailleCode=tailleMoitie1 << 8;
     tailleCode += tailleMoitie2;
	
	while (adresseEcriture < tailleCode-2) {
	
		donnee = receptionUart();//reception des données à écrire (un octet à la fois)
		notreMemoire.ecriture(adresseEcriture, donnee);//écriture de la donnée reçu à l'adresse actuelle
		_delay_ms(5);
		adresseEcriture += 0x01;//adresse actuelle +1
	
	}
	PORTA=0x02;
		
}
