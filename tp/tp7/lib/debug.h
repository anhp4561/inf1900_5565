/*
 * Autheurs-es : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
 *
 * Description : Module qui permet l'affichage de donnes avec RS232 a des fins de debogage
 */

#include "rs232.h"
#define INITmal

void initUart();

void debugPrint(const char x[], int taille);
// void debugPrint(unsigned char x[], int taille );
// void debugPrint(int x, int taille);

// #ifdef DEBUG
// # ifdef INIT
// #  define DEBUG_PRINT(x) initUart(); debugPrint(x) // Si vous definissez transmissionUART par vous memes, vous devez « undefine» INIT manuellement
// #  undef INIT
// # else
// #  define DEBUG_PRINT(x) debugPrint(x)
// # endif
// #else
// # define DEBUG_PRINT(x) do {} while (0) // code mort
// #endif

#ifdef DEBUG
# ifdef INIT
#  define DEBUG_PRINT(x, taille) initUart(); debugPrint(x, taille)  // Si vous definissez transmissionUART par vous memes, vous devez « undefine » INIT manuellement
#  undef INIT
# else
#  define DEBUG_PRINT(x, taille) debugPrint(x,taille)
# endif
#else
# define DEBUG_PRINT(x,taille) do {} while (0) // code mort
#endif