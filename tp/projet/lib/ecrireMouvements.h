/*
* Nom : Anh Pham, Younes Lazzali, Oscard Arcand et Ben Jemaa Manel
* Travail : Projet Final
* Section # : 3
* Equipe # : 5565
* Correcteur : Ghali chraibi ,	Charles Jiang 
* date : 28-03-2022
 * Description : Classe qui enregistre les instructions du robot en mémoire
 */

class ecrireEnMemoire {
    public:

        //Méthode qui initialise l'écriture des données en mémoire
        void initialisationEcriture( void );
        //Méthode qui écrit une instruction et une opérande en mémoire
        void ecrireInstruction(uint8_t instruction, uint8_t operande);
        //Méthode qui refait le parcours enregistré en mémoire
        void refaireParcours(Moteur moteurs);
    
};
