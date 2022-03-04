#define 	F_CPU   8000000UL
#include <avr/io.h> 
#include <util/delay.h>


void probleme1(){
    

   
    while(true){
       
       
        unsigned b=1000;//en us: //1kHz=1000s^-1=>b=1/1000s=1ms=1000us  
        unsigned a=b;   //donc a=b au debut et diminuera jusqu,elle devienne 0.
        const float TEMPS_UNITAIRE=0.1;
        const unsigned NOMBRE_DE_PERIODES_IDENTIQUES=3;//permet de regler la frequence.
        while(a!=0){   
            for(unsigned n=0;n<NOMBRE_DE_PERIODES_IDENTIQUES;n++){                 //sachant que la led s'eteint en 3s, le nombre de periode N=3*1000ms/b=3000/1ms= 3000 periodes  //cette boucle sert a generer des periode identique afin d'avoir 1kHz et eteindre la led en 3s
                PORTA = 0x02;
                for(unsigned i=0;i<a;i++)//delay prend des constantes donc on fera plusieur delays selon le besoin 
                    _delay_us(TEMPS_UNITAIRE);
                PORTA = 0x00;                      //la somme des 2 delay doit
                for(unsigned i=0;i<b-a;i++)
                    _delay_us(TEMPS_UNITAIRE);
            }
           a=a-1;
        }
        _delay_ms(200);
        a=b;                            //donc a=b au debut et diminuera jusqu,elle devienne 0.
        
    }
}
int main()
{
  DDRA = 0xff; //PORT A est en mode sortie
  DDRD = 0x00; //PORT D est en mode entree
 
  probleme1(); //enlever les commentaires pour tester 
  
  return 0; 
}


