/*
 * Autheurs-es : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
 *
 * Description : Classe permettant le controle d'une LED
 */

#include <avr/io.h>
class Led {
    public:
        Led (volatile uint8_t *port, int ledPin1, int ledPin2);
        // fait all allumer la led rouge
        void allumerRougeLed ();
        // fait all allumer la led verte
        void allumerVertLed();
        // fait la led alternee entre rouge et vert nIterations fois ce qui donne l'illusion que la led est ambre
        void allumerAmbreLed(int nIterations);
        // eteint la led
        void eteindreLed();

    private:
        // Cet attribut est le PORTX qu'on va ecrire dessus
        volatile uint8_t* port_;
        // Cet attribut est le premier pin connecte au Led
        int ledPin1_;
        // Cet attribut est le deuxieme pin connecte au Led
        int ledPin2_;

        // Exemple de construction : On veut allumer un Led avec les pins A0 et A1 du PORTA
        // PORTA sera port_ , ledPin1 sera 0 et ledPin2 sera 1
};
