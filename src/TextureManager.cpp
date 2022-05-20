#include "TextureManager.hpp" 

SDL_Texture* TextureManager::LoadTexture(const std::string& filePath) {
	SDL_Surface* tempSurface = IMG_Load(filePath.c_str()); 
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface); 
	SDL_FreeSurface(tempSurface); 
	return texture; 
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect dst) {
	SDL_RenderCopy(Game::renderer, tex, NULL, &dst); 
}

void TextureManager::Draw(SDL_Texture* tex, const Vector2D &pos, const Vector2D &size) {
	SDL_Rect dst; 
	SetPos(dst, pos, size); 
	SDL_RenderCopy(Game::renderer, tex, NULL, &dst); 
}

void TextureManager::DrawS(SDL_Texture* tex, const Vector2D &pos, 
							const Vector2D &size, SDL_Rect src) {
	SDL_Rect dst; 
	SetPos(dst, pos, size);  
	SDL_RenderCopy(Game::renderer, tex, &src, &dst); 
}

void TextureManager::DrawEx(SDL_Texture* tex, const Vector2D &pos, const Vector2D &size, 
					const int &angle, SDL_RendererFlip flip) {
	SDL_Rect dst;
	SetPos(dst, pos, size);
	SDL_RenderCopyEx(Game::renderer, tex, NULL, &dst, angle, nullptr, flip);  
}

void TextureManager::SetPos(SDL_Rect& dst, const Vector2D &pos, const Vector2D &size) {
	dst.x = pos.x; 
	dst.y = pos.y; 
	dst.w = size.x; 
	dst.h = size.y; 
}