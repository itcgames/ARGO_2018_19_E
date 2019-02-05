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
	
	m_player = new Entity();

	m_pistol = new Entity();

	p = new Player(m_renderer);

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

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	m_rs.render(m_renderer);
	SDL_RenderPresent(m_renderer);

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
}

