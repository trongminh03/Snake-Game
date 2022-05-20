#include "Fruit.hpp" 
#include "TextureManager.hpp" 
#include "Snake.hpp"

Vector2D Fruit::fruit(0, 0); 
int Fruit::size = FRUIT_SIZE; 

Fruit::Fruit() {}

Fruit::~Fruit() {
	SDL_DestroyTexture(fruitTexture); 
}  

void Fruit::Setup(const char* filePath) {
	fruitTexture = TextureManager::LoadTexture(filePath);
	Respawn(); 
} 

void Fruit::Update() {
	TextureManager::SetPos(srcR, {0, 0}, {size, size}); 
	TextureManager::SetPos(dstR, fruit, {size, size}); 
}

void Fruit::Render() {
	SDL_RenderCopy(Game::renderer, fruitTexture, &srcR, &dstR); 
}

void Fruit::Respawn() {
	fruit.x = rand()% ((BORDER_WIDTH - BORDER_THICK - FRUIT_SIZE) 
							- BORDER_THICK + 1) + BORDER_THICK;
	//rand()% (max - min + 1) + min (random trong khoảng từ min -> max);
	fruit.y = rand()% ((BORDER_HEIGHT - BORDER_THICK) 
					- BORDER_THICK + 1) + BORDER_THICK;  
	fruit.x = int(fruit.x / 20) * 20; 
	fruit.y = int(fruit.y / 20) * 20; 
}

void Fruit::Respawn2() {
	do{ 
		fruit.x = rand()% ((BORDER_WIDTH - BORDER_THICK 
						- FRUIT_SIZE) - BORDER_THICK + 1) + BORDER_THICK; 
		fruit.y = rand()% ((BORDER_HEIGHT - BORDER_THICK) 
						- BORDER_THICK + 1) + BORDER_THICK; 		
		//rand()% (max - min + 1) + min (random trong khoảng từ min -> max); 	
		fruit.x = int(fruit.x / 20) * 20; 
		fruit.y = int(fruit.y / 20) * 20; 
	} while (insideBlock({BLOCK1_X, BLOCK1_Y}, {BLOCK1_X + BLOCK1_W, BLOCK1_Y + BLOCK1_H})
		||insideBlock({BLOCK2_X, BLOCK2_Y}, {BLOCK2_X + BLOCK2_W, BLOCK2_Y + BLOCK2_H})); 
}

bool Fruit::insideBlock(const Vector2D &pos_min, const Vector2D &pos_max) {
	return (fruit.x + size > pos_min.x && fruit.x < pos_max.x && 
		    fruit.y + size > pos_min.y && fruit.y < pos_max.y); 
}

void Fruit::FreeTexture() {
	SDL_DestroyTexture(fruitTexture);
}