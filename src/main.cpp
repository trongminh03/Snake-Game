#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <iostream> 
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "Game.hpp"
#include "Menu.hpp"
#include "Audio.hpp"
#include "TextureManager.hpp"

Game* game = nullptr; 
Menu* GameMenu = nullptr; 
//Audio* theme_music; 

int main(int argc, char* argv[]) {
	srand(time(0)); 
	
	game = new Game(); 
	game->initWindow();  
	/*
	theme_music = new Audio(); 
	theme_music->loadMusic("res/audio/music/theme song.mp3"); 
	theme_music->playMusic(20); 
	*/ 
	GameMenu = new Menu();
	GameMenu->Setup();
	Home: 
		int i = GameMenu->showMenu(); 

		if (i == 1) {
			//exit
			Game::isRunning = false; 
		}	
		else if (i == 2) {
			//game instruction
			SDL_Texture* infor_text; 
			infor_text = TextureManager::LoadTexture("res/gfx/Background/infor_text.png"); 
			while (true) {
				SDL_RenderCopy(Game::renderer, infor_text, NULL, NULL); 
				SDL_RenderPresent(Game::renderer); 
				while (SDL_PollEvent(&Game::event)) {
					switch(Game::event.type) {
						case SDL_QUIT: 
							exit(0);  
						case SDL_KEYDOWN: 
							switch(Game::event.key.keysym.sym) {
								case SDLK_ESCAPE: break; 
								case SDLK_h: 
									SDL_DestroyTexture(infor_text);  
									goto Home; 
							}
					}
				}
			} 
			 
		}
		else if (i == 3) {
			//game credits
			SDL_Texture* credits_text; 
			credits_text = TextureManager::LoadTexture("res/gfx/Background/credits.png"); 
			while (true) {
				SDL_RenderCopy(Game::renderer, credits_text, NULL, NULL); 
				SDL_RenderPresent(Game::renderer); 
				while (SDL_PollEvent(&Game::event)) {
					switch(Game::event.type) {
						case SDL_QUIT: 
							exit(0); 
						case SDL_KEYDOWN: 
							switch(Game::event.key.keysym.sym) {
								case SDLK_ESCAPE: break; 
								case SDLK_h: 
									SDL_DestroyTexture(credits_text);  
									goto Home; 
							}
					}
				}
			}
		}
		else {
			//play game
			int numberOfPlayer = GameMenu->getNumPlayer(); 
			if (numberOfPlayer == 1) {
				game->gameLoop(); 
				if (Game::home == true) {
					goto Home;
				}
			}
			
			else if (numberOfPlayer == 2) {
				game->gameLoop2(); 
				if (Game::home == true) { 
					goto Home; 
				}
			}
			else if (numberOfPlayer == 3) {
				game->gameLoopAI(); 
				if (Game::home == true) {
					goto Home; 
				}
			}
		}
	
	delete game; 
	delete GameMenu; 
	//delete theme_music; 
	game->clean(); 
 	return 0; 
}