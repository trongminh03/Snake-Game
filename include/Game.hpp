#pragma once 
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream> 
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <chrono>
#include <climits>
#include "Console.hpp"
#include "Vector2D.hpp"

const std::string WINDOW_TITLE = "Snake Game";

class Game {
private: 
	SDL_Window* window;  
	const int FPS = 15;   
	const int frameDelay = 1000 / FPS;  
	Uint32 frameStart; 
	int frameTime; 
	int Quit = 0;   
public: 
	Game(); 
	~Game(); 

	void initWindow(); 
	void logSDLError(std::ostream& os, 
		const std::string &msg, bool fatal);
	void waitUntilKeyPressed(); 
	//setup
	void setup(); 
	void setup2();
	void setupAI();

	bool running();
	void handleEvents();
	//update 
	void update(); 
	void update2();
	void updateAI();
	//render  
	void render(); 
	void render2(); 
	void renderAI();
	//engine 
	void gameLoop(); 
	void gameLoop2();
	void gameLoopAI();
	 
	void clean(); 

	static SDL_Renderer* renderer; 
	static SDL_Event event; 
	static bool isRunning; 
	static Uint32 time_0; 
	static bool home;  
}; 