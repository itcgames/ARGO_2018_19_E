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

	void update(bool fscreen);
	void render(SDL_Renderer * renderer);
	SDL_Texture* loadFromFile(std::string path, SDL_Renderer* gRenderer);

private:
	GameState * m_currentGameState;

	vector<string> creditStrings;
	SDL_Renderer *m_renderer;
	vector<SDL_Texture*> textures;
	vector<SDL_Rect*> renderQuads;

	SDL_Texture* m_texture;

	int m_width;
	int m_height;

	SDL_Rect* m_sRect = new SDL_Rect();
	SDL_Rect* m_dRect = new SDL_Rect();

	std::string exit_text = "(B) Exit";
	SDL_Texture* exittexture;
	SDL_Rect exitRenderQuad;

	SDL_GameController * gameController = NULL;

	bool set = false;
};

