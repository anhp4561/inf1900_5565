
#include "LED.h"

const uint8_t ROUGE = 0x02;
const uint8_t VERT = 0x01;
const uint8_t ETEINT = 0x00;
const double ATTENTE_AMBRE=0.5;


void choisirPort(Port port)
{
    switch (port)
    {
        case A:
            
            break;
        case B:
           
            break;
        case C:
            
            break;
        case D:
            
            break;
    }
};

void eteindreLed(uint8_t PORT) {
PORT = ETEINT;  // eteindre la led 
}


void allumerLedRouge(uint8_t PORT) {
    PORT = 0x02; // allumer la led rouge 
}
void allumerLedVERT(uint8_t PORT) {
    PORT = 0x01; // allumer la led vert 
}

void ambre(uint8_t PORT) // allumer la led en ambré 
{
    PORT = ROUGE;     
    _delay_ms(ATTENTE_AMBRE);
    PORT =VERT; 
    _delay_ms(ATTENTE_AMBRE);

}








