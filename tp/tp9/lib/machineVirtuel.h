#include "moteur.h"
#include "led.h"
#include "timer.h"
// Moteur

void avancerMoteurVm(int pourcentagePwm, Moteur& moteurs);

void reculerMoteurVm (int pourcentagePwm, Moteur& moteurs);

void arreterMoteurVm (Moteur& moteurs);

void tournerDroiteMoteurVm (Moteur& moteurs);

void tournerGaucheMoteurVm (Moteur& moteurs);

// Led

void allumerLedVm(Led& led);

void allumerLedVm(int operande, Led& led1,Led& led2,Led& led3,Led& led4,Led& led5,Led& led6, Led& led7);

void eteindreLedVm(Led& led);

void eteindreLedVm(int operande, Led& led1,Led& led2,Led& led3,Led& led4,Led& led5,Led& led6, Led& led7);

// Delai

void attendreVm (uint8_t operande);

// Boucle

// les fonctions de boucles doivent se faire dans l'autre fichier, joue avec les addresses memoires, par exemple\
// on rentre au debut de la boucle, on enregistre l'addresse de la premiere instruction et on enregistre le compteur (operande)
// a la fin du double, on decremente le compteeur et on saute a l'addresse de la premiere instruction

// Sonnerie

void initialisationTimer1CtcVm (Timer1& timer1);

void jouerSonnerieVm (uint8_t note);

void arreterSonnerieVm () ;


