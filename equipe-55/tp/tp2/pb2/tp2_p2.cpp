/*
Authors: Oussaada Mohamed Adlane && Anh pham

Description:
A finite state machine which will turn an LED red, green or off depending on the current state

Material identification: 2x 5 volts rail , 2x 10kOhm resistor,2x 1 MOhm resistor,
2x Ground (0V) , 1x 1,5 KOhm, 1x DEL bicolore and 1x atmega324a. 
Used Pins : D2 , D3 on input and A0 , A1 on output.

+===============+====+====+============+========+
| Current State | D2 | D3 | Next State | Output |
+===============+====+====+============+========+
| INIT          |  0 |  0 | INIT       | RED    |
+---------------+----+----+------------+--------+
| INIT          |  1 |  0 | :STATE1     | RED    |
+---------------+----+----+------------+--------+
| INIT          |  0 |  1 | :STATE1     | RED    |
+---------------+----+----+------------+--------+
| :STATE1        |  0 |  0 | :STATE1     | GREEN  |
+---------------+----+----+------------+--------+
| :STATE1        |  1 |  0 | INIT       | GREEN  |
+---------------+----+----+------------+--------+
| :STATE1        |  0 |  1 | :STATE2     | GREEN  |
+---------------+----+----+------------+--------+
| :STATE2        |  0 |  0 | :STATE2     | OFF    |
+---------------+----+----+------------+--------+
| :STATE2        |  1 |  0 | :STATE1     | OFF    |
+---------------+----+----+------------+--------+
| :STATE2        |  0 |  1 | INIT       | OFF    |
+---------------+----+----+------------+--------+
*/


#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

const uint8_t OFF = 0;
const uint8_t POLARITY1 = _BV(1);
const uint8_t POLARITY2 = _BV(0);
uint8_t reading1;
uint8_t reading2;

bool isStable (uint8_t mask){
    reading1 = PIND;
    _delay_ms(10);
    reading2 = PIND;
    if (reading1 & mask  && reading1 == reading2)
        return true;
    return false;
}

int main () {
    enum class State {
    INIT,
    STATE1,
    STATE2
    };
    State current_state = State::INIT;
    while (true){
        switch (current_state) {
            case State::INIT:
                PORTA = POLARITY1;
                if (isStable(_BV(2))){
                    while (isStable(_BV(2)));
                    current_state = State::STATE1;
                }
                else if (isStable(_BV(3))){
                    while (isStable(_BV(3)));
                    current_state = State::STATE1;
                }
                else {
                    current_state = State::INIT;
                }
                break;
            case State::STATE1:
                PORTA = POLARITY2;
                if (isStable(_BV(2))){
                    while (isStable(_BV(2)));
                    current_state = State::INIT;
                }
                else if (isStable(_BV(3))){
                    while (isStable(_BV(3)));
                    current_state = State::STATE2;
                }
                else {
                    current_state = State::STATE1;
                }
                break;
            case State::STATE2:
                PORTA = OFF;
                if (isStable(_BV(2))){
                    while (isStable(_BV(2)));
                    current_state = State::STATE1;
                }
                else if (isStable(_BV(3))){
                    while (isStable(_BV(3)));
                    current_state = State::INIT;
                }
                else {
                    current_state = State::STATE2;
                }
                break;
        }
    }
}