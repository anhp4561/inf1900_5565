#include "interpreteurByteCode.h"

const int DEBUT = 0x01, 
ATTENDRE = 0x02, 
ALLUMERDEL = 0x44, 
ETEINDREDEL = 0x45, 
JOUERSON = 0x48, 
STOPSON = 0x09, 
STOPMOTEUR1 = 0x60, 
STOPMOTEUR2 = 0x61, 
AVANCER = 0x62, 
RECULER = 0x63, 
TOURNERDROITE = 0x64, 
TOURNERGAUCHE = 0x65, 
DEBUTBOUCLE = 0xC0, 
FINBOUCLE = 0xC1, 
FIN = 0xFF;


bool enMarche = false;

int main () {
     while(true){
     // lire le byte code ici 
         if (enMarche || (byteCode == 0x01)) { // 
             switch (byteCode){
                 case DEBUT:
                     enMarche = true
                     break;

                 case ATTENDRE:
                     break;

                 case ALLUMERDEL:
                     break;

                 case ETEINDREDEL:
                     break;

                 case JOUERSON:
                     break;

                 case STOPSON:
                     break;

                 case STOPMOTEUR1:
                     break;

                 case STOPMOTEUR2:
                     break;

                 case AVANCER:
                     break;

                 case RECULER:
                     break;

                 case TOURNERDROITE:
                     break;

                 case TOURNERGAUCHE:
                     break;

                 case DEBUTBOUCLE:
                     break;

                 case FINBOUCLE:
                     break;

                 case FIN:
                     break;
             }
         }
     }
 }
