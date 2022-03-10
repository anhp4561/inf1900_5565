#include "debug.h"
# include "RS232.h"

void initUART(){
    initialisationUART();
}

void debugPrint(uint16_t x){
    UARTTranmissionMot(x);
}

void debugPrint(const char* x){
    UARTTranmissionMot(x);
}

void debugPrint(unsigned char* x){
    UARTTranmissionMot(x);
}

