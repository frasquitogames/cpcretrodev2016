#include <cpctelera.h>

#include "game.h"
#include "estructuras/menu.h"
#include "estructuras/match.h"
#include "tiles/tiles.h"
#include "musica/musica.h"

#include "debug.h"


extern void play();
void initCPC();
void initMyGame();


T_Game myGame;
u8 i;

void initCPC(){
	cpct_disableFirmware();
	cpct_setVideoMode(0);
	cpct_setBorder(HW_BLACK);
	cpct_setPalette(g_palette, 16);
   	cpct_setVideoMode(0);
}

void initMyGame(){
	myGame.is_running = 1;
	myGame.op_p1 = 0;
	myGame.op_p2 = 0;
	myGame.op_lvl = 0;
	myGame.seed = 0;

	myGame.status = GS_ONMENU;
}

void intHandler()
{
	if(i++ == 6)
	{
		play();
		i = 0;
	}
}

void init(){
	initCPC();
	initMyGame();
	initMenu();
	initMusica();
	cpct_setInterruptHandler(intHandler);
}

void run(){
	
	init();
	myGame.is_running = 1;

	//Bucle principal del juego
	while(myGame.is_running){

		processInput();

		update();

		if(myGame.is_running){
			cpct_waitVSYNC();
			draw();
		}
	}

   
  

}

void processInput(){
	switch(myGame.status) {

	   	case GS_ONMENU:
	    	cpct_scanKeyboard();

	    break;

	   	default:
	   		cpct_scanKeyboard_f();
	}

}


void update(){
	switch(myGame.status) {

	   	case GS_ONMENU:
	   		updateMenu(&myGame);
	   		myGame.seed++;
	    break;

	    case GS_ONMATCH:    	
	   		updateMatch(&myGame);
	    break;
		case GS_BACK4MATCH:    	
	   		init();
	    break;

	}	
	 
}

void draw(){	
	switch(myGame.status) {

	   	case GS_ONMENU:
	   		drawMenu();

	    break;

	    case GS_ONMATCH:
	   		drawMatch();

	    break;



	}
	
	
}

