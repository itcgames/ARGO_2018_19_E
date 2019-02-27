#include "MenuScreen.h"



MenuScreen::MenuScreen(GameState * state, SDL_Renderer * renderer, TTF_Font* Font, SDL_GameController* controller){
	SDL_Color textColor = { 0, 0, 0, 255 };
	SDL_Surface * textSurface = new SDL_Surface;
	gGameController = controller;

	m_currentGameState = state;
	m_renderer = renderer;

	playtexture = init(Font, play_text, playtexture, playRenderQuad, 50, 600);
	onlinetexture = init(Font, online_text, onlinetexture, onlineRenderQuad, 385, 600);
	optiontexture = init(Font, options_text, optiontexture, optionRenderQuad, 720, 600);
	exittexture = init(Font, exit_text, exittexture, exitRenderQuad, 1055, 600);

	TTF_Font* menuFont = TTF_OpenFont("zorque.ttf", 150);
	
	titletexture = init(menuFont, title_text, titletexture, titleRenderQuad, 200, 50);

	m_texture = loadFromFile("assets/art/environment/banner2.1.png", m_renderer);

	m_texture2 = loadFromFile("assets/art/environment/banner1.png", m_renderer);
	
	m_texture3 = loadFromFile("assets/art/environment/MainMenu.png", m_renderer);

	std::cout << "CALLED" << std::endl;
	m_drawTexture = m_texture;
	
	m_sRectangle = new SDL_Rect;
	m_dRectangle = new SDL_Rect;
	m_sRectangle->x = 0;
	m_sRectangle->y = 0;
	m_sRectangle->w = 1200;
	m_sRectangle->h = 700;
	m_dRectangle->x = 0;
	m_dRectangle->y = -700;


	m_sRect = new SDL_Rect;
	m_dRect = new SDL_Rect;
	m_sRect->x = 0;
	m_sRect->y = 0;
	m_sRect->w = 0;
	m_sRect->h = 240;
	m_dRect->x = 0;
	m_dRect->y = -480;

	
}

SDL_Texture* MenuScreen::init(TTF_Font* Font, std::string & text, SDL_Texture* texture, SDL_Rect & quad, int x, int y) {
	SDL_Surface * textSurface = new SDL_Surface;
	SDL_Color textColor = { 0, 0, 0, 255 };
	
	textSurface = TTF_RenderText_Solid(Font, text.c_str(), textColor);
	texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

	int width = textSurface->w;
	int height = textSurface->h;
	SDL_FreeSurface(textSurface);
	quad = { x, y, width, height };
	return texture;
}

void MenuScreen::freeTexture() {

	//Free texture if it exists
	if (m_texture != NULL)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
		m_width = 0;
		m_height = 0;
	}
}

SDL_Texture* MenuScreen::loadFromFile(std::string path, SDL_Renderer* gRenderer) {

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			if (count < 2)
			{
				m_width2 = loadedSurface->w + 400;
				m_height2 = loadedSurface->h;
			}
			else
			{
				m_width = loadedSurface->w;
				m_height = loadedSurface->h;
			}
			
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	count++;
	
	return newTexture;
}


MenuScreen::~MenuScreen()
{

}

void MenuScreen::resetMenu()
{
	firstTime = true;
	lastButton = "";
	transitionTimer = 0;
	buttonTimer = 0;
	m_startTransition = false;
	m_startInTransition = true;
	m_dRect->y = -480;
	m_dRectangle->y = -700;
}


void MenuScreen::update(SDL_Window *window)
{
	bool AButton = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_A);
	bool BButton = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_B);
	bool XButton = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_X);
	bool YButton = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_Y);
	bool StartButton = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_START);


	if (m_startInTransition)
	{
		m_dRect->y += 10;
		m_dRectangle->y += 10;

		if (m_dRectangle->y >= 0)
		{
			m_startInTransition = false;
			m_dRectangle->y = 0;
			m_dRect->y = 240;
		}
	}
	if (!m_startInTransition) {
		if (AButton && !firstTime) {
			firstTime = true;
			buttonTimer = 0;
			m_startTransition = true;
			lastButton = "A";
			//*m_currentGameState = GameState::Game;
		}
		else if (XButton && !firstTime) {
			firstTime = true;
			buttonTimer = 0;
			m_startTransition = true;
			lastButton = "X";
		}
		else if (YButton && !firstTime) {
			firstTime = true;
			buttonTimer = 0;
			m_startTransition = true;
			lastButton = "Y";
		}
		else if (BButton && !firstTime) {
			SDL_DestroyWindow(window);
		}
		else if (StartButton && !firstTime) {
			firstTime = true;
			buttonTimer = 0;
			m_toggleFS = true;
		}
	}

	buttonTimer++;

	if (buttonTimer > setSecondTime)
		firstTime = false;

	if (m_drawTexture == m_texture) {

		if (m_sRect->w < 940) {
			m_sRect->w += 3;
		}
		else {
			m_sRect->x = 940;
			m_drawTexture = m_texture2;
		}
	}
	else {

		if (m_sRect->x > 0) {
			m_sRect->x -= 3;
		}
		else {
			m_sRect->w = 0;
			m_drawTexture = m_texture;
		}
	}

	if (m_startTransition)
	{
		m_dRect->y -= 10;
		m_dRectangle->y -= 10;
		transitionTimer++;
	}

	if (transitionTimer > 100 && lastButton == "A")
	{
		resetMenu();
		*m_currentGameState = GameState::Game;
	}
	else if (transitionTimer > 100 && lastButton == "X")
	{
		resetMenu();
		*m_currentGameState = GameState::Online;
	}
	else if (transitionTimer > 100 && lastButton == "Y")
	{
		resetMenu();
		*m_currentGameState = GameState::Credits;
	}
	
	std::cout << transitionTimer << std::endl;
}


void MenuScreen::render(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	m_dRectangle->w = m_width;
	m_dRectangle->h = m_height;
	SDL_RenderCopyEx(renderer, m_texture3, m_sRectangle, m_dRectangle, 0, NULL, SDL_FLIP_NONE);

	m_dRect->w = m_width2;
	m_dRect->h = m_height2;
	SDL_RenderCopyEx(renderer, m_drawTexture, m_sRect, m_dRect, 0, NULL, SDL_FLIP_NONE);

}
