#include "MenuScreen.h"



MenuScreen::MenuScreen(GameState * state, SDL_Renderer * renderer, TTF_Font* Font){
	SDL_Color textColor = { 0, 0, 0, 255 };
	SDL_Surface * textSurface = new SDL_Surface;

	m_currentGameState = state;
	m_renderer = renderer;

	playtexture = init(Font, play_text, playtexture, playRenderQuad, 50, 600);
	onlinetexture = init(Font, online_text, onlinetexture, onlineRenderQuad, 385, 600);
	optiontexture = init(Font, options_text, optiontexture, optionRenderQuad, 720, 600);
	exittexture = init(Font, exit_text, exittexture, exitRenderQuad, 1055, 600);

	TTF_Font* menuFont = TTF_OpenFont("arial.ttf", 150);
	
	titletexture = init(menuFont, title_text, titletexture, titleRenderQuad, 200, 50);

	if (!loadFromFile("banner.png", m_renderer)) {
		printf("Error loading image");
	}

	m_sRect = new SDL_Rect;
	m_dRect = new SDL_Rect;
	m_sRect->x = 0;
	m_sRect->y = 0;
	m_sRect->w = 940;
	m_sRect->h = 198;
	m_dRect->x = 0;
	m_dRect->y = 300;

	gGameController = SDL_GameControllerOpen(0);
	if (gGameController == NULL)
	{
		printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
	}
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

bool MenuScreen::loadFromFile(std::string path, SDL_Renderer* gRenderer) {
	//Free our texture first

	freeTexture();

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
			m_width = loadedSurface->w + 300;
			m_height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	m_texture = newTexture;
	return m_texture != NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	
		
	
}


MenuScreen::~MenuScreen()
{

}


void MenuScreen::update(SDL_Window *window)
{
	bool AButton = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_A);
	bool BButton = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_B);

	if (AButton) {
		*m_currentGameState = GameState::Game;
	}
	else if (BButton) {
		SDL_DestroyWindow(window);
	}
}


void MenuScreen::render(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	SDL_RenderCopy(renderer, playtexture, NULL, &playRenderQuad);
	SDL_RenderCopy(renderer, onlinetexture, NULL, &onlineRenderQuad);
	SDL_RenderCopy(renderer, optiontexture, NULL, &optionRenderQuad);
	SDL_RenderCopy(renderer, exittexture, NULL, &exitRenderQuad);
	SDL_RenderCopy(renderer, titletexture, NULL, &titleRenderQuad);

	m_dRect->w = m_width;
	m_dRect->h = m_height;

	//std::cout << "X= " << m_centre.x << "Y= " << m_centre.y << std::endl;
	SDL_RenderCopyEx(renderer, m_texture, m_sRect, m_dRect, 0, NULL, SDL_FLIP_NONE);

}
