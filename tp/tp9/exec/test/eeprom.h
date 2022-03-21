/*******************************************************************************************************************************************************************************************
 * Nom: FonctionnementRobot.cpp
 * Auteurs: Manel Ben Jemaa, Oscard Arcand, Anh Pham
 * Description: Permet de lire et ecricre dans la memoire eeprom de microcontrolleur 
 * Date: 18 mars 2022
 ******************************************************************************************************************************************************************************************/


#include "global.hpp"

using namespace std;

class Memoire{
private:
    //Current memory address in bytes
    uint16_t addresse_;

public:
    
    Memoire();
    Memoire(uint16_t);
    void setAddress(uint16_t);
    void changerAddress(uint16_t);
    uint16_t getAddress();
    void ecricreEeprom(unsigned char*, uint8_t);
    void lireEeprom(unsigned char&,uint8_t);
    bool isChar1EqualChar2(unsigned char*, unsigned char*);
};