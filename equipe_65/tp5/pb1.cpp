

#define 	F_CPU   8000000UL
#include <avr/io.h> 
#include <string.h> 
#include <util/delay.h>
#include <avr/eeprom.h>

char message[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
uint16_t EEMEM adresse =0x0000;

int main()
{
DDRA= 0xFF;
eeprom_write_block ( (const void *) message, (void *)adresse, sizeof(message)); 
_delay_ms(30);
char blockLu[sizeof(message)];
adresse=0;
eeprom_read_block((void*)blockLu, (const void*)adresse, sizeof(message));
_delay_ms(30);
if (strcmp(message,blockLu)==0){
PORTA=0X01;
}
else {
PORTA=0X02;
}
  
  return 0; 
}

