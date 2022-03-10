#ifndef UART_H
#define UART_H
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/eeprom.h>

void initialisationUART();
void transmissionUART(uint8_t donnee);
void UARTTranmissionMot(const char message[]);
void UARTTranmissionMot(unsigned char message[]);
void lecture(uint8_t *addressDebut, uint8_t valeurFin);
unsigned char USART_Receive( void );

#endif