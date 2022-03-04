
/*
* Nom : Ben Jemaa Manel(1871842),Lazzali Younes (2025718).
* Travail : TRAVAIL_PRATIQUE 2
* Section # : 3
* Ã‰quipe # : 65
* Correcteur : Ghali chraibi ,	Charles Jiang 
date : 30-01-2022
* Description: 
On ppuyer trois fois le bouton-poussoir D2 pour que la DEL tourne au rouge. Par la suite, un autre appui sur D2 fait que le système revient au départ pour pouvoir recommencer et la DEL s’éteint. Par contre, un appui sur D3 à tout moment ramènera le système au point de départ et tout sera à recommencer pour ce qui est du décompte et la DEL redevient éteinte ou le reste si elle n’a jamais eu le temps de devenir rouge.
* Broches I/O: 
PORTA : SORTIE: on a utilisé les pin A0 et A1 pour allumer et eteindre le DEL
PORTD : ENTREE: on a utilisé les pin D2 et D3 pour les interrupteurs  

*Table des etats probleme 1:

+--------------+----+----+---------------+--------+
| Etat         | D2 | D3 | Prochain Etat | Sortie |
+--------------+----+----+---------------+--------+
| INIT         | 0  |  0 | INIT          | ETEINT |
| INIT         | X  |  1 | INIT          | ETEINT |
| INIT         | 1  |  0 | APPUI1        | ETEINT |
| APPUI1       | 0  |  0 | APPUI1        | ETEINT |
| APPUI1       | 1  |  0 | APPUI2        | ETEINT |
| APPUI1       | X  |  1 | INIT          | ETEINT |
| APPUI2       | 0  |  0 | APPUI2        | ETEINT |
| APPUI2       | 1  |  0 | APPUI3        | ETEINT |
| APPUI2       | X  |  1 | INIT          | ETEINT |
| APPUI3       | 0  |  0 | APPUI3        | ROUGE  |
| APPUI3       | 1  |  0 | INIT          | ROUGE  |
| APPUI3       | X  |  1 | INIT          | ROUGE  |
+--------------+----+----+---------------+--------+
*
*/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
enum Etat { INIT, APPUI1 , APPUI2, APPUI3 };
const double REBOND = 10;
const uint8_t D2= 0x04; 
const uint8_t D3 = 0x08; 
const uint8_t ROUGE = 0x02;
void _delay_ms(double ms);
bool estBoutonPressé(uint8_t masque);
void changerEtat(Etat& etat, Etat prochainEtatD2, Etat prochainEtatD3);
void eteindreLed();


int main()
{

DDRD = 0x00; 
DDRA = 0xff; 
Etat etat=INIT;

while(true){
    switch (etat){
        case INIT: 
           changerEtat(etat,APPUI1,INIT);
           eteindreLed();
          break;
        case APPUI1: 
          changerEtat(etat,APPUI2,INIT);
          eteindreLed();
          break;
        case APPUI2: 
          changerEtat(etat,APPUI3,INIT);
          eteindreLed();
          break;
        case APPUI3:
          changerEtat(etat,INIT,INIT);
          PORTA=ROUGE;
          break;
          default:       
return 0;
}
}
return 0;
}

/*
Une methode qui permet d'eliminer anti rebond afin d'enlever les impulsion parasites
*/
bool estBoutonPressé(uint8_t masque) {
if (PIND & masque){     
_delay_ms(REBOND);
return (PIND & masque);
}
return false;
}

/*
une fonction qui permet de changer l'etat de notre machine selon le bonton sur lequel on apuis 
entrées: etat, prochainEtatD2, prochainEtatD3
*/
void changerEtat(Etat& etat, Etat prochainEtatD2, Etat prochainEtatD3){
while (PIND & D2 || PIND & D3){
    if (estBoutonPressé(D2)) {
      etat = prochainEtatD2;
}
    else if (estBoutonPressé(D3)){
        etat = prochainEtatD3;
}
}
}
void eteindreLed() {
PORTA = 0x00; // eteindre LED
}
