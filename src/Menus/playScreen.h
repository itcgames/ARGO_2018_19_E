#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "../Systems/HealthSystem.h"
#include "../Systems/ControlSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AISystem.h"
#include "../Systems/PhysicsSystem.h"
#include "../Systems/GunSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/GrenadeSystem.h"
#include "../Systems/RestartSystem.h"
#include "../Systems/AnimationsSystem.h"
#include "../Systems/NetworkSystem.h"

#include "../Player.h"
#include "../Hand.h"
#include "../AI.h"
#include "../Gun.h"
#include "../MapLoader.h"
#include "../Light.h"

#include "../ObserverPattern/AudioObserver.h"

#include "../Client/Client.h"

#include <SDL_ttf.h>

class PlayScreen 
{
public:
	PlayScreen(SDL_Renderer * renderer, TTF_Font* font);
	~PlayScreen() {}

	void update(bool * online, SDL_Event event, int size, Client * client);
	void render(SDL_Renderer * renderer);

	void initialise(bool online, int size, int num);

	AudioObserver* m_audioObserver;
	
	void checkRoundOver();
	void initialiseText(std::string message);

	std::vector<Hand *> m_leftHands;
	std::vector<Hand *> m_rightHands;
	std::vector<Player *> m_players;
	std::vector<AI *> m_aiCharacters;
	std::vector<Player *> m_networkCharacters;
	Gun* pistol;
	Gun* shotgun;
	Gun* juicer;
	Gun* grenade;
	std::vector<Entity*> m_ents;
	Light* testLight;

	SpriteComponent * m_backgroundSprite;

	HealthSystem m_hs;
	ControlSystem m_cs;
	RenderSystem m_rs;
	GunSystem m_guns;


	PhysicsSystem m_ps;
	AISystem m_ais;
	CollisionSystem m_collSys;
	GrenadeSystem m_grenadeSys;
	AnimationsSystem m_animationsSys;
	RestartSystem m_restartSys;
	NetworkSystem m_netSystem;
	

	SDL_Rect* m_camera;
	c2v* m_cameraCentre;

	MapLoader* m_map;

	int m_roundCounter = 0;
	const int ROUND_OVER = 100.0f;
	std::string round_text;
	SDL_Texture* text;
	SDL_Rect renderQuad;
	SDL_Color textColor = { 188, 110, 121, 255 };
	SDL_Surface * textSurface = new SDL_Surface;

	bool m_drawRoundText = false;

	SDL_Renderer * m_renderer;
	

	TTF_Font* Font;

	bool m_startGame = true;
};