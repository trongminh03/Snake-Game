#include "Timer.hpp" 

Timer::Timer() {}

Timer::~Timer() {}

void Timer::Setup() {
	font = TTF_OpenFont("res/font/EvilEmpire-4BBVK.ttf", 35);
	time_text.SetColor(GameText::WHITE_TEXT);  
}

void Timer::Update() {
	string strTime = "Timer: "; 
	time_val = 60 - (SDL_GetTicks() -  Game::time_0) / 1000; 
	//60 seconds countdown 
	val_str_time = to_string(time_val); 
	strTime += val_str_time;
	time_text.SetText(strTime); 
}

void Timer::Render() {
	dst_timer.x = 340; 
	dst_timer.y = 550;
	dst_timer.w = 150; 
	dst_timer.h = 50; 
	time_text.CreateGameText(font, dst_timer); 
}

Uint32 Timer::getTimeVal() {
	return time_val; 
}

void Timer::Free() {
	time_text.Free(); 
}