#include <stdio.h>

#include <cpctelera.h>

#include "match.h"
#include "../tiles/tiles.h"

#include "../niveles/pp.h"
#include "../niveles/ciudadanos.h"
#include "../niveles/psoe.h"
#include "../niveles/podemos.h"
#include "../niveles/sedes.h"

#include "../characters/rajoy.h"
#include "../characters/albert.h"
#include "../characters/susana.h"
#include "../characters/pablo.h"
#include "../characters/policia.h"
#include "../characters/fan.h"
#include "../characters/banquero.h"

#include "../sprites/pp.h"
#include "../sprites/ciudadanos.h"
#include "../sprites/psoe.h"
#include "../sprites/podemos.h"
#include "../sprites/hud.h"
#include "../sprites/uno.h"
#include "../sprites/dos.h"
#include "../sprites/tres.h"

#include "../objects/objetos.h"

#include "../debug.h"
#include "../musica/musica.h"



#define G_TILE_SIZE_W 4
#define G_TILE_SIZE_H 8

#define G_LOGO_SIZE 20

#define G_LEVEL_TILES 20

void initMatch(T_Game* game);
void initCharacter(T_Game* game, T_Character* cha);
void initNPC(T_NPC* npc);
void initObject();

void updateNPC(T_NPC* npc);
void updateCharacter(T_Character* cha);

void updateHUDSets();
void updateObjectSets();
void updateNPCsSets();
void updateCharacterSets();

void updateCountDown();
void updateSetsPerSecond();

void moveRight(T_Entity* ent);
void moveLeft(T_Entity* ent);
void moveDown(T_Entity* ent);
void moveUp(T_Entity* ent);

void manageObjectColision(T_ObjectType o_type, T_Character* cha); 
void manageNPCColision(T_CharacterType c_type, T_Character* cha);
u16 changeBanners(u8 c_type);
void quitBanners(u8 c_type);

void drawLevel();
void drawHUD();
void drawCountDown();
void drawHUDsets();
void drawCharacter(T_Character* cha);
void drawNPC(T_NPC* npc);
void drawObject();

void drawEnd();

cpctm_createTransparentMaskTable(g_tablaTrans, 0x0100, M0, 0);


T_Match myMatch;
T_Character myCharacter_1;
T_Character myCharacter_2;

T_NPC policeNPC_1;
T_NPC policeNPC_2;

T_NPC fanNPC_1;
T_NPC fanNPC_2;
T_NPC fanNPC_3;

T_Object myObject;

u8 colMap[20*20];



void initMatch(T_Game* game){

	if(!game->seed){
		game->seed++;
	}
	cpct_srand(game->seed);


	if(game->op_lvl == 1){
		myMatch.level = g_nivel_pp;
	}
	else if(game->op_lvl == 2){
		myMatch.level = g_nivel_ciudadanos;
	}
	else if(game->op_lvl == 3){
		myMatch.level = g_nivel_psoe;
	}
	else if(game->op_lvl == 4){
		myMatch.level = g_nivel_podemos;
	}
	else{
		myMatch.level = g_nivel_sedes;
	}

	myMatch.hud.time = 120;
	myMatch.hud.currentIt = 0;
	myMatch.hud.pvmem = CPCT_VMEM_START;
	myMatch.hud.cuad1 = 0;
	myMatch.hud.cuad2 = 0;
	myMatch.hud.countDown = 4;
	myMatch.hud.draw = 1;
	myMatch.status = MAS_DRAWINGLEVEL;

	myCharacter_1.entity.ptype = PT_P1;
	myCharacter_2.entity.ptype = PT_P2;

	policeNPC_1.entity.ctype = CT_POLICE;
	policeNPC_2.entity.ctype = CT_POLICE;
	fanNPC_1.entity.ctype = CT_FAN;
	fanNPC_2.entity.ctype = CT_FAN;
	fanNPC_3.entity.ctype = CT_FAN;


}

void initCharacter(T_Game* game, T_Character* cha){

	if(cha->entity.ptype == PT_P1){
		cha->entity.tile_x = 0;
		cha->entity.tile_y = 10;
		cha->entity.pscreen = (u8*)0xC320;
		cha->entity.step = ST_NORMAL;
		cha->entity.speed = ST_NORMAL;
		cha->otype = OT_NONE;
		cha->objectDuration = 0;
		cha->stopDuration = 0;

		if(game->op_p1 == 1){
			cha->entity.ctype = CT_RAJOY;
			cha->entity.sprite = g_rajoy_0;
			cha->banner = g_objetos_0;
			cha->colour = 6;
		}
		else if(game->op_p1 == 2){
			cha->entity.ctype = CT_ALBERT;
			cha->entity.sprite = g_albert_0;
			cha->banner = g_objetos_1;
			cha->colour = 9;
		}
		else if(game->op_p1 == 3){
			cha->entity.ctype = CT_SUSANA;
			cha->entity.sprite = g_susana_0;
			cha->banner = g_objetos_2;
			cha->colour = 2;
		}
		else{
			cha->entity.ctype = CT_PABLO;
			cha->entity.sprite = g_pablo_0;
			cha->banner = g_objetos_3;
			cha->colour = 3;
		}
	}
	else{
		cha->entity.tile_x = 19;
		cha->entity.tile_y = 10;
		cha->entity.pscreen = (u8*)0xC36C;
		cha->entity.step = ST_NORMAL;
		cha->entity.speed = ST_NORMAL;
		cha->otype = OT_NONE;
		cha->objectDuration = 0;
		cha->stopDuration = 0;

		if(game->op_p2 == 1){
			cha->entity.ctype = CT_RAJOY;
			cha->entity.sprite = g_rajoy_1;
			cha->banner = g_objetos_0;
			cha->colour = 6;
		}
		else if(game->op_p2 == 2){
			cha->entity.ctype = CT_ALBERT;
			cha->entity.sprite = g_albert_1;
			cha->banner = g_objetos_1;
			cha->colour = 9;	
		}
		else if(game->op_p2 == 3){
			cha->entity.ctype = CT_SUSANA;
			cha->entity.sprite = g_susana_1;
			cha->banner = g_objetos_2;
			cha->colour = 2;
		}
		else{
			cha->entity.ctype = CT_PABLO;
			cha->entity.sprite = g_pablo_1;
			cha->banner = g_objetos_3;
			cha->colour = 3;	
		}
	}

	cha->numPancartas = 0;

	cha->entity.draw = 1;
}

void initNPC(T_NPC* npc){
	u16 cont = 0;
   	npc->entity.ptype = PT_NPC;

   	if(npc->entity.ctype == CT_POLICE){

   		do{
			npc->entity.tile_y = (cpct_rand()%20);
		}

		while(npc->entity.tile_y == 9);
   		
   		npc->entity.tile_x = (cpct_rand()%20);
		while(!colMap[(npc->entity.tile_x)+(npc->entity.tile_y*20)]){
			if(npc->entity.tile_x == 19){
				npc->entity.tile_x = 0;
			}
			else{
				npc->entity.tile_x++;
			}

		}


		npc->entity.ltile_x = npc->entity.tile_x;
	   	npc->entity.ltile_y = npc->entity.tile_y;

	   	npc->entity.pscreen = cpct_getScreenPtr(CPCT_VMEM_START, npc->entity.tile_x*4, npc->entity.tile_y*8);
	   	npc->entity.lpscreen = 	npc->entity.pscreen;

	   	npc->entity.sprite = g_policia_0;
	   	npc->direction = cpct_rand()%4;
   	}
   	else if(npc->entity.ctype == CT_FAN){

   		do{
			npc->entity.tile_y = (cpct_rand()%20);
		}

		while(npc->entity.tile_y == 9);

		npc->entity.tile_x = (cpct_rand()%20);
		while(!colMap[(npc->entity.tile_x)+(npc->entity.tile_y*20)]){
			if(npc->entity.tile_x == 19){
				npc->entity.tile_x = 0;
			}
			else{
				npc->entity.tile_x++;
			}

		}

		

	   	npc->entity.ltile_x = npc->entity.tile_x;
	   	npc->entity.ltile_y = npc->entity.tile_y;

	   	npc->entity.pscreen = cpct_getScreenPtr(CPCT_VMEM_START, npc->entity.tile_x*4, npc->entity.tile_y*8);
	   	npc->entity.lpscreen = 	npc->entity.pscreen;

	   	npc->entity.sprite = g_fan_0;
	   	npc->direction = cpct_rand()%4;
   	}
   	else{

   	}
   	
   	npc->entity.step = ST_NORMAL;
	npc->entity.speed = ST_NORMAL;
	
	npc->entity.draw = 1;

}

void initObject(){
	myObject.type = OT_CLOCKPLUS;
	myObject.tile_x = 0;
	myObject.tile_y = 0;  
	myObject.lcolTile = 0;
	myObject.pscreen = CPCT_VMEM_START;
	myObject.timeOnScreen = 0;
	myObject.lsprite = NULL;
	myObject.sprite = NULL;
	myObject.draw = 0;

}



void updateMatch(T_Game* game){

	switch(myMatch.status){
			case MAS_INIT:
		    	initMatch(game);
		    	initCharacter(game, &myCharacter_1);
		    	initCharacter(game, &myCharacter_2);
		    	initObject();

		    break; 

		    case MAS_COUNTDOWN:
		    	updateCountDown();

		    break; 

		   	case MAS_PLAYING:	
		    	updateCharacter(&myCharacter_1);
		    	updateCharacter(&myCharacter_2);

		    	updateNPC(&policeNPC_1);
		    	updateNPC(&policeNPC_2);
		    	updateNPC(&fanNPC_1);	
		    	updateNPC(&fanNPC_2);
		    	updateNPC(&fanNPC_3);

		    	updateSetsPerSecond();

		    break;

			
		    case MAS_RETURNINGMENU:	
		    	game->status = GS_BACK4MATCH;
				myMatch.status = MAS_INIT;
				
		    break;

		   
	}
}

void drawMatch(){
	u16 cont = 0;
	switch(myMatch.status) {

		   	case MAS_DRAWINGLEVEL:
		   		cpct_clearScreen(0);
				
				while(cont < G_LEVEL_TILES * G_LEVEL_TILES){
					colMap[cont]=0;
					cont++;
				}
		    	drawLevel();

		    	initNPC(&policeNPC_1);
		    	initNPC(&policeNPC_2);
		    	initNPC(&fanNPC_1);
		    	initNPC(&fanNPC_2);
		    	initNPC(&fanNPC_3);

		    	drawHUD();

		    	drawCharacter(&myCharacter_1);
				drawCharacter(&myCharacter_2);

				drawNPC(&policeNPC_1);
				drawNPC(&policeNPC_2);
		    	drawNPC(&fanNPC_1);
		    	drawNPC(&fanNPC_2);
		    	drawNPC(&fanNPC_3);

		    	drawHUDsets();

  	 			myMatch.status = MAS_COUNTDOWN;

		    break;

		    case MAS_COUNTDOWN:
		   		drawCountDown();

		    break;

		    case MAS_PLAYING:
				drawCharacter(&myCharacter_1);
				drawCharacter(&myCharacter_2);

				drawNPC(&policeNPC_1);
				drawNPC(&policeNPC_2);
		    	drawNPC(&fanNPC_1);
		    	drawNPC(&fanNPC_2);
		    	drawNPC(&fanNPC_3);

				drawObject();

				drawHUDsets();

		    break;

		    case MAS_END:	
		    	drawEnd();
		    	//game->status = GS_BACK4MATCH;
		    break;
	}
}



void updateHUDSets(){
	myMatch.hud.time--;
	myMatch.hud.currentIt = 0;

	if(myCharacter_1.numPancartas + myCharacter_2.numPancartas != 0){
		myMatch.hud.cuad1 = (myCharacter_1.numPancartas*36)/(myCharacter_1.numPancartas + myCharacter_2.numPancartas);
		myMatch.hud.cuad2 = (myCharacter_2.numPancartas*36)/(myCharacter_1.numPancartas + myCharacter_2.numPancartas);
	
	}

	if(!myMatch.hud.time){
		myMatch.status = MAS_END;
	}
}

void updateObjectSets(){
	if(!myObject.timeOnScreen){

		// PROBABILIDAD DE QUE APAREZCA EL OBJETO
		if(cpct_rand()%5 == 0){
			myObject.tile_x = (cpct_rand()%20);
			myObject.tile_y = (cpct_rand()%20);

			while(!colMap[(myObject.tile_x)+(myObject.tile_y*20)]){
				if(myObject.tile_y == 19){
					myObject.tile_y = 0;
				}
				else{
					myObject.tile_y++;
				}

			}
			myObject.lcolTile = colMap[(myObject.tile_x)+(myObject.tile_y*20)];
			myObject.lsprite = g_tileset[myMatch.level[(myObject.tile_x)+(myObject.tile_y*20)]];
			myObject.timeOnScreen = 5;
			myObject.draw = 1;

			//QUE OBJETO APARECE ??
			switch(cpct_rand()%5){
				case 0:
					myObject.type = OT_JACKET;
					myObject.sprite = g_objetos_4;
					colMap[(myObject.tile_x)+(myObject.tile_y*20)] = 9;
				break;

				case 1:
					myObject.type = OT_AMNESTY;
					myObject.sprite = g_objetos_5;
					colMap[(myObject.tile_x)+(myObject.tile_y*20)] = 8;
				break;


				case 2:
					myObject.type = OT_CLOCKPLUS;
					myObject.sprite = g_objetos_6;
					colMap[(myObject.tile_x)+(myObject.tile_y*20)] = 6;
				break;

				case 3:
					myObject.type = OT_CLOCKLESS;
					myObject.sprite = g_objetos_7;
					colMap[(myObject.tile_x)+(myObject.tile_y*20)] = 7;
				break;

				case 4:
					myObject.type = OT_SNEAKERS;
					myObject.sprite = g_objetos_8;
					colMap[(myObject.tile_x)+(myObject.tile_y*20)] = 10;
				break;
				
			}

			myObject.pscreen = cpct_getScreenPtr(CPCT_VMEM_START, myObject.tile_x*4, myObject.tile_y*8);

		}
	}
	//si el objeto permance en pantalla
	else{
		myObject.timeOnScreen--;
		
		//si justo se acaba el tiempo de objeto en pantalla
		if(!myObject.timeOnScreen){
			colMap[(myObject.tile_x)+(myObject.tile_y*20)] = myObject.lcolTile;
			
			cpct_drawTileAligned4x8(myObject.lsprite, myObject.pscreen);

			//Si el objeto había caído sobre una pancarta
			if(myObject.lcolTile > TT_FLOOR){
				if(myObject.lcolTile == CT_RAJOY){
					cpct_drawSpriteMaskedAlignedTable(g_objetos_0, myObject.pscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
				}
				else if(myObject.lcolTile == CT_ALBERT){
					cpct_drawSpriteMaskedAlignedTable(g_objetos_1, myObject.pscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
				}
				else if(myObject.lcolTile == CT_SUSANA){
					cpct_drawSpriteMaskedAlignedTable(g_objetos_2, myObject.pscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
				}
				else{
					cpct_drawSpriteMaskedAlignedTable(g_objetos_3, myObject.pscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
				}
			}

			//si cuando se borra el tile donde esta el objeto esta alguno de los personajes
			if(myObject.pscreen == myCharacter_1.entity.pscreen){
				myCharacter_1.entity.draw = 1;
			}	
			else if(myObject.pscreen == myCharacter_2.entity.pscreen){
				myCharacter_2.entity.draw = 1;
			}
		
		}
		
	}

	if(myCharacter_1.objectDuration){
		if(!--myCharacter_1.objectDuration){
			myCharacter_1.entity.speed = ST_NORMAL;
			myCharacter_1.otype = OT_NONE;
		}

	}

	if(myCharacter_2.objectDuration){
		if(!--myCharacter_2.objectDuration){
			myCharacter_2.entity.speed = ST_NORMAL;
			myCharacter_2.otype = OT_NONE;
		}

	}

	
}

void updateNPCsSets(){
	fanNPC_1.direction = cpct_rand()%4;
	fanNPC_2.direction = cpct_rand()%4;
	fanNPC_3.direction = cpct_rand()%4;
	policeNPC_1.direction = cpct_rand()%4;
	policeNPC_2.direction = cpct_rand()%4;
}

void updateCharacterSets(){
	if(myCharacter_1.stopDuration){
		myCharacter_1.stopDuration--;
	}

	if(myCharacter_2.stopDuration){
		myCharacter_2.stopDuration--;
	}
}



void updateSetsPerSecond(){

	if(myMatch.hud.currentIt==50){
		updateHUDSets();
		updateObjectSets();
		updateNPCsSets();
		updateCharacterSets();

		myMatch.hud.draw = 1;
	}
	myMatch.hud.currentIt+=1;

}

void updateCountDown(){
	
	if(myMatch.hud.currentIt==100){
		myMatch.hud.currentIt = 0;
		myMatch.hud.countDown--;

		myMatch.hud.draw = 1;
	}
	myMatch.hud.currentIt+=1;
}


void updateNPC(T_NPC* npc){
	if(npc->entity.step < npc->entity.speed){
		npc->entity.step++;
	}

	
	if(npc->entity.step == npc->entity.speed){

		if(npc->entity.ctype == CT_POLICE){
			switch(npc->direction){
				case DT_RIGHT:
					moveRight(&npc->entity);
				break;

				case DT_LEFT:
					moveLeft(&npc->entity);
				break;

				case DT_UP:
					moveUp(&npc->entity);
				break;

				case DT_DOWN:
					moveDown(&npc->entity);
				break;
			}
		}
		else if(npc->entity.ctype == CT_FAN){
			switch(npc->direction){
				case DT_RIGHT:
					moveRight(&npc->entity);
				break;

				case DT_LEFT:
					moveLeft(&npc->entity);
				break;

				case DT_UP:
					moveUp(&npc->entity);
				break;

				case DT_DOWN:
					moveDown(&npc->entity);
				break;
			}

		}//end of fan

	}//end of step

	//si me he movido
	if(npc->entity.draw){
		npc->entity.step = 0;

		

	}// end of si me he movido


	//si la nueva posición es el personaje 1
	if(npc->entity.pscreen == myCharacter_1.entity.pscreen){
		if(myCharacter_1.otype == OT_AMNESTY){
			//do nothing
		}
		else{
			manageNPCColision(npc->entity.ctype, &myCharacter_1);
		}
	}
	else if(npc->entity.pscreen == myCharacter_2.entity.pscreen){
		if(myCharacter_2.otype == OT_AMNESTY){
			//do nothing
		}
		else{
			manageNPCColision(npc->entity.ctype, &myCharacter_2);
		}
	}

	


}


void updateCharacter(T_Character* cha){

	if(cha->entity.step < cha->entity.speed){
		cha->entity.step++;
	}

	
	if(cha->entity.step == cha->entity.speed && cha->stopDuration == 0){
	
		if(cpct_isAnyKeyPressed()){

			if(cha->entity.ptype == PT_P1){

				if(cpct_isKeyPressed(Key_A)){
					moveLeft(&cha->entity);
				}
				else if(cpct_isKeyPressed(Key_D)){
					moveRight(&cha->entity);
				}
				else if(cpct_isKeyPressed(Key_S)){
					moveDown(&cha->entity);
				}
				else if(cpct_isKeyPressed(Key_W)){
					moveUp(&cha->entity);
				}
			}

			else{
				if(cpct_isKeyPressed(Key_CursorLeft)){
					moveLeft(&cha->entity);
				}
				else if(cpct_isKeyPressed(Key_CursorRight)){
					moveRight(&cha->entity);
				}
				else if(cpct_isKeyPressed(Key_CursorDown)){
					moveDown(&cha->entity);
				}
				else if(cpct_isKeyPressed(Key_CursorUp)){
					moveUp(&cha->entity);
				}
			}

			//si me he movido
			if(cha->entity.draw){
				cha->entity.step = 0;

				//compruebo que en la posicion anterior no haya una pancarta del mismo personaje
				if(colMap[(cha->entity.ltile_x)+(cha->entity.ltile_y*20)] != cha->entity.ctype){
					cha->numPancartas++;
			
					if(colMap[(cha->entity.ltile_x)+(cha->entity.ltile_y*20)] > TT_FLOOR){
						
						//si es una pancarta
						if(colMap[(cha->entity.ltile_x)+(cha->entity.ltile_y*20)] < OT_CLOCKPLUS){
							if(cha->entity.ptype == PT_P1){
								myCharacter_2.numPancartas--;
							}
							else{
								myCharacter_1.numPancartas--;
							}
						}
						
					}
					//la posicion anterior será mi pancarta
					colMap[(cha->entity.ltile_x)+(cha->entity.ltile_y*20)] = cha->entity.ctype;
				}


				//si la nueva posición es un objeto
				if(colMap[(cha->entity.tile_x)+(cha->entity.tile_y*20)] > CT_PABLO){
					manageObjectColision(myObject.type, cha);
				}


			} // end-> if me he movido
		} // end-> key pressed
	}

}



void moveRight(T_Entity* ent){
	if(ent->tile_x < G_LEVEL_TILES - 1){
		if(colMap[(ent->tile_x+1)+(ent->tile_y*20)]){
			//igualo posiciones
			ent->ltile_x = ent->tile_x;
			ent->ltile_y = ent->tile_y;
			ent->lpscreen = ent->pscreen;

			//actualizo posiciones
			ent->tile_x++;
			ent->pscreen = cpct_getScreenPtr(CPCT_VMEM_START, ent->tile_x*4, ent->tile_y*8);

			if(ent->ctype == CT_RAJOY){
				ent->sprite = g_rajoy_0;
			}
			else if(ent->ctype == CT_ALBERT){
				ent->sprite = g_albert_0;
			}
			else if(ent->ctype == CT_SUSANA){
				ent->sprite = g_susana_0;
			}
			else if(ent->ctype == CT_PABLO){
				ent->sprite = g_pablo_0;
			}
			else if(ent->ctype == CT_POLICE){
				ent->sprite = g_policia_0;
			}
			else if(ent->ctype == CT_FAN){
				ent->sprite = g_fan_0;
			}
			else{
				ent->sprite = g_banquero_0;
			}

			ent->draw = 1;
		}
	}
}

void moveLeft(T_Entity* ent){
	if(ent->tile_x > 0){
		if(colMap[(ent->tile_x-1)+(ent->tile_y*20)]){
			//igualo posiciones
			ent->ltile_x = ent->tile_x;
			ent->ltile_y = ent->tile_y;
			ent->lpscreen = ent->pscreen;

			//actualizo posiciones
			ent->tile_x--;
			ent->pscreen = cpct_getScreenPtr(CPCT_VMEM_START, ent->tile_x*4, ent->tile_y*8);

			if(ent->ctype == CT_RAJOY){
				ent->sprite = g_rajoy_1;
			}
			else if(ent->ctype == CT_ALBERT){
				ent->sprite = g_albert_1;
			}
			else if(ent->ctype == CT_SUSANA){
				ent->sprite = g_susana_1;
			}
			else if(ent->ctype == CT_PABLO){
				ent->sprite = g_pablo_1;
			}
			else if(ent->ctype == CT_POLICE){
				ent->sprite = g_policia_1;
			}
			else if(ent->ctype == CT_FAN){
				ent->sprite = g_fan_1;
			}
			else{
				ent->sprite = g_banquero_1;
			}

			ent->draw = 1;
		}
	}
}

void moveDown(T_Entity* ent){
	if(ent->tile_y < G_LEVEL_TILES - 1){
		if(colMap[(ent->tile_x)+((ent->tile_y+1)*20)]){
			//igualo posiciones
			ent->ltile_x = ent->tile_x;
			ent->ltile_y = ent->tile_y;
			ent->lpscreen = ent->pscreen;

			//actualizo posiciones
			ent->tile_y++;
			ent->pscreen = cpct_getScreenPtr(CPCT_VMEM_START, ent->tile_x*4, ent->tile_y*8);

			if(ent->ctype == CT_RAJOY){
				ent->sprite = g_rajoy_2;
			}
			else if(ent->ctype == CT_ALBERT){
				ent->sprite = g_albert_2;
			}
			else if(ent->ctype == CT_SUSANA){
				ent->sprite = g_susana_2;
			}
			else if(ent->ctype == CT_PABLO){
				ent->sprite = g_pablo_2;
			}
			else if(ent->ctype == CT_POLICE){
				ent->sprite = g_policia_2;
			}
			else if(ent->ctype == CT_FAN){
				ent->sprite = g_fan_2;
			}
			else{
				ent->sprite = g_banquero_2;
			}

			ent->draw = 1;
		}
	}
}

void moveUp(T_Entity* ent){
	if(ent->tile_y > 0){
		if(colMap[(ent->tile_x)+((ent->tile_y-1)*20)]){
			//igualo posiciones
			ent->ltile_x = ent->tile_x;
			ent->ltile_y = ent->tile_y;
			ent->lpscreen = ent->pscreen;

			//actualizo posiciones
			ent->tile_y--;
			ent->pscreen = cpct_getScreenPtr(CPCT_VMEM_START, ent->tile_x*4, ent->tile_y*8);

			if(ent->ctype == CT_RAJOY){
				ent->sprite = g_rajoy_3;
			}
			else if(ent->ctype == CT_ALBERT){
				ent->sprite = g_albert_3;
			}
			else if(ent->ctype == CT_SUSANA){
				ent->sprite = g_susana_3;
			}
			else if(ent->ctype == CT_PABLO){
				ent->sprite = g_pablo_3;
			}
			else if(ent->ctype == CT_POLICE){
				ent->sprite = g_policia_3;
			}
			else if(ent->ctype == CT_FAN){
				ent->sprite = g_fan_3;
			}
			else{
				ent->sprite = g_banquero_3;
			}

			ent->draw = 1;
		}
	}
}




void manageObjectColision(T_ObjectType o_type, T_Character* cha){
	
	colMap[(myObject.tile_x)+(myObject.tile_y*20)] = cha->entity.ctype;
	myObject.lcolTile = cha->entity.ctype;

	switch(o_type){
		case OT_JACKET:
			cha->numPancartas += changeBanners(cha->entity.ctype);

			if(cha->entity.ptype == PT_P1){
				myCharacter_2.numPancartas = 0;
			}
			else{
				myCharacter_1.numPancartas = 0;
			}
			cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
		break;

		case OT_AMNESTY:
			cha->objectDuration = 7;
			cha->otype = OT_AMNESTY;
			cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
		break;

		case OT_CLOCKPLUS:
			myMatch.hud.time += 10;
			cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
		break;

		case OT_CLOCKLESS:
			myMatch.hud.time -= 10;
			cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
		break;


		case OT_SNEAKERS:
			cha->objectDuration = 7;
			cha->otype = OT_SNEAKERS;
			cha->entity.speed = ST_MAX;
			cpct_akp_SFXPlay(1, 15, 60, 0, 40, AY_CHANNEL_A);
		break;


	}
}

void manageNPCColision(T_CharacterType c_type, T_Character* cha){
	switch(c_type){
		case CT_POLICE:
			cha->objectDuration = 5;
			cha->otype = OT_AMNESTY;

			quitBanners(cha->entity.ctype);
			cha->numPancartas = 0;
			
		break;

		case CT_FAN:
			cha->objectDuration = 5;
			cha->otype = OT_AMNESTY;

			cha->stopDuration = 5;
			
		break;

		case CT_BANKER:
			
		break;

		


	}
}

u16 changeBanners(u8 c_type){
	u16 cont = 0;
	u8 col = 0;
	u8 fila = 0;
	u8* banner = NULL;
	u16 aux = 0;

	if(c_type == CT_RAJOY){
		banner = g_objetos_0;
	}
	else if(c_type == CT_ALBERT){
		banner = g_objetos_1;
	}
	else if(c_type == CT_SUSANA){
		banner = g_objetos_2;
	}
	else{
		banner = g_objetos_3;
	}


	while(cont < G_LEVEL_TILES * G_LEVEL_TILES){	
		
		if(colMap[cont] != c_type && colMap[cont] > TT_FLOOR && colMap[cont] < OT_JACKET){
			colMap[cont] = c_type;
			cpct_drawSpriteMaskedAlignedTable(banner, cpct_getScreenPtr(CPCT_VMEM_START, col, fila),  G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
			aux++;
		}
		col+=4;
		
		if(col == 80){
			fila+=8;
			col=0;
		}
		cont++;
	}
	return aux;
}

void quitBanners(u8 c_type){
	u16 cont = 0;
	u8 col = 0;
	u8 fila = 0;

	while(cont < G_LEVEL_TILES * G_LEVEL_TILES){	
		
		if(colMap[cont] == c_type){
			colMap[cont] = TT_FLOOR;
			cpct_drawTileAligned4x8(g_tileset[myMatch.level[cont]], cpct_getScreenPtr(CPCT_VMEM_START, col, fila));
		}
		col+=4;
		
		if(col == 80){
			fila+=8;
			col=0;
		}
		cont++;
	}

}

void drawLevel(){
	u16 cont = 0;
	u8 col = 0;
	u8 fila = 0;

	while(cont < G_LEVEL_TILES * G_LEVEL_TILES){
		
		cpct_drawTileAligned4x8(g_tileset[myMatch.level[cont]], cpct_getScreenPtr(CPCT_VMEM_START, col, fila));
		
		//init colMap
		if(myMatch.level[cont] < 21){
			colMap[cont] = TT_FLOOR;
		}
		//end init colMap

		col+=4;
		
		if(col == 80){
			fila+=8;
			col=0;
		}
		cont++;
	}
}

void drawHUD(){
	u8 cont = 0;
	u8 col = 5*4;
	u8 fila = 20*8;

	if(myCharacter_1.entity.ctype == CT_RAJOY){
		cpct_drawSprite (g_pp_0, cpctm_screenPtr(CPCT_VMEM_START, 0, 160), G_LOGO_SIZE, G_LOGO_SIZE);
		cpct_drawSprite (g_pp_1, cpctm_screenPtr(CPCT_VMEM_START, 0, 160 + G_LOGO_SIZE), G_LOGO_SIZE, G_LOGO_SIZE);
	}
	else if(myCharacter_1.entity.ctype == CT_ALBERT){
		cpct_drawSprite (g_ciudadanos_0, cpctm_screenPtr(CPCT_VMEM_START, 0, 160), G_LOGO_SIZE, G_LOGO_SIZE);
		cpct_drawSprite (g_ciudadanos_1, cpctm_screenPtr(CPCT_VMEM_START, 0, 160 + G_LOGO_SIZE), G_LOGO_SIZE, G_LOGO_SIZE);
	}
	else if(myCharacter_1.entity.ctype == CT_SUSANA){
		cpct_drawSprite (g_psoe_0, cpctm_screenPtr(CPCT_VMEM_START, 0, 160), G_LOGO_SIZE, G_LOGO_SIZE);
		cpct_drawSprite (g_psoe_1, cpctm_screenPtr(CPCT_VMEM_START, 0, 160 + G_LOGO_SIZE), G_LOGO_SIZE, G_LOGO_SIZE);
	}
	else{
		cpct_drawSprite (g_podemos_0, cpctm_screenPtr(CPCT_VMEM_START, 0, 160), G_LOGO_SIZE, G_LOGO_SIZE);
		cpct_drawSprite (g_podemos_1, cpctm_screenPtr(CPCT_VMEM_START, 0, 160 + G_LOGO_SIZE), G_LOGO_SIZE, G_LOGO_SIZE);
	}


	if(myCharacter_2.entity.ctype == CT_RAJOY){
		cpct_drawSprite (g_pp_0, cpctm_screenPtr(CPCT_VMEM_START, 60, 160), G_LOGO_SIZE, G_LOGO_SIZE);
		cpct_drawSprite (g_pp_1, cpctm_screenPtr(CPCT_VMEM_START, 60, 160 + G_LOGO_SIZE), G_LOGO_SIZE, G_LOGO_SIZE);
	}
	else if(myCharacter_2.entity.ctype == CT_ALBERT){
		cpct_drawSprite (g_ciudadanos_0, cpctm_screenPtr(CPCT_VMEM_START, 60, 160), G_LOGO_SIZE, G_LOGO_SIZE);
		cpct_drawSprite (g_ciudadanos_1, cpctm_screenPtr(CPCT_VMEM_START, 60, 160 + G_LOGO_SIZE), G_LOGO_SIZE, G_LOGO_SIZE);
	}
	else if(myCharacter_2.entity.ctype == CT_SUSANA){
		cpct_drawSprite (g_psoe_0, cpctm_screenPtr(CPCT_VMEM_START, 60, 160), G_LOGO_SIZE, G_LOGO_SIZE);
		cpct_drawSprite (g_psoe_1, cpctm_screenPtr(CPCT_VMEM_START, 60, 160 + G_LOGO_SIZE), G_LOGO_SIZE, G_LOGO_SIZE);
	}
	else{
		cpct_drawSprite (g_podemos_0, cpctm_screenPtr(CPCT_VMEM_START, 60, 160), G_LOGO_SIZE, G_LOGO_SIZE);
		cpct_drawSprite (g_podemos_1, cpctm_screenPtr(CPCT_VMEM_START, 60, 160 + G_LOGO_SIZE), G_LOGO_SIZE, G_LOGO_SIZE);
	}

	while(cont < g_hud_W * g_hud_H){
	
		cpct_drawTileAligned4x8(g_tileset[g_hud[cont]], cpctm_screenPtr(CPCT_VMEM_START, col, fila));

		col+=4;
		
		if(col == 60){
			fila+=8;
			col=5*4;
		}
		cont++;
	}

}

void drawCountDown(){
	if(myMatch.hud.draw){
		if(myMatch.hud.countDown == 3){
			cpct_drawSpriteMaskedAlignedTable (g_tres, cpctm_screenPtr(CPCT_VMEM_START, 9*4, 10*8), G_DOS_W, G_DOS_H, g_tablaTrans);
			cpct_akp_SFXPlay(1, 15, 36, 0, 40, AY_CHANNEL_A);
		}
		else if(myMatch.hud.countDown == 2){
			cpct_drawTileAligned4x8(g_tileset[myMatch.level[9+(10*20)]], cpctm_screenPtr(CPCT_VMEM_START, 9*4, 10*8));
			cpct_drawTileAligned4x8(g_tileset[myMatch.level[10+(10*20)]], cpctm_screenPtr(CPCT_VMEM_START, 10*4, 10*8));
			cpct_drawTileAligned4x8(g_tileset[myMatch.level[9+(11*20)]], cpctm_screenPtr(CPCT_VMEM_START, 9*4, 11*8));
			cpct_drawTileAligned4x8(g_tileset[myMatch.level[10+(11*20)]], cpctm_screenPtr(CPCT_VMEM_START, 10*4, 11*8));

			cpct_drawSpriteMaskedAlignedTable (g_dos, cpctm_screenPtr(CPCT_VMEM_START, 9*4, 10*8), G_DOS_W, G_DOS_H, g_tablaTrans);
			cpct_akp_SFXPlay(1, 15, 36, 0, 40, AY_CHANNEL_A);
		}
		else if(myMatch.hud.countDown == 1){
			cpct_drawTileAligned4x8(g_tileset[myMatch.level[9+(10*20)]], cpctm_screenPtr(CPCT_VMEM_START, 9*4, 10*8));
			cpct_drawTileAligned4x8(g_tileset[myMatch.level[10+(10*20)]], cpctm_screenPtr(CPCT_VMEM_START, 10*4, 10*8));
			cpct_drawTileAligned4x8(g_tileset[myMatch.level[9+(11*20)]], cpctm_screenPtr(CPCT_VMEM_START, 9*4, 11*8));
			cpct_drawTileAligned4x8(g_tileset[myMatch.level[10+(11*20)]], cpctm_screenPtr(CPCT_VMEM_START, 10*4, 11*8));

			cpct_drawSpriteMaskedAlignedTable (g_uno, cpctm_screenPtr(CPCT_VMEM_START, 9*4, 10*8), G_DOS_W, G_DOS_H, g_tablaTrans);
			cpct_akp_SFXPlay(1, 15, 36, 0, 40, AY_CHANNEL_A);
		}
		else if(myMatch.hud.countDown == 0){
			cpct_drawTileAligned4x8(g_tileset[myMatch.level[9+(10*20)]], cpctm_screenPtr(CPCT_VMEM_START, 9*4, 10*8));
			cpct_drawTileAligned4x8(g_tileset[myMatch.level[10+(10*20)]], cpctm_screenPtr(CPCT_VMEM_START, 10*4, 10*8));
			cpct_drawTileAligned4x8(g_tileset[myMatch.level[9+(11*20)]], cpctm_screenPtr(CPCT_VMEM_START, 9*4, 11*8));
			cpct_drawTileAligned4x8(g_tileset[myMatch.level[10+(11*20)]], cpctm_screenPtr(CPCT_VMEM_START, 10*4, 11*8));

			myMatch.status = MAS_PLAYING;
			cpct_akp_SFXPlay(1, 15, 60, 5, 40, AY_CHANNEL_A);
		}
		myMatch.hud.draw = 0;
	}

}

void drawHUDsets(){
	if(myMatch.hud.draw){
		myMatch.hud.pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 34,  192);
		sprintf(myMatch.hud.str, "%3u", myMatch.hud.time);
		cpct_drawStringM0(myMatch.hud.str, myMatch.hud.pvmem, 15, 1);

		
		if(myCharacter_1.numPancartas < 100){
			myMatch.hud.pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 22,  192);
			sprintf(myMatch.hud.str, "%2u", myCharacter_1.numPancartas);
			cpct_drawStringM0(myMatch.hud.str, myMatch.hud.pvmem, 15, 1);
		}
		else{
			myMatch.hud.pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 22,  192);
			cpct_drawStringM0("++", myMatch.hud.pvmem, 15, 1);
		}
		
		
		if(myCharacter_2.numPancartas < 100){
			myMatch.hud.pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 50,  192);
			sprintf(myMatch.hud.str, "%2u", myCharacter_2.numPancartas);		
			cpct_drawStringM0(myMatch.hud.str, myMatch.hud.pvmem, 15, 1);
		}
		else{
			myMatch.hud.pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 50,  192);		
			cpct_drawStringM0("++", myMatch.hud.pvmem, 15, 1);
		}


		
		if(myCharacter_1.numPancartas != 0  && myMatch.hud.cuad1 != 0){
			myMatch.hud.pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 22,  168);
			cpct_drawSolidBox (myMatch.hud.pvmem, cpct_px2byteM0 (myCharacter_1.colour,myCharacter_1.colour), myMatch.hud.cuad1, 8);	
		}

		if(myCharacter_2.numPancartas != 0 && myMatch.hud.cuad2 != 0){
			myMatch.hud.pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 22 + myMatch.hud.cuad1,  168);
			cpct_drawSolidBox (myMatch.hud.pvmem, cpct_px2byteM0 (myCharacter_2.colour,myCharacter_2.colour), myMatch.hud.cuad2, 8);	

			myMatch.hud.pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 57,  168);
			cpct_drawSolidBox (myMatch.hud.pvmem, cpct_px2byteM0 (myCharacter_2.colour,myCharacter_2.colour), 1, 8);	
		

		}
		



		myMatch.hud.draw = 0;
	}
}

void drawCharacter(T_Character* cha){

	if(cha->entity.draw){
		//Borro rastro
		cpct_drawTileAligned4x8(g_tileset[myMatch.level[(cha->entity.ltile_x)+((cha->entity.ltile_y)*20)]], cha->entity.lpscreen);
		


		//Dibujo sprite
		cpct_drawSpriteMaskedAlignedTable(cha->entity.sprite, cha->entity.pscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
		

		//Dibujo banner
		cpct_drawSpriteMaskedAlignedTable(cha->banner, cha->entity.lpscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);

		cha->entity.draw = 0;
	}

	if(cha->otype == OT_AMNESTY){
		if(myMatch.hud.currentIt % 3){
			cpct_drawSpriteMaskedAlignedTable(cha->entity.sprite, cha->entity.pscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
		}
		else{
			cpct_drawTileAligned4x8(g_tileset[myMatch.level[(cha->entity.tile_x)+((cha->entity.tile_y)*20)]], cha->entity.pscreen);
		}	
	}
	


	
}

void drawNPC(T_NPC* npc){
	if(npc->entity.draw){
		//Borro rastro
		cpct_drawTileAligned4x8(g_tileset[myMatch.level[(npc->entity.ltile_x)+((npc->entity.ltile_y)*20)]], npc->entity.lpscreen);

		//Dibujo sprite
		cpct_drawSpriteMaskedAlignedTable(npc->entity.sprite, npc->entity.pscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);

		
		//Draw banner
		if(colMap[(npc->entity.ltile_x)+(npc->entity.ltile_y*20)] == CT_RAJOY){
			cpct_drawSpriteMaskedAlignedTable(g_objetos_0, npc->entity.lpscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
		}
		else if(colMap[(npc->entity.ltile_x)+(npc->entity.ltile_y*20)] == CT_ALBERT){
			cpct_drawSpriteMaskedAlignedTable(g_objetos_1,npc->entity.lpscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
		}
		else if(colMap[(npc->entity.ltile_x)+(npc->entity.ltile_y*20)] == CT_SUSANA){
			cpct_drawSpriteMaskedAlignedTable(g_objetos_2, npc->entity.lpscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
		}
		else if(colMap[(npc->entity.ltile_x)+(npc->entity.ltile_y*20)] == CT_PABLO){
			cpct_drawSpriteMaskedAlignedTable(g_objetos_3, npc->entity.lpscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
		}
		//Draw object
		else if(colMap[(npc->entity.ltile_x)+(npc->entity.ltile_y*20)] == OT_JACKET){
			cpct_drawSpriteMaskedAlignedTable(g_objetos_4, npc->entity.lpscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
		}
		else if(colMap[(npc->entity.ltile_x)+(npc->entity.ltile_y*20)] == OT_AMNESTY){
			cpct_drawSpriteMaskedAlignedTable(g_objetos_5, npc->entity.lpscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
		}
		else if(colMap[(npc->entity.ltile_x)+(npc->entity.ltile_y*20)] == OT_CLOCKPLUS){
			cpct_drawSpriteMaskedAlignedTable(g_objetos_6, npc->entity.lpscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
		}
		else if(colMap[(npc->entity.ltile_x)+(npc->entity.ltile_y*20)] == OT_CLOCKLESS){
			cpct_drawSpriteMaskedAlignedTable(g_objetos_7, npc->entity.lpscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
		}
		else if(colMap[(npc->entity.ltile_x)+(npc->entity.ltile_y*20)] == OT_SNEAKERS){
			cpct_drawSpriteMaskedAlignedTable(g_objetos_8, npc->entity.lpscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
		}
		

		npc->entity.draw = 0;
	}
}

void drawObject(){
	if(myObject.draw){
		cpct_drawSpriteMaskedAlignedTable(myObject.sprite, myObject.pscreen, G_TILE_SIZE_W, G_TILE_SIZE_H, g_tablaTrans);
		myObject.draw = 0;
	}
}

void drawEnd(){
	u8 x = 5*4;
	u8 y = 5*8;
	u8 incx = 13;
	u8 incy = 20;
	u8 ganador = 0;
	u8 logo = 0;

	if(myCharacter_1.numPancartas > myCharacter_2.numPancartas){
		ganador = 1;
	}
	else if(myCharacter_1.numPancartas < myCharacter_2.numPancartas){
		ganador = 2;
	}



	cpct_drawSolidBox (cpct_getScreenPtr(CPCT_VMEM_START, x, y), cpct_px2byteM0 (1,1), 45, 90);

	if(ganador){
	cpct_drawStringM0("GANADOR",cpct_getScreenPtr(CPCT_VMEM_START, 28, 45), 15, 1);
		if(ganador == 1){
			logo = myCharacter_1.entity.ctype;
		}
		else{
			logo = myCharacter_2.entity.ctype;
		}

		if(logo == CT_RAJOY){
			cpct_drawSprite (g_pp_0, cpctm_screenPtr(CPCT_VMEM_START, x+incx,y+incy), G_LOGO_SIZE, G_LOGO_SIZE);
			cpct_drawSprite (g_pp_1, cpctm_screenPtr(CPCT_VMEM_START, x+incx,y+incy + G_LOGO_SIZE), G_LOGO_SIZE, G_LOGO_SIZE);

		}
		else if(logo == CT_ALBERT){
			cpct_drawSprite (g_ciudadanos_0, cpctm_screenPtr(CPCT_VMEM_START, x+incx,y+incy), G_LOGO_SIZE, G_LOGO_SIZE);
			cpct_drawSprite (g_ciudadanos_1, cpctm_screenPtr(CPCT_VMEM_START, x+incx,y+incy + G_LOGO_SIZE), G_LOGO_SIZE, G_LOGO_SIZE);
		}
		else if(logo == CT_SUSANA){
			cpct_drawSprite (g_psoe_0, cpctm_screenPtr(CPCT_VMEM_START, x+incx,y+incy), G_LOGO_SIZE, G_LOGO_SIZE);
			cpct_drawSprite (g_psoe_1, cpctm_screenPtr(CPCT_VMEM_START, x+incx,y+incy + G_LOGO_SIZE), G_LOGO_SIZE, G_LOGO_SIZE);
		}
		else if(logo == CT_PABLO){
			cpct_drawSprite (g_podemos_0, cpctm_screenPtr(CPCT_VMEM_START, x+incx,y+incy), G_LOGO_SIZE, G_LOGO_SIZE);
			cpct_drawSprite (g_podemos_1, cpctm_screenPtr(CPCT_VMEM_START, x+incx,y+incy + G_LOGO_SIZE), G_LOGO_SIZE, G_LOGO_SIZE);
		}


	}
	else{
		cpct_drawStringM0("EMPATE",cpct_getScreenPtr(CPCT_VMEM_START, 28, 45), 15, 1);
	}

	cpct_drawStringM0("PRES. ESC",cpct_getScreenPtr(CPCT_VMEM_START, 26, 120), 15, 1);


	myMatch.status = MAS_RETURNINGMENU;
}

