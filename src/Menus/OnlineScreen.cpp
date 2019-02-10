#include "OnlineScreen.h"


OnlineScreen::OnlineScreen(GameState * state, SDL_Renderer * renderer, TTF_Font * Font, SDL_GameController* controller, Client * client) {

	m_currentGameState = state;
	gGameController = controller;
	m_renderer = renderer;

	SDL_Color textColor = { 0, 0, 0, 255 };
	SDL_Surface * textSurface = new SDL_Surface;

	m_font = Font;

	m_strings.push_back("Lobby");
	m_strings.push_back("(B) Exit");

	m_textures.push_back(titletexture);
	m_textures.push_back(exittexture);

	m_quads.push_back(titleRenderQuad);
	m_quads.push_back(exitRenderQuad);

	m_textures[1] = init(Font, m_strings[1], m_textures[1], m_quads[1], 1055, 600);

	TTF_Font* menuFont = TTF_OpenFont("arial.ttf", 150);

	m_textures[0] = init(menuFont, m_strings[0], m_textures[0], m_quads[0], 350, 50);

	m_client = client;
	if (m_client->run()) {
		m_client->sendMessage("Join, Hello,");
	}
}

OnlineScreen::~OnlineScreen() {}

void OnlineScreen::update() {
	bool BButton = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_B);

	if (BButton) {
		*m_currentGameState = GameState::Menu;
	}

	m_client->receive();
	if (m_client->number != 0 && !m_joined) {
		SDL_Texture* playertexture;
		SDL_Rect playerRenderQuad;
		m_textures.push_back(playertexture);
		m_quads.push_back(playerRenderQuad);
		int num = m_client->number;
		std::string text = "Player: " + std::to_string(num);
		m_strings.push_back(text);

		m_textures.back() = init(m_font, m_strings.back(), m_textures.back(), m_quads.back(), 200, 150 + (100 * m_client->number));
		
		m_joined = true;
	}
}

void OnlineScreen::render(SDL_Renderer * renderer) {
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

	for (int i = 0; i < m_textures.size(); i++) {
		SDL_RenderCopy(renderer, m_textures[i], NULL, &m_quads[i]);
	}
	

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
