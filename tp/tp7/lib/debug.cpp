/*
 * Autheurs-es : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
 *
 * Description : Module qui permet l'affichage de donnes avec RS232 a des fins de debogage
 */
 
#include "debug.h"
#include "rs232.h"

void initUART(){
    initialisationUART();
}



void debugPrint(const char x[], int taille){
    UARTTranmissionMot(x, taille);
}
// void debugPrint(unsigned char x[], int taille){
//     UARTTranmissionMot(x, taille);
// }
// void debugPrint(int x, int taille){
//     transmissionUART(x);
// }

