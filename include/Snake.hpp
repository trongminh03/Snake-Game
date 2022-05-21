#pragma once 
#include "Game.hpp"
#include "Audio.hpp"
#include "Tails.hpp"
#include "Score.hpp"

using namespace std; 

class Snake {
public: 
	Snake(); 
	~Snake(); 

	void Setup(const string& filePath); 
	void Setup2(const string& head_color, const string& body_color, const string& tail_color, 
		const string& curve_color, const string& curveTail_color, 
		const Vector2D &startPos, const int &index, const GameText::TextColor &color); 
	// Movement 
	void Move(); 
	void Up(); 
	void Down(); 
	void Left(); 
	void Right(); 
	// Alive
	bool Inside(const Vector2D &pos_min, const Vector2D &pos_max); 
	bool CheckSelfCollide(); 
	bool isAlive() {return alive;}
	bool CheckHitBlock(const Vector2D &pos_min, const Vector2D &pos_max); 

	//1 player
	void Update(); 
	void Direction(); 
	void CheckCollideFood(); 

	//2 player
	void moveSet(); 
	void Update2();
	void Direction2();
	void moveSet2();
	void CheckCollideFood2();

	// AI
	void UpdateAI(); 
	void DirectionAI();
 	void autoFindPath(); 

 	//score
	int getScore(); 
	void UpdateScore(string msg); 
	void UpdateHighestScore(); 
	
	//render
	void Render();  
	void RenderHighestScore(const Vector2D &pos, const Vector2D &size); 
	void RenderScore(const Vector2D &pos, const Vector2D &size); 

	void FreeTexture();  
private:  
	Vector2D head; 
	int size = SNAKE_SIZE;
	int velocity = SNAKE_SIZE;
	Vector2D step;
	SDL_Texture* snakeTexture; 
	SDL_Rect srcR, dstR;  
	Audio eating_sound; 
	Audio lose_sound;  
	int score;  
	Tails tails; 
	Score game_score; 
	Score game_highestScore; 
	int HighestScore; 
	bool alive = true; 
	SDL_RendererFlip s_flip = SDL_FLIP_NONE; 
	int s_angle = 0; 
	bool isMove = false;

	bool resume = false; 

	enum eDirection {UP, DOWN, LEFT, RIGHT}; 
	eDirection dir;  
}; 