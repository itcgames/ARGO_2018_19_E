#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "State.h"
#include <iostream>
#include <SDL_ttf.h>

class SplashScreen : State
{
public:
	SplashScreen(GameState * state, SDL_Renderer * renderer, TTF_Font* Font, TTF_Font * subFont);
	SDL_Texture* loadFromFile(std::string path, SDL_Renderer* gRenderer);
	~SplashScreen();
	void update();
	void animateScreen();
	void render(SDL_Renderer * renderer);
private:
	GameState * m_currentGameState;

	float m_counter = 0;
	float m_switchTimer = 255;

	float m_redCount = 0;
	float m_blueCount = 0;
	float m_greenCount = 0;
	std::string splash_text = "PRESTIGE WORLDWIDE.";
	std::string splash_textTwo = "AN UNPLAYABLE GAME.";
	SDL_Renderer *m_renderer;
	SDL_Texture* text;
	SDL_Texture* textTwo;
	SDL_Rect renderQuad;
	SDL_Rect renderQuadTwo;

	SDL_Texture * m_staticTexture;

	int m_width;
	int m_height;

	SDL_Rect* m_sRect;
	SDL_Rect * m_staticRect;

	double m_alpha = 160;

	bool animateIn = true;
	bool animateOut = false;

	bool firstlanded = false;
	bool secondlanded = false;

	double m_textAlpha = 255;
	int counter = 0;
};

