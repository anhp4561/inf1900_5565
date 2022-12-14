/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : TRAVAIL_PRATIQUE 7
* Section # : 3
* Equipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
* date : 13-03-2022
 * Description : Classe qui contient les routines d'initialisation 
 * d'interruption externe pour chaque timer
 * 
 */
 
#include "interruptions.h"
#include <avr/interrupt.h> 

void initInterruption0 () {

// cli est une routine qui bloque toutes les interruptions.

// Il serait bien mauvais d'être interrompu alors que

// le microcontrôleur n'est pas prêt...

cli ();

// cette procédure ajuste le registre EIMSK

// de l’ATmega324PA pour permettre les interruptions externes

EIMSK |= (1 << INT0);


// il faut sensibiliser les interruptions externes aux

// changements de niveau du bouton-poussoir

// en ajustant le registre EICRA

EICRA |= (1 << ISC01);


// sei permet de recevoir à nouveau des interruptions.

sei ();

}

void initInterruption1 () {

// cli est une routine qui bloque toutes les interruptions.

// Il serait bien mauvais d'être interrompu alors que

// le microcontrôleur n'est pas prêt...

cli ();

// cette procédure ajuste le registre EIMSK

// de l’ATmega324PA pour permettre les interruptions externes

EIMSK |= (1 << INT1);


// il faut sensibiliser les interruptions externes aux

// changements de niveau du bouton-poussoir

// en ajustant le registre EICRA

EICRA |= (1 << ISC11);


// sei permet de recevoir à nouveau des interruptions.

sei ();

}

void initInterruption2 () {

// cli est une routine qui bloque toutes les interruptions.

// Il serait bien mauvais d'être interrompu alors que

// le microcontrôleur n'est pas prêt...

cli ();

// cette procédure ajuste le registre EIMSK

// de l’ATmega324PA pour permettre les interruptions externes

EIMSK |= (1 << INT2);


// il faut sensibiliser les interruptions externes aux

// changements de niveau du bouton-poussoir

// en ajustant le registre EICRA

EICRA |= (1 << ISC21);


// sei permet de recevoir à nouveau des interruptions.

sei ();

}
