#include "Game.h"

Game::Game()
{
	m_window = SDL_CreateWindow("Entity Component Systems", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 700, SDL_WINDOW_OPENGL);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	if (IMG_Init(imgFlags) != imgFlags)
	{
		cout << "Error: " << IMG_GetError() << endl;
	}
	m_currentGameState = new GameState;
	*m_currentGameState = (GameState::Splash);

	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
	}

	TTF_Font* Font = TTF_OpenFont("arial.ttf", 300);
	if (!Font) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	TTF_Font* menuFont = TTF_OpenFont("arial.ttf", 30);
	if (!menuFont) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}
	
	m_splash = new SplashScreen(m_currentGameState, m_renderer, Font);
	m_menu = new MenuScreen(m_currentGameState, m_renderer, menuFont);
	m_options = new OptionScreen();
	m_credits = new CreditScreen();
	m_screenSize = { 0,0,1200,700 };

	p = new Player(m_renderer);
	h = new Hand(m_renderer);
	ai = new AI(m_renderer);
	
	m_map = new MapLoader();

	m_map->load("testlevel.tmx", m_renderer);

	pistol = new Gun(m_renderer);

	

	initialise();

	m_ents.push_back((Entity*)p);
	m_ents.push_back((Entity*)ai);
	//m_ents.push_back((Entity*)pistol);
}

Game::~Game()
{
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


	switch (*m_currentGameState)
	{
	case GameState::None:
		break;
	case GameState::Splash:
		m_splash->update();
		break;
	case GameState::Menu:
		m_menu->update(m_window);
		break;
	case GameState::Options:
		break;
	case GameState::Game:
		m_hs.update();		
		m_ais.update();		
		m_ais.receive(m_ents);
		m_collSys.update(m_map->getTiles());
		
		m_cs.update(event);
		m_ps.update();
		m_guns.update();
		m_ps.bulletUpdate(m_renderer);
		break;
	case GameState::Credits:
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
	case GameState::Options:
		m_options->render(m_renderer);
		break;
	case GameState::Game:
		m_rs.render(m_renderer);
		m_map->draw(m_renderer);
		m_ps.bulletRender(m_renderer);
		p->render(m_renderer);
		break;
	case GameState::Credits:
		m_credits->render(m_renderer);
		break;
	default:
		break;
	}
	SDL_RenderPresent(m_renderer);

}

void Game::setGameState(GameState gameState)
{
	*m_currentGameState = gameState;
}


void Game::initialise()
{

	m_hs.addEntity((Entity*)p);
	m_cs.addEntity((Entity*)p);

	m_cs.addEntity((Entity*)pistol);
	m_cs.addEntity((Entity*)h);

	m_rs.addEntity((Entity*)p);
	m_rs.addEntity((Entity*)pistol);
	m_rs.addEntity((Entity*)h);
	
	m_rs.addEntity((Entity*)ai);

	m_ps.addEntity((Entity*)p);
	m_ps.addEntity((Entity*)ai);

	m_ais.addEntity((Entity*)ai);

	m_ps.addEntity((Entity*)pistol);
	m_ps.addEntity((Entity*)h);

	m_ps.addEntity((Entity*)pistol);
	m_guns.addEntity((Entity*)pistol);

	m_collSys.addEntity((Entity*)p);
	m_collSys.addEntity((Entity*)ai);
	m_collSys.addEntity((Entity*)pistol);
}

