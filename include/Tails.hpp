#pragma once 
#include "Game.hpp"  
#include <vector>

using namespace std; 

class Tails {
private:   
	 
	SDL_Texture* tailTexture; 
	SDL_Texture* lastTailTexture; 
	SDL_Texture* curveTexture;
	SDL_Texture* curveTailTexture; 

	SDL_Rect t_srcCurve; 
	SDL_Rect srcR, dstR;  

	Vector2D curve;  
public: 
	Tails(); 
	~Tails(); 
	void Setup(const string& body, const string& tail_, const string& curve_, const string& curve_tail); 
	void Update(); 
	void Render();  
	int getTotalTail();  
	
	int size = TAILS_SIZE;
	vector<Vector2D> tail;  
	int total_tail;   

	vector<int> t_angle;   

	void FreeTexture(); 
}; 