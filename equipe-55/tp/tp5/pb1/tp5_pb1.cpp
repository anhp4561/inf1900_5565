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
uint8_t address = 0x00;

int main () {
    uint8_t tableauChar [] = {'*','P','*','O','*','L','*','Y','*','T','*','E','*','C','*','H','*','N','*','I','*','Q','*','U','*','E','*',' ','*','M','*','O','*','N','*','T','*','R','*','E','*','A','*','L','*'};
    uint8_t retourRead [sizeof(tableauChar)] = {};

    eeprom_write_block((const void*)& tableauChar, (void*) address, (size_t) sizeof(tableauChar));
    eeprom_read_block((void*) retourRead, (const void*) address, (size_t) sizeof(retourRead));

    bool estIdentique = true;
    for (unsigned int i = 0; i < (sizeof(tableauChar)/sizeof(tableauChar[0])); i++){
        if (tableauChar[i] != retourRead[i]){
            estIdentique = false;
            break;
        }
    }
    if (estIdentique)
        PORTA = 1;
    else
        PORTA = 0;
}
