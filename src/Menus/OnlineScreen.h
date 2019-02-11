#pragma once
#include "State.h"
#include <SDL.h>
#include <SDL_image.h>
#include "State.h"
#include <iostream>
#include <SDL_ttf.h>
#include "../Client/Client.h"

#include <vector>

class OnlineScreen : State
{
public:
	OnlineScreen(GameState * state, SDL_Renderer * renderer, TTF_Font* Font, SDL_GameController* controller, Client * client);
	~OnlineScreen();

	void update();
	void render(SDL_Renderer* renderer);

	SDL_Texture* init(TTF_Font* Font, std::string & text, SDL_Texture* texture, SDL_Rect & quad, int x, int y);

	Client * m_client;
private: 
	GameState * m_currentGameState;

	SDL_Renderer *m_renderer;

	SDL_Texture* exittexture;
	SDL_Texture* titletexture;

	SDL_Rect exitRenderQuad;
	SDL_Rect titleRenderQuad;

	SDL_GameController* gGameController = NULL;

	std::vector<std::string> m_strings;
	std::vector<SDL_Texture*> m_textures;
	std::vector<SDL_Rect> m_quads;

	TTF_Font * m_font;

	bool m_joined = false;
};

