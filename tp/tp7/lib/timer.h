/*
 * Autheurs-es : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
 *
 * Description : Classe permettant le controle des différents timers.
 */

#ifndef TIMER_H
#define TIMER_H

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

enum Waveform
{
    WNORMAL,
    PWM_PHASE_CORRECT,
    CTC,
    PWM_FAST_PWM
};

enum CompareOutput
{
    CNORMAL,
    TOGGLE,
    CLEAR,
    SET
};

class Timer
{
protected:
    //Met un timer en mode normal
    virtual void setNormal() = 0;
    //Met un timer en mode correct
    virtual void setPWMPhaseCorrect() = 0;
    //Met un timer en mode CTC
    virtual void setCTC() = 0;
    //Met un timer en mode PWM rapide
    virtual void setFastPWM() = 0;

    //Met le mode de comparation à normal pour un timer
    virtual void setCompareNormal() = 0;
    //Met le mode de comparation à toggle pour un timer
    virtual void setCompareToggle() = 0;
    //Met le mode de comparation à clear pour un timer
    virtual void setCompareClear() = 0;
    //Met le mode de comparation à set pour un timer
    virtual void setCompareSet() = 0;

public: 
    //Choisit le mode d'un timer
    void setWaveform(Waveform mode);
    //Choisit le mode de sortie d'un timer
    void setCompareOutput(CompareOutput mode);
    //Choisit le prescaler d'un timer
    virtual void setPrescaler(uint16_t value);
    //Choisit la valeur de départ d'un timer
    virtual void setTimerStartValue(uint8_t percent) = 0;
    //virtual void setCompareValuePercent(uint8_t percentA, uint8_t percentB) = 0;
    //void setCompareValuePercent(uint8_t percentA, uint8_t percentB);
    virtual void setCompareValue(uint8_t valueA, uint8_t valueB) = 0;
    virtual void setInterupts(bool compareA, bool compareB, bool compareOF) = 0;
};

class Timer0 : public Timer
{
protected:
    void setNormal();
    void setPWMPhaseCorrect();
    void setCTC();
    void setFastPWM();
    void setCompareNormal();
    void setCompareToggle();
    void setCompareClear();
    void setCompareSet();

public:
    Timer0(/* args */);
    ~Timer0();
    void setPrescaler(uint16_t value);
    void setTimerValue(uint8_t value);
    void setCompareValue(uint8_t A, uint8_t B);
    void setTimerStartValue(uint8_t percent);
    void setInterupts(bool compareA, bool compareB, bool compareOF);
};

class Timer1 : public Timer
{
protected:
    void setNormal();
    void setPWMPhaseCorrect();
    void setCTC();
    void setFastPWM();
    void setCompareNormal();
    void setCompareToggle();
    void setCompareClear();
    void setCompareSet();

public:
    Timer1(/* args */);
    ~Timer1();
    void setPrescaler(uint16_t value);
    void setTimerValue(uint16_t value);
    void setCompareValue(uint8_t A, uint8_t B);
    void setTimerStartValue(uint8_t percent);
    //void setCompareValuePercent(uint8_t percentA, uint8_t percentB);
    void setInterupts(bool compareA, bool compareB, bool compareOF);
};

class Timer2 : public Timer
{
protected:
    void setNormal();
    void setPWMPhaseCorrect();
    void setCTC();
    void setFastPWM();
    void setCompareNormal();
    void setCompareToggle();
    void setCompareClear();
    void setCompareSet();

public:
    Timer2(/* args */);
    ~Timer2();
    void setPrescaler(uint16_t value);
    void setTimerValue(uint8_t value);
    void setCompareValue(uint8_t A, uint8_t B);
    void setTimerStartValue(uint8_t percent);
    //void setCompareValuePercent(uint8_t percentA, uint8_t percentB);
    void setInterupts(bool compareA, bool compareB, bool compareOF);
};

#endif
