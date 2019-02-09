#pragma once
#include "c:\Users\peter\Desktop\ARGO_2018_19_E\src\Menus\State.h"
#include <SDL.h>
#include <SDL_image.h>
#include "State.h"
#include <iostream>
#include <SDL_ttf.h>

class OnlineScreen : State
{
public:
	OnlineScreen(GameState * state, SDL_Renderer * renderer, TTF_Font* Font, SDL_GameController* controller);
	~OnlineScreen();

	void update();
	void render(SDL_Renderer* renderer);

	SDL_Texture* init(TTF_Font* Font, std::string & text, SDL_Texture* texture, SDL_Rect & quad, int x, int y);

private: 
	GameState * m_currentGameState;

	std::string title_text = "Lobby";
	std::string exit_text = "(B) Exit";

	SDL_Renderer *m_renderer;

	SDL_Texture* exittexture;
	SDL_Texture* titletexture;

	SDL_Rect exitRenderQuad;
	SDL_Rect titleRenderQuad;

	SDL_GameController* gGameController = NULL;
};

