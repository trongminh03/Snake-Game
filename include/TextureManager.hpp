#pragma once 
#include "Game.hpp" 

class TextureManager {
public: 
	static SDL_Texture* LoadTexture(const std::string& filePath); 
	static void Draw(SDL_Texture* tex, SDL_Rect dst); 
	static void Draw(SDL_Texture* tex, const Vector2D &pos, const Vector2D &size); 
	static void DrawS(SDL_Texture* tex, const Vector2D &pos, 
							const Vector2D &size, SDL_Rect src); 
	static void DrawEx(SDL_Texture* tex, const Vector2D &pos, const Vector2D &size, 
					const int &angle, SDL_RendererFlip flip = SDL_FLIP_NONE); 
	static void SetPos(SDL_Rect& dst, const Vector2D &pos, const Vector2D &size); 
}; 

