#include "can.h"
#include "moteur.h"
#include "capteur.h"

uint8_t  lectureCan(){
    uint8_t entreeAnalogique;
    can convertisseur ;  
    DDRA=0x00;
    const uint8_t pinA0 = 0;
    while(true){
           entreeAnalogique= (convertisseur.lecture(pinA0) >> 2);
    }
    return entreeAnalogique;
}

bool capteur::MettreJourPosition()
{
   
    uint8_t valeurCan = lectureCan();
    Moteur moteur;
   while(true)
   {
      Etat nouvelleEtat;
      if (valeurCan > CENTRE){
         nouvelleEtat = ERREUR;
         moteur.tournerGaucheMoteur(30);
         moteur.avancerMoteur(30,30);
         }

      else if (valeurCan  < CENTRE){
          nouvelleEtat = ERREUR;
          moteur.tournerDroiteMoteur(30);
          moteur.avancerMoteur(30,30);
          }
      else if (valeurCan  = CENTRE){
          nouvelleEtat = BONNE_POSITION;
          moteur.avancerMoteur(30,30);
          }
   }
}


