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

#include "../Entity.h"
#include "../Player.h"
#include "../Hand.h"
#include "../AI.h"
#include "../Gun.h"
#include "../MapLoader.h"
#include "../Light.h"

#include "../ObserverPattern/AudioObserver.h"
#include "../Camera.h"

#include "../Client/Client.h"

#include <SDL_ttf.h>

class PlayScreen 
{
public:
	PlayScreen(SDL_Renderer * renderer, TTF_Font* font);
	~PlayScreen() {}

	void update(bool * online, SDL_Event event, int size, Client * client);
	void render(SDL_Renderer * renderer);

	void sendPacket(Entity * ent, Client * client);

	void initialise(bool online, int size, int num);

	AudioObserver* m_audioObserver;
	
	void checkRoundOver();
	bool onlineRoundOver();
	void endRound();
	void initialiseText(std::string message, int index, int y);// SDL_Texture* texture, SDL_Rect* rect, int y);

	int gunAmount = 1;

	void deleteGuns();
	void spawnGuns();

	Camera* m_camera;
	SDL_Rect* m_focusPoint;
	SDL_Rect* m_offset;
	std::vector<c2v> m_playerPositions;

	std::vector<Hand *> m_leftHands;
	std::vector<Hand *> m_rightHands;
	std::vector<Player *> m_players;
	std::vector<AI *> m_aiCharacters;
	std::vector<Player *> m_networkCharacters;

	std::vector<Entity*> m_Gunents;
	std::vector<Entity*> m_playerents;
	std::vector<Gun*> m_guns;

	Light* testLight;

	SpriteComponent * m_backgroundSprite;

	HealthSystem m_hs;
	ControlSystem m_cs;
	RenderSystem m_rs;
	GunSystem m_gunSys;


	PhysicsSystem m_ps;
	AISystem m_ais;
	CollisionSystem m_collSys;
	GrenadeSystem m_grenadeSys;
	AnimationsSystem m_animationsSys;
	RestartSystem m_restartSys;
	NetworkSystem m_netSystem;

	MapLoader* m_map;

	int m_roundCounter = 0;
	const int ROUND_OVER = 100.0f;
	std::string round_text;
	SDL_Texture* text;
	SDL_Rect* renderQuad;
	std::string winner_text;
	SDL_Texture* w_text;
	SDL_Rect * winnerRenderQuad;
	SDL_Color textColor = { 211,211,211, 255 };
	SDL_Surface * textSurface = new SDL_Surface;

	bool m_drawRoundText = false;

	SDL_Renderer * m_renderer;
	

	TTF_Font* Font;

	bool m_startGame = true;

	Packet lastPacket;

	bool* m_online = false;

	bool m_multiplayer = false;

	bool m_roundEnd = false;

	bool m_drawTimer = false;

private: 
	int m_gunCounter = 0;
	const int SPAWN_NEW_GUN = 1000;
	float m_screenScale = 1.0f;

	int m_cameraCount = 0;
	const int TIME_BETWEEN_CAMERA_CHANGES = 36;

	bool m_startThrow = false;
	int m_throwTimer = 0;
	const int STOP_THROW = 4;

	c2v m_windowScale{ 0.69f, 0.5f };
	int randNum = 0;

	Client * m_client;

	SDL_Rect m_BGRect;

	int m_timerCounter = 0;
	int m_timer = 5;
};