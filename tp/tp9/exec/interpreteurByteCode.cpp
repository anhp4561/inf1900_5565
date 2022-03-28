/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : TRAVAIL_PRATIQUE 9
* Section # : 3
* Equipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
* date : 21-03-2022
* Description : Code permettant l'interpretation d'un bytecode
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
              VALEUR_MAX_TIMER0 = 255,
              UN_BYTE = 0x01;


int main ()
{
    DDRD = 0xff;
    bool enMarche = false;
    bool dansBoucle = false;
    bool estTermine = false;
    
    Memoire24CXXX memoire;
    Sonnerie sonnerie;
    Moteur moteurs;
    // Configuration des Leds : 
    Led led1 (&PORTA,0,1);
    
    uint16_t adresseDebutBoucle = 0x0000;
    uint8_t nombreIteration = -1;
    uint16_t adresseLecture = 0x0000; //initialisation pour écrire à la premère adresse mémoire
    uint8_t instructionByteCode;
    uint8_t operandeBytecode;
    while(true){
        if (estTermine == true)
            break;
        char tampon[50];
        int n = sprintf(tampon,"address est : %d\n", adresseLecture);
        DEBUG_PRINT(tampon, n);
        memoire.lecture(adresseLecture, &instructionByteCode); 
        adresseLecture +=UN_BYTE;
        memoire.lecture(adresseLecture, &operandeBytecode); 
        if (enMarche == true || instructionByteCode == DEBUT) { // mis == true pour que ca soit plus claire
            switch (instructionByteCode){
                case DEBUT:
                    enMarche = true;
                    adresseLecture += UN_BYTE;
                    break;

                case ATTENDRE:
                    for (int i = 0; i <  operandeBytecode ; i++){
                        _delay_ms(MULTIPLICATEUR_DELAI); 
                    }
                    adresseLecture += UN_BYTE;
                    break;

                case ALLUMER_DEL:
                    led1.allumerRougeLed();
                    adresseLecture += UN_BYTE;
                    break;

                case ETEINDRE_DEL:
                    led1.eteindreLed();
                    adresseLecture += UN_BYTE;
                    break;

                case JOUER_SON:
                    sonnerie.jouerSonnerie(operandeBytecode);
                    adresseLecture += UN_BYTE;
                    break;

                case ARRETER_SON:
                    sonnerie.arreterSonnerie();
                    adresseLecture += UN_BYTE;
                    break;

                case ARRETER_MOTEUR1:
                    moteurs.arreterMoteur();
                    adresseLecture += UN_BYTE;
                    break;

                case ARRETER_MOTEUR2:
                    moteurs.arreterMoteur();
                    adresseLecture += UN_BYTE;
                    break;

                case AVANCER_MOTEUR:
                    operandeBytecode = operandeBytecode * POURCENTAGE_PWM_MOTEUR / VALEUR_MAX_TIMER0;
                    moteurs.avancerMoteur(operandeBytecode,  operandeBytecode);
                    adresseLecture += UN_BYTE;   
                    break;

                case RECULER_MOTEUR:
                    operandeBytecode = operandeBytecode * POURCENTAGE_PWM_MOTEUR / VALEUR_MAX_TIMER0;
                    moteurs.reculerMoteur(operandeBytecode, operandeBytecode);
                    adresseLecture += UN_BYTE;
                    break;

                case TOURNER_DROITE_MOTEUR:
                    moteurs.tournerDroiteMoteur(POURCENTAGE_PWM_MOTEUR);
                    _delay_ms (1000);
                    moteurs.arreterMoteur();
                    adresseLecture += UN_BYTE;
                    break;

                case TOURNER_GAUCHE_MOTEUR:
                    moteurs.tournerGaucheMoteur(POURCENTAGE_PWM_MOTEUR);
                    _delay_ms (1200);
                    moteurs.arreterMoteur();
                    adresseLecture += UN_BYTE;
                    break;

                case DEBUT_BOUCLE: 
                    if (dansBoucle == false){
                        adresseDebutBoucle = adresseLecture + UN_BYTE;
                        nombreIteration = operandeBytecode;
                        dansBoucle = true;
                    }
                    else if (dansBoucle == true)
                        adresseLecture += UN_BYTE;
                    break;

                case FIN_BOUCLE:
                    if (nombreIteration > 0){
                        adresseLecture = adresseDebutBoucle;
                        nombreIteration--;
                    }
                    else if (nombreIteration <= -1){
                        dansBoucle = false;
                        adresseLecture += UN_BYTE;
                    }
                    break;

                case FIN:
                    enMarche = false;
                    estTermine = true;
                    break;
            }
        }
    }
}
