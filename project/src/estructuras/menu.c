#include <cpctelera.h>
#include "menu.h"
#include "../sprites/fondo.h"
#include "../sprites/pp.h"
#include "../sprites/ciudadanos.h"
#include "../sprites/psoe.h"
#include "../sprites/podemos.h"
#include "../musica/musica.h"

#include "../debug.h"

void drawMainScreen();
void drawPlayerSelection();
void drawChoseLvlScreen();
void drawInstructionsScreen();
void drawCreditsScreen();

T_Menu myMenu;


//public funtions implementation

void initMenu(){
	myMenu.pvmem = CPCT_VMEM_START;
	myMenu.screen = MS_MAIN;

	myMenu.draw = 1;
	initMusica();
}

void updateMenu(T_Game* game){
	u8* r = &game->is_running; 
	u8* p1 = &game->op_p1; 
	u8* p2 = &game->op_p2; 
	u8* lvl = &game->op_lvl;
	//u32* seed = &game->seed;
	T_GameStatus* s = &game->status;

	if(cpct_isAnyKeyPressed()){

		switch(myMenu.screen) {
		   	case MS_MAIN:
		   		if(cpct_isKeyPressed(Key_1)){
		   			myMenu.screen = MS_TWOPLAYER;
		   			myMenu.draw = 1;	
					cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
		   		}
		   		else if(cpct_isKeyPressed(Key_2)){
		   			myMenu.screen = MS_INSTRUCTIONS;
		   			myMenu.draw = 1;	
					cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
		   		}
		   		else if(cpct_isKeyPressed(Key_3)){
		   			myMenu.screen = MS_CREDITS;
		   			myMenu.draw = 1;	
					cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
		   		}
		   		else if(cpct_isKeyPressed(Key_4)){
		   			*r = 0;
				cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
		   		}
				else{
					cpct_akp_SFXPlay(1, 15, 36, 0, 40, AY_CHANNEL_A);
				}
		    break;


		    case MS_TWOPLAYER:
		    	if(!*p1){
		    		if(cpct_isKeyPressed(Key_1)){
			    		*p1 = 1;

			    		myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 6, 188);
						cpct_drawStringM0("J1", myMenu.pvmem, 15, 1);
						cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
			    	}
			    	else if(cpct_isKeyPressed(Key_2)){
			   			*p1 = 2;

			   			myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 26, 188);
						cpct_drawStringM0("J1", myMenu.pvmem, 15, 1);
						cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
			   		}
			   		else if(cpct_isKeyPressed(Key_3)){
			   			*p1 = 3;

			   			myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 46, 188);
						cpct_drawStringM0("J1", myMenu.pvmem, 15, 1);
						cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
			   		}
			   		else if(cpct_isKeyPressed(Key_4)){
			   			*p1 = 4;

			   			myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 66, 188);
						cpct_drawStringM0("J1", myMenu.pvmem, 15, 1);
						cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
			   		}
		    	}
		    	else{
		    		if(cpct_isKeyPressed(Key_1) && *p1 != 1){
			    		*p2 = 1;

						myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 6, 188);
						cpct_drawStringM0("J2", myMenu.pvmem, 15, 1);

			    		myMenu.screen = MS_CHOSELVL;
			    		myMenu.draw = 1;
						cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
			    	}
			    	else if(cpct_isKeyPressed(Key_2) && *p1 != 2){
			   			*p2 = 2;

			   			myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 26, 188);
						cpct_drawStringM0("J2", myMenu.pvmem, 15, 1);

			   			myMenu.screen = MS_CHOSELVL;
			   			myMenu.draw = 1;
						cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
			   		}
			   		else if(cpct_isKeyPressed(Key_3) && *p1 != 3){
			   			*p2 = 3;

			   			myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 46, 188);
						cpct_drawStringM0("J2", myMenu.pvmem, 15, 1);

			   			myMenu.screen = MS_CHOSELVL;
			   			myMenu.draw = 1;
						cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
			   		}
			   		else if(cpct_isKeyPressed(Key_4) && *p1 != 4){
			   			*p2 = 4;

			   			myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 66, 188);
						cpct_drawStringM0("J2", myMenu.pvmem, 15, 1);

			   			myMenu.screen = MS_CHOSELVL;
			   			myMenu.draw = 1;
						cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
			   		}
		    	}

		    	if(cpct_isKeyPressed(Key_Esc)){
		   			myMenu.screen = MS_MAIN;
		   			myMenu.draw = 1;
					cpct_akp_SFXPlay(1, 15, 36, 0, 40, AY_CHANNEL_A);
		   		}

		   	break;

		   	case MS_CHOSELVL:
				if(cpct_isKeyPressed(Key_1)){
		    		*lvl = 1;
		    		*s = GS_ONMATCH;
					cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
		    	}
		    	else if(cpct_isKeyPressed(Key_2)){
		   			*lvl = 2;
		   			*s = GS_ONMATCH;
					cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
		   		}
		   		else if(cpct_isKeyPressed(Key_3)){
		   			*lvl = 3;
		   			*s = GS_ONMATCH;
					cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
		   		}
		   		else if(cpct_isKeyPressed(Key_4)){
		   			*lvl = 4;
		   			*s = GS_ONMATCH;
					cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
		   		}
		   		else if(cpct_isKeyPressed(Key_5)){
		   			*lvl = 5;
		   			*s = GS_ONMATCH;
					cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
		   		}
		   		else if(cpct_isKeyPressed(Key_Esc)){
		   			myMenu.draw = 1;
		   			*p1 = 0;
		   			*p2 = 0;
		   			myMenu.screen = MS_TWOPLAYER;
					cpct_akp_SFXPlay(1, 15, 36, 0, 40, AY_CHANNEL_A);
		   		}

		   	break;

		    case MS_INSTRUCTIONS:
		    case MS_CREDITS:
		   		if(cpct_isKeyPressed(Key_Esc)){
		   			cpct_setVideoMode(0);

		   			myMenu.screen = MS_MAIN;
		   			myMenu.draw = 1;
					cpct_akp_SFXPlay(1, 15, 36, 0, 40, AY_CHANNEL_A);
		   		}

		    break;

		}
	
	}
}

void drawMenu(){
	if(myMenu.draw){
		switch(myMenu.screen) {

		   	case MS_MAIN:
		   		cpct_clearScreen(cpct_px2byteM0 (1,1));
		    	drawMainScreen();

		    break;

		    case MS_TWOPLAYER:
		   		cpct_clearScreen(cpct_px2byteM0 (1,1));
		    	drawPlayerSelection();

		    break;

		    case MS_CHOSELVL:
		   		cpct_clearScreen(cpct_px2byteM0 (1,1));
		    	drawChoseLvlScreen();

		    break;

		    case MS_INSTRUCTIONS:
		   		cpct_clearScreen(0);
		    	drawInstructionsScreen();

		    break;

		    case MS_CREDITS:
		   		cpct_clearScreen(0);
		    	drawCreditsScreen();

		    break;

		}
		myMenu.draw = 0;
	}	
}


void drawMainScreen(){

	cpct_drawSprite (g_fondo_0, CPCT_VMEM_START, G_FONDO_0_W, G_FONDO_0_H);
	cpct_drawSprite (g_fondo_1, cpctm_screenPtr(CPCT_VMEM_START, G_FONDO_0_W, 0), G_FONDO_1_W, G_FONDO_1_H);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 29, 128);
	cpct_drawStringM0("1 Jugar", myMenu.pvmem, 15, 1);
	
	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 21, 146);
	cpct_drawStringM0("2 Controles", myMenu.pvmem, 15, 1);
	
	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 22, 164);
	cpct_drawStringM0("3 Creditos", myMenu.pvmem, 15, 1);
	
	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 29, 182);
	cpct_drawStringM0("4 Salir", myMenu.pvmem, 15, 1);
}


void drawPlayerSelection(){
	cpct_drawSprite (g_fondo_0, CPCT_VMEM_START, G_FONDO_0_W, G_FONDO_0_H);
	cpct_drawSprite (g_fondo_1, cpctm_screenPtr(CPCT_VMEM_START, G_FONDO_0_W, 0), G_FONDO_1_W, G_FONDO_1_H);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 12, 110);
	cpct_drawStringM0("Elige partido:", myMenu.pvmem, 6, 1);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 8, 134);
	cpct_drawStringM0("1    2    3    4", myMenu.pvmem, 15, 1);

	cpct_drawSprite (g_pp_0, cpctm_screenPtr(CPCT_VMEM_START, 0, 144), 20, 20);
	cpct_drawSprite (g_pp_1, cpctm_screenPtr(CPCT_VMEM_START, 0, 144 + 20), 20, 20);

	cpct_drawSprite (g_ciudadanos_0, cpctm_screenPtr(CPCT_VMEM_START, 20, 144), 20, 20);
	cpct_drawSprite (g_ciudadanos_1, cpctm_screenPtr(CPCT_VMEM_START, 20, 144 + G_PP_0_H), 20, 20);

	cpct_drawSprite (g_psoe_0, cpctm_screenPtr(CPCT_VMEM_START, 40, 144), 20, 20);
	cpct_drawSprite (g_psoe_1, cpctm_screenPtr(CPCT_VMEM_START, 40, 144 + 20), 20, 20);

	cpct_drawSprite (g_podemos_0, cpctm_screenPtr(CPCT_VMEM_START, 60, 144), 20, 20);
	cpct_drawSprite (g_podemos_1, cpctm_screenPtr(CPCT_VMEM_START, 60, 144 + 20), 20, 20);
}

void drawChoseLvlScreen(){
	cpct_drawSprite (g_fondo_0, CPCT_VMEM_START, G_FONDO_0_W, G_FONDO_0_H);
	cpct_drawSprite (g_fondo_1, cpctm_screenPtr(CPCT_VMEM_START, G_FONDO_0_W, 0), G_FONDO_1_W, G_FONDO_1_H);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 4, 110);
	cpct_drawStringM0("Elige un escenario:", myMenu.pvmem, 6, 1);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 12, 130);
	cpct_drawStringM0("1 Sede PP", myMenu.pvmem, 15, 1);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 12, 144);
	cpct_drawStringM0("2 Sede Ciudadanos", myMenu.pvmem, 15, 1);
	
	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 12, 158);
	cpct_drawStringM0("3 Sede PSOE", myMenu.pvmem, 15, 1);
	
	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 12, 172);
	cpct_drawStringM0("4 Sede Podemos", myMenu.pvmem, 15, 1);
	
	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 12, 186);
	cpct_drawStringM0("5 Cuatro Sedes", myMenu.pvmem, 15, 1);
	

	

}

void drawInstructionsScreen(){
	cpct_setVideoMode(2);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 0);
	cpct_drawStringM2("********************* Pulsa [Esc] para volver al Menu **************************", myMenu.pvmem, 1);
	
	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 8*2);
	cpct_drawStringM2("********************************************************************************", myMenu.pvmem, 1);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 16*2);
	cpct_drawStringM2("************** Jugador-1 **************************** Jugador-2 ****************", myMenu.pvmem, 1);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 24*2);
	cpct_drawStringM2("** Tecla A: Mov. a la izquierda   ** Cursor Izquierda: Mov. a la izquierda    **", myMenu.pvmem, 1);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 32*2);
	cpct_drawStringM2("** Tecla D: Mov. a la derecha     ** Cursor Derecha: Mov. a la derecha        **", myMenu.pvmem, 1);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 40*2);
	cpct_drawStringM2("** Tecla W: Mov. a arriba         ** Cursor Arriba: Mov. a arriba             **", myMenu.pvmem, 1);
	
	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 48*2);
	cpct_drawStringM2("** Tecla S: Mov. a abajo          ** Cursor Abajo: Mov. a abajo               **", myMenu.pvmem, 1);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 88*2);
	cpct_drawStringM2("********************************************************************************", myMenu.pvmem, 1);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 96*2);
	cpct_drawStringM2("********************* Pulsa [Esc] para volver al Menu **************************", myMenu.pvmem, 1);


}

void drawCreditsScreen(){
	cpct_setVideoMode(2);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 0);
	cpct_drawStringM2("********************* Pulsa [Esc] para volver al Menu **************************", myMenu.pvmem, 1);
	
	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 8*2);
	cpct_drawStringM2("********************************************************************************", myMenu.pvmem, 1);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 16*2);
	cpct_drawStringM2("* Realizado por Ruben Rodriguez Pardo (@iRuBi_Rp).", myMenu.pvmem, 1);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 24*2);
	cpct_drawStringM2("* Realizado por Miguel Angel Garcia Honrubia (@Almiso9).", myMenu.pvmem, 1);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 32*2);
	cpct_drawStringM2("* Licencia: GNU GPL.", myMenu.pvmem, 1);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 40*2);
	cpct_drawStringM2("* Se ha usado la tecnologia CPCtelera, de Fran Gallego (@FranGallegoBR).", myMenu.pvmem, 1);
	

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 88*2);
	cpct_drawStringM2("********************************************************************************", myMenu.pvmem, 1);

	myMenu.pvmem = cpctm_screenPtr(CPCT_VMEM_START, 0, 96*2);
	cpct_drawStringM2("********************* Pulsa [Esc] para volver al Menu **************************", myMenu.pvmem, 1);
}


