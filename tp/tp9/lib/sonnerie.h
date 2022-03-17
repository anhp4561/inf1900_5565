#define F_CPU 8000000
#include <avr/interrupt.h>
#include <util/delay.h>
// Sonnerie
class Sonnerie {
public :
    Sonnerie ();
    
    ~Sonnerie ();

    void jouerSonnerieVm (uint8_t note);

    void arreterSonnerieVm ();

private :
    void initialisationTimer1CtcVm (/*Timer1& timer1*/);
    double frequencePwm_ = 0;

};