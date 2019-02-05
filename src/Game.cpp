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
	m_currentGameState = (GameState::Game);
	
	m_splash = new SplashScreen();
	m_menu = new MenuScreen();
	m_options = new OptionScreen();
	m_credits = new CreditScreen();
	m_screenSize = { 0,0,1200,700 };
	m_pistol = new Entity();

	p = new Player(m_renderer);
	ai = new AI(m_renderer);

	initialise();
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

	switch (m_currentGameState)
	{
	case GameState::None:
		break;
	case GameState::Splash:
		break;
	case GameState::Menu:
		break;
	case GameState::Options:
		break;
	case GameState::Game:
		m_hs.update();
		m_as.update();
		SDL_PollEvent(&event);
		m_cs.update(event);
	
		break;
	case GameState::Credits:
		break;
	default:
		break;
	}

	
	m_hs.update();
	m_as.update();
	SDL_PollEvent(&event);
	m_cs.update(event);
	m_ps.update();
}

void Game::render() {
	if (m_renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}
	SDL_RenderClear(m_renderer);

	switch (m_currentGameState)
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
	m_currentGameState = gameState;
}


void Game::initialise()
{

	SpriteComponent* spriteComponent = new SpriteComponent(0, 0, 257, 259);
	spriteComponent->loadFromFile("human.png", m_renderer);
	spriteComponent->setPosition(v2(300, 100));
	spriteComponent->setScale(v2(0.5f, 0.5f));

	m_pistol->addComponent(spriteComponent);
	m_pistol->addComponent(new PositionComponent(600, 100));

	m_hs.addEntity((Entity*)p);
	m_cs.addEntity((Entity*)p);

	m_rs.addEntity((Entity*)p);

	m_rs.addEntity(m_pistol);
	m_ps.addEntity((Entity*)p);

	m_ais.addEntity((Entity*)ai);
	//m_ps.addEntity((Entity*)ai);
}

