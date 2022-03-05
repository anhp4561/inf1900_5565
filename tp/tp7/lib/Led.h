#include <avr/io.h>
class Led {
    public:
        Led (volatile uint8_t *port, int premierPin, int deuxiemePin);

        void allumerRougeLed ();

        void allumerVertLed();

        void allumerAmbreLed(int nIterations);
        
        void eteindreLed();

    private:
        volatile uint8_t* port_;
        int premierPin_;
        int deuxiemePin_;
};
