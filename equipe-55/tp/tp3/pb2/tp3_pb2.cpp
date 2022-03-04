/* 
Authors: Oussaada Mohamed Adlane && Anh pham

Description:
A program which turns a motor at varying intensities.

Material identification: 2x 5 volts rail , 2x 10kOhm resistor,2x 1 MOhm resistor,
2x Ground (0V) , 1x 1,5 KOhm, 1x DEL bicolore and 1x atmega324a. 
Used Pins : D2 , D3 on input and A0 , A1 on output.
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>
uint8_t OFF = _BV(1);
uint8_t ON = _BV(0)|_BV(1);
uint8_t LED_ON = 1;
uint8_t LED_OFF = 0;



void powerMotor (int frequency, float percentage) { // frequency in Hz
    int time = 2; // in seconds, represents 20 seconds
    int nIterations = time * frequency;
    float period = 1.0 / frequency;
    float delayOn =  period * percentage;
    float delayOff = period * (1-percentage);
    for (int i = 0; i < nIterations; i++){
        PORTB = ON;
        _delay_loop_2(delayOn * F_CPU);
        PORTB = OFF;
        _delay_loop_2(delayOff * F_CPU);
    }
}
int main () {
    DDRB = 0xFF; // PORTB output mode
    DDRA = 0xFF;
    while (true){
        powerMotor(60, 0.00);
        PORTA = LED_ON;
        _delay_ms(2000);
        PORTA = LED_OFF;
        powerMotor(60, 0.25);
        PORTA = LED_ON;
        _delay_ms(2000);
        PORTA = LED_OFF;
        powerMotor(60, 0.50);
        PORTA = LED_ON;
        _delay_ms(2000);
        PORTA = LED_OFF;
        powerMotor(60, 0.75);
        PORTA = LED_ON;
        _delay_ms(2000);
        PORTA = LED_OFF;
        powerMotor(60, 1.00);
        PORTA = LED_ON;
        _delay_ms(2000);
        PORTA = LED_OFF;
        powerMotor(400, 0.00);
        PORTA = LED_ON;
        _delay_ms(2000);
        PORTA = LED_OFF;
        powerMotor(400, 0.25);
        PORTA = LED_ON;
        _delay_ms(2000);
        PORTA = LED_OFF;
        powerMotor(400, 0.50);
        PORTA = LED_ON;
        _delay_ms(2000);
        PORTA = LED_OFF;
        powerMotor(400, 0.75);
        PORTA = LED_ON;
        _delay_ms(2000);
        PORTA = LED_OFF;
        powerMotor(400, 1.00);       
        PORTA = LED_ON;
        _delay_ms(2000);
        PORTA = LED_OFF;
    }
}