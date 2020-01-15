#ifndef _MENU_H_
#define _MENU_H_
	
	#include "../game.h"
	#include "match.h"

	typedef enum{
		MS_MAIN = 0,
		MS_TWOPLAYER,
		MS_CHOSELVL,
		MS_INSTRUCTIONS,
		MS_CREDITS,

		NUMSCREENS

	}T_MenuScreen;

	typedef struct{
		u8* pvmem;
		T_MenuScreen screen;

		u8 draw;

	}T_Menu;

	
	void initMenu();
	void updateMenu(T_Game* game);
	void drawMenu();


#endif