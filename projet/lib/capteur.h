#include "can.h"


class capteur
{
public:
   enum Etat  { BONNE_POSITION, ERREUR };

const uint16_t PROCHE = 65;
const uint16_t CENTRE = 69;
const uint16_t LOIN = 70;
 
   uint8_t lectureCan();
   bool MettreJourPosition();  
private:

};

