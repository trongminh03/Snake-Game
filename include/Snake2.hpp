#pragma once
#include "Snake.hpp" 
#include "Timer.hpp"
#include "TextureManager.hpp"

class Snake2 {
private: 
	Snake player1; 
	Snake player2; 
	Timer timer;
	int winner; 
public: 
	Snake2(); 
	~Snake2(); 

	void Setup(); 
	void Update(); 
	void Render();
	void Logic();  
	int isWinner();
	void FreeTexture(); 
};
