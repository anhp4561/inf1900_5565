class LED{
public:
void eteindreLed(uint8_t PORT);
void allumerLedRouge(uint8_t PORT);
void allumerLedVert(uint8_t PORT);
void allumerAmbre(uint8_t pin);
void choisirPort(char port);

private:
void allumerLed(uint8_t couleur, uint8_t pin);
};
