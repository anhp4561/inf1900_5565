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


int main () {
    bool enMarche = false;
    bool dansBoucle = false;
    Memoire24CXXX memoire;
    Sonnerie sonnerie;
    Moteur moteurs;
    // Configuration des Leds : 
    Led led1 (&PORTA,0,1);
    Led led2 (&PORTA,2,3);
    Led led3 (&PORTA,4,5);
    Led led4 (&PORTA,6,7);
    Led led5 (&PORTB,0,1);
    Led led6 (&PORTB,6,7); // Sauter PORTB 2,3,4,5 pour ne pas creer de conflit avec moteurs
    Led led7 (&PORTC,0,1);
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
                    switch (operandeBytecode) { // Anh (message pour oscar) : J'ai remis les switchs cases pcq si l'operande = 0x03, ca va allumer led1 et led2.
                        case 1 :
                            led1.allumerRougeLed();
                            break;
                        case 2 :
                            led2.allumerRougeLed();
                            break;
                        case 4 :
                            led3.allumerRougeLed();
                            break;
                        case 8 :
                            led4.allumerRougeLed();
                            break;
                        case 16 :
                            led5.allumerRougeLed();
                            break;
                        case 32 :
                            led6.allumerRougeLed();
                            break;
                        case 64 :
                            led7.allumerRougeLed();
                            break;
                        case 127 :
                            led1.allumerRougeLed();
                            led2.allumerRougeLed();
                            led3.allumerRougeLed();
                            led4.allumerRougeLed();
                            led5.allumerRougeLed();
                            led6.allumerRougeLed();
                            led7.allumerRougeLed();
                            break;
                        default: // Si une seule DEL est utilisée, l'opérande est ignoré (mais présent).
                            led1.allumerRougeLed();
                            break;
                    }
                    adresseLecture += 0x10;
                    break;

                case ETEINDRE_DEL:
                    switch (operandeBytecode) {
                        case 1 :
                            led1.eteindreLed();
                            break;
                        case 2 :
                            led2.eteindreLed();
                            break;
                        case 4 :
                            led3.eteindreLed();
                            break;
                        case 8 :
                            led4.eteindreLed();
                            break;
                        case 16 :
                            led5.eteindreLed();
                            break;
                        case 32 :
                            led6.eteindreLed();
                            break;
                        case 64 :
                            led7.eteindreLed();
                            break;
                        case 127 :
                            led1.eteindreLed();
                            led2.eteindreLed();
                            led3.eteindreLed();
                            led4.eteindreLed();
                            led5.eteindreLed();
                            led6.eteindreLed();
                            led7.eteindreLed();
                            break;
                        default: // Si une seule DEL est utilisée, l'opérande est ignoré (mais présent).
                            led1.allumerRougeLed();
                            break;
                    }

                    adresseLecture += 0x10;
                    break;

                case JOUER_SON:
                    sonnerie.jouerSonnerie(operandeBytecode);
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
                    if (dansBoucle == false){
                        adresseLecture = adresseDebutBoucle + 0x10;
                        nombreIteration = operandeBytecode;
                        dansBoucle = true;
                    }
                    break;

                case FIN_BOUCLE:
                    if (nombreIteration >= 0){
                        adresseLecture = adresseDebutBoucle + 0x10;
                        nombreIteration--;
                    }
                    else if (nombreIteration <= -1){
                        dansBoucle = false;
                    }
                    break;

                case FIN:
                    enMarche = false;
                    break;
            }
        }
    }
}
