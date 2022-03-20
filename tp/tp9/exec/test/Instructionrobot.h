/*******************************************************************************************************************************************************************************************
 * Nom: instructionRobot.cpp
 * Auteurs: Manel Ben Jemaa, Oscard Arcand, Anh Pham
 * Description: Le code qui suit est l'implementation des m�thodes de la classe instructionRobot
 * Date: 18 mars 2022
 ******************************************************************************************************************************************************************************************/


#define F_CPU 8000000
#include <util/delay.h>
#define TAUX_25_MS 24 
#define NB_BITS 8
#define PREMIERE_NOTE 45
#define RATIO_ROUE 50
#define DIVISEUR_FREQUENCE 256 


class InstructionRobot

{

public:

	void debut();

	void fin();

	void attendre(uint8_t coefficient);

	void gererDel(uint8_t choixDel, bool estEteint);

	void jouerSonorite(int valeur);

	void arreterSonorite();

	uint8_t puissanceDeux(uint8_t exposant);
    void arreterMoteur();
    void avancer(uint8_t ratio);
    void reculer(uint8_t ratio);
    void tournerDroite();
    void tournerGauche();

};