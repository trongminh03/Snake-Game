#include "Tails.hpp" 
#include "TextureManager.hpp"
#include "Snake.hpp"

Tails::Tails() {}

Tails::~Tails() {
	FreeTexture(); 
}

void Tails::Setup(const string& body, const string& tail_, const string& curve_, 
			const string& curve_tail) {
	tailTexture = TextureManager::LoadTexture(body); 
	lastTailTexture = TextureManager::LoadTexture(tail_); 
	curveTexture = TextureManager::LoadTexture(curve_); 
	curveTailTexture = TextureManager::LoadTexture(curve_tail); 

	total_tail = 3; 
	TextureManager::SetPos(t_srcCurve, {0, 0}, {20, 20}); 
	curve.SetPos(-1, -1); 
	
	for (int i = 0; i <= total_tail; i++) {
		tail.push_back({0, 0}); 
		t_angle.push_back(0);  
	}
}

void Tails::Update() { 	 
	total_tail++; 
	tail.push_back({0, 0}); 
	switch(t_angle[total_tail - 1]) {
		case 0: 
			tail[total_tail] = tail[total_tail - 1] - Vector2D(size, 0); 
			t_angle[total_tail] = t_angle[total_tail - 1]; 
			break; 
		case 90: 
			tail[total_tail] = tail[total_tail - 1] - Vector2D(0, size); 
			t_angle[total_tail] = t_angle[total_tail - 1]; 
			break; 
		case 180: 
			tail[total_tail] = tail[total_tail - 1] + Vector2D(size, 0); 
			t_angle[total_tail] = t_angle[total_tail - 1]; 
			break; 
		case -90: 
			tail[total_tail] = tail[total_tail - 1] + Vector2D(0, size); 
			t_angle[total_tail] = t_angle[total_tail - 1]; 
			break; 
	}
}

void Tails::Render() { 
	if (tail[total_tail] == curve) {
		TextureManager::DrawS(curveTailTexture, tail[total_tail], 
						{size, size}, t_srcCurve); 
	}
	else {
		TextureManager::DrawEx(lastTailTexture, tail[total_tail], 
							{size, size}, t_angle[total_tail], SDL_FLIP_NONE);	
	}
	for (int i = 1; i < total_tail; i++) {
		if (tail[i - 1] + tail[i + 1] == tail[i] * 2 - Vector2D(size, size)) {
			TextureManager::DrawEx(curveTexture, tail[i], {size, size}, 0, SDL_FLIP_NONE);
			if (i == total_tail - 1) {
				curve = tail[i];   				
				if (tail[i - 1].x > tail[i + 1].x) {
					TextureManager::SetPos(t_srcCurve, {0, 0}, {20, 20}); 
				}
				else {
					TextureManager::SetPos(t_srcCurve, {140, 0}, {20, 20});
				}
			}
		}
		else if (tail[i - 1] + tail[i + 1] == tail[i] * 2 + Vector2D(size, -size)) {
			TextureManager::DrawEx(curveTexture, tail[i], Vector2D(size, size), 
									0, SDL_FLIP_HORIZONTAL);
			if (i == total_tail - 1) {
				curve = tail[i];   
				if (tail[i - 1].x > tail[i + 1].x) {
					TextureManager::SetPos(t_srcCurve, {20, 0}, {20, 20}); 
				} 
				else {
					TextureManager::SetPos(t_srcCurve, {80, 0}, {20, 20}); 
				}				
			}
		}
		else if (tail[i - 1] + tail[i + 1] == tail[i] * 2 + Vector2D(-size, size)) {
			TextureManager::DrawEx(curveTexture, tail[i], 
								{size, size}, -90, SDL_FLIP_NONE);
			if (i == total_tail - 1) {			
				curve = tail[i];   
				if (tail[i - 1].x > tail[i + 1].x) {
					TextureManager::SetPos(t_srcCurve, {120, 0}, {20, 20}); 
				}
				else {
					TextureManager::SetPos(t_srcCurve, {60, 0}, {20, 20}); 
				}
			}
		}
		else if (tail[i - 1] + tail[i + 1] == tail[i] * 2 + Vector2D(size, size)) {
			TextureManager::DrawEx(curveTexture, tail[i], {size, size}, 
									90, SDL_FLIP_HORIZONTAL);
			if (i == total_tail - 1) {
				curve = tail[i];    
				if (tail[i - 1].x > tail[i + 1].x) {
					TextureManager::SetPos(t_srcCurve, {100, 0}, {20, 20}); 
				}
				else {
					TextureManager::SetPos(t_srcCurve, {40, 0}, {20, 20});
				}				
			}
		}
		else { 
			TextureManager::DrawEx(tailTexture, tail[i], {size, size}, 
									t_angle[i], SDL_FLIP_NONE);
		}
	}
}

void Tails::FreeTexture() {
	SDL_DestroyTexture(tailTexture); 
	SDL_DestroyTexture(lastTailTexture); 
	SDL_DestroyTexture(curveTexture); 
	SDL_DestroyTexture(curveTailTexture); 
}
