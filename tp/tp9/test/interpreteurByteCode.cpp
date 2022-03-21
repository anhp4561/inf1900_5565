#define F_CPU 8000000
#include <avr/io.h> 
#include <stdio.h>
//#include "debug.h"
#include "memoire_24.h"
//#include "led.h"
#include "moteur.h"
#include "sonnerie.h"
#include "Instructionrobot.h"
#include "rs232.h"

#define DERNIERE_ADRESSE_MEMOIRE 0x3E8 //1KB

//MULTIPLICATEUR_DELAI = 25,
//POURCENTAGE_PWM_MOTEUR = 100,
enum Instruction
{
	DBT = 0b00000001,
	ATT = 0b00000010,
	DAL = 0b01000100,
	DET = 0b01000101,
	SGO = 0B01001000,
	SAR = 0b00001001,
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
//VALEUR_MAX_TIMER0 = 255;

int main () {
    //Memoire24CXXX memoire;
    Sonnerie sonnerie;
    Moteur moteurs;

    ///Partie ecriture dans la memoire
    Memoire24CXXX notreMemoire = Memoire24CXXX();
    initialisationUart();
	uint8_t donnee;
	uint16_t adresseEcriture = 0x0000;//initialisation pour écrire à la premère adresse mémoire
	while (adresseEcriture < DERNIERE_ADRESSE_MEMOIRE) {
		donnee = receptionUart();//reception des données à écrire (un octet à la fois)
		notreMemoire.ecriture(adresseEcriture, donnee);//écriture de la donnée reçu à l'adresse actuelle
		adresseEcriture += 0x01;//adresse actuelle +1
    }
    //Partie lecture de la memoire 
    uint16_t adresseLecture = 0x0000;
    while (true)
	{	bool enMarche = false;
     Memoire24CXXX memoireLu = Memoire24CXXX();
     uint8_t instructionBytecode;
        memoireLu.lecture(adresseLecture, &instructionBytecode); // pas encore sur de l'utilisation de lecture
        uint8_t operandeBytecode;
        memoireLu.lecture(adresseLecture, &operandeBytecode); 
        PORTB = instructionBytecode;

	InstructionRobot instructionRobot;

		if ((enMarche = true) || (instructionBytecode == 0x01))
		{ 
			switch (instructionBytecode)
			{
			case DBT:
				instructionRobot.debut();
				enMarche = true;
				break;

			case ATT:
				instructionRobot.attendre(operandeBytecode);
				break;

			case DAL:
				instructionRobot.gererDel(operandeBytecode, true);
				break;

			case DET:
				instructionRobot.gererDel(operandeBytecode, false);
				break;

			case SGO:
				instructionRobot.jouerSonorite(operandeBytecode);
				break;

			case SAR:
				instructionRobot.arreterSonorite();
				break;

			case MAR:
				instructionRobot.arreterMoteur();
				break;

			case MARR:
				instructionRobot.arreterMoteur();
				break;

			case MAV:
				instructionRobot.avancer(operandeBytecode);
				break;

			case MRE:
				instructionRobot.reculer(operandeBytecode);
				break;

			case TRD:
				instructionRobot.tournerDroite();
				break;

			case TRG:
				instructionRobot.tournerGauche();

			case FIN:
				instructionRobot.fin();
				enMarche = false;
				break;
			}
		}
	}
}
        

