#include "Snake.hpp" 
#include "TextureManager.hpp"
#include "Fruit.hpp"

Snake::Snake() {}

Snake::~Snake() {
	FreeTexture(); 
} 

void Snake::Setup(const string& filePath) {
	//snake head
	snakeTexture = TextureManager::LoadTexture(filePath); 
	head.SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);  
	s_angle = 0; 
	s_flip = SDL_FLIP_NONE; 
	//tails
	tails.Setup("res/gfx/Snake/body.png", "res/gfx/Snake/last_tail.png", 
					"res/gfx/Snake/curve.png", "res/gfx/Snake/curve_tail.png"); 
	tails.tail[0] = head; 
	tails.t_angle[0] = s_angle;
	for (int i = 0; i < tails.total_tail; i++) {
		tails.tail[i + 1] = tails.tail[i] + Vector2D(- TAILS_SIZE, 0); 
		tails.t_angle[i + 1] = tails.t_angle[i]; 
	}
	 
	//score
	score = 0; 
	game_score.Setup(GameText::RED_TEXT);   
	game_highestScore.Setup(GameText::WHITE_TEXT); 
	HighestScore = game_highestScore.getHighestScore();
	game_highestScore.Update(HighestScore, "Highest Score: "); 
	//sound
	eating_sound.loadSound("res/audio/sound/eating.wav"); 
	lose_sound.loadSound("res/audio/sound/lose.wav");

	step.SetPos(0, 0); 
	isMove = false; 
	alive = true;  
}

void Snake::Setup2(const string &head_color, const string &body_color, const string &tail_color,
            const string &curve_color, const string &curveTail_color, 
            const Vector2D &startPos, const int &index, const GameText::TextColor &color) {
	//snake head
	snakeTexture = TextureManager::LoadTexture(head_color);
	head = startPos;
	s_angle = 0; 
	if (index == 1) 
		s_angle = 0; 
	else if (index == -1) 
		s_angle = 180;  
	//tails
	tails.Setup(body_color, tail_color, curve_color, curveTail_color); 
	tails.tail[0] = head; 
	tails.t_angle[0] = s_angle;  
	for (int i = 0; i < tails.total_tail; i++) {
		tails.tail[i + 1] = tails.tail[i] + Vector2D( - index * TAILS_SIZE, 0); 
		tails.t_angle[i + 1] = tails.t_angle[i]; 
	}
	//score
	score = 0; 
	game_score.Setup(color);    
	//sound
	eating_sound.loadSound("res/audio/sound/eating.wav");  
	lose_sound.loadSound("res/audio/sound/lose.wav"); 

	step.SetPos(0, 0); 
	dir = RIGHT; 
	isMove = false; 
	alive = true; 
}

void Snake::Update() { 
	moveSet();
	if (isMove == true) {
		for (int i = tails.total_tail; i > 0; i--) {
			tails.tail[i] = tails.tail[i - 1];  
			tails.t_angle[i] = tails.t_angle[i - 1]; 
		}
		tails.tail[0] = head; 
		tails.t_angle[0] = s_angle; 
	}

	CheckCollideFood(); 
	if (CheckSelfCollide() || !Inside(Vector2D(BORDER_THICK, BORDER_THICK), 
						Vector2D(BORDER_WIDTH - BORDER_THICK, BORDER_HEIGHT))) 
		alive = false;  
	
	if (!isAlive()) 
		Game::isRunning = false; 
	
	if (!Game::isRunning) 
		lose_sound.playSound(); 
}

void Snake::Update2() { 
	if (isMove == true) {
		for (int i = tails.total_tail; i > 0; i--) {
			tails.tail[i] = tails.tail[i - 1];   
			tails.t_angle[i] = tails.t_angle[i - 1]; 
		}
		tails.tail[0] = head; 
		tails.t_angle[0] = s_angle;
	}
	
	CheckCollideFood2(); 
	if (CheckSelfCollide() || !Inside({BORDER_THICK, BORDER_THICK}, 
								{BORDER_WIDTH - BORDER_THICK, BORDER_HEIGHT}) 
	||CheckHitBlock({BLOCK1_X, BLOCK1_Y}, {BLOCK1_X + BLOCK1_W, BLOCK1_Y + BLOCK1_H})
	||CheckHitBlock({BLOCK2_X, BLOCK2_Y}, {BLOCK2_X + BLOCK2_W, BLOCK2_Y + BLOCK2_H}))
		alive = false;  

	if (!isAlive()) {
		Game::isRunning = false; 
	}

	if (!Game::isRunning) 
		lose_sound.playSound();
}

void Snake::UpdateAI() {
	autoFindPath(); 
	DirectionAI();
	Move(); 

	for (int i = tails.total_tail; i > 0; i--) {
		tails.tail[i] = tails.tail[i - 1];
		tails.t_angle[i] = tails.t_angle[i - 1]; 
	}
	tails.tail[0] = head; 
	tails.t_angle[0] = s_angle;

	CheckCollideFood();  
	if (CheckSelfCollide() || !Inside(Vector2D(20, 20), Vector2D(780, 520)))  
		alive = false; 

	if (!isAlive()) 
		Game::isRunning = false; 

	if (!Game::isRunning) 
		lose_sound.playSound(); 
}

void Snake::DirectionAI() {
	switch(dir) {
		case UP: 
			Up(); 
			break; 
		case DOWN: 
			Down(); 
			break; 
		case LEFT: 
			Left(); 
			break; 
		case RIGHT: 
			Right(); 
			break; 
	}
}

void Snake::autoFindPath() {
	int hCostA = 0;
	int hCostB = 0;
	int hCostC = 0;

	Vector2D distance; 
	bool blocked = false;
	int fCostA = 999999999;
	int fCostB = 999999999;
	int fCostC = 999999999;
	switch(dir) {
		case UP:
			hCostA = 0;
			hCostB = 0;
			hCostC = 0;
			if (tails.tail[0].y - size >= BORDER_THICK) {
				// If no body parts blocking
				for(int i = tails.total_tail; i > 0; i--) {
					if (tails.tail[0] - Vector2D(0, size) == tails.tail[i]) {
						blocked = true;
						break;
					}
				}
				if (blocked != true) {
					// Going up
					distance.x = abs((Fruit::fruit.x - tails.tail[0].x) / size);
					distance.y = abs((Fruit::fruit.y - (tails.tail[0].y - size)) / size);
					if (distance.y != 0) {
						hCostA = 4;
					}
					hCostA += (distance.x * 10) + (distance.y * 10);
					fCostA = hCostA + 10;
				}
				blocked = false;
            }
			// If space to go left
			if(tails.tail[0].x - size >= BORDER_THICK) {
				// If no body parts blocking
				for(int i = tails.total_tail; i > 0; i--) {
					if (tails.tail[0] - Vector2D(size, 0) == tails.tail[i]) {
						blocked = true;
						break;
					}
				}
				if (blocked != true) {
					// Going left
					distance.x = abs((Fruit::fruit.x - (tails.tail[0].x - size)) / size);
					distance.y = abs((Fruit::fruit.y - tails.tail[0].y) / size);
					if (distance.y != 0) {
						hCostB = 4;
					}
					hCostB+= (distance.x * 10) + (distance.y * 10);
					fCostB = hCostB + 14;
				}
				blocked = false;
			}
			
			// If space to go right
			if(tails.tail[0].x + size < BORDER_WIDTH - BORDER_THICK) {
				// If no body parts blocking
				for(int i = tails.total_tail; i > 0; i--) {
					if (tails.tail[0] + Vector2D(size, 0) == tails.tail[i]) {
						blocked = true;
						break;
					}
				}
				if (blocked != true) {
					// Going right
					distance.x = abs((Fruit::fruit.x - (tails.tail[0].x + size)) / size);
					distance.y = abs((Fruit::fruit.y - tails.tail[0].y) / size);
					if (distance.y != 0) {
						hCostC = 4;
					}
					hCostC+= (distance.x * 10) + (distance.y * 10);
					fCostC = hCostC + 14;
				}
				blocked = false;
			}
			
			if(fCostA <= fCostB && fCostA <= fCostC) {
				dir = UP;
			} else if (fCostB < fCostA && fCostB <= fCostC) {
				dir = LEFT;
			} else if(fCostC < fCostB && fCostC < fCostA) {
				dir = RIGHT;
			}
			fCostA = 999999999;
			fCostB = 999999999;
			fCostC = 999999999;
			
			break;
		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		case DOWN:
			hCostA = 0;
			hCostB = 0;
			hCostC = 0;
			
			// If space to go down
			if (tails.tail[0].y + size < BORDER_HEIGHT - BORDER_THICK) {
				// If no body parts blocking
				for (int i = tails.total_tail; i > 0; i--) {
					if (tails.tail[0] + Vector2D(0, size) == tails.tail[i]) {
						blocked = true;
						break;
					}
				}
				if (blocked != true) {
					// Going down
					distance.x = abs((Fruit::fruit.x - tails.tail[0].x) / size);
					distance.y = abs((Fruit::fruit.y - (tails.tail[0].y + size)) / size);
					if (distance.y != 0) {
						hCostA = 4;
					}
					hCostA += (distance.x * 10) + (distance.y * 10);
					fCostA = hCostA + 10;
				}
				blocked = false;
			}
			
			// If space to go left
			if (tails.tail[0].x - size >= BORDER_THICK) {
				// If no body parts blocking
				for (int i = tails.total_tail; i > 0; i--) {
					if (tails.tail[0] - Vector2D(size, 0) == tails.tail[i]) {
						blocked = true;
						break;
					}
				}
				if (blocked != true) {
					// Going left
					distance.x = abs((Fruit::fruit.x - (tails.tail[0].x - size)) / size);
					distance.y = abs((Fruit::fruit.y - tails.tail[0].y) / size);
					if (distance.y != 0) {
						hCostB = 4;
					}
					hCostB += (distance.x * 10) + (distance.y * 10);
					fCostB = hCostB + 14;
				}
				blocked = false;
			}
			
			// If space to go right
			if (tails.tail[0].x + size < BORDER_WIDTH - BORDER_THICK) {
				// If no body parts blocking
				for (int i = tails.total_tail; i > 0; i--) {
					if (tails.tail[0] + Vector2D(size, 0) == tails.tail[i]) {
						blocked = true;
						break;
					}
				}
				if (blocked != true) {
					// Going right
					distance.x = abs((Fruit::fruit.x - (tails.tail[0].x + size)) / size);
					distance.y = abs((Fruit::fruit.y - tails.tail[0].y) / size);
					if (distance.y != 0) {
						hCostC = 4;
					}
					hCostC += (distance.x * 10) + (distance.y * 10);
					fCostC = hCostC + 14;
				}
				blocked = false;
			}
			
			if (fCostA <= fCostB && fCostA <= fCostC) {
				dir = DOWN;
			} else if (fCostB < fCostA && fCostB <= fCostC) {
				dir = LEFT;
			} else if (fCostC < fCostB && fCostC < fCostA) {
				dir = RIGHT;
			}
			fCostA = 999999999;
			fCostB = 999999999;
			fCostC = 999999999;
			
			break;

		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		case LEFT:
			hCostA = 0;
			hCostB = 0;
			hCostC = 0;
			
			// If space to go left
			if (tails.tail[0].x - size >= BORDER_THICK) {
				// If no body parts blocking
				for (int i = tails.total_tail; i > 0; i--) {
					if (tails.tail[0] - Vector2D(size, 0) == tails.tail[i]) {
						blocked = true;
						break;
					}
				}
				if (blocked != true) {
					// Going left
					distance.x = abs((Fruit::fruit.x - (tails.tail[0].x - size)) / size);
					distance.y = abs((Fruit::fruit.y - tails.tail[0].y) / size);
					if (distance.y != 0) {
						hCostA = 4;
					}
					hCostA += (distance.x * 10) + (distance.y * 10);
					fCostA = hCostA + 10;
				}
				blocked = false;
			}
			
			// If space to go down
			if (tails.tail[0].y + size < BORDER_HEIGHT) {
				// If no body parts blocking
				for (int i = tails.total_tail; i > 0; i--) {
					if (tails.tail[0] + Vector2D(0, size) == tails.tail[i]) {
						blocked = true;
						break;
					}
				}
				if (blocked != true) {
					// Going down
					distance.x = abs((Fruit::fruit.x - tails.tail[0].x) / size);
					distance.y = abs((Fruit::fruit.y - (tails.tail[0].y + size)) / size);
					if (distance.y != 0) {
						hCostB = 4;
					}
					hCostB += (distance.x * 10) + (distance.y * 10);
					fCostB = hCostB + 14;
				}
				blocked = false;
			}
			
			// If space to go up
			if (tails.tail[0].y - size >= BORDER_THICK) {
				// If no body parts blocking
				for (int i = tails.total_tail; i > 0; i--) {
					if (tails.tail[0] - Vector2D(0, size) == tails.tail[i]) {
						blocked = true;
						break;
					}
				}
				if (blocked != true) {
					// Going up
					distance.x = abs((Fruit::fruit.x - tails.tail[0].x) / size);
					distance.y = abs((Fruit::fruit.y - (tails.tail[0].y - size)) / size);
					if (distance.y != 0) {
						hCostC = 4;
					}
					hCostC += (distance.x * 10) + (distance.y * 10);
					fCostC = hCostC + 14;
				}
				blocked = false;
			}
			
			if (fCostA <= fCostB && fCostA <= fCostC) {
				dir = LEFT;
			} else if (fCostB < fCostA && fCostB <= fCostC) {
				dir = DOWN;
			} else if (fCostC < fCostB && fCostC < fCostA) {
				dir = UP;
			}

			fCostA = 999999999;
			fCostB = 999999999;
			fCostC = 999999999;
			
			break;

		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		case RIGHT:
			hCostA = 0;
			hCostB = 0;
			hCostC = 0;
			
			// If space to go right
			if (tails.tail[0].x + size < BORDER_WIDTH - BORDER_THICK) {
				// If no body parts blocking
				for (int i = tails.total_tail; i > 0; i--) {
					if (tails.tail[0] + Vector2D(size, 0) == tails.tail[i]) {
						blocked = true;
						break;
					}
				}
				if (blocked != true) {
					// Going right
					distance.x = abs((Fruit::fruit.x - (tails.tail[0].x + size)) / size);
					distance.y = abs((Fruit::fruit.y - tails.tail[0].y) / size);
					if (distance.y != 0) {
						hCostA = 4;
					}
					hCostA += (distance.x * 10) + (distance.y * 10);
					fCostA = hCostA + 10;
				}
				blocked = false;
			}
			
			// If space to go down
			if (tails.tail[0].y + size < BORDER_HEIGHT) {
				// If no body parts blocking
				for (int i = tails.total_tail; i > 0; i--) {
					if (tails.tail[0] + Vector2D(0, size) == tails.tail[i]) {
						blocked = true;
						break;
					}
				}
				if (blocked != true) {
					// Going down
					distance.x = abs((Fruit::fruit.x - tails.tail[0].x) / size);
					distance.y = abs((Fruit::fruit.y - (tails.tail[0].y + size)) / size);
					if (distance.y != 0) {
						hCostB = 4;
					}
					hCostB += (distance.x * 10) + (distance.y * 10);
					fCostB = hCostB + 14;
				}
				blocked = false;
			}
			
			// If space to go up
			if (tails.tail[0].y - size >= BORDER_THICK) {
				// If no body parts blocking
				for (int i = tails.total_tail; i > 0; i--) {
					if (tails.tail[0] - Vector2D(0, size) == tails.tail[i]) {
						blocked = true;
						break;
					}
				}
				if (blocked != true) {
					// Going up
					distance.x = abs((Fruit::fruit.x - tails.tail[0].x) / size);
					distance.y = abs((Fruit::fruit.y - (tails.tail[0].y - size)) / size);
					if (distance.y != 0) {
						hCostC = 4;
					}
					hCostC += (distance.x * 10) + (distance.y * 10);
					fCostC = hCostC + 14;
				}
				blocked = false;
			}
			
			if (fCostA <= fCostB && fCostA <= fCostC) {
				dir = RIGHT;
			} else if (fCostB < fCostA && fCostB <= fCostC) {
				dir = DOWN;
			} else if (fCostC < fCostB && fCostC < fCostA) {
				dir = UP;
			}

			fCostA = 999999999;
			fCostB = 999999999;
			fCostC = 999999999;
			
			break;
    }
}

void Snake::Direction() {
	if (Game::event.type == SDL_KEYDOWN) {
		switch(Game::event.key.keysym.sym) {
			case SDLK_ESCAPE:  
				SDL_Texture* pause_texture; 
				pause_texture = TextureManager::LoadTexture("res/gfx/Background/pause.png");  
				while (true) {
					SDL_RenderCopy(Game::renderer, pause_texture, NULL, NULL); 
					SDL_RenderPresent(Game::renderer); 
					while (SDL_PollEvent(&Game::event)) {
						switch(Game::event.type) {
							case SDL_QUIT: 
								exit(0); 
							case SDL_KEYDOWN: 
								switch(Game::event.key.keysym.sym) {
									case SDLK_ESCAPE:
										SDL_DestroyTexture(pause_texture);
										goto HandleEvents; 
								}
						}
					}
				} 
				HandleEvents:
				break;
			case SDLK_LEFT: 
				Left(); 
				break;  
			case SDLK_RIGHT: 
				Right();
				break;  
			case SDLK_UP: 
				Up(); 
				break;  
			case SDLK_DOWN: 
				Down();	  
				break; 
		}
	}
}

void Snake::Direction2() {
	if (Game::event.type == SDL_KEYDOWN) {
		switch(Game::event.key.keysym.sym) {
			case SDLK_ESCAPE: break; 
			case SDLK_a: 
				Left();
				break;  
			case SDLK_d: 
				Right(); 
				break;  
			case SDLK_w: 
				Up(); 
				break;  
			case SDLK_s: 
				Down();	
				break; 
		}
	}
}

void Snake::Move() {
	head += step; 
}

void Snake::Up() {
	if (step.y == 0) {
		step.SetPos(0, -velocity);  
		s_angle = -90;
		s_flip = SDL_FLIP_NONE;
	}
 
}

void Snake::Down() {
	if (step.y == 0) {
		step.SetPos(0, velocity);  
		s_angle = 90;
		s_flip = SDL_FLIP_NONE;
	}
}

void Snake::Right() {
	if (step.x == 0) {
		step.SetPos(velocity, 0); 
		s_angle = 0;
		s_flip = SDL_FLIP_NONE;
	}
}

void Snake::Left() {
	if (step.x == 0) {
		step.SetPos(-velocity, 0); 
		s_angle = 180; 
		s_flip = SDL_FLIP_NONE; 
	}
}

void Snake::moveSet() {
	Direction(); 
	Move(); 
	if (step.x != 0 || step.y != 0) isMove = true; 
}

void Snake::moveSet2() {
	Direction2(); 
	Move();
	if (step.x != 0 || step.y != 0) isMove = true;
}

void Snake::CheckCollideFood() {
	if (head + Vector2D(size, size) > Fruit::fruit 
		&& Fruit::fruit + Vector2D(size, size) > head) {
		eating_sound.playSound(); 
		tails.Update(); 
		Fruit::Respawn(); 
		score += 10;	
	}
}

void Snake::CheckCollideFood2() {
	if (head + Vector2D(size, size) > Fruit::fruit 
		&& Fruit::fruit + Vector2D(size, size) > head) {
		eating_sound.playSound(); 
		tails.Update(); 
		Fruit::Respawn2();   
		score += 10;
	}
}


bool Snake::Inside(const Vector2D &pos_min, const Vector2D &pos_max) {
	return (pos_min <= head && head + Vector2D(size, size) <= pos_max);
}

bool Snake::CheckSelfCollide() {
	for (int i = 1; i <= tails.total_tail; i++) {
		if (head + Vector2D(size, size) > tails.tail[i] 
			&& tails.tail[i] + Vector2D(TAILS_SIZE, TAILS_SIZE) > head) {
			return true; 
		}
	}
	return false; 
}

bool Snake::CheckHitBlock(const Vector2D &pos_min, const Vector2D &pos_max) {
	return (head + Vector2D(size, size) > pos_min && head < pos_max); 
}

void Snake::UpdateScore(string msg) {
	game_score.Update(score, msg); 
}

void Snake::UpdateHighestScore() { 
	if (score > HighestScore) {
		HighestScore = score; 
		game_highestScore.Update(score, "Highest Score: "); 
	}
	if (!Game::isRunning) game_highestScore.Record(HighestScore); 
}

void Snake::Render() { 
	TextureManager::DrawEx(snakeTexture, head, Vector2D(size, size), s_angle, s_flip); 
	tails.Render();  
}

void Snake::RenderScore(const Vector2D &pos, const Vector2D &size) {
	game_score.Render(pos, size); 
}

void Snake::RenderHighestScore(const Vector2D &pos, const Vector2D &size) {
	game_highestScore.Render(pos, size); 
}

int Snake::getScore() {
	return score; 
}

void Snake::FreeTexture() {
	SDL_DestroyTexture(snakeTexture);
	tails.FreeTexture(); 
	game_score.Free(); 
	game_highestScore.Free(); 
}