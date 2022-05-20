#pragma once 
#include "Game.hpp" 
#include "GameText.hpp" 
#include <time.h>

using namespace std; 

class Timer: public GameText {
private: 
	GameText time_text; 
	string val_str_time; 
	TTF_Font* font = NULL; 
	SDL_Rect dst_timer;  
	Uint32 time_val; 
public: 
	Timer(); 
	~Timer(); 

	void Setup(); 
	void Update(); 
	void Render(); 
	Uint32 getTimeVal(); 
	void Free(); 
}; 