

#define 	F_CPU   8000000UL
#include <avr/io.h> 
#include <string.h> 
#include <util/delay.h>
#include <avr/eeprom.h>

void initialisationUART ( void ) {

// 2400 bauds. Nous vous donnons la valeur des deux

// premiers registres pour vous éviter des complications.

UBRR0H = 0;

UBRR0L = 0xCF;

// permettre la réception et la transmission par le UART0

UCSR0A = (1<<UDRE0) ;// flag sur etat du registre 

UCSR0B =  (1<<TXEN0)|(1<<RXEN0);// peremet la transmission et la reception

// Format des trames: 8 bits, 1 stop bits, sans parité

UCSR0C = (1<<UCSZ00)|(1<<UCSZ01); // 8 bit de data 

}

// Du USART vers le PC

void transmissionUART ( uint8_t donnee ) {

while (!( UCSR0A & (1<<UDRE0))) // wait while register is free et UDRE0 flag indique si le transmettre est pret a recevoir du data 
UDR0 = donnee; // load data in the register
_delay_ms(30);
}

unsigned char USART_Receive( void )
{
/* Wait for empty transmit buffer */
while ( !(UCSR0A & (1<<RXC0)) );
/* Get and return received data from buffer */
return UDR0;
}

int main (){

initialisationUART ();
char mot[100] = "";

uint8_t i, j;

for ( j = 0; j < 100; i++ ) {


mot[j]= USART_Receive();
if(mot[j]== 0xFF){

break;
}
}

for ( i = 0; i < 100; i++ ) {

for ( j=0; j < 20; j++ ) {

transmissionUART ( mot[j] );

}

}
} 
