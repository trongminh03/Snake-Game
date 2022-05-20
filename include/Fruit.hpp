#pragma once 
#include "Game.hpp" 

class Fruit {
private: 
	SDL_Rect srcR, dstR; 
	SDL_Texture* fruitTexture;
public: 
	Fruit(); 
	~Fruit(); 

	void Setup(const char* filePath); 
	void Update(); 
	void Render(); 
	static void Respawn(); 
	static void Respawn2(); 
	static bool insideBlock(const Vector2D &pos_min, const Vector2D &pos_max); 

	//static int fruitX, fruitY;
	static Vector2D fruit;  
	static int size; 

	void FreeTexture(); 
}; 