#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "State.h"
#include <iostream>
#include <SDL_ttf.h>

class SplashScreen : State
{
public:
	SplashScreen(GameState * state, SDL_Renderer * renderer, TTF_Font* Font);
	~SplashScreen();
	void update();
	void render(SDL_Renderer * renderer);
private:
	GameState * m_currentGameState;

	float m_counter = 0;
	float m_switchTimer = 255;

	float m_redCount = 0;
	float m_blueCount = 0;
	float m_greenCount = 0;
	std::string splash_text = "ARGO";
	SDL_Renderer *m_renderer;
	SDL_Texture* text;
	SDL_Rect renderQuad;
};

