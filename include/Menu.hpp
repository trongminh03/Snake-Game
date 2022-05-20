#pragma once 
#include "Game.hpp" 
#include "GameText.hpp" 
#include "Score.hpp"

class Menu: public GameText {
private:
	SDL_Rect pos_menu[MENU_ITEM];
	SDL_Rect src_menu[MENU_ITEM]; 
	bool selected[MENU_ITEM] = {0, 0, 0, 0}; 
	SDL_Texture* menu; 
	SDL_Texture* play; 
	SDL_Texture* exit; 
	SDL_Texture* infor;  
	SDL_Texture* credits; 
	//MENU: 0: play game, 1: exit, 2: info, 3: credits; 


	SDL_Rect pos_opt[NUM_PLAYER];  
	SDL_Rect src_opt[NUM_PLAYER]; 
	bool selected_opt[NUM_PLAYER] ={0, 0, 0};
	SDL_Texture* mode[NUM_PLAYER]; 
	SDL_Texture* option;  
	//OPTION: 0: exit, 1: player1, 2: player2;  

	SDL_Rect pos_end[MENU_ITEM]; 
	SDL_Rect src_end[MENU_ITEM];  
	bool selected_end[MENU_ITEM] = {0, 0, 0}; 
	SDL_Texture* end; 
	SDL_Texture* exitButton; 
	SDL_Texture* playAgain; 
	SDL_Texture* backButton; 
	//END: 0: play gain, 1: exit, 2: back

	Score game_score; 
	int xm = 0, ym = 0; 
	SDL_Event m_event;

	TTF_Font* font = NULL;
	TTF_Font* font2 = NULL; 
public: 
	Menu();  
	~Menu(); 

	void Setup(); 
	bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);  
	int showMenu();
	int getNumPlayer();
	int endMenu(const char* path); 
	int endMenu(const char* path, const int& score); 
	void FreeTexture(); 
}; 