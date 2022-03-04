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
uint8_t address = 0x00;

void initialisationUART ( void ) {
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    UCSR0A = 0;
    UCSR0A |= (1<< TXC0) | (1<< UDRE0 ) | ( 1 << MPCM0); // 1<<TXC0 clears the bit which means no new data in transmit buffer (UDRn), 1 << UDR0 clears the bit which means transmit buffer is empty, 1<< MPCM0 the
    //incoming frames received by the USART Receiver that do not contain address information will be ignored
    UCSR0B = (1 << RXCIE0) | ( 1 << TXCIE0) | ( 1 << UDRIE0) | ( 1 << RXEN0) | ( 1<< TXEN0); // 1 << RXCIE0 Enables interrupt in RXCn flag, 1 << TXCIE0 enables interrupt on TXCn flag
    //  1 << UDRIE0 enables interrupt on UDRIEn flag, 1 << RXEN0 receiver enable, 1<< TXEN0 transmitter enable
    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C = ( 1 << UCSZ01) | ( 1 << UCSZ00) ; // UCSZ02 UCSZ01 UCSZ00 = 0 1 1 = 8-bit character size, 1 stop bit and parity disabled by default
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
    char mots[21] = "Le robot en INF1900\n";
    uint8_t i, j;
    for ( i = 0; i < 100; i++ ) {
        for ( j=0; j < 20; j++ ) {
            transmissionUART ( mots[j] );
        }
    }

}

// uint8_t tableauChar [] = {'*','P','*','O','*','L','*','Y','*','T','*','E','*','C','*','H','*','N','*','I','*','Q','*','U','*','E','*',' ','*','M','*','O','*','N','*','T','*','R','*','E','*','A','*','L','*'};
//     uint8_t retourRead [sizeof(tableauChar)] = {};

//     eeprom_write_block((const void*)& tableauChar, (void*) address, (size_t) sizeof(tableauChar));
//     eeprom_read_block((void*) retourRead, (const void*) address, (size_t) sizeof(retourRead));

//     bool estIdentique = true;
//     for (unsigned int i = 0; i < (sizeof(tableauChar)/sizeof(tableauChar[0])); i++){
//         if (tableauChar[i] != retourRead[i]){
//             estIdentique = false;
//             break;
//         }
//     }
//     if (estIdentique)
//         PORTA = 1;
//     else
//         PORTA = 0;
