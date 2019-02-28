#include "Game.h"

Game* Game::s_pInstance = 0;

Game::Game()
{
	m_window = SDL_CreateWindow("Entity Component Systems", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 700, SDL_WINDOW_OPENGL);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_screen = SDL_CreateRGBSurface(0, 1200, 700, 32,
		0,
		0,
		0,
		0);;

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	
	//Initialize SDL
	if (SDL_Init( SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) | SDL_INIT_AUDIO < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}


	//Initialize SDL_mixer 
	if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, NULL, 2048 ) < 0) 
	{ 
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() ); 
	}

	//Allocate 128 channels for a max for 128 audio chunks playing at one time
	Mix_AllocateChannels(128);


	if (IMG_Init(imgFlags) != imgFlags)
	{
		cout << "Error: " << IMG_GetError() << endl;
	}
	m_currentGameState = new GameState;
	*m_currentGameState = (GameState::Menu);
	aObserver = new AudioObserver();
	aObserver->load();
	aObserver->StartBGM(1);

	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
	}

	Font = TTF_OpenFont("arial.ttf", 200);
	if (!Font) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	splashFont = TTF_OpenFont("joystixmonospace.ttf", 50);
	if (!Font) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	headerFont = TTF_OpenFont("joystixmonospace.ttf", 65);
	if (!Font) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	//SplashFont = TTF_OpenFont("joystixmonospace.ttf", 100);
	//if (!Font) {
	//	printf("TTF_OpenFont: %s\n", TTF_GetError());
	//	// handle error
	//}

	TTF_Font* creditsFont = TTF_OpenFont("arial.ttf", 100);
	if (!creditsFont) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	TTF_Font* menuFont = TTF_OpenFont("arial.ttf", 30);
	if (!menuFont) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}
	m_client = new Client("149.153.106.155", 54000);
	setUpController();
	m_creditsScreen = new CreditScreen(m_currentGameState, m_renderer, creditsFont, menuFont, gGameController);
	m_playScreen = new PlayScreen(m_currentGameState, m_renderer, Font, gGameController);
	m_splash = new SplashScreen(m_currentGameState, m_renderer, headerFont, splashFont);
	m_menu = new MenuScreen(m_currentGameState, m_renderer, menuFont, gGameController);
	m_onlineScreen = new OnlineScreen(m_currentGameState, m_renderer, menuFont, gGameController, m_client, m_online);
	m_options = new OptionScreen();
	
	m_screenSize = { 0,0,1200,700 };

	vignettetexture = m_menu->loadFromFile("assets/art/environment/vignette.png", m_renderer);
}

Game::~Game()
{
}

void Game::fullScreenToggle(SDL_Window* Window) {
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
	SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
	SDL_ShowCursor(IsFullscreen);

	if (fScreen) {
		fScreen = false;
	}
	else {
		fScreen = true;
	}
}

void Game::run()
{
	const Uint32 fps = 60;
	const Uint32 minimumFrameTime = 1000 / fps;

	Uint32 frameTime;
	Uint32 lastFrameTime = 0;
	Uint32 deltaTime = 0;

	while (!exit) {
		frameTime = SDL_GetTicks();

		deltaTime = frameTime - lastFrameTime;
		lastFrameTime = frameTime;
		
		update();
		render();

		if ((SDL_GetTicks() - frameTime) < minimumFrameTime)
			SDL_Delay(minimumFrameTime - (SDL_GetTicks() - frameTime));
	}

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::update() {
	SDL_PollEvent(&event);
	m_client->receive();

	m_toggleCounter++;
	if (m_menu->m_toggleFS && m_toggleCounter > ALLOW_TOGGLE) {
		fullScreenToggle(m_window);
		m_menu->m_toggleFS = false;
		m_toggleCounter = 0;
	}

	switch (*m_currentGameState)
	{
	case GameState::None:
		break;
	case GameState::Splash:
		m_splash->update();
		break;
	case GameState::Menu:
		m_menu->update(m_window, fScreen);
		break;
	case GameState::Online:
		m_onlineScreen->update();
		break;
	case GameState::Options:
		break;
	case GameState::Game:
		m_playScreen->update(m_online, event, m_onlineScreen->m_lobbySize, m_client);
		break;
	case GameState::Credits:
		m_creditsScreen->update();
		break;
	default:
		break;
	}


}

void Game::render() {
	if (m_renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}
	SDL_RenderClear(m_renderer);
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	m_startPlay = false;

	switch (*m_currentGameState)
	{
	case GameState::None:
		break;
	case GameState::Splash:
		m_splash->render(m_renderer);
		break;
	case GameState::Menu:
		m_menu->render(m_renderer);
		break;
	case GameState::Online:
		m_onlineScreen->render(m_renderer);
		break;

	case GameState::Options:
		m_options->render(m_renderer);
		break;
	case GameState::Game:
		m_startPlay = true;
		m_playScreen->render(m_renderer);
		if (!fScreen) {
			SDL_RenderCopyEx(m_renderer, vignettetexture, new SDL_Rect{ 0,0,1200,700 }, new SDL_Rect{ 0,0,(int)(1200 / 0.55), (int)(700 / 0.55) }, 0, NULL, SDL_FLIP_NONE);
		}
		else {
			SDL_RenderCopyEx(m_renderer, vignettetexture, new SDL_Rect{ 0,0,1200,700 }, new SDL_Rect{ 0,0,(int)(1280 / 0.55), (int)(720 / 0.55) }, 0, NULL, SDL_FLIP_NONE);
		}
		break;
	case GameState::Credits:
		m_creditsScreen->render(m_renderer);
		break;
	default:
		break;
	}

	if (!m_startPlay) {
		if (!fScreen) {
			SDL_RenderCopyEx(m_renderer, vignettetexture, new SDL_Rect{ 0,0,1200,700 }, new SDL_Rect{ 0,0,1200,700 }, 0, NULL, SDL_FLIP_NONE);
		}
		else {
			SDL_RenderCopyEx(m_renderer, vignettetexture, new SDL_Rect{ 0,0,1200,700 }, new SDL_Rect{ 0,0,1280,720 }, 0, NULL, SDL_FLIP_NONE);

		}
	}
	
	SDL_RenderPresent(m_renderer);
}


void Game::initialiseText(std::string message) {
	round_text = message;
	textSurface = TTF_RenderText_Solid(Font, round_text.c_str(), textColor);
	text = SDL_CreateTextureFromSurface(m_renderer, textSurface);
	int text_width = textSurface->w;
	int text_height = textSurface->h;
	SDL_FreeSurface(textSurface);
	renderQuad = { 150, 200, text_width, text_height };
}

void Game::setUpController() {
	gGameController = SDL_GameControllerOpen(0);
	if (gGameController == NULL)
	{
		printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
	}
	
	

}

void Game::setGameState(GameState gameState)
{
	*m_currentGameState = gameState;
}

