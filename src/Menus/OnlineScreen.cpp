#include "OnlineScreen.h"


OnlineScreen::OnlineScreen(GameState * state, SDL_Renderer * renderer, TTF_Font * Font, SDL_GameController* controller, Client * client, bool * online) {

	m_currentGameState = state;
	gGameController = controller;
	m_renderer = renderer;

	SDL_Color menuColor = { 0, 0, 0, 255 };
	SDL_Surface * textSurface = new SDL_Surface;

	m_font = Font;

	std::string LString = "Lobby";
	std::string EString = "(B) Exit";
	std::string PString = "(A) Start";


	exittexture = init(Font, EString, exittexture, exitRenderQuad, 1055, 600, menuColor);
	playtexture = init(Font, PString, playtexture, playRenderQuad, 145, 600, menuColor);

	m_menuFont = TTF_OpenFont("joystixmonospace.ttf", 90);

	titletexture = init(m_menuFont, LString, titletexture, titleRenderQuad, 350, 50, menuColor);
	
	m_texture = loadFromFile("assets/art/environment/Lobby.png", m_renderer);

	m_client = client;
	

	m_BGRect.x = 120; m_BGRect.y = 900; m_BGRect.w = 920; m_BGRect.h = 400;
	
	m_online = online;


	m_sRectangle = new SDL_Rect;
	m_dRectangle = new SDL_Rect;
	m_sRectangle->x = 0;
	m_sRectangle->y = 0;
	m_sRectangle->w = 1200;
	m_sRectangle->h = 700;
	m_dRectangle->x = 0;
	m_dRectangle->y = 700;
}

OnlineScreen::~OnlineScreen() {}

void OnlineScreen::update() {
	if (!m_joined && !m_firstRunThrough) {
		m_firstRunThrough = true;
		

		if (m_client->run()) {
			m_joined = true;
		}
		
		while (m_client->number == 0 && m_joined) {
			m_client->receive();
			responseTimer++;
			if (responseTimer > NO_RESPONSE) {
				responseTimer = 0;
				m_joined = false;
			}
		}	

		if (m_joined) {
			SDL_Texture* playertexture;
			SDL_Rect playerRenderQuad;
			m_textures.push_back(playertexture);
			m_quads.push_back(playerRenderQuad);
			int num = m_client->number;
			m_index.push_back(m_client->number);
			std::string text = "Player: " + std::to_string(num);
			m_strings.push_back(text);
			SDL_Color textColor = { 255, 255, 255, 255 };
			m_textures.back() = init(m_font, m_strings.back(), m_textures.back(), m_quads.back(), 200, 150 + (100 * m_client->number), textColor);

		}
		else {
			std::string NSString = "No server";
			SDL_Color textColor = { 255, 255, 255, 255 };

			noServerTexture = init(m_menuFont, NSString, noServerTexture, noServerRenderQuad, 240, 250, textColor);

		}
		

		if (m_client->number > 1) {
			fillLobby();
		}
	}
	bool BButton = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_B);
	bool AButton = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_A);


	if (BButton) {
		m_joined = false;
		m_pack.message = 3;
		m_pack.playerNum = m_client->number;
		m_client->sendMessage(m_pack);
		//*m_currentGameState = GameState::Menu;
		lastButton = "B";
		outAnimation = true;
		m_firstRunThrough = false;
		m_textures.clear();
		m_strings.clear();
		m_quads.clear();
		m_index.clear();
	}

	m_client->receive();
	if (m_client->m_joiners.size() > 0) {
		addMember();
	}

	if (m_client->m_leavers.size() > 0) {
		removeMember();
	}

	if (m_strings.size() > 0) {
		m_ready2Play = true;
		if (AButton) {
			m_joined = false;
			m_pack.message = 4;
			m_pack.playerNum = m_client->number;
			lastButton = "A";
			m_client->sendMessage(m_pack);
			*m_online = true;
			*m_currentGameState = GameState::Game;
			//outAnimation = true;
			m_lobbySize = m_strings.size();
		}
		else if (m_client->m_startGame) {
			m_joined = false;
			*m_online = true;
			*m_currentGameState = GameState::Game;
			//outAnimation = true;
			//lastButton = "A";
			m_lobbySize = m_strings.size();
		}
	}
	else {
		m_ready2Play = false;
	}

	if (inAnimation)
	{
		m_dRectangle->y -= 10;
		m_BGRect.y -= 10;
		if (m_dRectangle->y <= 0)
		{
			inAnimation = false;
			m_dRectangle->y = 0;
			m_BGRect.y = 200;
		}
	}

	if (outAnimation)
	{
		m_dRectangle->y += 10;
		m_BGRect.y += 10;
		animationTimer++;
	}

	if (animationTimer >= 100 && lastButton == "B")
	{
		resetMenu();
		*m_currentGameState = GameState::Menu;
	}

	else if (animationTimer >= 100 && lastButton == "A")
	{
		resetMenu();
		*m_currentGameState = GameState::Game;
	}
}

void OnlineScreen::removeMember() {
	int i = 0;
	for (; i < m_index.size() && i != m_client->m_leavers[0]; i++) {}
	i--;
	m_index.erase(m_index.begin() + i);
	m_textures.erase(m_textures.begin() + i);
	m_strings.erase(m_strings.begin() + i);
	m_quads.erase(m_quads.begin() + i);

	if (m_client->m_leavers[0] < m_client->number) {
		for (int j = 0; j < m_strings.size(); j++) {
			if (m_strings.at(j) == "Player: " + std::to_string(m_client->number)) {
				m_client->number--;
				m_strings.at(j) = "Player: " + std::to_string(m_client->number);
				SDL_Color textColor = { 255, 255, 255, 255 };
				m_textures.at(j) = init(m_font, m_strings.at(j), m_textures.at(j), m_quads.at(j), 200, 150 + (100 * m_client->number), textColor);
				break;
			}
		}
	}
	else if (m_client->m_leavers[0] > m_client->number) {
		for (int j = m_client->number; j < (m_strings.size() + 1); j++) {
			int temp = j - 1;
			m_strings.at(temp) = "Player: " + std::to_string(j);
			SDL_Color textColor = { 255, 255, 255, 255 };
			m_textures.at(temp) = init(m_font, m_strings.at(temp), m_textures.at(temp), m_quads.at(temp), 200, 150 + (100 * (j)), textColor);
		}
	}

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
	SDL_Color textColor = { 255, 255, 255, 255 };
	m_textures.back() = init(m_font, m_strings.back(), m_textures.back(), m_quads.back(), 200, 150 + (100 * m_client->m_joiners[0]), textColor);
	m_client->m_joiners.pop_back();
}

void OnlineScreen::fillLobby() {
	int tempVal = m_client->number;
	tempVal--;
	while (tempVal != 0) {
		SDL_Texture* playertexture;
		SDL_Rect playerRenderQuad;
		m_textures.push_back(playertexture);
		m_quads.push_back(playerRenderQuad);
		m_index.push_back(tempVal);
		std::string text = "Player: " + std::to_string(tempVal);
		m_strings.push_back(text);
		SDL_Color textColor = { 255, 255, 255, 255 };
		m_textures.back() = init(m_font, m_strings.back(), m_textures.back(), m_quads.back(), 200, 150 + (100 * tempVal), textColor);

		tempVal--;
	}
}

void OnlineScreen::render(SDL_Renderer * renderer) {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 28, 32, 82, 255);

	m_dRectangle->w = m_width;
	m_dRectangle->h = m_height;
	SDL_RenderCopyEx(renderer, m_texture, m_sRectangle, m_dRectangle, 0, NULL, SDL_FLIP_NONE);

	SDL_RenderFillRect(renderer, &m_BGRect);

	//SDL_RenderCopy(renderer, exittexture, NULL, &exitRenderQuad);
	//SDL_RenderCopy(renderer, titletexture, NULL, &titleRenderQuad);
	if (!inAnimation) {
		if (m_ready2Play) {
			SDL_RenderCopy(renderer, playtexture, NULL, &playRenderQuad);
		}

		if (!m_joined) {
			SDL_RenderCopy(renderer, noServerTexture, NULL, &noServerRenderQuad);
		}
	}

	for (int i = 0; i < m_textures.size(); i++) {
		SDL_RenderCopy(renderer, m_textures[i], NULL, &m_quads[i]);
	}

	
	

}

SDL_Texture* OnlineScreen::loadFromFile(std::string path, SDL_Renderer* gRenderer) {

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
		

			m_width = loadedSurface->w;
			m_height = loadedSurface->h;
			

		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
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

void OnlineScreen::resetMenu()
{
	lastButton = "";
	animationTimer = 0;
	outAnimation = false;
	inAnimation = true;
	m_dRectangle->y = 700;
	m_BGRect.y = 900;
}
