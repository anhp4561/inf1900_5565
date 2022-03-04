#define 	F_CPU   8000000UL
#include <avr/io.h> 
#include <util/delay.h>




void pwm(double pourcentage, double freq){
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


int main()
{
  DDRA = 0xff; //PORT A est en mode sortie
  DDRB = 0xff;
  DDRD = 0x00; //PORT D est en mode entree
  PORTB = 0xff;
 while(true){
  pwm(0,60);
  pwm(25,60);
  pwm(50,60);
  pwm(75,60);
  pwm(100,60);
  
  pwm(0,400);
  pwm(25,400);
  pwm(50,400);
  pwm(75,400);
  pwm(100,400);
  }
  return 0; 
}


