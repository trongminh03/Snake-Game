#pragma once 
#include "Game.hpp" 
#include <SDL2/SDL_mixer.h>

class Audio {
private:
	Mix_Chunk* chunk = NULL;
	Mix_Music* music = NULL;
	int volume; 

public:
	Audio(); 
	~Audio(); 
	
	void loadSound(const char* path);  
	void loadMusic(const char* path); 
	void playSound();  
	void playMusic();
	void playMusic(const int& v);    
}; 

