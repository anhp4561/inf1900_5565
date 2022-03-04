#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
/**
 * Objectif du TP1: 
 * 1- Allumer une DEL sans interagir avec le bouton
 *      1.1- Identifier les pins que vous allez utiliser => A0-A1
 *      1.2- Configurer le mode (entrer/sortie) des ports => Sortie
 *      1.3- Envoyer les bons signaux => Allumer del
 *  
 * 2- Allumer une DEL avec le bouton
 *      2.1- Identifier les pins du bouton => D2
 *      2.2- Configurer le mode(entrer/sortie) du bouton => Entrer
 *      2.3- Capter le signal du bouton => Appuyer
 * 3- Refactor le code
 * 
 * Matériel utiliser:
 * - Del1: cathode (+) => PA0, anode (-) => PA1
 * - Del2: cathode (+) => PA1, anode (-) => PA0
 * - Button: PD2
 * 
 * Table de vérité:
 * Ou (||) de comparaison =>
 *        A - B - (A || B)
 *        V   V      V
 *        V   F      V
 *        F   V      V
 *        F   F      F
 * Et (&&) de comparaison =>
 *        A - B - (A && B)
 *        V   V      V
 *        V   F      F
 *        F   V      F
 *        F   F      F
 * 
 * A = 0b0000
 * B = 0b0001
 * C = A | B => C = 0b0001 équivalent de true en boolean 
 * 
 * D = A & B => D = 0b0000 équivalent de false en boolean
 * 
 * */
int main()
{
    // Étape 1.1
    // Mode sortie pour A0 A1
    // DDRA = 0x3;
    // DDRA = 0b0000'0011;
    // DDRA = 3;
    // DDRA = 0b0000'0001 | 0b0000'0010;

    // Refactor
    // 1 << DDA0 == 0b0000'0001
    // DDRA = 0b????'????
    // DDRA | 1 << DDA0 ==> 0b????'???? | 0b0000'0001 == 0b????'???1
    DDRA |= (1 << DDA0) | (1 << DDA1);

    // Étape 2.1
    // Mode entrer pour D2
    // DDRD = 0x0;
    // DDRD = 0b0000'0000;
    // DDRD = 0;

    // Refactor
    // 1 << DDD2 == 0b0000'0100
    // ~(1 << DDD2) == 0b1111'1011
    // DDRD = 0b????'????
    // DDRD & ~(1 << DDD2) ==> 0b????'???? & 0b1111'1011 == 0b????'?0??
    DDRD &= ~(1 << DDD2);

    const uint8_t debounceTime = 10;
    while (true)
    {
        const bool buttonPressed = PIND & (1 << PIND2);

        if (buttonPressed)
        {
            // Vérification debounce
            _delay_ms(debounceTime);
            // Étape 2.3
            // La valeur de PIND lorsque le bouton est appuyé 0b0000'0100
            // PIND & 0b0000'0100 ==> 0b0000'0100 ==> 4 ==> true
            // PIND && 0b0000'0100 ==> true && true ==> true (pas bonne manière de le faire)
            // PIND == 0b0000'0100 ==> true ==> true (pas bonne manière de le faire)
            if (PIND & (1 << PIND2))
            {
                // Étape 1.3
                // Affecter le signal 1 sur la pin A0 et le signal 0 sur la pin A1
                // PORTA = 0x1;
                // PORTA = 0b0000'0001;
                // PORTA = 1;

                // Refactor
                PORTA = 1 << PA0;
            }
            else
            {
                // Étape 1.3
                // Affecter le signal 1 sur la pin A1 et le signal 0 sur la pin A0
                // PORTA = 0x2;
                // PORTA = 0b0000'0010;
                // PORTA = 2;

                // Refactor
                PORTA = 1 << PA1;
            }
        }
    }

    return 0;
}