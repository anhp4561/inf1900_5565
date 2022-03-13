/*
 * Autheurs-es : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
 *
 * Description : Classe permettant le controle des deux moteurs du robot
 */

class Moteur {
    public:
        // WGM03 WGM02 WGM01 WGM00 = 0 0 0 1 PWM, Phase correct , 8-bit
        // WGM03 WGM02 WGM01 WGM00 = 0 0 1 1 PWM, Phase correct , 10-bit
        // prescalor / 8
        // Met OC0A/OC0B a 0 lorsque TCNT0 est egal a OCR0A/OCR0B et qu'on compte vers le haut
        // Met OC0A/OC0B a 1 lorsque TCNT0 est egal a OCR0A/OCR0B et qu'on compte vers le bas
        // fonction pris du dossier desperate-student de Ahmad Faour
        void initialisationTimer0Pwm();

        void avancerMoteur(int pourcentageOC0A, int pourcentageOC0B);

        void reculerMoteur(int pourcentageOC0A, int pourcentageOC0B);

        void tournerGaucheMoteur(int pourcentageOC0A);

        void tournerDroiteMoteur(int pourcentageOC0B);

        void arreterMoteur();

    private:
        void reglerVitesseMoteur(int pourcentageOC0A, int pourcentageOC0B);

};


// Emplacement des cables lors de la programmation de Moteur.h et de Moteur.cpp
// PB2 vers Direction M1
// PB3 ou OC0A vers Enable M1
// PB4 ou OC0B vers Enable M2
// PB5 vers Direction M2
// Donc, PB2 et PB3 pour le moteur a gauche
//       PB4 et PB5 pour le moteur a droite