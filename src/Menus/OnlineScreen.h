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
	OnlineScreen(GameState * state, SDL_Renderer * renderer, TTF_Font* Font, SDL_GameController* controller, Client * client, bool * online);
	SDL_Texture* loadFromFile(std::string path, SDL_Renderer* gRenderer);
	~OnlineScreen();

	void update();
	void render(SDL_Renderer* renderer);

	void fillLobby();
	void addMember();
	void removeMember();

	SDL_Texture* init(TTF_Font* Font, std::string & text, SDL_Texture* texture, SDL_Rect & quad, int x, int y, SDL_Color color);
	void resetMenu();

	Client * m_client;

	int m_lobbySize = 0;
private: 
	GameState * m_currentGameState;

	SDL_Renderer *m_renderer;

	SDL_Texture* exittexture;
	SDL_Texture* titletexture;
	SDL_Texture* playtexture;
	SDL_Texture* noServerTexture;

	SDL_Rect exitRenderQuad;
	SDL_Rect titleRenderQuad;
	SDL_Rect playRenderQuad;
	SDL_Rect noServerRenderQuad;


	SDL_GameController* gGameController = NULL;

	std::vector<std::string> m_strings;
	std::vector<SDL_Texture*> m_textures;
	std::vector<SDL_Rect> m_quads;
	std::vector<int> m_index;

	TTF_Font * m_font;
	TTF_Font * m_menuFont;

	SDL_Rect m_BGRect;


	bool m_joined = false;
	bool *m_online = new bool(false);
	bool m_ready2Play;
	bool m_firstRunThrough = false;
	Packet m_pack;

	int responseTimer = 0;
	int NO_RESPONSE = 12000;


	SDL_Texture* m_texture;
	int m_width;
	int m_height;

	SDL_Rect * m_sRectangle;
	SDL_Rect * m_dRectangle;

	bool inAnimation = true;
	bool outAnimation = false;

	double animationTimer = 0;

	std::string lastButton = "";
};

