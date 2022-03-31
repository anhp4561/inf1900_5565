/********************************************************************
 * Nom:	ecrireMouvements.cpp
 * Auteurs: Manel Ben Jemaa, Oscar Arcand, Anh Phan 
 * Description: Le code qui suit permet d'écrire le bytecode des
 * mouvements du robot dans la mémoire
 * Date: 17 mars 2022
 *******************************************************************/
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "debug.h"
#include <memoire_24.h>
#include "ecrireMouvements.h"
#include "moteur.h"

uint16_t adresseEcriture;
const uint8_t UN_BYTE = 0x01;
Memoire24CXXX notreMemoire = Memoire24CXXX();
Moteur moteurs = Moteur();

void initialisationEcriture()
{
	//initialisation pour écrire à la premère adresse mémoire
	adresseEcriture = 0x00;
}

void ecrireEnMemoire(uint8_t pourcentageLeft, uint8_t pourcentageRight)
{
	//écriture de l'instruction reçue à l'adresse actuelle
	notreMemoire.ecriture(adresseEcriture, pourcentageLeft); 
	_delay_ms(5);
	adresseEcriture += 0x01; //adresse actuelle +1

	//écriture de l'opérande reçue à l'adresse actuelle
    notreMemoire.ecriture(adresseEcriture, pourcentageRight); 
	_delay_ms(5);
	adresseEcriture += 0x01; //adresse actuelle +1

	}

void refaireParcours() 
{
	uint16_t adresseLecture = 0x00;
	uint8_t pourcentageLeft;
	uint8_t pourcentageRight;

	while(adresseLecture < adresseEcriture) 
	{
	notreMemoire.lecture(adresseLecture, &pourcentageLeft);
	adresseLecture +=UN_BYTE;
    notreMemoire.lecture(adresseLecture, &pourcentageRight);
	adresseLecture +=UN_BYTE;

	moteurs.avancerMoteur(pourcentageLeft, pourcentageRight);
	}
}

