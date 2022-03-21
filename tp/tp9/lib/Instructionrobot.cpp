/*******************************************************************************************************************************************************************************************
 * Nom: instructionRobot.cpp
 * Auteurs: Manel Ben Jemaa, Oscard Arcand, Anh Pham
 * Description: Le code qui suit est l'implementation des méthodes de la classe instructionRobot
 * Date: 18 mars 2022
 ******************************************************************************************************************************************************************************************/

#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include "moteur.h"
#include "sonnerie.h"
#include <Instructionrobot.h>

 /****************************************************************************************************************************************************
  * Nom :         debut
  * Description:  Indique le debut du code. La DEL clignote 2 fois en vers
  * Mnemonique:   dbt
  * Code binaire: 0x01
  * Operande:     non
  * Retour:       void
  ***************************************************************************************************************************************************/

void InstructionRobot::debut()
{
	DDRB = 0xff;  //PORTD en sortie

	PORTB = 0x02; //DEL B2
	_delay_ms(100);
	PORTB = 0x00; 
	_delay_ms(100);
	PORTB = 0x02;
	_delay_ms(100);
	PORTB = 0x00;

	Moteur moteur = Moteur();
}

/******************************************************************************************************************************************************************************
 * Nom :         fin
 * Description:  fin de l'execution du code.
 * Mnemonique:   fin
 * Code binaire: 0xFF
 * Op�rande:     non
 * Retour:       void
 ******************************************************************************************************************************************************************************/

void InstructionRobot::fin()
{

	// Eteindre DEL
	gererDel(127, false);

	//Arrete moteur
	arreterMoteur();

	//Arrete sonorite
	arreterSonorite();
}

/******************************************************************************************************************************************************************************
 * Nom :         attendre
 * Description:  attendre 25 ms fois la valeur de l'opérande
 * Mn�monique:   att
 * Code binaire: 0x02
 * Op�rande:     oui
 * Retour:       void
 ******************************************************************************************************************************************************************************/

void InstructionRobot::attendre(uint8_t coefficient)
{
	for (int i = 0; i < coefficient; i++) {
		_delay_ms(TAUX_25_MS);
	}
}


/******************************************************************************************************************************************************************************
 * Nom :         gererDel
 * Description:  attendre 25 ms fois la valeur de l'opérande
 * Mn�monique:   att
 * Code binaire: 0x02
 * Op�rande:     oui
 * Retour:       void
 ******************************************************************************************************************************************************************************/

void InstructionRobot::gererDel(uint8_t choixDel, bool choixAllume)
{
	//Del deja initialise dans debut()
	uint16_t choix = 0x00;
	int puissance, tampon = choixDel;
	if (choixAllume)
	{
		choix = 0x01;
	}
	for (int i = NB_BITS - 1; i > 0; i--)
	{
		puissance = puissanceDeux(i);
		if (puissance < tampon)
		{
			//allume les dels correspondantes, soit toujours PORTB puisqu'on a qu'un seul port.
			switch (i)
			{
			case 7:
				PORTB = choix;
				break;
			case 6:
				PORTB = choix;
				break;
			case 5:
				PORTB = choix;
				break;
			case 4:
				PORTB = choix;
				break;
			case 3:
				PORTB = choix;
				break;
			case 2:
				PORTB = choix;
				break;
			case 1:
				PORTB = choix;
				break;
			}
			tampon -= puissance;
		}
	}
}

/******************************************************************************************************************************************************************************
 * Nom :         jouerSonorite
 * Description:  jouer une note selon les fréquences données dans le 00000000000000000tableau 3.
 * Mnémonique:   sgo
 * Code binaire: 0x48
 * Opérande:     oui
 * Retour:       void
 ******************************************************************************************************************************************************************************/

void InstructionRobot::jouerSonorite(int valeur) {
Sonnerie sonnerie = Sonnerie();
sonnerie.jouerSonnerie(valeur);

}

/******************************************************************************************************************************************************************************
 * Nom :         arreterSonorite
 * Description:  arreter la sonorite
 * Mnémonique:   sar
 * Code binaire: 0x09
 * Retour:       void
 ******************************************************************************************************************************************************************************/

void InstructionRobot::arreterSonorite() {

	Sonnerie sonnerie = Sonnerie();
	sonnerie.arreterSonnerie();
}

/******************************************************************************************************************************************************************************
 * Nom :         puissanceDeux
 * Description:  puissance de deux pour des exposants positif
 * Parametres:	 uint8_t exposant
 * Retour:       uint8_t
 ******************************************************************************************************************************************************************************/

 //exposant maximum 7 sinon depasse le range des uint8_t
uint8_t InstructionRobot::puissanceDeux(uint8_t exposant)
{

	uint8_t resultat = 1;

	if (exposant != 0)
	{
		for (int j = 0; j <= exposant; j++)
		{
			resultat *= 2;// puissance de 2
		}
	}

	return resultat;
}
/******************************************************************************************************************************************************************************
 * Nom :         arreterMoteur
 * Description:  arreter les moteurs
 * Mnémonique:   mar
 * Retour:       void
 ******************************************************************************************************************************************************************************/

void InstructionRobot::arreterMoteur() {

	Moteur moteur = Moteur();

	moteur.arreterMoteur();

}

/******************************************************************************************************************************************************************************
 * Nom :         avancer
 * Description:  avancer en ligne droite
 * Mnémonique:   mav
 * Code binaire: 0x62
  * Retour:       void
 ******************************************************************************************************************************************************************************/
void InstructionRobot::avancer(uint8_t ratio) {

	Moteur moteur = Moteur();

	moteur.avancerMoteur(ratio,ratio);

}

/******************************************************************************************************************************************************************************
 * Nom :         reculer
 * Description:  reculer en ligne droite
 * Mnémonique:   mre
 * Code binaire: 0x63
 * Retour:       void
 ******************************************************************************************************************************************************************************/
void InstructionRobot::reculer(uint8_t ratio) {

	Moteur moteur = Moteur();

	moteur.reculerMoteur(ratio, ratio);

}

/******************************************************************************************************************************************************************************
 * Nom :         tournerDroite
 * Description:  virage du robot de 90 degrés a droite
 * Mnémonique:   trd
 * Code binaire: 0x64
 * Retour:       void
 ******************************************************************************************************************************************************************************/

void InstructionRobot::tournerDroite() {

	Moteur moteur = Moteur();

	moteur.tournerDroiteMoteur(100);

}

/******************************************************************************************************************************************************************************
 * Nom :         tournerGauche
 * Description:  virage du robot de 90 degr�s � gauche
 * Mnémonique:   trg
 * Code binaire: 0x65
 * Retour:       void
 ******************************************************************************************************************************************************************************/
void InstructionRobot::tournerGauche() {
	Moteur moteur = Moteur();

	moteur.tournerGaucheMoteur(100);

}
