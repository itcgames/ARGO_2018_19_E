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
#include "Menus/SplashScreen.h"
#include "Menus/CreditScreen.h"
#include "Menus/MenuScreen.h"
#include "Menus/OptionScreen.h"
#include "Components/SpriteComponent.h"

#include "Player.h"
#include "Hand.h"
#include "AI.h"
#include "Gun.h"
#include "MapLoader.h"


using namespace std;

enum class GameState
{
	None,
	Splash,
	Menu,
	Options,
	Game,
	Credits,
	End
};
class Game {

public:
	Game();
	~Game();

	void run();
	SDL_Texture* loadTexture(std::string file);

	GameState m_currentGameState;
	GameState m_previousGameState;
	void setGameState(GameState gameState);

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
	Hand* h;
	AI *ai;
	Gun* pistol;
	std::vector<Entity*> m_ents;

	SpriteComponent* m_backgroundSprite;

	HealthSystem m_hs;
	ControlSystem m_cs;
	RenderSystem m_rs;
	GunSystem m_guns;
	PhysicsSystem m_ps;
	AISystem m_ais;
	CollisionSystem m_collSys;

	SDL_Rect m_screenSize;


	SplashScreen * m_splash;
	MenuScreen * m_menu;
	OptionScreen * m_options;
	CreditScreen * m_credits;
};



#endif // !GAME
