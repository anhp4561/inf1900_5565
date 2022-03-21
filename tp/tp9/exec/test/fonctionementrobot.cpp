/*******************************************************************************************************************************************************************************************
 * Nom: FonctionnementRobot.cpp
 * Auteurs: Manel Ben Jemaa, Oscard Arcand, Anh Pham
 * Description: Permet de lire les instructions éctirtes en mémoire, de déterminer l'instruction lu, d'éxecuter cette derniére et de déterminer le nombre d'instructions.
 * Date: 18 mars 2022
 ******************************************************************************************************************************************************************************************/

#include <memoire_24.h>
#include "instructionRobot.h
#include "moteur.h"
#include "sonnerie.h"
#include "eeprom.h"

#define ADRESSE_DEBUT_DONNE 0x02

enum Instruction
{
	DBT = 0x01,
	ATT = 0b00000010,
	DAL = 0b01000100,
	DET = 0b01000101,
	MON = 0b00011000,
	MOF = 0b00011001,
	MAR = 0b01100000,
	MARR = 0b01100001, //Nom différent, mais c'est aussi MAR
	MAV = 0b01100010,
	MRE = 0b01100011,
	TRD = 0b01100100,
	TRG = 0b01100101,
	DBC = 0b11000000,
	FBC = 0b11000001,
	FIN = 0b11111111

};

int main()
{

	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0x30;

	initialisationUart();

	Memoire memoire(0);
	unsigned char valeur;

	for (;;)
	{
		valeur = receptionUart();
		memoire.ecricreEeprom(&valeur, 1);
		if (valeur == 0xFF)
			break;
	}

	memoire.setAddress(0);

	unsigned char instruction;
	unsigned char op;

	bool exit = false;
	bool enMarche = false;

	InstructionRobot instructionRobot;
	while (!exit)
	{
		memoire.lireEeprom(instruction, 1);
		memoire.lireEeprom(op, 1);
		PORTB = instruction;
		if (enMarche || (byteCode == 0x01))
		{ 
			switch (byteCode)
			{
			case DBT:
				instructionRobot.debut();
				estDebute = true;
				break;

			case ATT:
				instructionRobot.attendre(operande);
				break;

			case DAL:
				instructionRobot.gererDel(operande, true);
				break;

			case DET:
				instructionRobot.gererDel(operande, false);
				break;

			case SGO:
				instructionRobot.jouerSonorite(operande);
				break;

			case SAR:
				instructionRobot.arreterSonorite();
				break;

			case MAR:
				instructionRobot.arreterMoteur();
				break;

			case MAR2:
				instructionRobot.arreterMoteur();
				break;

			case MAV:
				instructionRobot.avancerMoteur(operande);
				break;

			case MRE:
				instructionRobot.reculerMoteur(operande);
				break;

			case TRD:
				instructionRobot.tournerDroiteMoteur();
				break;

			case TRG:
				instructionRobot.tournerGaucheMoteur();

			case FIN:
				instructionRobot.fin();
				estDebute = false;
				break;
			}
		}
	}
}