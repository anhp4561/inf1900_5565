#include <avr/io.h>
#include "debug.h"



    int main()
{
    DDRA = 0xFF;
    DDRB = 0xFF;
    DDRC = 0x00;
    DDRD = 0xFF;
    

    DEBUG_PRINT((-3453));
    DEBUG_PRINT((6590));

    return 0;
}
