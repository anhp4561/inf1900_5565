#include <avr/io.h> 
#define F_CPU 8000000UL
#include <util/delay.h>

const uint8_t rouge =0x02;
const uint8_t vert =0x01;
const uint8_t OFF=0x00;

bool interrupteur()
{   
    if(PIND & 0x04){
        _delay_ms (10.0); 
        if(PIND & 0x04){
           
            return true;
        }
    } 
    return false;
}
  int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRD = 0x00; // PORT D est en mode entrée 
 
 
  for(;;){

  if (interrupteur()){
         _delay_ms(1000);
      PORTA=rouge ;
       PORTA=vert;
  _delay_ms(10);
        }


else  { 
        PORTA=OFF;
      
        }

       
}
 return 0;
 } 

