/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : TRAVAIL_PRATIQUE 7
* Section # : 3
* Equipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
* date : 21-03-2022
*
* Description :  Cette classe permet de jouer une sonnerie
 */

#define F_CPU 8000000
#include <avr/interrupt.h>
#include <util/delay.h>

class Sonnerie
{
public:
    Sonnerie();

    ~Sonnerie();

    void jouerSonnerie(uint8_t note);

    void arreterSonnerie();

private:
    void initialisationTimer1Ctc();
    double frequencePwm_ = 0;
};