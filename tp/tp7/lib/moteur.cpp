/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : TRAVAIL_PRATIQUE 7
* Section # : 3
* Equipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
* date : 13-03-2022
* Description : 
 Classe permettant le controle des deux moteurs du robot
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "moteur.h"
/* Methode permet l`ìnitialisation du PMW
*/
void Moteur::initialisationTimer0Pwm(){
    cli();
    // Justification pour le registre de direction B :
    // On utilise le timer0 pour generer les pwms.
    // les pins 3 et 4 du PORTB qui correspondent a OC0A et OC0B vont emettre les pwms
    // les pins 2 et 5 du PORTB vont servir a fournir les directions aux moteurs
    // On utilise les pins adjacentes aux pins OC0A et OC0B puisqu'on utilise les cables doubles femelle vers femelle
    DDRB |= (1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5);
    TCNT0 = 0;
    TCCR0A =
        (1 << WGM00) |
        (1 << WGM01) | // Mettre cette ligne en commentaire pour utiliser PWM Phase Correct 8-bit
        (1 << COM0A1) |
        (1 << COM0B1);
    TCCR0B = (1 << CS01);
    sei();
}
/* Methode permet d'avancer les roues du moteurs 
entrée : pourcentageOC0A,pourcentageOC0B
*/
void Moteur::avancerMoteur(int pourcentageOC0A, int pourcentageOC0B){
    PORTB &= ~(1 << PB2 | 1 << PB5);
    reglerVitesseMoteur(pourcentageOC0A, pourcentageOC0B);
}
/* Methode permet de reculer les roues du moteurs 
entrée : pourcentageOC0A,pourcentageOC0B
*/
void Moteur::reculerMoteur(int pourcentageOC0A, int pourcentageOC0B){
    PORTB |= (1 << PB2 | 1 << PB5);
    reglerVitesseMoteur(pourcentageOC0A, pourcentageOC0B);
}
/* Methode permet de trouver a gauche le roues du moteurs 
entrée : pourcentageOC0A,pourcentageOC0B
*/
void Moteur::tournerGaucheMoteur(int pourcentageOC0B){
    PORTB &= ~(1 << PB5);
    reglerVitesseMoteur(0, pourcentageOC0B);
}
/* Methode permet de tourner a droite le roues du moteurs 
entrée : pourcentageOC0A
*/
void Moteur::tournerDroiteMoteur(int pourcentageOC0A){
    PORTB &= ~(1 << PB2);
    reglerVitesseMoteur(pourcentageOC0A, 0);
}
/* Methode permet d`arreter le moteurs
*/
void Moteur::arreterMoteur(){
    OCR0A = 0;
    OCR0B = 0;
}
/* Methode permet de regler la vitesse du moteurs 
entrée : pourcentageOC0A,pourcentageOC0B
*/
void Moteur::reglerVitesseMoteur(int pourcentageOC0A, int pourcentageOC0B){
    const uint8_t VALEUR_MAX_TIMER0 = 254;
    const uint8_t DIVISEUR_POURCENTAGE = 100;
    OCR0A = VALEUR_MAX_TIMER0 * pourcentageOC0A / DIVISEUR_POURCENTAGE;
    OCR0B = VALEUR_MAX_TIMER0 * pourcentageOC0B / DIVISEUR_POURCENTAGE;
}
