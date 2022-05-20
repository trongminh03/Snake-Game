#pragma once 
#include "Game.hpp" 
#include <string>
#include "SDL2/SDL_ttf.h"

class GameText { 
protected: 
	std::string str_val; 
	SDL_Color text_color;
	SDL_Surface* surface_;
	SDL_Texture* texture_; 
public: 
	GameText(); 
	~GameText(); 
	void Init(TTF_Font* font); 
	void SetText(const std::string& text); 
	void SetColor(const int& type); 
	void Render(const SDL_Rect &dstR); 
	void CreateGameText(TTF_Font* font, const SDL_Rect &dstR); 
	void Free(); 

	enum TextColor {
		RED_TEXT = 0, 
		WHITE_TEXT = 1, 
		BLACK_TEXT = 2,  
		GREEN_TEXT = 3,
		PINK_TEXT = 4, 
		LIGHT_YELLOW_TEXT = 5, 
	}; 
}; 