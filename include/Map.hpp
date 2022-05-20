#pragma once
#include "Game.hpp" 
#include "TextureManager.hpp"

class Map {
private:
	SDL_Texture* border[2]; 
	//SDL_Texture* map; 
	SDL_Rect dst_border[4]; 
	//SDL_Rect dst_map; 

	SDL_Texture* roadblock; 
	SDL_Rect dst_roadblock[2]; 

public:
	Map();
	Map(const std::string& filePath); 
	~Map(); 

	void Setup(); 
	void Setup2();
	void RenderBorder(); 
	void RenderRoadblock(); 
	void setDst(SDL_Rect& dst, int x, int y, int w, int h); 
	void FreeBorderTexture(); 
	void FreeRoadblockTexture(); 
}; 