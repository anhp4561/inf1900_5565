/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : TRAVAIL_PRATIQUE 9
* Section # : 3
* Equipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
* date : 21-03-2022
* Description : Classe permettant le controle des deux moteurs du robot
 */
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

int main(){
    bool enMarche = false;
    bool dansBoucle = false;
    Memoire24CXXX memoire;
    Sonnerie sonnerie;
    Moteur moteurs;
    // Configuration des Leds :
    Led led1(&PORTA, 0, 1);
    uint16_t adresseDebutBoucle = 0x0000;
    uint8_t nombreIteration = -1;
    uint16_t adresseLecture = 0x0000; //initialisation pour écrire à la premère adresse mémoire
    while (true) {
        uint8_t instructionByteCode;
        memoire.lecture(adresseLecture, &instructionByteCode); 
        uint8_t operandeBytecode;
        memoire.lecture(adresseLecture, &operandeBytecode); 
        if (enMarche == true || instructionByteCode == DEBUT){ 
            switch (instructionByteCode){
            case DEBUT:
                enMarche = true;
                adresseLecture += 0x10;
                break;
            case ATTENDRE:
                for (int i = 0; i < operandeBytecode; i++){
                    _delay_ms(MULTIPLICATEUR_DELAI);
                }
                adresseLecture += 0x10;
                break;
            case ALLUMER_DEL:
                led1.allumerRougeLed();
                adresseLecture += 0x10;
                break;
            case ETEINDRE_DEL:
                led1.eteindreLed();
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
                _delay_ms(50);
                moteurs.arreterMoteur();
                adresseLecture += 0x10;
                break;
            case TOURNER_GAUCHE_MOTEUR:
                moteurs.tournerDroiteMoteur(POURCENTAGE_PWM_MOTEUR);
                _delay_ms(50);
                moteurs.arreterMoteur();
                adresseLecture += 0x10;
                break;
            case DEBUT_BOUCLE: // mettre error pour catch boucle imbriquer ou faire un bool dansBoucle.
                if (dansBoucle == false) {
                    adresseDebutBoucle = adresseLecture + 0x10;
                    nombreIteration = operandeBytecode;
                    dansBoucle = true;
                }
                else if (dansBoucle == true)
                    adresseLecture += 0x10;
                break;
            case FIN_BOUCLE:
                if (nombreIteration >= 0){
                    adresseLecture = adresseDebutBoucle;
                    nombreIteration--;
                }
                else if (nombreIteration <= -1){
                    dansBoucle = false;
                    adresseLecture += 0x10;
                }
                break;
            case FIN:
                enMarche = false;
                break;
            }
        }
    }
}
