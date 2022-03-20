#define F_CPU 8000000
#include <avr/interrupt.h>
#include <util/delay.h>
// Sonnerie
class Sonnerie {
public :
    Sonnerie ();
    
    ~Sonnerie ();

    void jouerSonnerie (uint8_t note);

    void arreterSonnerie ();

private :
    void initialisationTimer1Ctc (/*Timer1& timer1*/);
    double frequencePwm_ = 0;
    
};