#include <avr/io.h>
#include "debug.h"
#include "RS232.h"

int main()
{
    DDRA = 0xFF;

    char vec[5] = {'H', 'e', 'l', 'l', 'o'};

    uint16_t i = 0;

    initialisationUART();

    for (;;)
    {

        PORTA = 0x01;

        vec[i++] = i;

        transmissionUART(vec[i]);
        DEBUG_PRINT((vec[i]));

        // on devrait quitter ce programme éventuellement... mais non...

        if (i == 50)
        {

            PORTA = 0x00;

            return 0;
        }
    }

    return 0;
}
