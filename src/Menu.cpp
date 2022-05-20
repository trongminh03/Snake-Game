#include "Menu.hpp" 
#include "TextureManager.hpp"

Menu::Menu() {}

Menu::~Menu() {
	SDL_DestroyTexture(menu);
	SDL_DestroyTexture(infor);
	SDL_DestroyTexture(play);
	SDL_DestroyTexture(exit);
	SDL_DestroyTexture(backButton);
	SDL_DestroyTexture(exitButton); 
	SDL_DestroyTexture(playAgain); 
} 

void Menu::Setup() {
	font = TTF_OpenFont("res/font/SVN-Times New Roman 2 bold.ttf", 35);
	font2 = TTF_OpenFont("res/font/SVN-Times New Roman 2 bold.ttf", 55); 
	/*MENU*/ //MENU: 0: play game, 1: exit, 2: info;
	//dst
	TextureManager::SetPos(pos_menu[PLAY_GAME], Vector2D(290, 220), Vector2D(250, 75)); 
	TextureManager::SetPos(pos_menu[EXIT], Vector2D(360, 320), Vector2D(100, 75)); 
	TextureManager::SetPos(pos_menu[INFOR], Vector2D(570, 190), Vector2D(64, 64)); 
	//texture
	menu = TextureManager::LoadTexture("res/gfx/Background/background.png"); 
	infor = TextureManager::LoadTexture("res/gfx/Button/information.png");
	play = TextureManager::LoadTexture("res/gfx/Button/play.png"); 
	exit = TextureManager::LoadTexture("res/gfx/Button/exit.png"); 

	/*OPTION*/ //OPTION: 0: player1, 1: player2, 3: AI;
	//dst 
	for (int i = 0; i <= 2; i++) {
		TextureManager::SetPos(pos_opt[i], Vector2D(250, 105 + i * 160), Vector2D(300, 130)); 
	}
	//texture
	option = TextureManager::LoadTexture("res/gfx/Background/option_background.png");
	mode[PLAYER_1] = TextureManager::LoadTexture("res/gfx/Button/1P.png");  
	mode[PLAYER_2] = TextureManager::LoadTexture("res/gfx/Button/2P.png"); 
	mode[AI] = TextureManager::LoadTexture("res/gfx/Button/AI.png");

	/*END*/ //END: 0: play gain, 1: exit, 2: back
	//dst
	TextureManager::SetPos(pos_end[PLAY_AGAIN], Vector2D(130, 310), Vector2D(210, 100)); 
	TextureManager::SetPos(pos_end[EXIT], Vector2D(500, 310), Vector2D(210, 100)); 
	TextureManager::SetPos(pos_end[BACK], Vector2D(20, 20), Vector2D(64, 64)); 
	//texture
	backButton = TextureManager::LoadTexture("res/gfx/Button/backButton.png"); 
	exitButton = TextureManager::LoadTexture("res/gfx/Button/exitButton.png"); 
	playAgain = TextureManager::LoadTexture("res/gfx/Button/again.png"); 
	game_score.Setup(GameText::LIGHT_YELLOW_TEXT); 
}

bool Menu::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect) {
	return (x >= rect.x && x <= rect.x + rect.w 
		   	&& y >= rect.y && y <= rect.y + rect.h);
}

int Menu::showMenu() { 
	TextureManager::SetPos(src_menu[0], Vector2D(0, 0), Vector2D(225, 50)); 
	TextureManager::SetPos(src_menu[1], Vector2D(0, 0), Vector2D(78, 50)); 
	TextureManager::SetPos(src_menu[2], Vector2D(0, 0), Vector2D(64, 64)); 
	while (true) {
		SDL_RenderClear(Game::renderer); 
		SDL_RenderCopy(Game::renderer, menu, NULL, NULL);
		SDL_RenderCopy(Game::renderer, play, &src_menu[0], &pos_menu[0]); 
		SDL_RenderCopy(Game::renderer, exit, &src_menu[1], &pos_menu[1]); 
		SDL_RenderCopy(Game::renderer, infor, &src_menu[2], &pos_menu[2]);
		SDL_RenderPresent(Game::renderer);
		while (SDL_PollEvent(&m_event)) {
			switch(m_event.type) {
				case SDL_QUIT: 
					SDL_DestroyTexture(menu); 
					SDL_DestroyTexture(infor); 
					SDL_DestroyTexture(play); 
					SDL_DestroyTexture(exit); 
					return 1;   
				case SDL_MOUSEMOTION: 
					xm = m_event.motion.x; 
					ym = m_event.motion.y;
					if (CheckFocusWithRect(xm, ym, pos_menu[PLAY_GAME])) {
						if (!selected[PLAY_GAME]) {
							selected[PLAY_GAME] = 1; 
							TextureManager::SetPos(src_menu[PLAY_GAME], Vector2D(225, 0), 
												Vector2D(225, 50)); 
						}
					}
					else {
						if (selected[PLAY_GAME]) {
							selected[PLAY_GAME] = 0; 
							TextureManager::SetPos(src_menu[0], Vector2D(0, 0), 
												Vector2D(225, 50)); 
						}
					}

					if (CheckFocusWithRect(xm, ym, pos_menu[EXIT])) {
						if (!selected[EXIT]) {
							selected[EXIT] = 1; 
							TextureManager::SetPos(src_menu[EXIT], Vector2D(78, 0), 
												Vector2D(78, 50)); 
						}
					}
					else {
						if (selected[EXIT]) {
							selected[EXIT] = 0; 
							TextureManager::SetPos(src_menu[EXIT], Vector2D(0, 0), 
												Vector2D(78, 50)); 
						}
					}

					
					if (CheckFocusWithRect(xm, ym, pos_menu[INFOR])) {
						if (!selected[INFOR]) {
							selected[INFOR] = 1; 
							TextureManager::SetPos(src_menu[INFOR], Vector2D(64, 0), 
												Vector2D(64, 64)); 
						}
					}
					else {
						if (selected[INFOR]) {
							selected[INFOR] = 0; 
							TextureManager::SetPos(src_menu[INFOR], Vector2D(0, 0), 
												Vector2D(64, 64)); 
						}
					}
					break;  
				case SDL_MOUSEBUTTONDOWN: 
					xm = m_event.button.x; 
					ym = m_event.button.y;
					if (CheckFocusWithRect(xm, ym, pos_menu[PLAY_GAME])) {
						return 0; 
					}
					if (CheckFocusWithRect(xm, ym, pos_menu[EXIT])) { 
						return 1; 
					}
					if (CheckFocusWithRect(xm, ym, pos_menu[INFOR])) { 
						return 2; 
					}
					break;
				case SDL_KEYDOWN: 
					if (m_event.key.keysym.sym == SDLK_ESCAPE) {
						return 0; 
					}
				default: 
					break; 
			}
		}
	}
	return 1; 
}

int Menu::getNumPlayer() {
	for (int i = 0; i <=2; i++) {
		TextureManager::SetPos(src_opt[i], Vector2D(0, 0), Vector2D(300, 130)); 
	}
	while (true) {
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, option, NULL, NULL);
		for (int i = 0; i <= 2; i++) {
			SDL_RenderCopy(Game::renderer, mode[i], &src_opt[i], &pos_opt[i]); 
		}
		SDL_RenderPresent(Game::renderer);
		while (SDL_PollEvent(&m_event)) {
			switch(m_event.type) {
				case SDL_QUIT: 
					return 0;   
				case SDL_MOUSEMOTION: 
					xm = m_event.motion.x; 
					ym = m_event.motion.y;
					for (int i = 0; i < NUM_PLAYER; i++) {
						if (CheckFocusWithRect(xm, ym, pos_opt[i])) {
							if (!selected[i]) {
								selected[i] = 1; 
								TextureManager::SetPos(src_opt[i], Vector2D(300, 0), 
													Vector2D(300, 130)); 
							}
						}
						else {
							if (selected[i]) {
								selected[i] = 0; 
								TextureManager::SetPos(src_opt[i], Vector2D(0, 0), 
													Vector2D(300, 130));   
							}
						}
					}
					break;  
				case SDL_MOUSEBUTTONDOWN: 
					xm = m_event.button.x; 
					ym = m_event.button.y;
					for (int i = 0; i < NUM_PLAYER; i++) {
						if (CheckFocusWithRect(xm, ym, pos_opt[i])) {
							return i + 1;   
						}
					}
					break;
				case SDL_KEYDOWN: 
					if (m_event.key.keysym.sym == SDLK_ESCAPE) {
						return 4;  
					}
				default: 
					break; 
			}
		}
	}
	return 0; 
}

int Menu::endMenu(const char* path) {
	end = TextureManager::LoadTexture(path); 
	TextureManager::SetPos(src_end[PLAY_AGAIN], Vector2D(0, 0), Vector2D(210, 100)); 
	TextureManager::SetPos(src_end[EXIT], Vector2D(0, 0), Vector2D(210, 100)); 
	TextureManager::SetPos(src_end[BACK], Vector2D(0, 0), Vector2D(64, 64)); 
	while (true) {
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, end, NULL, NULL);
		SDL_RenderCopy(Game::renderer, playAgain, &src_end[PLAY_AGAIN], &pos_end[PLAY_AGAIN]); 
		SDL_RenderCopy(Game::renderer, exitButton, &src_end[EXIT], &pos_end[EXIT]); 
		SDL_RenderCopy(Game::renderer, backButton, &src_end[BACK], &pos_end[BACK]); 
		SDL_RenderPresent(Game::renderer);
		while (SDL_PollEvent(&m_event)) {
			switch(m_event.type) {
				case SDL_QUIT: 
					return 1;   
				case SDL_MOUSEMOTION: 
					xm = m_event.motion.x; 
					ym = m_event.motion.y;

					for (int i = 0; i <= 1; i++) {
						if (CheckFocusWithRect(xm, ym, pos_end[i])) {
							if (!selected_end[i]) {
								selected_end[i] = 1; 
								TextureManager::SetPos(src_end[i], Vector2D(210, 0), 
													Vector2D(210, 100)); 
							}
						}
						else {
							if (selected_end[i]) {
								selected_end[i] = 0; 
								TextureManager::SetPos(src_end[i], Vector2D(0, 0), 
													Vector2D(210, 100));
							}
						}
					}
					if (CheckFocusWithRect(xm, ym, pos_end[BACK])) {
						if (!selected_end[BACK]) {
							selected_end[BACK] = 1; 
							TextureManager::SetPos(src_end[BACK], Vector2D(64, 0), 
												Vector2D(64, 64));  
						}
					}
					else {
						if (selected_end[BACK]) {
							selected_end[BACK] = 0; 
							TextureManager::SetPos(src_end[BACK], Vector2D(0, 0), 
												Vector2D(64, 64)); 
						}
					}
					break;  
				case SDL_MOUSEBUTTONDOWN: 
					xm = m_event.button.x; 
					ym = m_event.button.y;

					for (int i = 0; i <= 1; i++) {
						if (CheckFocusWithRect(xm, ym, pos_end[i])) {
							return i;   
						} 
					}
					if (CheckFocusWithRect(xm, ym, pos_end[BACK])) {
							return 2; 
					}
					break;
				case SDL_KEYDOWN: 
					if (m_event.key.keysym.sym == SDLK_ESCAPE) {
						return 0;  
					}
				default: 
					break; 
			}
		}
	}
	return 1; 
}

int Menu::endMenu(const char* path, const int& score) {
	end = TextureManager::LoadTexture(path);
	game_score.Update(score, "Your score: "); 
	game_score.CreateText();  
	TextureManager::SetPos(src_end[PLAY_AGAIN], Vector2D(0, 0), Vector2D(210, 100)); 
	TextureManager::SetPos(src_end[EXIT], Vector2D(0, 0), Vector2D(210, 100)); 
	TextureManager::SetPos(src_end[BACK], Vector2D(0, 0), Vector2D(64, 64)); 
	while (true) {
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, end, NULL, NULL);
		SDL_RenderCopy(Game::renderer, playAgain, &src_end[PLAY_AGAIN], &pos_end[PLAY_AGAIN]); 
		SDL_RenderCopy(Game::renderer, exitButton, &src_end[EXIT], &pos_end[EXIT]); 
		SDL_RenderCopy(Game::renderer, backButton, &src_end[BACK], &pos_end[BACK]); 
		game_score.Render2(Vector2D(240, 170), Vector2D(340, 100)); 
		SDL_RenderPresent(Game::renderer);
		while (SDL_PollEvent(&m_event)) {
			switch(m_event.type) {
				case SDL_QUIT: 
					return 1;   
				case SDL_MOUSEMOTION: 
					xm = m_event.motion.x; 
					ym = m_event.motion.y;

					for (int i = 0; i <= 1; i++) {
						if (CheckFocusWithRect(xm, ym, pos_end[i])) {
							if (!selected_end[i]) {
								selected_end[i] = 1; 
								TextureManager::SetPos(src_end[i], Vector2D(210, 0), 
													Vector2D(210, 100)); 
							}
						}
						else {
							if (selected_end[i]) {
								selected_end[i] = 0; 
								TextureManager::SetPos(src_end[i], Vector2D(0, 0), 
													Vector2D(210, 100));
							}
						}
					}
					if (CheckFocusWithRect(xm, ym, pos_end[BACK])) {
						if (!selected_end[BACK]) {
							selected_end[BACK] = 1; 
							TextureManager::SetPos(src_end[BACK], Vector2D(64, 0), 
												Vector2D(64, 64));  
						}
					}
					else {
						if (selected_end[BACK]) {
							selected_end[BACK] = 0; 
							TextureManager::SetPos(src_end[BACK], Vector2D(0, 0), 
												Vector2D(64, 64)); 
						}
					}
					break;  
				case SDL_MOUSEBUTTONDOWN: 
					xm = m_event.button.x; 
					ym = m_event.button.y;

					for (int i = 0; i <= 1; i++) {
						if (CheckFocusWithRect(xm, ym, pos_end[i])) {
							return i;   
						} 
					}
					if (CheckFocusWithRect(xm, ym, pos_end[BACK])) {
						return 2; 
					}
					break;
				case SDL_KEYDOWN: 
					if (m_event.key.keysym.sym == SDLK_ESCAPE) {
						return 0;  
					}
				default: 
					break; 
			}
		}
	}
	return 1; 
}

void Menu::FreeTexture() {
	SDL_DestroyTexture(menu);
	SDL_DestroyTexture(infor);
	SDL_DestroyTexture(play);
	SDL_DestroyTexture(exit);
	SDL_DestroyTexture(backButton);
	SDL_DestroyTexture(exitButton); 
	SDL_DestroyTexture(playAgain); 
}