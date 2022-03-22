/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : TRAVAIL_PRATIQUE 7
* Section # : 3
* Equipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
* date : 13-03-2022
 * Description : Module qui permet le debogage a l'aide du RS232
 */

#include "rs232.h"
#define INITmal

void initUart();

void debugPrint(char x[], uint8_t taille);

#ifdef DEBUG
#define DEBUG_PRINT(x, taille) initUart(); debugPrint(x, taille) // Si vous definissez transmissionUART par vous memes, vous devez « undefine » INIT manuellement
#else
#define DEBUG_PRINT(x, taille) do{} while (0) // code mort
#endif