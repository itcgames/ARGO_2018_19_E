#include "OnlineScreen.h"


OnlineScreen::OnlineScreen(GameState * state, SDL_Renderer * renderer, TTF_Font * Font, SDL_GameController* controller) {

	m_currentGameState = state;
	gGameController = controller;
	m_renderer = renderer;

	SDL_Color textColor = { 0, 0, 0, 255 };
	SDL_Surface * textSurface = new SDL_Surface;

	exittexture = init(Font, exit_text, exittexture, exitRenderQuad, 1055, 600);

	TTF_Font* menuFont = TTF_OpenFont("arial.ttf", 150);

	titletexture = init(menuFont, title_text, titletexture, titleRenderQuad, 200, 50);

}

OnlineScreen::~OnlineScreen() {}

void OnlineScreen::update() {
	bool BButton = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_B);

	if (BButton) {
		*m_currentGameState = GameState::Menu;
	}
}

void OnlineScreen::render(SDL_Renderer * renderer) {
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

	SDL_RenderCopy(renderer, exittexture, NULL, &exitRenderQuad);
	SDL_RenderCopy(renderer, titletexture, NULL, &titleRenderQuad);

}



SDL_Texture * OnlineScreen::init(TTF_Font * Font, std::string & text, SDL_Texture * texture, SDL_Rect & quad, int x, int y) {
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
