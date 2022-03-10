#include "debug.h"
# include "rs232.h"

void initUART(){
    initialisationUART();
}


void debugPrint(const char* x){
    UARTTranmissionMot(x);
}
void debugPrint(unsigned char* x){
    UARTTranmissionMot(x);
}
void debugPrint(int x){
    transmissionUART(x);
}

