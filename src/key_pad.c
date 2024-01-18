/* +------------------------------------------------+ */
/* |         Atmel 4x4 klavestnica kniznica         | */
/* |            Atmel 4x4 keypad library            | */
/* | (c)copyright 2015 nitram147 (www.nitram147.eu) | */
/* +------------------------------------------------+ */

#include <avr/io.h>
#include <util/delay.h>

#include "klavestnica.h"

volatile char klaves [4][4] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

volatile uint8_t tempklaves;

uint8_t nacitajklavesy(){
	KLDDR = 0xF0;
	KLPORT = 0x0F;
	_delay_ms(10);
	tempklaves = KLPIN & 0x0F;
	KLDDR = 0x0F;
	KLPORT = 0xF0;
	_delay_ms(10);
	tempklaves |= (KLPIN & 0xF0);
	KLPORT = 0;
	KLDDR = 0;
	_delay_ms(10);
	return tempklaves;
}

uint8_t drzanieklavesy(){
	uint8_t drzklvtmp = nacitajklavesy();
	while(drzklvtmp == nacitajklavesy()){}
	return drzklvtmp;
}

char zistiklaves(uint8_t tmpkl){
	uint8_t prkl,drkl,rdk,stp;
	rdk = 9;stp = 9;
	prkl = tmpkl & 0xF0;
	prkl >>= 4;
	drkl = tmpkl & 0x0F;
	if(prkl==0x07){rdk=0;}
	else if (prkl==0x0B){rdk=1;}
	else if (prkl==0x0D){rdk=2;}
	else if (prkl==0x0E){rdk=3;}
	if(drkl==0x07){stp=0;}
	else if (drkl==0x0B){stp=1;}
	else if (drkl==0x0D){stp=2;}
	else if (drkl==0x0E){stp=3;}
	if(rdk != 9 && stp != 9){return klaves[rdk][stp];}else{return 0xFF;}

}

