/* 
Author: Anh pham

Description:
A finite state machine which will control the LED output depending on the state

Used Pins : D2 on input and B0 , B1 on output.

State Table:
+---------------+----------+-----------------+------------+--------------+
| Current State | gCounter | isButtonPressed | Next State | Output       |
+---------------+----------+-----------------+------------+--------------+
| INIT          | 0        | 0               | INIT       | OFF          |
+---------------+----------+-----------------+------------+--------------+
| INIT          | 0        | 1               | STATE1     | OFF          |
+---------------+----------+-----------------+------------+--------------+
| STATE1        | 120      | 1               | STATE2     | OFF          |
+---------------+----------+-----------------+------------+--------------+
| STATE1        | 0-119    | 0               | STATE2     | OFF          |
+---------------+----------+-----------------+------------+--------------+
| STATE2        | 0-120    | 0               | INIT       | BLINKING LED |
+---------------+----------+-----------------+------------+--------------+
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t gCounter = 0;

void initialisationTimer()
{
    cli();
    TCNT1 = 0;
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode with 1024 prescalor
    TIMSK1 = (1 << OCIE1A);
    OCR1A = 781; // counting to 781 will last about a tenth of a second
    sei();
}

ISR(TIMER1_COMPA_vect)
{
    gCounter ++;
    TIFR1 |= (1 << OCF1A);
}

bool isButtonPressed (){
    uint8_t dButtonReading1 = PIND;
    _delay_ms(30);
    uint8_t dButtonReading2 = PIND;
    if (!(dButtonReading1 & (1<<PD2)) && dButtonReading1 == dButtonReading2)
        return true;
    return false;
}

enum class State { INIT, STATE1, STATE2 };

void initialisationUART ( void ) {
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A = 0;
    UCSR0B |= ( 1 << RXEN0) | ( 1<< TXEN0);
    UCSR0C = 0;
}

// FROM USART to the  PC
void transmissionUART ( uint8_t donnee ) {
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) )
    ;
    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

int main () {
    DDRD = 0x00;
    DDRB = 0xff;
    State currentState = State::INIT;
    const uint8_t GREEN = 1<< PB1; 
    const uint8_t RED = 1 << PB0; 
    const uint8_t OFF = 0;
    initialisationUART();
    while (true){
        switch (currentState) {
            case State::INIT:
                gCounter = 0;
                if (isButtonPressed())
                    currentState = State::STATE1;
                else 
                    currentState = State::INIT;
                break;

            case State::STATE1:
                initialisationTimer();
                sei(); 
                while (isButtonPressed() && gCounter < 120)
                ; // does nothing while gCounter goes up and button is pressed
                cli(); 
                currentState = State::STATE2;
                break;

            case State::STATE2:
                uint8_t delayPwm1 = 50;
                for (int i = 0; i < 5 ; i++){ // PWM period is 100ms and we want the LED to blink green for half a second, so we iterate 5 times
                    PORTB = OFF;
                    _delay_ms (delayPwm1);
                    PORTB = GREEN;
                    _delay_ms (delayPwm1);
                }
                PORTB = OFF;
                uint16_t delay1 = 2000;
                uint8_t delayPwm2 = 250;
                _delay_ms (delay1);
                for (int i = 0; i < (gCounter/2); i++){
                    PORTB = RED;
                    _delay_ms (delayPwm2);
                    PORTB = OFF;
                    _delay_ms (delayPwm2);
                }
                PORTB = GREEN;
                uint16_t delay2 = 1000;
                _delay_ms (delay2);
                PORTB = OFF;
                currentState = State::INIT;
                break;
        }
        transmissionUART(gCounter); // to see the value of gCounter through serieViaUSB
    }
}