#include "AISnake.hpp"  

AISnake::AISnake() {}

AISnake::~AISnake() {
	FreeTexture(); 
} 

void AISnake::Setup() {
	player.Setup2("res/gfx/Snake/snake.png", "res/gfx/Snake/body.png", 
				"res/gfx/Snake/last_tail.png", "res/gfx/Snake/curve.png", 
				"res/gfx/Snake/curve_tail.png", Vector2D(680, 460), -1, GameText::RED_TEXT); 
	AI_Snake.Setup2("res/gfx/Snake/snake2.png", "res/gfx/Snake/body2.png", 
				"res/gfx/Snake/last_tail2.png", "res/gfx/Snake/curve2.png", 
				"res/gfx/Snake/curve_tail2.png", Vector2D(100, 60), 1, GameText::GREEN_TEXT); 
	timer.Setup(); 
	winner = 0;  
}

void AISnake::Update() {
	player.Update(); 
	player.UpdateScore("Player: "); 
	
	AI_Snake.UpdateAI(); 
	AI_Snake.UpdateScore("AI Snake: "); 

	timer.Update(); 

	Logic(); 
}

void AISnake::Render() {
	AI_Snake.Render(); 
	AI_Snake.RenderScore({SCORE2_X, SCORE2_Y}, {SCORE2_W, SCORE2_H});

	player.Render();  
	player.RenderScore({SCORE1_X, SCORE1_Y}, {SCORE1_W, SCORE1_H});  
	
	timer.Render(); 
}

void AISnake::Logic() {
	if (player.isAlive() == false) {
		Game::isRunning = false; 
		winner = 2;  
	}
	if (AI_Snake.isAlive() == false) {
		Game::isRunning = false; 
		winner = 1;  
	}
	if (timer.getTimeVal() == 0) {
		if (player.getScore() > AI_Snake.getScore()) { 
			Game::isRunning = false; 
			winner = 1; 	  			
		} 
		else if (player.getScore() < AI_Snake.getScore()) {
			Game::isRunning = false; 
			winner = 2;  
		}
		else {
			Game::isRunning = false; 
			winner = 0;  
		}
	}
}

int AISnake::isWinner() {
	return winner; 
}

void AISnake::FreeTexture() {
	player.FreeTexture(); 
	AI_Snake.FreeTexture(); 
	timer.Free(); 
}
