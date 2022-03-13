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

