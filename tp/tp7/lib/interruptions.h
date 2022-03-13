/*
 * Autheurs-es : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
 *
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
