/*
 * Autheurs-es : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
 *
 * Description : Collection de fonctions qui permettent la transmission et la lectureUart de donnes avec UART et RS232
 */

#ifndef UART_H
#define UART_H
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/eeprom.h>

void initialisationUart();
void transmissionUart(uint8_t donnee);
void transmissionUartString(const char message[], int taile);
void lectureUart(uint8_t *addressDebut, uint8_t valeurFin);
unsigned char receptionUart( void );

#endif