
/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : TRAVAIL_PRATIQUE 7
* Section # : 3
* Equipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
date : 13-03-2022
 *
 * Description : 
 Cette classe permet l'initialisation transmission et la reception des données en utilisant RS232
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
unsigned char receptionUart(void);

#endif