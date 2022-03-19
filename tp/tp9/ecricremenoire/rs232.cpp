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
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C = (1<<USBS0)|(1 << UCSZ01) | (1 << UCSZ00);
}

/******************************************************************************************************
 * Nom:	transmissionUart
 * Description: Initialisation des registres qui permetent la reception  et la transmission de données
 * Parametres:	void
 * Retour:		void
 *****************************************************************************************************/

void transmissionUart(uint8_t donnee){
    while (!(UCSR0A & (1 << UDRE0)))
        _delay_ms(30);
    UDR0 = donnee;
}

/******************************************************************************************************
 * Nom:	receptionUart
 * Description: Reception des données à écrire (un octet à la fois)
 * Parametres:	aucun
 * Retour:		uint8_t
 *****************************************************************************************************/

unsigned char receptionUart(void){
    while (!(UCSR0A & (1 << RXC0)))
        ;
    return UDR0;
}
