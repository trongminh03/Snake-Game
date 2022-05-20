#include "GameText.hpp" 

GameText::GameText() {}

GameText::~GameText() { 
	SDL_DestroyTexture(texture_); 
}

void GameText::SetText(const std::string& text) {
	str_val = text; 
}

void GameText::SetColor(const int& type) {
	if (type == RED_TEXT) {
		SDL_Color color = {255, 0, 0}; 
		text_color = color; 
	}
	else if (type == WHITE_TEXT) {
		SDL_Color color = {255, 255, 255}; 
		text_color = color; 
	}
	else if (type == BLACK_TEXT) {
		SDL_Color color = {0, 0, 0}; 
		text_color = color; 
	}
	else if (type == GREEN_TEXT) {
		SDL_Color color = {34, 139, 34}; 
		text_color = color; 
	}
	else if (type == PINK_TEXT) {
		SDL_Color color = {249, 109, 109}; 
		text_color = color; 
	}
	else if (type == LIGHT_YELLOW_TEXT) {
		SDL_Color color = {238, 232, 170}; 
		text_color = color; 
	}
}

void GameText::CreateGameText(TTF_Font* font, const SDL_Rect &dstR) {
	Free(); 
	surface_ = TTF_RenderText_Solid(font, str_val.c_str(), text_color); 
	texture_ = SDL_CreateTextureFromSurface(Game::renderer, surface_); 
	SDL_RenderCopy(Game::renderer, texture_, NULL, &dstR); 
	SDL_FreeSurface(surface_);
}

void GameText::Init(TTF_Font* font) {
	surface_ = TTF_RenderText_Solid(font, str_val.c_str(), text_color); 
	texture_ = SDL_CreateTextureFromSurface(Game::renderer, surface_);
	SDL_FreeSurface(surface_);
}

void GameText::Render(const SDL_Rect &dstR) {
	SDL_RenderCopy(Game::renderer, texture_, NULL, &dstR);
}

void GameText::Free() {
	SDL_DestroyTexture(texture_); 
}