/*****************************************************************************************
 * Nom : Oscar Arcand (2144801) Manel Ben Jemaa (1871842) Younes Lazzali (2025718)
 * Travail : TRAVAIL_PRATIQUE 6
 * Section # : 3
 * Ã‰quipe # : 65
 * Correcteur : Ghali chraibi ,	Charles Jiang
 
 * Description: Quand le bouton est enfoncé, un compteur qui incrémente 10 fois par seconde est activé. 
 * Quand le bouton est relâché ou lorsque le compteur atteint 120, la lumière clignote vert pendant 1/2 seconde. 
 * Ensuite, la carte mère ne fait rien. Puis, deux secondes plus tard, la lumière rouge s'allume. 
 * Elle clignote (compteur / 2) fois au rythme de 2 fois par seconde. 
 * Ensuite, la lumière tourne au vert pendant une seconde. Finalement, elle s'éteint et le robot revient à son état original.

 * entrees/sorties:
 * PortD entree; Pin D2 utilisé
 * PortB sorties; Pins B0 et B1 utilisés

 *****************************************************************************************/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

const int MAX_COMPTEUR = 120;        // Maximum que le compteur peut atteindre
const int DELAI_MINIMUM = 1;         //Nombre de ms pour le delai minimum
const int DELAI_100MS = 100;         //Nombre de ms pour un délai de 0.1 seconde
const int DELAI_QUART_SECONDE = 250; //Nombre de ms pour un délai de 0.25 seconde
const int DELAI_DEMIE_SECONDE = 500; //Nombre de ms pour un délai de 0.5 seconde
const int DELAI_1_SECONDE = 1000;    //Nombre de ms pour un délai de 1 seconde
const int DELAI_2_SECONDES = 2000;   //Nombre de ms pour un délai de 2 seconde

void initialisation()
{
    DDRB = 0xff; // PORT B est en mode sortie
    DDRD = 0x00; // PORT D est en mode entrée
}

void eteindreLed()
{
    PORTB = 0x00; // eteindre la led
}

void allumerVertLed()
{
    PORTB = 0x01; // Allume la LED en vert
}

void allumerRougeLed()
{
    PORTB = 0x02; // Allume la LED en rouge
}

int main()
{
    initialisation();
    while (true) {
        int compteur = 0; // initialise le compteur à zéro.
        eteindreLed();    // La LED commence éteinte
        while (PIND & (1 << PIND2)) { // Attend que le bouton poussoir soit enfoncé.
            _delay_ms(DELAI_MINIMUM);
        }
        while (!(PIND & (1 << PIND2)) && compteur != MAX_COMPTEUR) { // Augmente le compteur à chaque 0.1 seconde tant que le bouton poussoir est enfoncé ou que le compteur est rendu à 120
            compteur++;
            _delay_ms(DELAI_100MS);
        }
        allumerVertLed(); // Allume la LED en vert pour 0.5 secondes
        _delay_ms(DELAI_DEMIE_SECONDE);
        eteindreLed(); // Éteint la LED pour 2 secondes
        _delay_ms(DELAI_2_SECONDES);
        for (int i = 0; i < compteur; i = i + 2) {  // Fait une boucle qui incrémente de 2 pour compter compteur/2 fois
            allumerRougeLed(); // La LED est allumée en rouge pendant un quart de seconde
            _delay_ms(DELAI_QUART_SECONDE);
            eteindreLed(); // Puis la LED est éteinte pour un quart de seconde.
            _delay_ms(DELAI_QUART_SECONDE);
        }
        allumerVertLed(); // La LED est allumée en vert pour une seconde
        _delay_ms(DELAI_1_SECONDE);
    }
}
