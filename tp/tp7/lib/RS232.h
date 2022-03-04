// Permettre la réception et la transmission par le UART0
// 2400 bauds
// Format des trames: 8 bits, 1 stop bits, sans parité
void initialisationUART ( void );
// Transmettre donnee du UART vers le PC
void transmissionUART ( uint8_t donnee );

unsigned char USART_Receive( void );