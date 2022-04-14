/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : Projet final
* Section # : 3
* Equipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
* date : 20-04-2022
 * Description : Classe permettant le controle des différents timers.
 */
#include "timer.h"

//Met un timer en mode normal
void setNormal(uint8_t timer)
{
    switch(timer) 
    {
    case 0:
        TCCR0A &= ~(1 << WGM01) & ~(1 << WGM00);
        TCCR0B &= ~(1 << WGM02);
        break;
    case 1:
         TCCR1A &= ~(1 << WGM11) & ~(1 << WGM10);
        TCCR1B &= ~(1 << WGM12);
        break;
    case 2:
        TCCR2A &= ~(1 << WGM21) & ~(1 << WGM20);
        TCCR2B &= ~(1 << WGM22);
        break;
    default:
        break;
    }
}
//Met un timer en mode correct
void setPWMPhaseCorrect(uint8_t timer)
{
    switch(timer) 
    {
    case 0:
        TCCR0A &= ~(1 << WGM01);
        TCCR0A |= (1 << WGM00);
        TCCR0B &= ~(1 << WGM02);
        break;
    case 1:
        TCCR1A &= ~(1 << WGM11);
        TCCR1A |= (1 << WGM10);
        TCCR1B &= ~(1 << WGM12);
        break;
    case 2:
        TCCR2A &= ~(1 << WGM21);
        TCCR2A |= (1 << WGM20);
        TCCR2B &= ~(1 << WGM22);
        break;
    default:
        break;
    }
}
//Met un timer en mode CTC
void setCTC(uint8_t timer)
{
    switch(timer) 
    {
    case 0:
        TCCR0A &= ~(1 << WGM01) & ~(1 << WGM00);
        TCCR0B |= (1 << WGM02);
        break;
    case 1:
        TCCR1A &= ~(1 << WGM11);
        TCCR1A &= ~(1 << WGM10);
        TCCR1B |= (1 << WGM12);
        break;
    case 2:
        TCCR2A |= (1 << WGM21);
        TCCR2A &= ~(1 << WGM20);
        TCCR2B &= ~(1 << WGM22);
        break;
    default:
        break;
    }
}
//Met un timer en mode PWM rapide
void setFastPWM(uint8_t timer)
{
    switch(timer) 
    {
    case 0:
        TCCR0A |= (1 << WGM01) | (1 << WGM00);
        TCCR0B &= ~(1 << WGM02);
        break;
    case 1:
        TCCR1A |= (1 << WGM11) | (1 << WGM10);
        TCCR1B &= ~(1 << WGM12);
        break;
    case 2:
        TCCR2A |= (1 << WGM21) | (1 << WGM20);
        TCCR2B &= ~(1 << WGM22);
        break;
    default:
        break;
    }
}
//Met le mode de comparation à normal pour un timer
void setCompareNormal(uint8_t timer)
{
    switch(timer) 
    {
    case 0:
        TCCR0A &= ~(1 << COM0A1) & ~(1 << COM0A0);
        TCCR0A &= ~(1 << COM0B1) & ~(1 << COM0B0);
        break;
    case 1:
        TCCR1A &= ~(1 << COM1A1) & ~(1 << COM1A0);
        break;
    case 2:
        TCCR2A &= ~(1 << COM2A1) & ~(1 << COM2A0);
        TCCR2A &= ~(1 << COM2B1) & ~(1 << COM2B0);
        break;
    default:
        break;
    }
}
//Met le mode de comparation à toggle pour un timer
void setCompareToggle(uint8_t timer)
{
    switch(timer) 
    {
    case 0:
        TCCR0A &= ~(1 << COM0A1);
        TCCR0A |= (1 << COM0A0);
        TCCR0A &= ~(1 << COM0B1);
        TCCR0A |= (1 << COM0B0);
        break;
    case 1:
        TCCR1A &= ~(1 << COM1A1);
        TCCR1A |= (1 << COM1A0);
        TCCR1A &= ~(1 << COM1B1);
        TCCR1A |= (1 << COM1B0);
        break;
    case 2:
        TCCR2A &= ~(1 << COM2A1);
        TCCR2A |= (1 << COM2A0);
        TCCR2A &= ~(1 << COM2B1);
        TCCR2A |= (1 << COM2B0);
        break;
    default:
        break;
    }
}
//Met le mode de comparation à clear pour un timer
void setCompareClear(uint8_t timer)
{
    switch(timer) 
    {
    case 0:
        TCCR0A |= (1 << COM0A1);
        TCCR0A &= ~(1 << COM0A0);
        TCCR0A |= (1 << COM0B1);
        TCCR0A &= ~(1 << COM0B0);
        break;
    case 1:
        TCCR1A |= (1 << COM1A1);
        TCCR1A &= ~(1 << COM1A0);
        TCCR1A |= (1 << COM1B1);
        TCCR1A &= ~(1 << COM1B0);
        break;
    case 2:
        TCCR2A |= (1 << COM2A1);
        TCCR2A &= ~(1 << COM2A0);
        TCCR2A &= ~(1 << COM2B1);
        TCCR2A |= (1 << COM2B0);
        break;
    default:
        break;
    }
}
//Met le mode de comparation à set pour un timer
void setCompareSet(uint8_t timer)
{
    switch(timer) 
    {
    case 0:
        TCCR0A |= (1 << COM0A1) | (1 << COM0A0);
        TCCR0A |= (1 << COM0B1) | (1 << COM0B0);
        break;
    case 1:
        TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
        TCCR1A |= (1 << COM1B1) | (1 << COM1B0);
        break;
    case 2:
        TCCR2A |= (1 << COM2A1) | (1 << COM2A0);
        TCCR2A |= (1 << COM2B1) | (1 << COM2B0);
        break;
    default:
        break;
    }
}

//Choisit le mode du timer 0
void timer0SetWaveform(int mode)
{
    switch (mode)
    {
    case 0:
        //Met un timer en mode normal
        setNormal(0);
        break;
    case 1:
        //Met un timer en mode correct
        setPWMPhaseCorrect(0);
        break;
    case 2:
        //Met un timer en mode CTC
        setCTC(0);
        break;
    case 3:
        //Met un timer en mode PWM rapide
        setFastPWM(0);
        break;
    default:
        break;
    }
}

//Choisit le mode du timer 1
void timer1SetWaveform(int mode)
{
    switch (mode)
    {
    case 0:
        //Met un timer en mode normal
        setNormal(1);
        break;
    case 1:
        //Met un timer en mode correct
        setPWMPhaseCorrect(1);
        break;
    case 2:
        //Met un timer en mode CTC
        setCTC(1);
        break;
    case 3:
        //Met un timer en mode PWM rapide
        setFastPWM(1);
        break;
    default:
        break;
    }
}

//Choisit le mode du timer 2
void timer2SetWaveform(int mode)
{
    switch (mode)
    {
    case 0:
        //Met un timer en mode normal
        setNormal(2);
        break;
    case 1:
        //Met un timer en mode correct
        setPWMPhaseCorrect(2);
        break;
    case 2:
        //Met un timer en mode CTC
        setCTC(2);
        break;
    case 3:
        //Met un timer en mode PWM rapide
        setFastPWM(2);
        break;
    default:
        break;
    }
}

//Choisit le mode de sortie du timer 0
void timer0SetCompareOutput(int mode)
{
    
    switch (mode)
    {
    case 0:
        //Met le mode de comparation à normal pour un timer
        setCompareNormal(0);
        break;
    case 1:
        //Met le mode de comparation à toggle pour un timer
        setCompareToggle(0);
        break;
    case 2:
        //Met le mode de comparation à clear pour un timer
        setCompareClear(0);
        break;
    case 3:
        //Met le mode de comparation à set pour un timer
        setCompareSet(0);
        break;
    default:
        break;
    }
}

//Choisit le mode de sortie du timer 1
void timer1SetCompareOutput(int mode)
{
    
    switch (mode)
    {
    case 0:
        //Met le mode de comparation à normal pour un timer
        setCompareNormal(1);
        break;
    case 1:
        //Met le mode de comparation à toggle pour un timer
        setCompareToggle(1);
        break;
    case 2:
        //Met le mode de comparation à clear pour un timer
        setCompareClear(1);
        break;
    case 3:
        //Met le mode de comparation à set pour un timer
        setCompareSet(1);
        break;
    default:
        break;
    }
}

//Choisit le mode de sortie du timer 2
void timer2SetCompareOutput(int mode)
{
    
    switch (mode)
    {
    case 0:
        //Met le mode de comparation à normal pour un timer
        setCompareNormal(2);
        break;
    case 1:
        //Met le mode de comparation à toggle pour un timer
        setCompareToggle(2);
        break;
    case 2:
        //Met le mode de comparation à clear pour un timer
        setCompareClear(2);
        break;
    case 3:
        //Met le mode de comparation à set pour un timer
        setCompareSet(2);
        break;
    default:
        break;
    }
}

//Choisit le prescaler du timer 0
void timer0SetPrescaler(uint16_t value){
    switch (value){
    case 0:
        TCCR0B &= ~(1 << CS02) & ~(1 << CS01) & ~(1 << CS00);
        break;
    case 1:
        TCCR0B &= ~(1 << CS02) & ~(1 << CS01);
        TCCR0B |= (1 << CS00);
        break;
    case 8:
        TCCR0B &= ~(1 << CS02) & ~(1 << CS00);
        TCCR0B |= (1 << CS01);
        break;
    case 64:
        TCCR0B &= ~(1 << CS02);
        TCCR0B |= (1 << CS01) | (1 << CS00);
        break;
    case 256:
        TCCR0B &= ~(1 << CS01) & ~(1 << CS00);
        TCCR0B |= (1 << CS02);
        break;
    case 1024:
        TCCR0B |= (1 << CS02) | (1 << CS02);
        TCCR0B &= ~(1 << CS01);
        break;
    default:
        break;
    }
}

//Choisit le prescaler du timer 1
void timer1SetPrescaler(uint16_t value){
    switch (value){
    case 0:
        TCCR1B &= ~(1 << CS12) & ~(1 << CS11) & ~(1 << CS10);
        break;
    case 1:
        TCCR1B &= ~(1 << CS12) & ~(1 << CS01);
        TCCR1B |= (1 << CS10);
        break;
    case 8:
        TCCR1B &= ~(1 << CS12) & ~(1 << CS10);
        TCCR1B |= (1 << CS11);
        break;
    case 64:
        TCCR1B &= ~(1 << CS12);
        TCCR1B |= (1 << CS11) | (1 << CS10);
        break;
    case 256:
        TCCR1B &= ~(1 << CS11) & ~(1 << CS10);
        TCCR1B |= (1 << CS12);
        break;
    case 1024:
        TCCR1B |= (1 << CS12) | (1 << CS12);
        TCCR1B &= ~(1 << CS11);
        break;
    default:
        break;
    }
}

//Choisit le prescaler du timer 2
void timer2SetPrescaler(uint16_t value){
    switch (value){
    case 0:
        TCCR2B &= ~(1 << CS22) & ~(1 << CS21) & ~(1 << CS20);
        break;
    case 1:
        TCCR2B &= ~(1 << CS22) & ~(1 << CS21);
        TCCR2B |= (1 << CS20);
        break;
    case 8:
        TCCR2B &= ~(1 << CS22) & ~(1 << CS20);
        TCCR2B |= (1 << CS21);
        break;
    case 64:
        TCCR2B &= ~(1 << CS22);
        TCCR2B |= (1 << CS21) | (1 << CS20);
        break;
    case 256:
        TCCR2B &= ~(1 << CS21) & ~(1 << CS20);
        TCCR2B |= (1 << CS22);
        break;
    case 1024:
        TCCR2B |= (1 << CS22) | (1 << CS22);
        TCCR2B &= ~(1 << CS21);
        break;
    default:
        break;
    }
}

//Choisit la valeur du timer 0
void setTimer0Value(uint8_t value){
    TCNT0 = value;
}

//Choisit la valeur du timer 1
void setTimer1Value(uint16_t value){
    TCNT1 = value;
}

//Choisit la valeur du timer 2
void setTimer2Value(uint8_t value){
    TCNT2 = value;
}

//Choisit la valeur pour comparer avec le timer 0
void timer0SetCompareValue(uint16_t A, uint16_t B){
    OCR0A = A;
    OCR0B = B;
}

//Choisit la valeur pour comparer avec le timer 1
void timer1SetCompareValue(uint8_t A, uint8_t B){
    OCR1A = A;
    OCR1B = B;
}

//Choisit la valeur pour comparer avec le timer 2
void timer2SetCompareValue(uint8_t A, uint8_t B){
    OCR2A = A;
    OCR2B = B;
}

//Choisit la valeur de départ du timer 0
void setTimer0StartValue(uint8_t percent){
    uint8_t hundred = 100;
    uint8_t bits = 255;
    int value = (percent * bits) / hundred;
    percent = value;
    setTimer0Value(percent);
}

//Choisit la valeur de départ du timer 1
void setTimer1StartValue(uint8_t percent){
    uint16_t hundred = 100;
    uint16_t bits = 65534;
    uint16_t speed = percent * (bits / hundred);

    setTimer1Value(speed);
}

//Choisit la valeur de départ du timer 2
void setTimer2StartValue(uint8_t percent){
    uint8_t hundred = 100;
    uint8_t bits = 255;
    int value = (percent * bits) / hundred;
    percent = value;
    setTimer2Value(percent);
}

//Méthode qui initialise les interruptions avec le timer 0
void timer0SetInterupts(bool compareA, bool compareB, bool compareOF){
    if (compareA) {
        TIMSK0 |= (1 << OCIE0A);
    }
    else{
        TIMSK0 &= ~(1 << OCIE0A);
    }

    if (compareB){
        TIMSK0 |= (1 << OCIE0B);
    }
    else{
        TIMSK0 &= ~(1 << OCIE0B);
    }

    if (compareOF){
        TIMSK0 |= (1 << TOIE0);
    }
    else{
        TIMSK0 &= ~(1 << TOIE0);
    }
}

//Méthode qui initialise les interruptions avec le timer 1
void timer1setInterupts(bool compareA, bool compareB, bool compareOF){
    if (compareA){
        TIMSK1 |= (1 << OCIE1A);
    }
    else{
        TIMSK1 &= ~(1 << OCIE1A);
    }
    if (compareB){
        TIMSK1 |= (1 << OCIE1B);
    }
    else{
        TIMSK1 &= ~(1 << OCIE1B);
    }

    if (compareOF){
        TIMSK1 |= (1 << TOIE1);
    }
    else{
        TIMSK1 &= ~(1 << TOIE1);
    }
}

//Méthode qui initialise les interruptions avec le timer 2
void timer2SetInterupts(bool compareA, bool compareB, bool compareOF){
    if (compareA){
        TIMSK2 |= (1 << OCIE2A);
    }
    else{
        TIMSK2 &= ~(1 << OCIE2A);
    }

    if (compareB){
        TIMSK2 |= (1 << OCIE2B);
    }
    else{
        TIMSK2 &= ~(1 << OCIE2B);
    }

    if (compareOF){
        TIMSK2 |= (1 << TOIE2);
    }
    else{
        TIMSK2 &= ~(1 << TOIE2);
    }
}