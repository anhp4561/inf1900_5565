

/*
* Nom : Ben Jemaa Manel(1871842),Lazzali Younes (2025718).
* Travail : TRAVAIL_PRATIQUE 2
* Section # : 3
* Ã‰quipe # : 65
* Correcteur : Ghali chraibi, Charles Jiang 
date : 30-01-2022
* Description: 
Au debut la DEL doit s'allumer en rouge. Par la suite, un appuie du bouton-poussoir sur D2 ou D3 fait que la DEL prend la couleur verte.
De là, un appui sur D2 fait que le système revient au départ et la DEL reprend la couleur rouge. 
Au contraire, si l’appui provient du bouton-poussoir sur D3, la DEL s’éteint. Quand la DEL est éteinte, 
un appui sur D2 fait qu’elle revient dans l’état où elle était en vert précédemment. 
Si l’appui est plutôt sur le bouton-poussoir D3, on revient à l’état de départ avec le rouge pour ce qui est de la couleur de la DEL
* Broches I/O: 
PORTA : SORTIE: on a utilisé les pin A0 et A1 pour allumer et eteindre le DEL
PORTD : ENTREE: on a utilisé les pin D2 et D3 pour les interrupteurs  

*Table des etats probleme 2:
+--------------+----+----+---------------+--------+
| Etat Present | D2 | D3 | Etat suivant  | Sortie |
+--------------+----+----+---------------+--------+
| init         | 0  | 0  | INIT          | ROUGE  |
| init         | 1  | X  | APPUI1        | ROUGE  |
| init         | 0  | 1  | APPUI1        | ROUGE  |
| appui1       | 0  | 0  | APPUI1        | VERT   |
| appui1       | 1  | 0  | INIT          | VERT   |
| appui1       | X  | 1  | Etat2         | VERT   |
| appui2       | 0  | 0  | APPUI2        | ETEINT |
| appui2       | 1  | X  | APPUI1        | ETEINT |
| appui2       | 0  | 1  | INIT          | ETEINT |
+--------------+----+----+---------------+--------+
*
*/
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

enum Etat { INIT, APPUI1, APPUI2};
const uint8_t BOUTON_D2= 0x04; 
const uint8_t BOUTON_D3 = 0x08; 
const uint8_t VERT = 0x01;
void _delay_ms(double ms);
bool estBoutonPressé(uint8_t masque);
void changerEtat(Etat& etat, Etat prochainEtatD2, Etat prochainEtatD3);
void eteindreLed();
void allumerLed();
const double REBOND = 10;

int main()
{

DDRD = 0x00; // PORT D en mode entré
DDRA = 0xff; // PORT A en mode sortie
Etat etat=INIT;

while(true) {
    switch (etat){
        case INIT: 
          changerEtat(etat,APPUI1,APPUI1);
          allumerLed();
          break;
        case APPUI1: 
          changerEtat(etat,INIT,APPUI2);
          PORTA=VERT;
          break;
        case APPUI2: 
          changerEtat(etat,APPUI1,INIT);
          eteindreLed();
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
while (PIND & BOUTON_D2 || PIND & BOUTON_D3){
    if (estBoutonPressé(BOUTON_D2)) {
        etat = prochainEtatD2;
} 
    else if (estBoutonPressé(BOUTON_D3)) {
        etat = prochainEtatD3;
}
}
}

void eteindreLed() {
PORTA = 0x00;  // eteindre la led 
}

void allumerLed() {
PORTA = 0x02; // allumer la led rouge 
}
