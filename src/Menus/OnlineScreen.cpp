#include "OnlineScreen.h"


OnlineScreen::OnlineScreen(GameState * state, SDL_Renderer * renderer, TTF_Font * Font, SDL_GameController* controller, Client * client) {

	m_currentGameState = state;
	gGameController = controller;
	m_renderer = renderer;

	SDL_Color menuColor = { 0, 0, 0, 255 };
	SDL_Surface * textSurface = new SDL_Surface;

	m_font = Font;

	m_strings.push_back("Lobby");
	m_strings.push_back("(B) Exit");

	m_textures.push_back(titletexture);
	m_textures.push_back(exittexture);

	m_quads.push_back(titleRenderQuad);
	m_quads.push_back(exitRenderQuad);

	m_textures[1] = init(Font, m_strings[1], m_textures[1], m_quads[1], 1055, 600, menuColor);

	TTF_Font* menuFont = TTF_OpenFont("arial.ttf", 150);

	m_textures[0] = init(menuFont, m_strings[0], m_textures[0], m_quads[0], 350, 50, menuColor);

	m_client = client;
	

	m_BGRect.x = 100; m_BGRect.y = 200; m_BGRect.w = 1000; m_BGRect.h = 400;
	

}

OnlineScreen::~OnlineScreen() {}

void OnlineScreen::update() {
	if (!m_joined) {

		m_client = new Client("149.153.106.155", 54000);

		if (m_client->run()) {
			m_client->sendMessage("Join, Hello,");
		}
		
		while (m_client->number == 0) {
			m_client->receive();
		}	

		SDL_Texture* playertexture;
		SDL_Rect playerRenderQuad;
		m_textures.push_back(playertexture);
		m_quads.push_back(playerRenderQuad);
		int num = m_client->number;
		m_index.push_back(m_client->number);
		std::string text = "Player: " + std::to_string(num);
		m_strings.push_back(text);
		SDL_Color textColor = { 200, 200, 200, 255 };
		m_textures.back() = init(m_font, m_strings.back(), m_textures.back(), m_quads.back(), 200, 150 + (100 * m_client->number), textColor);


		if (m_client->number > 1) {
			fillLobby();
		}
		m_joined = true;
	}
	bool BButton = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_B);

	if (BButton) {
		m_joined = false;
		m_client->sendMessage("Leave," + std::to_string(m_client->number) + ",");
		*m_currentGameState = GameState::Menu;
	}

	m_client->receive();
	if (m_client->m_joiners.size() > 0) {
		addMember();
	}

	if (m_client->m_leavers.size() > 0) {
		removeMember();
	}
}

void OnlineScreen::removeMember() {
	int i = 0;
	for (; i < m_index.size() && i != m_client->m_leavers[0]; i++) {}
	m_index.erase(m_index.begin() + i);
	m_textures.erase(m_textures.begin() + i);
	m_strings.erase(m_strings.begin() + i);
	m_quads.erase(m_quads.begin() + i);
	m_client->m_leavers.pop_back();
}

void OnlineScreen::addMember() {
	SDL_Texture* playertexture;
	SDL_Rect playerRenderQuad;
	m_textures.push_back(playertexture);
	m_quads.push_back(playerRenderQuad);
	m_index.push_back(m_client->m_joiners[0]);
	int num = m_client->number;
	std::string text = "Player: " + std::to_string(m_client->m_joiners[0]);
	m_strings.push_back(text);
	SDL_Color textColor = { 200, 200, 200, 255 };
	m_textures.back() = init(m_font, m_strings.back(), m_textures.back(), m_quads.back(), 200, 150 + (100 * m_client->m_joiners[0]), textColor);
	m_client->m_joiners.pop_back();
}

void OnlineScreen::fillLobby() {
	int tempVal = m_client->number;
	while (tempVal != 0) {
		SDL_Texture* playertexture;
		SDL_Rect playerRenderQuad;
		m_textures.push_back(playertexture);
		m_quads.push_back(playerRenderQuad);
		m_index.push_back(tempVal);
		std::string text = "Player: " + std::to_string(tempVal);
		m_strings.push_back(text);
		SDL_Color textColor = { 200, 200, 200, 255 };
		m_textures.back() = init(m_font, m_strings.back(), m_textures.back(), m_quads.back(), 200, 150 + (100 * tempVal), textColor);

		tempVal--;
	}
}

void OnlineScreen::render(SDL_Renderer * renderer) {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &m_BGRect);
	for (int i = 0; i < m_textures.size(); i++) {
		SDL_RenderCopy(renderer, m_textures[i], NULL, &m_quads[i]);
	}
	

}



SDL_Texture * OnlineScreen::init(TTF_Font * Font, std::string & text, SDL_Texture * texture, SDL_Rect & quad, int x, int y, SDL_Color color) {
	SDL_Surface * textSurface = new SDL_Surface;

	textSurface = TTF_RenderText_Solid(Font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

	int width = textSurface->w;
	int height = textSurface->h;
	SDL_FreeSurface(textSurface);
	quad = { x, y, width, height };
	return texture;
}
