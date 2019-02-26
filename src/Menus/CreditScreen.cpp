#include "CreditScreen.h"



CreditScreen::CreditScreen(GameState * state, SDL_Renderer * renderer, TTF_Font* Font, TTF_Font* menuFont, SDL_GameController* controller) : m_currentGameState(state), m_renderer(renderer) {
	gameController = controller;
	
	SDL_Color textColor = { 50, 50, 50, 255 };
	SDL_Surface * textSurface = new SDL_Surface;

	creditStrings.push_back("Brendan Horlick");
	creditStrings.push_back("Simon Dowling");
	creditStrings.push_back("James Condon");
	creditStrings.push_back("Peter Daly");
	creditStrings.push_back("Jemma Corrigan Coules ");
	creditStrings.push_back("Stephen Kinsella");
	creditStrings.push_back("                ");
	creditStrings.push_back("Thanks for playing!");

	for (int i = 0; i < creditStrings.size(); i++) {
		textSurface = TTF_RenderText_Solid(Font, creditStrings.at(i).c_str(), textColor);
		textures.push_back(SDL_CreateTextureFromSurface(m_renderer, textSurface));
		int text_width = textSurface->w;
		int text_height = textSurface->h;
		SDL_FreeSurface(textSurface);
		renderQuads.push_back(new SDL_Rect{ 600 - (text_width / 2), 650 + (i * 150), text_width, text_height });
	}
	

	textSurface = TTF_RenderText_Solid(menuFont, exit_text.c_str(), textColor);
	exittexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

	int width = textSurface->w;
	int height = textSurface->h;
	SDL_FreeSurface(textSurface);
	exitRenderQuad = { 1055, 600, width, height };

	m_dRect->x = 0;
	m_dRect->y = 0;
	m_dRect->w = 1200;
	m_dRect->h = 700;

	m_sRect->x = 0;
	m_sRect->y = 0;
	m_sRect->w = 1200;
	m_sRect->h = 700;

	m_texture = loadFromFile("assets/art/environment/credits.png", renderer);
	
}


void CreditScreen::update() {
	for (int i = 0; i < renderQuads.size(); i++) {
		renderQuads.at(i)->w = renderQuads.at(i)->y ;
		renderQuads.at(i)->x = 600 - (renderQuads.at(i)->w / 2);
		renderQuads.at(i)->y -= 1;
		if (renderQuads.at(i)->y < 0) {
			renderQuads.at(i)->y = 850 + (4 * 150);
		}
	}

	bool BButton = SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_B);

	if (BButton) {
		for (int i = 0; i < renderQuads.size(); i++) {
			renderQuads.at(i)->y = 650 + (i * 150);
		}
		*m_currentGameState = GameState::Menu;
	}
}

SDL_Texture* CreditScreen::loadFromFile(std::string path, SDL_Renderer* gRenderer) {

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


	return newTexture;
}


void CreditScreen::render(SDL_Renderer * renderer)
{
	SDL_RenderCopyEx(renderer, m_texture, m_sRect, m_dRect, 0, NULL, SDL_FLIP_NONE);

	SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
	for (int i = 0; i < creditStrings.size(); i++) {
		SDL_RenderCopy(renderer, textures.at(i), NULL, renderQuads.at(i));
	}
	SDL_RenderCopy(renderer, exittexture, NULL, &exitRenderQuad);

	
}