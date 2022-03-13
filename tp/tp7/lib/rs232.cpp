/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : TRAVAIL_PRATIQUE 7
* Section # : 3
* Ã‰quipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
* date : 13-03-2022
* Description : 
 Cette classe permet l'initialisation transmission et la reception des données en utilisant RS232
 */

#define F_CPU 8000000
#include <util/delay.h>
#include "rs232.h"

/* methode permmettant l'initialisation de l'UART en utilisant les ressources interne de Atmega
*/
void initialisationUart(){
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    UCSR0A = 0;
    UCSR0A |= (1 << TXC0) | (1 << UDRE0) | (1 << MPCM0);
    UCSR0B = (1 << RXCIE0) | (1 << TXCIE0) | (1 << UDRIE0) | (1 << RXEN0) | (1 << TXEN0);
    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

/* methode permmettant la transmission  de l'UART  vers le PC
*/
void transmissionUart(uint8_t donnee){
    while (!(UCSR0A & (1 << UDRE0)))
        _delay_ms(30);
    UDR0 = donnee;
}
/* methode permmettant la transmission  d'une chaine de caractére de l'UART  vers le PC
*/
void transmissionUartString(const char message[], int taille){
    for (uint8_t i = 0; i < taille; i++){
        transmissionUart(message[i]);
    }
}



void lectureUart(uint8_t *addressDebut, uint8_t valeurFin){
    char temp = eeprom_read_byte(addressDebut);
    uint8_t *address = addressDebut;
    while (temp != valeurFin){
        transmissionUart(temp);
        address++;
        temp = eeprom_read_byte(address);
    }
}
/* methode permmettant de recevoir une valeur de pc a partir du UART
*/
unsigned char receptionUart(void){
    while (!(UCSR0A & (1 << RXC0)))
        ;
    return UDR0;
}
