#include "Game.hpp" 
#include "TextureManager.hpp"
#include "Snake.hpp"
#include "Fruit.hpp"
#include "Score.hpp"
#include "Map.hpp"
#include "Snake2.hpp"
#include "Menu.hpp"
#include "AISnake.hpp"
#include <string>

SDL_Texture* background = nullptr; 

Snake snake; 
Snake2 snake2; 
AISnake snakeAI;

Fruit fruit; 
Map border; 
Map roadblock; 
Menu endBackground; 

bool Game::isRunning = false;
Uint32 Game::time_0; 
bool Game::home;

SDL_Renderer* Game::renderer = nullptr; 
SDL_Event Game::event;

Game::Game() {} 

Game::~Game() {
	window = NULL; 
	renderer = NULL;
	SDL_DestroyTexture(background); 
} 

void Game::initWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    	logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    isRunning = true; 
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    //Initialize the truetype font API.
	if (TTF_Init() < 0)
	{
		logSDLError(std::cout, "TTF_Init", true);
	} 
}

void Game::logSDLError(std::ostream& os,
                const std::string &msg, bool fatal = false) {
	os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void Game::setup() {
	Game::isRunning = true; 
	background = TextureManager::LoadTexture("res/gfx/Background/grey2.png");
	border.Setup(); 
	snake.Setup("res/gfx/Snake/snake.png"); 
	fruit.Setup("res/gfx/Snake/golden-apple.png"); 
    endBackground.Setup();
    home = false; 
}

void Game::setup2() {
	Game::isRunning = true; 
    background = TextureManager::LoadTexture("res/gfx/Background/grey2.png");
    border.Setup();  
    roadblock.Setup2(); 
    snake2.Setup(); 
    fruit.Setup("res/gfx/Snake/golden-apple.png");
    time_0 = SDL_GetTicks(); 
    endBackground.Setup();  
    home = false; 
}

void Game::setupAI() {
	Game::isRunning = true; 
    background = TextureManager::LoadTexture("res/gfx/Background/grey2.png");
    border.Setup();  
    snakeAI.Setup(); 
    fruit.Setup("res/gfx/Snake/golden-apple.png");   
    time_0 = SDL_GetTicks(); 
    endBackground.Setup(); 
    home = false; 
}
 
bool Game::running() {
	return isRunning; 
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT :
			if (MessageBoxA(NULL, "Do you wanna quit?", "End game", 
						   MB_YESNO | MB_ICONQUESTION) == IDYES) {
				isRunning = false;
				Quit = 1; 
			}
		default:
			break;
	}
}

void Game::waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if (SDL_WaitEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}

void Game::update() { 
	snake.Update(); 
	snake.UpdateScore("Score: ");
	snake.UpdateHighestScore(); 
	fruit.Update();  
}

void Game::update2() {
	snake2.Update(); 
	fruit.Update(); 
}

void Game::updateAI() {
	snakeAI.Update(); 
	fruit.Update(); 
}
 
void Game::render() {
	SDL_RenderClear(renderer); 
	SDL_RenderCopy(renderer, background, NULL, NULL); 
	snake.Render(); 
	border.RenderBorder();
	snake.RenderScore({SCORE_X, SCORE_Y}, {SCORE_W, SCORE_H}); 
	snake.RenderHighestScore({HISCORE_X, HISCORE_Y}, {HISCORE_W, HISCORE_H}); 
	fruit.Render(); 
	SDL_RenderPresent(renderer);
}

void Game::render2() {
	SDL_RenderClear(renderer); 
	SDL_RenderCopy(renderer, background, NULL, NULL); 
	snake2.Render(); 
	border.RenderBorder();
	roadblock.RenderRoadblock(); 
	fruit.Render();  
	SDL_RenderPresent(renderer);
}

void Game::renderAI() {
	SDL_RenderClear(renderer); 
	SDL_RenderCopy(renderer, background, NULL, NULL); 
	snakeAI.Render(); 
	border.RenderBorder();
	fruit.Render();  
	SDL_RenderPresent(renderer);
}
 
void Game::gameLoop() {
	setup(); 
	while (running()) {
		frameStart = SDL_GetTicks(); 

		handleEvents(); 
		update(); 
		render();  

		frameTime = SDL_GetTicks() - frameStart; 
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime); 
		} 
		if (Quit == 1) {
			isRunning = false; 
		}
		else {
			if (!isRunning) {
				int chooseOption = endBackground.endMenu("res/gfx/Background/game_over.png", 
													snake.getScore());
				//PLAY AGAIN
				if (chooseOption == 0) { 
					SDL_RenderClear(renderer); 
					endBackground.FreeTexture(); 
					setup(); 
					isRunning = true;					
				}
				//BACK
				else if (chooseOption == 2) {
					SDL_RenderClear(renderer); 
					endBackground.FreeTexture(); 
					home = true; 
				}
			}
		} 
	}
}

void Game::gameLoop2() {
	setup2(); 
	while (running()) {
		frameStart = SDL_GetTicks();

		handleEvents(); 
		update2(); 
		render2(); 

		frameTime = SDL_GetTicks() - frameStart; 
		if (frameDelay > frameTime) {	
			SDL_Delay(frameDelay - frameTime); 
		} 

		if (Quit == 1) {
			isRunning = false; 
		}
		else {
			if (!isRunning) {
				if (snake2.isWinner() == 1) {	
					int chooseOption = endBackground
										.endMenu("res/gfx/Background/P1_win.png");
					if (chooseOption == 0) {
						SDL_RenderClear(renderer); 
						endBackground.FreeTexture(); 
						setup2(); 
						isRunning = true;
					}
					else if (chooseOption == 2) {
						SDL_RenderClear(renderer);  
						endBackground.FreeTexture(); 
						home = true; 						
					}
				}
				else if (snake2.isWinner() == 2) {
					int chooseOption = endBackground
										.endMenu("res/gfx/Background/P2_win.png");
					if (chooseOption == 0) {
						SDL_RenderClear(renderer); 
						endBackground.FreeTexture(); 
						setup2(); 
						isRunning = true;
					}	
					else if (chooseOption == 2) {
						SDL_RenderClear(renderer);  
						home = true; 						
					}				
				}
				else {
					int chooseOption = endBackground
										.endMenu("res/gfx/Background/tie.png");
					if (chooseOption == 0) {
						setup2(); 
						endBackground.FreeTexture(); 
						isRunning = true;
					}	
					else if (chooseOption == 2) {
						SDL_RenderClear(renderer); 
						endBackground.FreeTexture();  
						home = true; 						
					}			
				}
			}
		} 
	}
}

void Game::gameLoopAI() {
	setupAI(); 
	while (running()) {
		frameStart = SDL_GetTicks(); 
		
		handleEvents(); 
		updateAI(); 
		renderAI(); 

		frameTime = SDL_GetTicks() - frameStart; 
		if (frameDelay > frameTime) {	
			SDL_Delay(frameDelay - frameTime); 
		}
		if (Quit == 1) {
			isRunning = false; 
		}
		else {
			if (!isRunning) {
				if (snakeAI.isWinner() == 1) {	
					int chooseOption = endBackground
										.endMenu("res/gfx/Background/You_win.png");
					if (chooseOption == 0) {
						SDL_RenderClear(renderer); 
						endBackground.FreeTexture(); 
						setupAI(); 
						isRunning = true;
					}
					else if (chooseOption == 2) {
						SDL_RenderClear(renderer); 
						endBackground.FreeTexture();   
						home = true; 						
					}
				}
				else if (snakeAI.isWinner() == 2) {
					int chooseOption = endBackground
										.endMenu("res/gfx/Background/AI_win.png");
					if (chooseOption == 0) {
						SDL_RenderClear(renderer);  
						endBackground.FreeTexture(); 
						setupAI(); 
						isRunning = true;
					}	
					else if (chooseOption == 2) {
						SDL_RenderClear(renderer);   
						endBackground.FreeTexture(); 
						home = true; 						
					}				
				}
				else {
					int chooseOption = endBackground
										.endMenu("res/gfx/Background/tie.png");
					if (chooseOption == 0) {
						SDL_RenderClear(renderer); 
						endBackground.FreeTexture();   
						setupAI(); 
						isRunning = true;
					}	
					else if (chooseOption == 2) {
						SDL_RenderClear(renderer); 
						endBackground.FreeTexture(); 
						home = true; 						
					}			
				}
			}
		} 
	}
}

void Game::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//Shutdown and cleanup the truetype font API.
	TTF_Quit();
	IMG_Quit(); 
	SDL_Quit();
}
