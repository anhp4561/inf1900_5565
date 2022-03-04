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