#include <cpctelera.h>
#include <stdio.h>

#include "debug.h"

u8 str[8];
u8* pscr;

void pu8(u8 cad[], u8 val, u8 pos){
	u8 x = 0;
	u8 y = 0;

	switch(pos){
		case 1:
		x = 0;
		y = 161; 
		break; 

		case 2:
		x = 20;
		y = 161; 
		break;

		case 3:
		x = 40;
		y =161; 
		break; 

		case 4:
		x = 60;
		y = 161; 
		break; 
		case 5:
		x = 0;
		y = 181; 
		break; 

		case 6:
		x =20;
		y =181; 
		break; 

		case 7:
		x =40;
		y =181; 
		break; 

		case 8:
		x =60;
		y =181; 
		break; 
	}

	pscr = cpct_getScreenPtr(CPCT_VMEM_START, x,  y);
	cpct_drawStringM0(cad, pscr, 3, 0);
	
	if(val < 10){	
		sprintf(str, "%1u", val);
	}
	else if(val < 100){
		sprintf(str, "%2u", val);
	}
	else{
		sprintf(str, "%3u", val);
	}

	pscr = cpct_getScreenPtr(CPCT_VMEM_START, x,  y+9);
	cpct_drawStringM0(str, pscr, 3, 0);

}


void pentro(u8 x, u8 y){
	pscr = cpct_getScreenPtr(CPCT_VMEM_START, x,  y);
	cpct_drawStringM0("entro", pscr, 3, 0);
}

void wfk(cpct_keyID key) {
   do
      cpct_scanKeyboard_f();
   while( ! cpct_isKeyPressed(key) );
   do
      cpct_scanKeyboard_f();
   while( cpct_isKeyPressed(key) );
}

