#ifndef GAME
#define GAME

#include <iostream>
#include "./Systems/HealthSystem.h"
#include "./Systems/ControlSystem.h"
#include "./Systems/RenderSystem.h"
#include "./Systems/AISystem.h"
#include "./Systems/PhysicsSystem.h"
#include "./Systems/GunSystem.h"
#include "./Systems/CollisionSystem.h"
#include "./Systems/GrenadeSystem.h"
#include "Menus/SplashScreen.h"
#include "Menus/CreditScreen.h"
#include "Menus/MenuScreen.h"
#include "Menus/OptionScreen.h"
#include "Menus/OnlineScreen.h"
#include "Components/SpriteComponent.h"

#include "Player.h"
#include "Hand.h"
#include "AI.h"
#include "Gun.h"
#include "MapLoader.h"


using namespace std;


class Game {
	
public:
	Game();
	~Game();

	void run();
	SDL_Texture* loadTexture(std::string file);

	GameState * m_currentGameState;
	GameState m_previousGameState;
	void setGameState(GameState gameState);

	SDL_Renderer * getScreen() const { return m_renderer; }

	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	static Game* s_pInstance;

	void setUpController();

	SDL_Rect* getCamera();
	c2v* getCameraCentre();
	void setCameraCentre(float x, float y);
	void setCameraPosition(int x, int y);

private:

	void update();
	void render();
	void initialise();

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Event event;
	bool exit;

	MapLoader* m_map;

	Player* p;
	Hand* h1;
	Hand* h2;
	AI *ai;
	Gun* pistol;
	Gun* shotgun;
	Gun* grenade;
	std::vector<Entity*> m_ents;

	SpriteComponent* m_backgroundSprite;

	HealthSystem m_hs;
	ControlSystem m_cs;
	RenderSystem m_rs;
	GunSystem m_guns;
	
	
	PhysicsSystem m_ps;
	AISystem m_ais;
	CollisionSystem m_collSys;
	GrenadeSystem m_grenadeSys;

	SDL_Rect m_screenSize;

	SDL_Rect* m_camera;
	c2v* m_cameraCentre;


	SplashScreen * m_splash;
	MenuScreen * m_menu;
	OptionScreen * m_options;
	CreditScreen * m_credits;
	OnlineScreen * m_onlineScreen;
	


	
	SDL_Surface* m_screen;
	SDL_GameController* gGameController = NULL;

	Client * m_client;

	bool *m_online = new bool(false);
};



#endif // !GAME
