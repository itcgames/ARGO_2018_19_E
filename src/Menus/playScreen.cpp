#include "playScreen.h"

PlayScreen::PlayScreen(GameState * state, SDL_Renderer * renderer, TTF_Font* font, SDL_GameController * controller) {

	m_gameController = controller;
	Font = font;

	m_renderer = renderer;

	m_currentGameState = state;

	testLight = new Light(c2v{ 0.0f, 300.0f }, 5, 22, 130, renderer);
	testLight->setPosition(c2v{ 400.0f, 0.0f });
	testLight->setSize(c2v{ 3.0f, 3.0f });

	m_audioObserver = new AudioObserver();
	m_audioObserver->load();

	m_camera = new Camera();
	m_focusPoint = new SDL_Rect();
	m_offset = new SDL_Rect();


	m_backgroundSpriteOne = new SpriteComponent(0, 0, 1920, 1080);
	m_backgroundSpriteOne->loadFromFile("assets/art/environment/Cyber_Background_3_FINAL.png", renderer);
	m_backgroundSpriteOne->setPosition(c2v{ 0.0f, 0.0f });
	m_backgroundSpriteOne->setScale(c2v{ 1.5f, 1.6f });

	m_backgroundSpriteTwo = new SpriteComponent(0, 0, 1920, 1080);
	m_backgroundSpriteTwo->loadFromFile("assets/art/environment/Game_BG_1.png", renderer);
	m_backgroundSpriteTwo->setPosition(c2v{ 0.0f, 0.0f });
	m_backgroundSpriteTwo->setScale(c2v{ 1.5f, 1.6f });

	m_backgroundSpriteThree = new SpriteComponent(0, 0, 1920, 1080);
	m_backgroundSpriteThree->loadFromFile("assets/art/environment/Background_4_FINAL.png", renderer);
	m_backgroundSpriteThree->setPosition(c2v{ 0.0f, 0.0f });
	m_backgroundSpriteThree->setScale(c2v{ 1.5f, 1.6f });


	m_currentLevel = m_backgroundSpriteOne;
	for (int i = 0; i < 4; i++)
	{
		m_playerPositions.push_back(c2v{ 0, 0 });
	}

	m_map = new MapLoader();

	m_map->load("testlevel.tmx", renderer);

	m_pistolSpriteComponent = new SpriteComponent(0, 0, 210, 295);
	m_pistolSpriteComponent->setPosition(c2v{ 999999, 999999 });
	m_pistolSpriteComponent->setScale(c2v{ 0.2f, 0.2f });
	m_pistolSpriteComponent->loadFromFile("assets/pistol.png", renderer);

	m_shotgunSpriteComponent = new SpriteComponent(0, 0, 33, 139);
	m_shotgunSpriteComponent->setPosition(c2v{ 999999, 999999 });
	m_shotgunSpriteComponent->setScale(c2v{ 2.0f, 1.5f });
	m_shotgunSpriteComponent->loadFromFile("assets/art/character/finished_character_assets/ShotgunGlow2.png", renderer);

	m_juicerSpriteComponent = new SpriteComponent(0, 0, 100, 150);
	m_juicerSpriteComponent->setPosition(c2v{ 999999, 999999 });
	m_juicerSpriteComponent->setScale(c2v{ 2.0f, 2.0f });
	m_juicerSpriteComponent->loadFromFile("assets/art/character/finished_character_assets/MiniGunGlow.png", renderer);

	m_stabbyboySpriteComponent = new SpriteComponent(0, 0, 12, 136);
	m_stabbyboySpriteComponent->setPosition(c2v{ 999999, 999999 });
	m_stabbyboySpriteComponent->setScale(c2v{ 2.0f, 2.0f });
	m_stabbyboySpriteComponent->loadFromFile("assets/art/character/finished_character_assets/Katana.png", renderer);

	m_grenadeSpriteComponent = new SpriteComponent(0, 0, 150, 200);
	m_grenadeSpriteComponent->setPosition(c2v{ 999999,999999 });
	m_grenadeSpriteComponent->setScale(c2v{ 0.2f, 0.2f });
	m_grenadeSpriteComponent->loadFromFile("assets/grenade.png", renderer);


	m_guns.push_back(new Gun(renderer, 4, 1500, 100,gunAmount, m_grenadeSpriteComponent->getTexture()));
	gunAmount = gunAmount + 1;
	m_guns.push_back(new Gun(renderer, 3, 1000, 100,gunAmount, m_juicerSpriteComponent->getTexture()));
	gunAmount = gunAmount + 1;
	m_guns.push_back(new Gun(renderer, 2, 300, 100,gunAmount, m_shotgunSpriteComponent->getTexture()));
	gunAmount = gunAmount + 1;
	//m_guns.push_back(new Gun(renderer, 4, 300, 100, gunAmount, m_grenadeSpriteComponent->getTexture()));
	//gunAmount = gunAmount + 1;
	m_guns.push_back(new Gun(renderer, 5, 700, 100,gunAmount, m_stabbyboySpriteComponent->getTexture()));
	gunAmount = gunAmount + 1;




	for (Gun * g : m_guns) {
		m_Gunents.push_back((Entity*)g);	
	}

	m_BGRect.x = -2400; m_BGRect.y = 0; m_BGRect.w = 2400; m_BGRect.h = 1400;
}

void PlayScreen::initialise(bool online, int size, int num) {
	*m_online = online;

	m_audioObserver->StartBGM(0);

	if (SDL_NumJoysticks() >= 2) {
		m_multiplayer = true;
	}
	else {
		m_multiplayer = false;
	}
	
	if (online) {

		if (m_map->getSpawnPoints().at(num - 1)->first == false)
		{
			m_players.push_back(new Player(m_renderer, m_map->getSpawnPoints().at(num - 1)->second.x, m_map->getSpawnPoints().at(num - 1)->second.y, SDL_GameControllerOpen(0), num - 1, Font));
			m_leftHands.push_back(new Hand(m_renderer, 1, num));
			m_rightHands.push_back(new Hand(m_renderer, 2, num));
			m_map->getSpawnPoints().at(num - 1)->first = true;
		
		}	
		
		if (num < size) {
			for (int i = num + 1; i <= size; i++) {
				if (m_map->getSpawnPoints().at(i - 1)->first == false)
				{
					Player * player = new  Player(m_renderer, m_map->getSpawnPoints().at(i - 1)->second.x, m_map->getSpawnPoints().at(i - 1)->second.y, SDL_GameControllerOpen(i), i - 1, Font);
					m_networkCharacters.push_back(player);
					m_leftHands.push_back(new Hand(m_renderer, 1, i));
					m_rightHands.push_back(new Hand(m_renderer, 2, i));
					m_map->getSpawnPoints().at(i - 1)->first = true;
				}
				
			}
		}

		if (num > 1) {
			for (int i = num - 1; i > 0; i--) { 
				if (m_map->getSpawnPoints().at(i - 1)->first == false)
				{
					Player * player = new  Player(m_renderer, m_map->getSpawnPoints().at(i - 1)->second.x, m_map->getSpawnPoints().at(i - 1)->second.y, SDL_GameControllerOpen(i), i - 1, Font);
					m_networkCharacters.push_back(player);
					m_leftHands.push_back(new Hand(m_renderer, 1, i));
					m_rightHands.push_back(new Hand(m_renderer, 2, i));
					m_map->getSpawnPoints().at(i - 1)->first = true;
				}

				
			}
		}

		for (Player * net : m_networkCharacters) {
			m_hs.addEntity((Entity*)net);
			m_rs.addEntity((Entity*)net);
			m_ps.addEntity((Entity*)net);
			m_restartSys.addEntity((Entity*)net);
			m_collSys.addEntity((Entity*)net);
			m_netSystem.addEntity((Entity*)net);
			m_animationsSys.addEntity((Entity*)net);
		}
	}
	else {

		for (int i = 0; i < SDL_NumJoysticks(); i++) 
		{
			for (int j = 0; j < m_map->getSpawnPoints().size(); j++)
			{
				if (m_map->getSpawnPoints().at(j)->first == false)
				{
					Player * player = new Player(m_renderer, m_map->getSpawnPoints().at(j)->second.x, m_map->getSpawnPoints().at(j)->second.y, SDL_GameControllerOpen(i), i, Font);
					m_playerents.push_back((Entity*)player);
					m_players.push_back(player);
					m_leftHands.push_back(new Hand(m_renderer, 1, i));
					m_rightHands.push_back(new Hand(m_renderer, 2, i));
					m_map->getSpawnPoints().at(j)->first = true;
					
					break;
				}
			}
		}
		int noOfPlayers = SDL_NumJoysticks();
		
		for (int i = 0; i < (4 - SDL_NumJoysticks()); i++) 
		{
			for (int j = 0; j < m_map->getSpawnPoints().size(); j++)
			{
				if (m_map->getSpawnPoints().at(j)->first == false)
				{
					AI * ai = new AI(m_renderer, m_map->getSpawnPoints().at(j)->second.x, m_map->getSpawnPoints().at(j)->second.y, noOfPlayers);
					m_playerents.push_back((Entity*)ai);
					m_aiCharacters.push_back(ai);
					m_leftHands.push_back(new Hand(m_renderer, 1, noOfPlayers));
					m_rightHands.push_back(new Hand(m_renderer, 2, noOfPlayers));
					m_map->getSpawnPoints().at(j)->first = true;
					noOfPlayers += 1;
				}
			}
		}

		//std::cout << noOfPlayers << std::endl;
	}


	for (Player * net : m_players) {
		m_hs.addEntity((Entity*)net);
		m_rs.addEntity((Entity*)net);
		m_ps.addEntity((Entity*)net);
		m_restartSys.addEntity((Entity*)net);
		m_collSys.addEntity((Entity*)net);
		m_cs.addEntity((Entity*)net);

	}

	for (Gun * gun : m_guns) {
		m_rs.addEntity((Entity*)gun);
		m_cs.addEntity((Entity*)gun);
		m_ps.addEntity((Entity*)gun);
		m_gunSys.addEntity((Entity*)gun);
		m_collSys.addEntity((Entity*)gun);
		m_restartSys.addEntity((Entity*)gun);
		Entity* ent = (Entity*)gun;
		TagComponent* tc = (TagComponent*)ent->getCompByType("TAG");
		if (tc->getSubTag() == "grenade") {
			m_grenadeSys.addEntity((Entity*)gun);
		}
	}

	for (Hand * net : m_leftHands) {
		m_hs.addEntity((Entity*)net);
		m_rs.addEntity((Entity*)net);
		m_ps.addEntity((Entity*)net);
		m_restartSys.addEntity((Entity*)net);
		m_collSys.addEntity((Entity*)net);
		m_cs.addEntity((Entity*)net);

	}
	for (Hand * net : m_rightHands) {
		m_hs.addEntity((Entity*)net);
		m_rs.addEntity((Entity*)net);
		m_ps.addEntity((Entity*)net);
		m_restartSys.addEntity((Entity*)net);
		m_collSys.addEntity((Entity*)net);
		m_cs.addEntity((Entity*)net);
		
	}

	m_ps.registerAudioObserver(m_audioObserver);


	for (AI * ai : m_aiCharacters) {

		m_collSys.addEntity((Entity*)ai);
		m_ais.addEntity((Entity*)ai);
		m_rs.addEntity((Entity*)ai);
		m_ps.addEntity((Entity*)ai);
		m_restartSys.addEntity((Entity*)ai);
	}


	m_ais.recieveLevel(m_map->getWalkPoints(), m_map->getJumpPoints(), m_map->getTiles(), m_map->getWidth(), m_map->getHeight());
	m_ps.recieveLevel(m_map->getWidth(), m_map->getHeight());
	m_ps.setRenderer(m_renderer);
	m_grenadeSys.setRenderer(m_renderer);
	m_collSys.setRenderer(m_renderer);
	m_animationsSys.setRenderer(m_renderer);

}

void PlayScreen::update(bool * online, SDL_Event event, int size, Client * client) {
	m_online = online;

	if (m_startGame) {

		initialise(*online, size, client->number);
		m_startGame = false;
	}
	
	m_cs.update(event);
	m_collSys.update(m_map->getTiles());
	m_ps.update(m_renderer);
	m_gunSys.update();

	SDL_RenderSetScale(m_renderer, m_windowScale.x, m_windowScale.y);

	m_ps.bulletUpdate(m_renderer);
	m_grenadeSys.update(m_map->getTiles(), m_aiCharacters, m_players);
	m_ais.update();
	m_ais.receive(m_Gunents, m_playerents);
	m_hs.update();


	int entityIndex = 0;
	for(int i = 0; i < m_players.size(); i++)
	{
		PositionComponent* pc = (PositionComponent*)m_players.at(i)->getCompByType("POSITION");
		m_playerPositions.at(i) = c2v{ pc->getX(), pc->getY() };
		entityIndex++;
	}

	for (int i = 0; i < m_aiCharacters.size(); i++)
	{
		PositionComponent* pc = (PositionComponent*)m_aiCharacters.at(i)->getCompByType("POSITION");
		m_playerPositions.at(entityIndex) = c2v{ pc->getX(), pc->getY() };
		entityIndex++;
	}

	m_focusPoint = m_camera->focus(m_playerPositions);
	m_camera->update(m_focusPoint);
	m_cameraCount = 0;


	//if (m_focusPoint->w > 0) {
	//	(SCREEN_WIDTH / m_focusPoint->w) > 1.0f ? ((m_screenScale < 1.0f) ? m_screenScale += 0.01f : m_screenScale = 1.0f) : (m_screenScale > 0.55f ? m_screenScale -= 0.01f : m_screenScale = 0.55f);
	//}


	m_cameraCount++;

	
	SDL_RenderSetScale(m_renderer, 0.55f, 0.55f);

	checkRoundOver();

	if (m_roundEnd || m_ps.startRoundCount < 100) {
		m_drawTimer = true;

		m_timerCounter++;
		if (m_timerCounter > 20) {
			m_timer--;
			initialiseText(std::to_string(m_timer), 0, 700);
			renderQuad->x = 1000;
			m_timerCounter = 0;
		}
		
	}
	else {
		m_drawTimer = false;
	}
	
	if ((*online)) {
		for (Entity * ent : m_netSystem.m_entities) {
			
			if (client->packet->message == 5) {
				m_netSystem.update(client->packet);

				client->receive();
			}
			
		}
		Entity * ent = (Entity*)m_players[0];
		

		sendPacket(ent, client);
	}
	

	if (!(*online) && !m_gameOver) {
		for (Player * p : m_players) {
			Entity * ent = (Entity *)p;
			TagComponent * tag = (TagComponent*)ent->getCompByType("TAG");
			if (tag->getScore() >= 5) {
				endRound();
				initialiseText(tag->getSubTag(), 1, 200);
				m_gameOver = true;
			}
		}
		
	}

	bool BackButton = SDL_GameControllerGetButton(m_gameController, SDL_CONTROLLER_BUTTON_BACK);


	if (BackButton && !firstTime) {
		firstTime = true;
		m_pressed = true;
		buttonTimer = 0;
	}

	buttonTimer++;
	


	if (buttonTimer > 100)
	{
		firstTime = false;
	}


	for (Player * p : m_players) {
		Entity * ent = (Entity *)p;
		TagComponent * tag = (TagComponent*)ent->getCompByType("TAG");
		ControlComponent * control = (ControlComponent*)ent->getCompByType("CONTROL");
		
		if (m_pressed && control->isPlayer)
		{
			std::cout << "hello" << std::endl;
			if (!ent->checkComponent("AI"))
			{
				ent->addComponent(new AIComponent());
			}
			if (!ent->checkComponent("Ray"))
			{
				ent->addComponent(new RayCastComponent());
			}
			m_ais.addEntity(ent);
			tag->setSubTag2("AI_Player");
			control->isPlayer = false;
			m_cs.removeEntity(tag->getID());
			m_pressed = false;
		}
		if (m_pressed && !control->isPlayer)
		{

			tag->setSubTag2("");
			m_cs.addEntity(ent);
			control->isPlayer = true;
			m_ais.removeEntity(tag->getID());
			m_pressed = false;
			
		}
	}

	if (m_restart)
	{
		m_restartSys.reset(randNum, m_map->getSpawnPoints(), *online, client->number, size);
		m_restart = false;
	}

	if (m_gameOver) {
		initialiseText("Victory", 0, 500);
		renderQuad->x = 600;

		endRound();
	}
	
}

void PlayScreen::sendPacket(Entity * ent, Client * client) {

	m_client = client;

	ControlComponent * cc = (ControlComponent*)ent->getCompByType("CONTROL");
	PositionComponent * pc = (PositionComponent*)ent->getCompByType("POSITION");
	TagComponent * tc = (TagComponent*)ent->getCompByType("TAG");

	Packet p;

	p.message = 5;
	p.playerNum = cc->m_playerNum;
	p.left = cc->getLeft();
	p.right = cc->getRight();
	p.jump = cc->getJump();
	p.fire = cc->getFire();
	p.gunAngle = cc->getAngle();
	p.alive = cc->getAlive();
	p.throwWeapon = cc->getThrowWeapon();
	p.position.x = pc->getX();
	p.position.y = pc->getY();

	p.roundOver = m_roundEnd;

	if (p.throwWeapon && !lastPacket.throwWeapon) {
		m_startThrow = true;
		m_throwTimer = 0;
	}

	if (m_startThrow && m_throwTimer < STOP_THROW) {
		
		p.throwWeapon = true;
		cout << p.throwWeapon << endl;
		m_throwTimer++;
	}
	else {
		m_startThrow = false;
	}

	if (p.message != lastPacket.message || p.playerNum != lastPacket.playerNum ||
		p.left != lastPacket.left || p.right != lastPacket.right || p.jump != lastPacket.jump ||
		p.fire != lastPacket.fire || p.gunAngle != lastPacket.gunAngle || p.alive != lastPacket.alive ||
		p.throwWeapon != lastPacket.throwWeapon || p.position.x != lastPacket.position.x ||
		p.position.y != lastPacket.position.y) {

		client->sendMessage(p);
	}

	lastPacket.message = p.message;
	lastPacket.playerNum = p.playerNum;
	lastPacket.left = p.left;
	lastPacket.right = p.right;
	lastPacket.jump = p.jump;
	lastPacket.fire = p.fire;
	lastPacket.gunAngle = p.gunAngle;
	lastPacket.alive = p.alive;
	lastPacket.throwWeapon = p.throwWeapon;
	lastPacket.position.x = p.position.x;
	lastPacket.position.y = p.position.y;
	lastPacket.roundOver = p.roundOver;

	for (Player * p : m_networkCharacters) {
		Entity * ent = (Entity*)p;
		ControlComponent * cc = (ControlComponent*)ent->getCompByType("CONTROL");
		if (cc->getRoundOver()) {
			//m_roundEnd = true;
		}
	}
}

void PlayScreen::render(SDL_Renderer * renderer) {
	m_currentLevel->render(m_renderer);
	m_map->draw(m_renderer, m_camera);
	for (AI * ai : m_aiCharacters) {
		ai->render(m_renderer, m_camera);
	}
	for (Player *p : m_players) {
		p->render(m_renderer, m_camera);
	}

	m_rs.render(m_renderer, m_camera);
	m_ps.bulletRender(m_renderer, m_camera);

	for (Player *p : m_networkCharacters) {
		p->render(m_renderer, m_camera);
	}
	m_rs.render(m_renderer, m_camera);
	for (Player *p : m_players) {
		p->renderMarker(m_renderer);
	}

	//m_animationsSys.render();
	testLight->render(m_renderer);
	m_grenadeSys.render();
	m_collSys.render();
	//m_emitter->update();
	SDL_SetRenderDrawColor(renderer, 183, 110, 121, 255);
	SDL_RenderFillRect(renderer, &m_BGRect);
	if (m_drawRoundText) {
		
		SDL_RenderCopy(m_renderer, w_text, NULL, winnerRenderQuad);
	}
	if (m_drawTimer) {
		SDL_RenderCopy(m_renderer, text, NULL, renderQuad);
	}
	
}

void PlayScreen::initialiseText(std::string message, int index, int y) {// SDL_Texture* texture, SDL_Rect* rect, int y) {
	//round_text = message;
	
	if (index == 0) {
		textSurface = TTF_RenderText_Solid(Font, message.c_str(), textColor);
		text = SDL_CreateTextureFromSurface(m_renderer, textSurface);
		int text_width = textSurface->w;
		int text_height = textSurface->h;
		SDL_FreeSurface(textSurface);
		renderQuad = new SDL_Rect{ 150, y, text_width, text_height };
		//renderQuad->x = 800 - (renderQuad->w / 2);
	}
	else {
		textSurface = TTF_RenderText_Solid(Font, message.c_str(), textColor);
		w_text = SDL_CreateTextureFromSurface(m_renderer, textSurface);
		int text_width = textSurface->w;
		int text_height = textSurface->h;
		SDL_FreeSurface(textSurface);
		winnerRenderQuad = new SDL_Rect{ 150, y, text_width, text_height };
		//winnerRenderQuad->x = 900 - (winnerRenderQuad->w / 2);
	}
	
}

bool PlayScreen::onlineRoundOver() {
	int dead = 0;
	int playerAmount = m_players.size() + m_networkCharacters.size();
	for (Player * p : m_players) {
		Entity * ent = (Entity *)p;
		ControlComponent * control = (ControlComponent*)ent->getCompByType("CONTROL");
		if (!control->getAlive()) {
			dead++;
		}
	}
	for (Player * p : m_networkCharacters) {
		Entity * ent = (Entity *)p;
		ControlComponent * control = (ControlComponent*)ent->getCompByType("CONTROL");
		if (!control->getAlive()) {
			dead++;
		}
	}
	
	if (dead >= (playerAmount - 1)) {
		if (!m_drawRoundText) {
		initialiseText("Player Wins", 1, 200);
		winnerRenderQuad->x = 150;

		m_drawRoundText = true;
		}
		if(m_timer < 5)
			m_timer = 10;
		return true;
	}
	return false;
}

void PlayScreen::endRound() {
	m_roundCounter++;
	m_BGRect.x += (1200.0 / 25);

	if (m_roundCounter > ROUND_OVER) {

		if (*m_online) {
			randNum = 1;
		}
		else {
			randNum = (rand() % 5) + 1;
		}

		

		if (randNum == 1) {
			m_map->load("testlevel.tmx", m_renderer);
			m_currentLevel = m_backgroundSpriteOne;
		}
		else if (randNum == 2) {
			m_map->load("level3.tmx", m_renderer);
			m_currentLevel = m_backgroundSpriteTwo;
		}
		else if (randNum == 3) {
			m_map->load("level5.tmx", m_renderer);
			m_currentLevel = m_backgroundSpriteThree;
		}
		else if (randNum == 4) {
			m_map->load("level6.tmx", m_renderer);
			m_currentLevel = m_backgroundSpriteThree;
		}
		else if (randNum == 5) {
			m_map->load("level7.tmx", m_renderer);
			m_currentLevel = m_backgroundSpriteTwo;
		}
		m_roundCounter = 0;
		m_drawRoundText = false;
		m_roundEnd = false;

		m_restart = true;
		m_ais.recieveLevel(m_map->getWalkPoints(), m_map->getJumpPoints(), m_map->getTiles(), m_map->getWidth(), m_map->getHeight());
		m_ps.recieveLevel(m_map->getWidth(), m_map->getHeight());
		m_ps.startRoundCount = 0;
		m_BGRect.x = -2400; m_BGRect.y = 0;
		initialiseText(std::to_string(m_timer), 0, 700);
		renderQuad->x = 1000;
		if (m_gameOver) {
			*m_currentGameState = GameState::Menu;

			for (Player * p : m_players) {
				Entity * ent = (Entity *)p;
				TagComponent * tag = (TagComponent*)ent->getCompByType("TAG");
				tag->setScore(0);
			}
			SDL_RenderSetScale(m_renderer, 1.0f, 1.0f);
			m_timer = 5;
			m_gameOver = false;
			highest = 0;
		}
	}
}

void PlayScreen::checkRoundOver() {
	
	if (*m_online && !m_roundEnd) {
		m_roundEnd = onlineRoundOver();
	}
	else {
		int dead = 0;
		if (!m_multiplayer) {
			Entity * ent = (Entity *)m_players[0];
			ControlComponent * control = (ControlComponent*)ent->getCompByType("CONTROL");
			if (!control->getAlive()) {
				if (!m_drawRoundText) {
					initialiseText("AI Wins", 1, 200);
					winnerRenderQuad->x = 600;

					m_drawRoundText = true;
				}
				if (m_timer < 5)
					m_timer = 10;
				m_roundEnd = true;

			}
		}
		
		for (Player * p : m_players) {
			Entity * ent = (Entity *)p;
			ControlComponent * control = (ControlComponent*)ent->getCompByType("CONTROL");
			if (!control->getAlive()) {
				dead++;

			}
		}
		
		for (AI * ai : m_aiCharacters) {
			Entity * ent = (Entity *)ai;
			ControlComponent * control = (ControlComponent*)ent->getCompByType("CONTROL");
			if (!control->getAlive()) {
				dead++;
			}
		}
		if (dead >= 3) {
			if (!m_drawRoundText) {
				for (Player * p : m_players) {
					Entity * ent = (Entity *)p;
					ControlComponent * control = (ControlComponent*)ent->getCompByType("CONTROL");
					TagComponent * tag = (TagComponent*)ent->getCompByType("TAG");
					if (control->getAlive()) {
						tag->setScore(tag->getScore() + 1);
						initialiseText(tag->getSubTag() + " Wins!", 1, 200);
						winnerRenderQuad->x = 150;
						checkScore();
					}
				}
				m_drawRoundText = true;
			}
			m_roundEnd = true;
			if (m_timer < 5)
				m_timer = 10;
		}
	}

	if (m_roundEnd) {
		endRound();
	}
}

void PlayScreen::checkScore()
{
	for (Entity * ent : m_playerents) {
		TagComponent * tag = (TagComponent*)ent->getCompByType("TAG");

		
		if (tag->getScore() >= highest)
		{
			highest = tag->getScore();
			tag->setLeader(true);
		}
		else
		{
			tag->setLeader(false);
		}

	}
}