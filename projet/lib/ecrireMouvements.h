/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : Projet Final
* Section # : 3
* Equipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
* date : 28-03-2022
 * Description : Classe qui enregistre les instructions du robot en mémoire
 */

#include "moteur.h"

//Méthode qui initialise l'écriture des données en mémoire
void initialisationEcriture();
//Méthode qui écrit une instruction et une opérande en mémoire
void ecrireEnMemoire(uint8_t pourcentageLeft, uint8_t pourcentageRight);
//Méthode qui refait le parcours enregistré en mémoire
void refaireParcours(Moteur moteurs, uint8_t adresseL);
//méthode qui donne l'adresse finale ou nous avons écrit en mémoire
uint8_t getAdresseEcriture();
//méthode qui retourne une donnée en mémoire
uint8_t getMemoire(uint16_t adresseL);
    

