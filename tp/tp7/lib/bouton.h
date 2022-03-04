bool estBoutonPressé(uint8_t masque, uint8_t PIN) {
if (PIN & masque){   
_delay_ms(REBOND);
return (PIN & masque);
}
return false;
}