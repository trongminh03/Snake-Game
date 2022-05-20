#include "Audio.hpp" 

Audio::Audio() {
	SDL_Init(SDL_INIT_AUDIO); 
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
		std::cout << "Audio Error" << Mix_GetError();
	}
}

Audio::~Audio() {} 

void Audio::loadSound(const char* path) {
	chunk = Mix_LoadWAV(path); 
	if (chunk == NULL) {
		std::cout << "Audio Error " << Mix_GetError();  
		exit(0); 
	}
}

void Audio::loadMusic(const char* path) {
	music = Mix_LoadMUS(path); 
	if (music == NULL) {
		std::cout << "Audio Error" << Mix_GetError(); 
		exit(0); 
	}
}

void Audio::playSound() {
	Mix_PlayChannel(-1, chunk, 0); 
}

void Audio::playMusic() {
	Mix_PlayMusic(music, -1); 
}