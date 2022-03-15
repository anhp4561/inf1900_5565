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

class interruptions {
    public:

        //Méthode qui initialise la l'interruption 0 qui serait activée par un signal au pin D1
        void initInterruption0 ( void );
        //Méthode qui initialise la l'interruption 1 qui serait activée par un signal au pin D2
        void initInterruption1 ( void );
        //Méthode qui initialise la l'interruption 2 qui serait activée par un signal au pin D3
        void initInterruption2 ( void );

    
};
