#include "SplashScreen.h"

SplashScreen::SplashScreen(GameState * state, SDL_Renderer * renderer, TTF_Font* Font, TTF_Font* subFont) : m_currentGameState(state), m_renderer(renderer){
	
	
	SDL_Color textColor = { 0, 0, 0, 255 };
	SDL_Surface * textSurface = new SDL_Surface;
	textSurface = TTF_RenderText_Solid(Font, splash_text.c_str(), textColor);
	text = SDL_CreateTextureFromSurface(m_renderer, textSurface);
	int text_width = textSurface->w;
	int text_height = textSurface->h;
	SDL_FreeSurface(textSurface);
	renderQuad = { 100, -60, text_width, text_height };

	textSurface = TTF_RenderText_Solid(subFont, splash_textTwo.c_str(), textColor);
	textTwo = SDL_CreateTextureFromSurface(m_renderer, textSurface);
	int text_widthTwo = textSurface->w;
	int text_heightTwo = textSurface->h;
	SDL_FreeSurface(textSurface);
	renderQuadTwo = { 200, 700, text_widthTwo, text_heightTwo };

	m_staticTexture = loadFromFile("assets/art/environment/static.png", m_renderer);



	
	

	m_staticRect = new SDL_Rect();
	m_sRect = new SDL_Rect;
	m_staticRect->x = 0;
	m_staticRect->y = 0;
	m_sRect->x = 0;
	m_sRect->y = 0;
	m_sRect->w = 1200;
	m_sRect->h = 700;

}


SDL_Texture* SplashScreen::loadFromFile(std::string path, SDL_Renderer* gRenderer) {

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
		
				m_width = loadedSurface->w;
				m_height = loadedSurface->h;
			

		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}



SplashScreen::~SplashScreen() {


}


void SplashScreen::update() {

	if (renderQuad.y < 250)
	{
		renderQuad.y += 4;
	}
	else
	{
		firstlanded = true;
	}
	if (renderQuadTwo.y > 350)
	{
		renderQuadTwo.y -= 4;
	}
	else
	{
		secondlanded = true;
	}

	if (firstlanded && secondlanded)
	{
		counter++;
		
	}
	if (counter > 50)
	{
		if (m_textAlpha >= 0)
		{
			m_textAlpha -= 2;
		}
		
	}
	

	if( m_counter < m_switchTimer) {
		m_counter++;
		m_redCount = (m_counter / m_switchTimer) * 188;
		m_blueCount = (m_counter / m_switchTimer) * 110;
		m_greenCount = (m_counter / m_switchTimer) * 121;
	}
	else {
		*m_currentGameState = GameState::Menu;
	}
	animateScreen();
}


void SplashScreen::animateScreen()
{
	if (animateIn) {
		if (m_alpha <= 200)
		{
			m_alpha += 20;
		}
		else
		{
			m_alpha = 200;
			animateIn = false;
			animateOut = true;
		}
	}
	if (animateOut)
	{
		if (m_alpha >= 160)
		{
			m_alpha -= 20;
		}
		else
		{
			m_alpha = 160;
			animateIn = true;
			animateOut = false;
		}
	}
}


void SplashScreen::render(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_SetTextureAlphaMod(m_staticTexture, m_alpha);

	m_staticRect->w = m_width;
	m_staticRect->h = m_height;

	SDL_RenderCopyEx(renderer, m_staticTexture, m_sRect, m_staticRect, 0, NULL, SDL_FLIP_NONE);
	//SDL_SetRenderDrawColor(renderer, m_redCount, m_blueCount, m_greenCount, 255);

	SDL_SetTextureAlphaMod(text, m_textAlpha);
	SDL_SetTextureAlphaMod(textTwo, m_textAlpha);

	SDL_RenderCopy(renderer, text, NULL, &renderQuad);
	SDL_RenderCopy(renderer, textTwo, NULL, &renderQuadTwo);

}