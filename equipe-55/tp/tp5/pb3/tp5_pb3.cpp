/* 
Authors: Oussaada Mohamed Adlane && Anh pham

Description:
A program which turns an LED red while slowly decreasing its intensity. It will then do the same with the LED lit green.

Material identification: 2x 5 volts rail , 2x 10kOhm resistor,2x 1 MOhm resistor,
2x Ground (0V) , 1x 1,5 KOhm, 1x DEL bicolore and 1x atmega324a. 
Used Pins : D2 , D3 on input and A0 , A1 on output.
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <memoire_24.h>
uint16_t address = 0x0000;
uint8_t test = 'g';

void initialisationUART ( void ) {
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
void transmissionUART ( uint8_t donnee ) {
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) )
    ;
    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

int main () {
    DDRD = 1;
    initialisationUART();
    // uint8_t tableau[] = {'H','E','L','L','O',' ', 'W','O','R','L','D','!', ' '};
    // uint8_t retour[sizeof(tableau)] = {};
    // Memoire24CXXX memoire = Memoire24CXXX();
    // memoire.ecriture(address, tableau, sizeof(tableau));
    // //uint8_t* capture;
    // memoire.lecture(address, retour, sizeof(retour));
    // for (uint8_t valeur : tableau){
    //     transmissionUART(valeur);
    //}
    uint16_t address = 0x0000;
    Memoire24CXXX memoire;
    uint8_t donnee1 = 0x12;
    uint8_t donnee2 = 0x34;
    uint8_t donnee3 = 0x56;
    uint8_t donnee4 = 0x78;
    uint8_t donnee5 = 0x90;
    uint8_t donneeLecture;

    // memoire.ecriture(address,donnee1);
    // _delay_ms(5);
    // address += 0x01;
    // memoire.ecriture(address,donnee2);
    // _delay_ms(5);
    // address += 0x01;
    // memoire.ecriture(address,donnee3);
    // _delay_ms(5);
    // address += 0x01;
    // memoire.ecriture(address,donnee4);
    // _delay_ms(5);
    // address += 0x01;
    // memoire.ecriture(address,donnee5);

    _delay_ms(5);
    for(int i = 0; i < 18; i++) {
    memoire.lecture(i, &donneeLecture);
    transmissionUART(donneeLecture);
    }
}

