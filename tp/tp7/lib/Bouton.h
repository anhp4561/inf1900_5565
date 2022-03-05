#include <avr/io.h>
class Bouton {
    public:
        Bouton (volatile uint8_t *pin, int boutonPin);

        // Pour les boutons poussoirs qui utilisent un pull-down resistor
        // comme le bouton a usage general sur la carte mere
        // Si le bouton est presse, on lit la valeur "1" sur le pin, sinon "0"
        bool estBoutonPressePullDown();

        // Pour les boutons poussoirs qui utilisent un pull-up resistor
        // comme le bouton utilise au tp6
        // Si le bouton est presse, on lit la valeur "0" sur le pin, sinon "1"
        bool estBoutonPressePullUp();

    private:
        volatile uint8_t* pin_;
        int boutonPin_;
};
