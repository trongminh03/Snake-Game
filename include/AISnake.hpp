#pragma once
#include "Snake.hpp" 
#include "Timer.hpp"
#include "TextureManager.hpp"

class AISnake {
private: 
	Snake player; 
	Snake AI_Snake; 
	Timer timer; 
	int winner; 
public:
	AISnake();
	~AISnake();

	void Setup(); 
	void Update(); 
	void Render(); 
	void Logic();
	int isWinner(); 
	void FreeTexture(); 
};
