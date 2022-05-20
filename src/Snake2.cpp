#include "Snake2.hpp" 

Snake2::Snake2() {}

Snake2::~Snake2() {
	FreeTexture(); 
}

void Snake2::Setup() {
	player1.Setup2("res/gfx/Snake/snake.png", "res/gfx/Snake/body.png", 
				"res/gfx/Snake/last_tail.png", "res/gfx/Snake/curve.png", 
				"res/gfx/Snake/curve_tail.png", Vector2D(680, 460), -1, GameText::RED_TEXT); 
	player2.Setup2("res/gfx/Snake/snake2.png", "res/gfx/Snake/body2.png", 
				"res/gfx/Snake/last_tail2.png", "res/gfx/Snake/curve2.png", 
				"res/gfx/Snake/curve_tail2.png", Vector2D(100, 60), 1, GameText::GREEN_TEXT);
	timer.Setup(); 
	winner = 0; 
}

void Snake2::Update() {
	player1.moveSet(); 
	player1.Update2(); 
	player1.UpdateScore("Player 1: "); 

	player2.moveSet2();
	player2.Update2();  
	player2.UpdateScore("Player 2: "); 

	timer.Update(); 

	Logic(); 
}

void Snake2::Render() {
	player1.Render();  
	player1.RenderScore({SCORE1_X, SCORE1_Y}, {SCORE1_W, SCORE1_H});  
	player2.Render(); 
	player2.RenderScore({SCORE2_X, SCORE2_Y}, {SCORE2_W, SCORE2_H});
	timer.Render(); 
}

void Snake2::Logic() {
	if (player1.isAlive() == false) {
		Game::isRunning = false; 
		winner = 2; 
	}
	if (player2.isAlive() == false) {
		Game::isRunning = false; 
		winner = 1; 
	}
	if (timer.getTimeVal() == 0) {
		if (player1.getScore() > player2.getScore()) { 
			Game::isRunning = false; 
			winner = 1; 	  			
		} 
		else if (player1.getScore() < player2.getScore()) {
			Game::isRunning = false; 
			winner = 2; 
		}
		else {
			Game::isRunning = false; 
			winner = 0;  
		}
	} 
}

int Snake2::isWinner() {
	return winner; 
}

void Snake2::FreeTexture() {
	player1.FreeTexture(); 
	player2.FreeTexture(); 
	timer.Free();
}