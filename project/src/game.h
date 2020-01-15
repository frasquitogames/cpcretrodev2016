#ifndef _GAME_H_
#define _GAME_H_

	typedef enum {
	   GS_ONMENU = 0,
	   GS_ONMATCH,
	   GS_BACK4MATCH,

	   GS_NUMGAMESTATUS

	} T_GameStatus;

	typedef struct Game{
		u8 is_running;
		u8 op_p1;
		u8 op_p2;
		u8 op_lvl;
		u32 seed;
		T_GameStatus status;
   
	} T_Game;



	//funciones principales del juego
	void init();
	void run();

	void processInput();
	void update();
	void draw();


	//void exit();



#endif