#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "State.h"
#include <iostream>
#include <vector>
#include <SDL_ttf.h>

using namespace std;

class CreditScreen : State
{
public:
	CreditScreen(GameState * state, SDL_Renderer * renderer, TTF_Font* Font, TTF_Font* menuFont, SDL_GameController* controller);
	~CreditScreen() {};

	void update();
	void render(SDL_Renderer * renderer);

private:
	GameState * m_currentGameState;

	vector<string> creditStrings;
	SDL_Renderer *m_renderer;
	vector<SDL_Texture*> textures;
	vector<SDL_Rect*> renderQuads;

	std::string exit_text = "(B) Exit";
	SDL_Texture* exittexture;
	SDL_Rect exitRenderQuad;

	SDL_GameController * gameController = NULL;
};

