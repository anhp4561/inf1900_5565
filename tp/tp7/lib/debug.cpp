/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : TRAVAIL_PRATIQUE 7
* Section # : 3
* Equipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
* date : 13-03-2022
 * Description : Module qui permet le debogage a l'aide du RS232
 */

#include "debug.h"
#include "rs232.h"
/*Methode permettant l'initialisation de l'UART
*/
void initUart(){
    initialisationUart();
}
/* methode permet d'imprimer en urilisant RS232
*/
void debugPrint(const char x[], int taille){
    transmissionUartString(x, taille);
}


