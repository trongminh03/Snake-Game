#include "Map.hpp" 

Map::Map() {}

Map::~Map() {
	SDL_DestroyTexture(border[0]); 
	SDL_DestroyTexture(border[1]); 
	SDL_DestroyTexture(roadblock); 
} 

void Map::Setup() {
	border[0] = TextureManager::LoadTexture("res/gfx/Background/border.png"); 
	border[1] = TextureManager::LoadTexture("res/gfx/Background/border1.png"); 

	setDst(dst_border[0], 0, BORDER_HEIGHT, BORDER_WIDTH, BORDER_THICK); 
	setDst(dst_border[1], 0, 0, BORDER_THICK, BORDER_HEIGHT); 
	setDst(dst_border[2], 0, 0, BORDER_WIDTH, BORDER_THICK); 
	setDst(dst_border[3], BORDER_WIDTH - BORDER_THICK, 0, BORDER_THICK, BORDER_HEIGHT); 
}

void Map::Setup2() {
	//roadblock
	roadblock = TextureManager::LoadTexture("res/gfx/Background/block.png"); 

	setDst(dst_roadblock[0], BLOCK1_X, BLOCK1_Y, BLOCK1_W, BLOCK1_H); 
	setDst(dst_roadblock[1], BLOCK2_X, BLOCK2_Y, BLOCK2_W, BLOCK2_H);
}

void Map::setDst(SDL_Rect& dst, int x, int y, int w, int h) {
	dst.x = x; 
	dst.y = y; 
	dst.w = w; 
	dst.h = h; 
}

void Map::RenderBorder() {
	for (int i = 0; i < 4; i++) {
		if (i % 2 == 0) {
			TextureManager::Draw(border[0], dst_border[i]);  
		}
		else {
			TextureManager::Draw(border[1], dst_border[i]); 
		}	
	}
}

void Map::RenderRoadblock() {
	TextureManager::Draw(roadblock, dst_roadblock[0]); 
	TextureManager::Draw(roadblock, dst_roadblock[1]); 
}

void Map::FreeBorderTexture() {
	SDL_DestroyTexture(border[0]); 
	SDL_DestroyTexture(border[1]); 
}

void Map::FreeRoadblockTexture() {
	SDL_DestroyTexture(roadblock); 
}