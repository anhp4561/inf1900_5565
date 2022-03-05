#include <avr/io.h>
class Led {
    public:
        Led (volatile uint8_t *port, int LedPin1, int LedPin2);

        void allumerRougeLed ();

        void allumerVertLed();

        void allumerAmbreLed(int nIterations);
        
        void eteindreLed();

    private:
        // Cet attribut est le PORTX qu'on va ecrire dessus
        volatile uint8_t* port_;
        // Cet attribut est le premier pin connecte au Led
        int LedPin1_;
        // Cet attribut est le deuxieme pin connecte au Led
        int LedPin2_;

        // Exemple de construction : On veut allumer un Led avec les pins A0 et A1 du PORTA
        // PORTA sera port_ , A0 sera LedPin1 et A1 sera LedPin2
};
