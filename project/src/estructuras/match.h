
#ifndef _MATCH_H_
#define _MATCH_H_

#include "../game.h"
	
	typedef enum{
		TT_WALL = 0,
		TT_FLOOR,

	}T_TileType;
	
	typedef enum{
		CT_RAJOY = 2,
		CT_ALBERT,
		CT_SUSANA,
		CT_PABLO,
		CT_POLICE,
		CT_FAN,
		CT_BANKER,

	}T_CharacterType;

	typedef enum{
		OT_JACKET = 9,
		OT_AMNESTY,
		OT_CLOCKPLUS,
		OT_CLOCKLESS,
		OT_SNEAKERS,
		OT_NONE,

	}T_ObjectType;

	typedef enum{
		PT_NPC = 0,
		PT_P1,
		PT_P2,
		
		PT_NUMPLAYERS

	}T_PlayerType;

	typedef struct{
		T_ObjectType type;
		u8 tile_x;
	   	u8 tile_y;
	   	u8 lcolTile;
	    u8 *pscreen;

	    u8 timeOnScreen;
	    u8 *lsprite; 
	   	u8 *sprite;

	   	u8 draw;

	}T_Object;

	
	typedef enum{
		ST_NORMAL = 6,
		ST_MAX = 2,

	}T_SpeedType;

	typedef struct {
		T_PlayerType ptype;
		T_CharacterType ctype; 

	   	u8 tile_x;
	   	u8 ltile_x;
	   	u8 tile_y;  
	    u8 ltile_y;
	    u8 *pscreen;
	   	u8 *lpscreen;

	   	u8 step;
	   	T_SpeedType speed;

	   	u8 *sprite;
	   	
	   	u8 draw; 

	}T_Entity;

	typedef enum{
		DT_RIGHT = 0,
		DT_LEFT,
		DT_UP,
		DT_DOWN,

	}T_DirectionType;

	typedef struct{
		T_Entity entity;
		T_DirectionType direction;

	}T_NPC;


	typedef struct{
		T_Entity entity;

	   	T_ObjectType otype;
	   	u8 objectDuration;

	   	u8 *banner;
	   	u8 colour;

	   	u8 stopDuration;

	    u16 numPancartas;

	}T_Character;


	typedef enum{
		MAS_INIT = 0,
		MAS_DRAWINGLEVEL,
		MAS_COUNTDOWN,
		MAS_PLAYING,
		MAS_END,
		MAS_RETURNINGMENU,

		MAS_NUMSTATUS

	}T_MatchStatus;

	typedef struct{
		u16 time;
		u8 currentIt;
		u8* pvmem;
		u8 str[4];
		u16 cuad1;
		u16 cuad2;
		u8 countDown;
		u8 draw;

	}T_HUD;

	typedef struct{
		T_MatchStatus status;
		u8* level;
		T_HUD hud;

	}T_Match;

	void updateMatch(T_Game* game);
	void drawMatch();

#endif