/* 
Authors: Oussaada Mohamed Adlane && Anh pham

Description:
A program which turns an LED red when the button connected to port D2 is pressed 3 times consecutively.
There is also a reset button connected to port D3 which will turn off the LED and clear the number of consecutive button presses.

Material identification: 2x 5 volts rail , 2x 10kOhm resistor,2x 1 MOhm resistor,
2x Ground (0V) , 1x 1,5 KOhm, 1x DEL bicolore and 1x atmega324a. 
Used Pins : D2 , D3 on input and A0 , A1 on output.

State table: 

+---------------+----+----+------------+--------+
| Acctual State | D2 | D3 | Next State | Output |
+---------------+----+----+------------+--------+
| INIT          | 1  | 0  | STATE1     | NONE   |
| INIT          | 0  | 0  | INIT       | NONE   |
| INIT          | 1  | 1  | INIT       | NONE   |
| INIT          | 0  | 1  | INIT       | NONE   |
+---------------+----+----+------------+--------+
| STATE1        | 1  | 0  | STATE2     | NONE   |
| STATE1        | 0  | 0  | STATE1     | NONE   |
| STATE1        | 1  | 1  | INIT       | NONE   |
| STATE1        | 0  | 1  | INIT       | NONE   |
+---------------+----+----+------------+--------+
| STATE2        | 1  | 0  | STATE3     | NONE   |
| STATE2        | 0  | 0  | STATE2     | NONE   |
| STATE2        | 1  | 1  | INIT       | NONE   |
| STATE2        | 0  | 1  | INIT       | NONE   |
+---------------+----+----+------------+--------+
| STATE3        | 1  | 0  | INIT       | RED    |
| STATE3        | 0  | 0  | STATE3     | RED    |
| STATE3        | 1  | 1  | INIT       | RED    |
| STATE3        | 0  | 1  | INIT       | RED    |
+---------------+----+----+------------+--------+

*/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

int main()
{
    enum State
    {
        INIT,
        STATE1,
        STATE2,
        STATE3
    };
    DDRA = 0xFF;
    DDRD = 0x00;
   
    State currentState = INIT;
    bool pressed = false;
    bool reset = false;
    while (true)
    {

        if (PIND == 1 << PIND2)
        {

            switch (currentState)
            {

            case INIT:

                pressed = true;
                break;

            case STATE1:
                pressed = true;
                break;

            case STATE2:

                pressed = true;
                break;
            case STATE3:

                pressed = true;
                break;

            default:

                break;
            }
        }
        else if (PIND == 1 << PIND3)
        {

            reset = true;
        }
        else
        {
            if (!(currentState == STATE3))
            {
                PORTA = PORTA0;
            }
            else
            {
                PORTA = 1 << PORTA1;
            }

            if (reset == true)
            {
                currentState = INIT;
            }
            if (pressed == true)
            {
                switch (currentState)
                {
                case INIT:
                    currentState = STATE1;
                    break;
                case STATE1:
                    currentState = STATE2;
                    break;
                case STATE2:
                    currentState = STATE3;
                    break;
                case STATE3:
                    currentState = INIT;

                    break;
                default:

                    break;
                }
            }

            pressed = false;
            reset = false;
        }
    }
}