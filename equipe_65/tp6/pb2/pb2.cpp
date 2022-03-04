/*****************************************************************************************
* Nom : Ben Jemaa Manel(1871842),Lazzali Younes (2025718), Oscar Arcand(2144801).
* Travail : TRAVAIL_PRATIQUE 2
* Section # : 3
* Ã‰quipe # : 65
* Correcteur : Ghali chraibi ,	Charles Jiang 
  date : 21-02-2022
  
 * Description: Ce programme permet d'allumer une DEL bicolore en fonction
 * si la lumiere est basse la DEL prend la couleur verte (courant dans B0)
 * si la lumiere est forte la DEL devient rouge
 * sinon dans le cas ou l'intensite de la lumiere est moyenne la DEL devient ambre.

 * entrees/sorties:
 * PORTA entree: on a utilisé la pin A0 
 * PORTB Sortie : on a utilisé les pins B0,B1  
 
 *Mesures faits avant de commencer:
 *Vref est ajustee a 5v
 *on a verifie la valeur maximale (lumniere forte) de la tension avec un voltmetre = 3.62V
 *on a verifie la valeur minimale (lumniere basse) de la tension avec un voltmetre = 2.38V

 *****************************************************************************************/

#define  F_CPU   8000000UL
#include <avr/io.h>  
#include <util/delay.h>
#include "can.h" 

const uint8_t pinA0 = 0;
const double VALEUR_CAPTEUR_MIN = 121.0;//quand la lumiere est forte le voltage =2.38 V => VALEUR_CAPTEUR_MIN=2.38/5*255=121
const double VALEUR_CAPTEUR_MAX = 185.0;//quand la lumiere est faible le voltage =3.57 V => VALEUR_CAPTEUR_MAX=3.62/5*255=185
const double ATTENTE_AMBRE=0.5; //temps qu'il faut attendre en varaiant entre le rouge et vert pour avoir la couleur ambré
enum Sortie{VERT=0b01,ROUGE=0b10};

/**********************************************************************************
 * cette fonction permet d'initialiser les ports A et B (A0 entree ; B0,B1 sorties)
 * retourne void
 *  parametre void
 **********************************************************************************/

void initialisation()
{
    DDRA=0x00;
    DDRB=VERT | ROUGE;
}

/**********************************************************************************
 * cette fonction permet de generer la couleur ambre
 * retourne void
 *  parametre void
 **********************************************************************************/
void ambre()
{
    PORTB = ROUGE;     
    _delay_ms(ATTENTE_AMBRE);
    PORTB =VERT; 
    _delay_ms(ATTENTE_AMBRE);
}

int main(void)
{
    uint8_t entreeAnalogique;
    can convertisseur ;   
    initialisation();
    while(true){
        entreeAnalogique= (convertisseur.lecture(pinA0) >> 2);  //garder que les 8 bits les plus significatifs
        if(entreeAnalogique<VALEUR_CAPTEUR_MIN){    
            PORTB = VERT;                                                                                             
        }
        else if (entreeAnalogique>VALEUR_CAPTEUR_MAX){
            PORTB = ROUGE;                                                                                             
        }
        else {                
            ambre();        
        }
    }
}
