/*******************************************************************************************************************************************************************************************
 * Nom: FonctionnementRobot.cpp
 * Auteurs: Manel Ben Jemaa, Oscard Arcand, Anh Pham
 * Description: Permet de lire les instructions éctirtes en mémoire, de déterminer l'instruction lu, d'éxecuter cette derniére et de déterminer le nombre d'instructions.
 * Date: 18 mars 2022
 ******************************************************************************************************************************************************************************************/

#include <memoire_24.h>
#include "instructionRobot.h
#include "moteur.h

#define ADRESSE_DEBUT_DONNE 0x02

enum Instruction {
	DBT = 0x01, ATT = 0x02, DAL = 0x44, DET = 0x45,
	SGO = 0x48, SAR = 0x09, MAR = 0x60, MAR2 = 0x61, MAV = 0x62, MRE = 0x63,
	TRD = 0x64, TRG = 0x65, DBC = 0xC0, FBC = 0xC1, FIN = 0xFF
};


/****************************************************************************************************************************************************
 * Nom:	determinerInstruction
 * Description: Permet d'appeler les méthodes appropriées de la classe instructionRobot selon l'instruction et l'operande pass�e en param�tre
 * Parametres:	Instruction instruction, uint8_t operande et bool &estDebute
 * Retour:		void
 ***************************************************************************************************************************************************/

void determinerInstruction(Instruction instruction, uint8_t operande, bool& estDebute)
{
	InstructionRobot instructionRobot;
	switch (instruction)
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