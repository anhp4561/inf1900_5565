#define F_CPU 8000000
#include <avr/io.h> 
#include <stdio.h>
#include "debug.h"
#include "memoire_24.h"
#include "led.h"
#include "moteur.h"
#include "sonnerie.h"

const uint8_t DEBUT = 0x01, 
ATTENDRE = 0x02, 
ALLUMER_DEL = 0x44, 
ETEINDRE_DEL = 0x45, 
JOUER_SON = 0x48, 
ARRETER_SON = 0x09, 
ARRETER_MOTEUR1 = 0x60, 
ARRETER_MOTEUR2 = 0x61, 
AVANCER_MOTEUR = 0x62, 
RECULER_MOTEUR = 0x63, 
TOURNER_DROITE_MOTEUR = 0x64, 
TOURNER_GAUCHE_MOTEUR = 0x65, 
DEBUT_BOUCLE = 0xC0, 
FIN_BOUCLE = 0xC1, 
FIN = 0xFF,
MULTIPLICATEUR_DELAI = 25,
POURCENTAGE_PWM_MOTEUR = 100,
VALEUR_MAX_TIMER0 = 255;


bool enMarche = false;
void allumerLedVm(int operande, Led& led0 = Led(), Led& led1 = Led(),Led& led2 = Led(),Led& led3 = Led(),Led& led4 = Led(),Led& led5 = Led(),Led& led6 = Led(), Led& led7 = Led()); // signature de la fonction

int main () {
    Memoire24CXXX memoire;
    Sonnerie sonnerie;
    Moteur moteurs;
    uint16_t adresseDebutBoucle;
    uint8_t nombreIteration = -1;
    uint16_t adresseLecture = 0x0000;//initialisation pour écrire à la premère adresse mémoire
    while(true){
        uint8_t* pointeurInstruction;
        uint8_t instructionBytecode = memoire.lecture(adresseLecture, pointeurInstruction); // pas encore sur de l'utilisation de lecture
        uint8_t* pointeurOperande;
        uint8_t operandeBytecode = memoire.lecture(adresseLecture, pointeurOperande); // pas encore sur de l'utilisation de lecture
        if (enMarche == true || instructionBytecode == DEBUT) { // mis == true pour que ca soit plus claire
            switch (instructionBytecode){
                case DEBUT:
                    enMarche = true;
                    adresseLecture += 0x10;
                    break;

                case ATTENDRE:
                    for (int i = 0; i < operandeBytecode ; i++){
                        _delay_ms(MULTIPLICATEUR_DELAI); 
                    }
                    adresseLecture += 0x10;
                    break;

                case ALLUMER_DEL:
                    allumerLedVm(operandeBytecode); // a voir apres, peut etre faire un autre switch case ?
                    adresseLecture += 0x10;
                    break;

                case ETEINDRE_DEL:
                    // a voir apres, peut etre faire un autre switch
                    adresseLecture += 0x10;
                    break;

                case JOUER_SON:
                    sonnerie.jouerSonorite(operandeBytecode);
                    adresseLecture += 0x10;
                    break;

                case ARRETER_SON:
                    sonnerie.arreterSonnerie();
                    adresseLecture += 0x10;
                    break;

                case ARRETER_MOTEUR1:
                    moteurs.arreterMoteur();
                    adresseLecture += 0x10;
                    break;

                case ARRETER_MOTEUR2:
                    moteurs.arreterMoteur();
                    adresseLecture += 0x10;
                    break;

                case AVANCER_MOTEUR:
                    operandeBytecode = operandeBytecode * POURCENTAGE_PWM_MOTEUR / VALEUR_MAX_TIMER0;
                    moteurs.avancerMoteur(operandeBytecode, operandeBytecode);
                    adresseLecture += 0x10;
                    break;

                case RECULER_MOTEUR:
                    operandeBytecode = operandeBytecode * POURCENTAGE_PWM_MOTEUR / VALEUR_MAX_TIMER0;
                    moteurs.reculerMoteur(operandeBytecode, operandeBytecode);
                    adresseLecture += 0x10;
                    break;

                case TOURNER_DROITE_MOTEUR:
                    moteurs.tournerDroiteMoteur(POURCENTAGE_PWM_MOTEUR);
                    _delay_ms (50);
                    moteurs.arreterMoteur();
                    adresseLecture += 0x10;
                    break;

                case TOURNER_GAUCHE_MOTEUR:
                    moteurs.tournerDroiteMoteur(POURCENTAGE_PWM_MOTEUR);
                    _delay_ms (50);
                    moteurs.arreterMoteur();
                    adresseLecture += 0x10;
                    break;

                case DEBUT_BOUCLE: // mettre error pour catch boucle imbriquer ou faire un bool dansBoucle.
                    adresseLecture = adresseDebutBoucle + 0x10;
                    break;

                case FIN_BOUCLE:
                    if (nombreIteration >= 0){
                        adresseLecture = adresseDebutBoucle + 0x10;
                        nombreIteration--;
                    }
                    break;

                case FIN:
                    enMarche = false;
                    break;
            }
        }
    }
}

void allumerLedVm(int operande, Led& led0 = Led(), Led& led1 = Led(),Led& led2 = Led(),Led& led3 = Led(),Led& led4 = Led(),Led& led5 = Led(),Led& led6 = Led(), Led& led7 = Led()) { // changer le nom de variable operandes
if ((operande & 0x01) == 0x01) {
    led0.allumerRougeLed();
}

if ((operande & 0x02) == 0x02) {
    led1.allumerRougeLed();
}

if ((operande & 0x04) == 0x04) {
    led2.allumerRougeLed();
}

if ((operande & 0x08) == 0x08) {
    led3.allumerRougeLed();
}

if ((operande & 0x10) == 0x10) {
    led4.allumerRougeLed();
}

if ((operande & 0x20) == 0x20) {
    led5.allumerRougeLed();
}

if ((operande & 0x40) == 0x40) {
    led6.allumerRougeLed();
}

if ((operande & 0x80) == 0x80) {
    led7.allumerRougeLed();
}

}
