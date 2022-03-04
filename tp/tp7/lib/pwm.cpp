#define 	F_CPU   8000000UL
#include <avr/io.h> 
#include <util/delay.h>




void setPwm(double pourcentage, double freq){
const float TEMPS_UNITAIRE=0.1;
unsigned b = 1/freq;
unsigned a=pourcentage*b/100;
const unsigned TEMPS_D_ACTIVITE_Second=2;
unsigned nbPeriodes = unsigned(TEMPS_D_ACTIVITE_Second/b);
    for(unsigned n=0;n<nbPeriodes;n++){                
        PORTA=0x01;
        for(unsigned i=0;i<a;i++)
            _delay_ms(TEMPS_UNITAIRE);
        PORTA= 0x00;                     
        for(unsigned i=0;i<b-a;i++)
            _delay_ms(TEMPS_UNITAIRE);
    }      
}
