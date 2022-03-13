/*
 * Autheurs-es : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
 *
 * Description : Collection de fonctions qui permettent la transmission et la lectureUart de donnes avec UART et RS232
 */

#define F_CPU 8000000
#include <util/delay.h>
#include "rs232.h"
void initialisationUart() {
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    UCSR0A = 0;
    UCSR0A |= (1<< TXC0) | (1<< UDRE0 ) | ( 1 << MPCM0);
    UCSR0B = (1 << RXCIE0) | ( 1 << TXCIE0) | ( 1 << UDRIE0) | ( 1 << RXEN0) | ( 1<< TXEN0);
    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C = ( 1 << UCSZ01) | ( 1 << UCSZ00) ;
}

// Du USART vers le PC

void transmissionUart ( uint8_t donnee ) {

while (!( UCSR0A & (1<<UDRE0)))  
_delay_ms(30);
UDR0 = donnee; 

}


void transmissionUartString(const char message[], int taille){
    for(uint8_t i=0;i < taille; i++){
        transmissionUart (message[i]);
    }
}
void transmissionUartString(unsigned char message[], int taille){
    for(uint8_t i=0;i < taille; i++){
        transmissionUart (message[i]);
    }
}


void lectureUart(uint8_t *addressDebut, uint8_t valeurFin){
    char temp = eeprom_read_byte(addressDebut);
    uint8_t *address = addressDebut;
    while(temp != valeurFin){
        transmissionUart (temp);
        address++;
        temp = eeprom_read_byte(address);
    }
    }

unsigned char receptionUart( void )
{
while ( !(UCSR0A & (1<<RXC0)));
return UDR0;
}
