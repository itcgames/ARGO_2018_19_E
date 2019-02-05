#ifndef GAME
#define GAME

#include <iostream>
#include "./Systems/HealthSystem.h"
#include "./Systems/ControlSystem.h"
#include "./Systems/RenderSystem.h"
#include "./Systems/AISystem.h"

using namespace std;

class Game {

public:
	Game();
	~Game();

	void run();
	SDL_Texture* loadTexture(std::string file);
private:

	void update();
	void render();
	void initialise();

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Event event;
	bool exit;

	Entity* m_player;
	Entity* m_cat;
	Entity* m_alien;
	Entity* m_dog;

	HealthSystem m_hs;
	ControlSystem m_cs;
	RenderSystem m_rs;
	AISystem m_as;

};



#endif // !GAME
