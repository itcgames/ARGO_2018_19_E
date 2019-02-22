#include "SplashScreen.h"

SplashScreen::SplashScreen(GameState * state, SDL_Renderer * renderer, TTF_Font* Font) : m_currentGameState(state), m_renderer(renderer){
	
	
	SDL_Color textColor = { 188, 110, 121, 255 };
	SDL_Surface * textSurface = new SDL_Surface;
	textSurface = TTF_RenderText_Solid(Font, splash_text.c_str(), textColor);
	text = SDL_CreateTextureFromSurface(m_renderer, textSurface);
	int text_width = textSurface->w;
	int text_height = textSurface->h;
	SDL_FreeSurface(textSurface);
	renderQuad = { 150, 200, text_width, text_height };
}


SplashScreen::~SplashScreen() {


}


void SplashScreen::update() {

	if( m_counter < m_switchTimer) {
		m_counter++;
		m_redCount = (m_counter / m_switchTimer) * 188;
		m_blueCount = (m_counter / m_switchTimer) * 110;
		m_greenCount = (m_counter / m_switchTimer) * 121;
	}
	else {
		*m_currentGameState = GameState::Menu;
	}
}


void SplashScreen::render(SDL_Renderer * renderer)
{

	SDL_SetRenderDrawColor(renderer, m_redCount, m_blueCount, m_greenCount, 255);
	SDL_RenderCopy(renderer, text, NULL, &renderQuad);

}