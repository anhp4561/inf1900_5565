
#define     F_CPU   8000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include "LED.h"

const uint8_t ROUGE = 0x02;
const uint8_t VERT = 0x01;
const uint8_t ETEINT = 0x00;
const double ATTENTE_AMBRE = 0.5;
uint8_t port = 1;

void choisirPort(char port)
{
    switch (port)
    {
    case A:
        port = "A";
        break;
    case B:
        port = "B";
        break;
    case C:
        port = "C";
        break;
    case D:
        port = "D";
        break;
    }
};

void eteindreLed(uint8_t pin)
{
    allumerLed(uint8_t ETEINT, uint8_t pin); // eteindre la led
}

void allumerLedRouge(uint8_t pin)
{
    allumerLed(uint8_t ROUGE, uint8_t pin); // allumer la led rouge
}
void allumerLedVert(uint8_t pin)
{
    allumerLed(uint8_t VERT, uint8_t pin); // allumer la led vert
}

void ambre(uint8_t pin) // allumer la led en ambré
{
    switch (port)
    {
    case A:
        PORTA = ROUGE;
        _delay_ms(ATTENTE_AMBRE);
        PORTA = VERT;
        _delay_ms(ATTENTE_AMBRE);
        break;
    case B:
        PORTB = ROUGE;
        _delay_ms(ATTENTE_AMBRE);
        PORTB = VERT;
        _delay_ms(ATTENTE_AMBRE);
        break;
    case C:
        PORTC = ROUGE;
        _delay_ms(ATTENTE_AMBRE);
        PORTC = VERT;
        _delay_ms(ATTENTE_AMBRE);
        break;
    case D:
        PORTD = ROUGE;
        _delay_ms(ATTENTE_AMBRE);
        PORTD = VERT;
        _delay_ms(ATTENTE_AMBRE);
        break;
    }
}

private
void allumerLed(uint8_t couleur, uint8_t pin)
{
    switch (port)
    {
    case A:
        PORTA = (couleur << pin);
        break;
    case B:
        PORTB = (couleur << pin);
        break;
    case C:
        PORTC = (couleur << pin);
        break;
    case D:
        PORTD = (couleur << pin);
        break;
    }
}