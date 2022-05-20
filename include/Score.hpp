#pragma once 
#include "Game.hpp" 
#include "GameText.hpp"
#include "TextureManager.hpp"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std; 

class Score : public GameText {
private:
	GameText score_text; 
	string val_str_score; 
	TTF_Font* font = NULL;  
	SDL_Rect src, dst; 
public: 
	Score(); 
	~Score(); 
 	
 	void Setup(const GameText::TextColor &color); 
	void Update(const int &score, const string &str); 
	void CreateText();
	void Render(const Vector2D &pos, const Vector2D& size); 
	void Render2(const Vector2D &pos, const Vector2D& size); 
	int getHighestScore(); 
	int UpdateHighestScore(); 
	void Free(); 
	void Record(const int &HighestScore); 
}; 
