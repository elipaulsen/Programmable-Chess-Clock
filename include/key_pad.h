/* +------------------------------------------------+ */
/* |         Atmel 4x4 klavestnica kniznica         | */
/* |            Atmel 4x4 keypad library            | */
/* | (c)copyright 2015 nitram147 (www.nitram147.eu) | */
/* +------------------------------------------------+ */

uint8_t nacitajklavesy();//nacita stav klavestnice / load keyboard status
uint8_t drzanieklavesy();//nacita stav klavestnice, pocka na uvolnenie / load keyboard status wait, until key release
char zistiklaves(uint8_t tmpkl);// vrati stlaceny klaves / return pressed key

//nastavenie portu na ktorom je klavestnica / setup of keyboard port
//!!! Klavestnica musi byt na jednom celom 8bitovom porte / keyboard must be connected to one full 8bit port

#define KLDDR DDRD
#define KLPORT PORTD
#define KLBIT PF
#define KLPIN PIND
