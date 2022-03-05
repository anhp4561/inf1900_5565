#include <avr/io.h>
class Bouton {
    public:
        Bouton (volatile uint8_t *pin, int boutonPin);

        // enum class pris du dossier desperate-student-librairy de Ahmad Faour
        enum class Etat {
            AUCUN,
            PRESSE,
            MAINTENU,
            RELACHE
        };

        // Pour les boutons poussoirs qui utilisent un pull-down resistor
        // comme le bouton a usage general sur la carte mere
        // Si le bouton est presse, on lit la valeur "1" sur le pin, sinon "0"
        bool estBoutonPresseRappel();

        // Pour les boutons poussoirs qui utilisent un pull-up resistor
        // comme le bouton utilise au tp6
        // Si le bouton est presse, on lit la valeur "0" sur le pin, sinon "1"
        bool estBoutonPresseTirage();

        // fonction pris du dossier desperate-student-librairy de Ahmad Faour
        void actualiserEtat(); 

    private:
        // Cet attribut est la PINX qu'on va lire
        volatile uint8_t* pin_;
        // Cet attribut est le PXY qu'on va lire
        int boutonPin_;
        // Exemple de construction : On veut lire la valeur 2 sur PIND
        // PIND sera pin_ et 2 sera boutonPin_
        Etat etat_;
};
