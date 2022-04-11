/********************************************************************
 * Nom:	ecrireMouvements.cpp
 * Auteurs: Manel Ben Jemaa, Oscar Arcand, Anh Phan 
 * Description: Le code qui suit permet d'écrire le bytecode des
 * mouvements du robot dans la mémoire
 * Date: 17 mars 2022
 *******************************************************************/
#define F_CPU 8000000
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "debug.h"
#include <memoire_24.h>
#include "ecrireMouvements.h"

static uint16_t adresseEcriture;
const uint8_t UN_BYTE = 0x01;
Memoire24CXXX notreMemoire = Memoire24CXXX();

void initialisationEcriture()
{
	//initialisation pour écrire à la premère adresse mémoire
	adresseEcriture = 0x00;
	initialisationUart();
}

void ecrireEnMemoire(uint8_t pourcentageLeft, uint8_t pourcentageRight)
{
	//écriture de l'instruction reçue à l'adresse actuelle
	notreMemoire.ecriture(adresseEcriture, pourcentageLeft); 
	adresseEcriture += 0x01; //adresse actuelle +1
	_delay_ms(5);

	//écriture de l'opérande reçue à l'adresse actuelle
    notreMemoire.ecriture(adresseEcriture, pourcentageRight); 
	adresseEcriture += 0x01; //adresse actuelle +1
	_delay_ms(5);
	}

void refaireParcours(Moteur moteurs, uint8_t adresseL) 
{	
	uint8_t adresseLecture = adresseL;
	uint8_t pourcentageLeft;
	uint8_t pourcentageRight;

	/*
	for(int i = 0; i < 40; i++) {
	notreMemoire.lecture(i, &donneeLecture);
	transmissionUart(donneeLecture);
	}
	*/

	
		notreMemoire.lecture(adresseLecture, &pourcentageLeft);
		adresseLecture +=UN_BYTE;
    	notreMemoire.lecture(adresseLecture, &pourcentageRight);
		adresseLecture +=UN_BYTE;

		moteurs.avancerMoteur(pourcentageLeft, pourcentageRight);
		transmissionUart(pourcentageLeft);
		transmissionUart(pourcentageRight);
	
}

uint8_t getAdresseEcriture() {
	return adresseEcriture;
}

uint8_t getMemoire(uint16_t adresseL){
	uint8_t adresseLecture = adresseL;
	uint8_t transmission;
	notreMemoire.lecture(adresseLecture, &transmission);
	return transmission;
}

