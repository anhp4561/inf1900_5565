 /*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : projet final
* Section # : 3
* Equipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
* date : 20-04-2022
 * Description : Classe permettant le controle des différents timers.
 */


#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


//Met un timer en mode normal
void setNormal(uint8_t timer);
//Met un timer en mode correct
void setPWMPhaseCorrect(uint8_t timer);
//Met un timer en mode CTC
void setCTC(uint8_t timer);
//Met un timer en mode PWM rapide
void setFastPWM(uint8_t timer);
//Met le mode de comparation à normal pour un timer
void setCompareNormal(uint8_t timer);
//Met le mode de comparation à toggle pour un timer
void setCompareToggle(uint8_t timer);
//Met le mode de comparation à clear pour un timer
void setCompareClear(uint8_t timer);
//Met le mode de comparation à set pour un timer
void setCompareSet(uint8_t timer);
//Choisit le mode du timer 0
void timer0SetWaveform(int mode);
//Choisit le mode du timer 1
void timer1SetWaveform(int mode);
//Choisit le mode du timer 2
void timer2SetWaveform(int mode);
//Choisit le mode de sortie du timer 0
void timer0SetCompareOutput(int mode);
//Choisit le mode de sortie du timer 1
void timer1SetCompareOutput(int mode);
//Choisit le mode de sortie du timer 2
void timer2SetCompareOutput(int mode);
//Choisit le prescaler du timer 0
void timer0SetPrescaler(uint16_t value);
//Choisit le prescaler du timer 1
void timer1SetPrescaler(uint16_t value);
//Choisit le prescaler du timer 2
void timer2SetPrescaler(uint16_t value);
//Choisit la valeur du timer 0
void setTimer0Value(uint8_t value);
//Choisit la valeur de départ du timer 0
void setTimer0StartValue(uint8_t percent);
//Choisit la valeur de départ du timer 1
void setTimer1StartValue(uint8_t percent);
//Choisit la valeur de départ du timer 2
void setTimer2StartValue(uint8_t percent);
//Méthode qui initialise les interruptions avec le timer 0
void timer0SetInterupts(bool compareA, bool compareB, bool compareOF);
//Méthode qui initialise les interruptions avec le timer 1
void timer1setInterupts(bool compareA, bool compareB, bool compareOF);
//Méthode qui initialise les interruptions avec le timer 2
void timer2SetInterupts(bool compareA, bool compareB, bool compareOF);