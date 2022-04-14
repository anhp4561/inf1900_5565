#define F_CPU 8000000
#include <avr/io.h> 
#include <stdio.h>
#include "debug.h"
#include "memoire_24.h"

int main () {
    Memoire24CXXX memoire;
    initialisationUart();
    uint8_t tailleMoitie1 = receptionUart();
    uint8_t tailleMoitie2 = receptionUart();
    uint16_t tailleCode = tailleMoitie2;
    uint16_t tailleCode = tailleMoitie1 << 4;
    ta
    for (int i = 0; i < tailleMoitie1 ; i++)
        tailleCode += 0x100; // pour concatener tailleMoitie1 et tailleMoitie2
	uint16_t adresseEcriture = 0x0000;//initialisation pour écrire à la premère adresse mémoire
    uint16_t adresseEcritureFinal = adresseEcriture + tailleCode - 0x02; // pour ne pas prendre en compte les 2 premiers bytes qui donnent la taille
    char tampon[50];
    int n = sprintf(tampon,"La valeur de tailleCode est : %d\n", tailleCode);
    DEBUG_PRINT(tampon, n);
    while (adresseEcriture < adresseEcritureFinal){
        uint8_t donnee = receptionUart();//reception des données à écrire (un octet à la fois)
		memoire.ecriture(adresseEcriture, donnee);//écriture de la donnée reçu à l'adresse actuelle
		adresseEcriture += 0x01; // passe au prochain byte
    }
}