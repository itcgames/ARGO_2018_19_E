#ifndef GAME
#define GAME

#include <iostream>

#include "Menus/SplashScreen.h"
#include "Menus/CreditScreen.h"
#include "Menus/MenuScreen.h"
#include "Menus/OptionScreen.h"
#include "Menus/OnlineScreen.h"
#include "Menus/playScreen.h"



using namespace std;


class Game {
	
public:
	Game();
	~Game();

	void run();
	//SDL_Texture* loadTexture(std::string file);

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

	/*SDL_Rect* getCamera();
	c2v* getCameraCentre();
	void setCameraCentre(float x, float y);
	void setCameraPosition(int x, int y);*/
	void initialiseText(std::string message);

private:

	void update();
	void render();

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	
	bool exit;
	
	SplashScreen * m_splash;
	MenuScreen * m_menu;
	OptionScreen * m_options;
	CreditScreen * m_credits;
	OnlineScreen * m_onlineScreen;
	PlayScreen * m_playScreen;
	SDL_Rect m_screenSize;

	void setUpController();
	
	SDL_Surface* m_screen;
	SDL_GameController* gGameController = NULL;

	Client * m_client;

	bool *m_online = new bool(false);

	TTF_Font* Font;

	std::string round_text;
	SDL_Texture* text;
	SDL_Rect renderQuad;
	SDL_Color textColor = { 188, 110, 121, 255 };
	SDL_Surface * textSurface = new SDL_Surface;
	SDL_Event event;
};



#endif // !GAME
