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
#include "instructionRobot.h"

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
	PORTB = 0x00; // DEL � off
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
 * Description:  jouer une note selon les fréquences données dans le tableau 3.
 * Mnémonique:   sgo
 * Code binaire: 0x48
 * Opérande:     oui
 * Retour:       void
 ******************************************************************************************************************************************************************************/

void InstructionRobot::jouerSonorite(int valeur) {


	double frequence[37] = { 110,116.5409404,123.4708253,130.8127827,138.5913155, 146.832384, 155.5634919,164.8137785,174.6141157,
	184.9972114,195.997718,207.6523488,220,233.0818808,246.9416506,261.6255653,277.182631,293.6647679,
	311.1269837,329.6275569,349.2282314,369.9944227,391.995436,415.3046976,440,466.1637615,493.8833013,
	523.2511306,554.365262,587.3295358,622.2539674,659.2551138,698.4564629,739.9888454,
	783.990872,830.6093952,880 };


	valeur -= PREMIERE_NOTE;// trouver l'indice de la note voulue dans le tableau de frequences

	TCNT0 = 0;
	TCCR0A |= (1 << WGM01) | (1 << COM0A0) | (1 << COM0B1);//mode PWM
	TCCR0B |= (1 << CS02);
	OCR0A = (F_CPU / (2 * DIVISEUR_FREQUENCE * frequence[valeur])) - 1;   //Formule documentation ATmega page 144


}

/******************************************************************************************************************************************************************************
 * Nom :         arreterSonorite
 * Description:  arreter la sonorite
 * Mn�monique:   sar
 * Code binaire: 0x09
 * Op�rande:     non
 * Retour:       void
 ******************************************************************************************************************************************************************************/

void InstructionRobot::arreterSonorite() {

	TCCR0A &= (0 << COM0A1);
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