/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : TRAVAIL_PRATIQUE 7
* Section # : 3
* Equipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
* date : 13-03-2022
 * Description : Classe qui contient les routines d'initialisation 
 * d'interruption externe pour chaque timer
 */

#include <avr/interrupt.h>

class interruptions
{
public:
    void initInterruption0();
    void initInterruption1();
    void initInterruption2();
};
