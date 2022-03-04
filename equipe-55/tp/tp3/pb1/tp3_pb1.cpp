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
uint8_t OFF = 0x00;
uint8_t POLARITY1 = 0x02; // red LED
uint8_t POLARITY2 = 0x01; // green LED

void lowerLed (uint8_t color) {
    double time = 0.70; // in seconds. Time used to be equal to 3.0 since we were asked to gradually turn off the LED in 3 seconds.
    // However, if time = 3.0, the LED would turn off in 13 seconds. Possible explanation : Slow computation / unoptimised code led to unwanted delays.
    // Possible solution : use a for loop instead of a while loop. b  = 0.001 s and we want time = 3.0, so 3000 iterations. Ex : for (int i = 0; i < 3000 ; i++)
    // this might work since we`re not summing or subtracting anything which might be the cause of the unwanted delays.
    double counter = 0.0;
    double delayHigh = 0.001; // in seconds. This represents the variable a in the PWM percentage equation. Ex : PWM 20% -> a = 20 / b = 100
    double delayLow = 0.0;  // in seconds. This represents the period of the PWM - a. High + Low = 1000 microseconds, inverse of b = 1 kHz
    double delay = 0.0000007;
    while (counter <= time){
        PORTA = color;
        _delay_loop_2(delayHigh * F_CPU);
        PORTA = OFF;
        _delay_loop_2(delayLow * F_CPU);
        delayLow += delay;
        delayHigh -= delay;
        counter += (delayHigh + delayLow);
    }
}
int main() {
    DDRA = 0xFF; // PORTA output mode
    DDRD = 0x00; // PORTD input mode
    while (true) { // Infinite loop
        lowerLed(POLARITY1);
        _delay_ms(500);
        lowerLed(POLARITY2);
        _delay_ms(500);
    }
}

