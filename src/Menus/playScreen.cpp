#include "playScreen.h"

PlayScreen::PlayScreen(SDL_Renderer * renderer, TTF_Font* font) {

	Font = font;

	m_renderer = renderer;

	testLight = new Light(c2v{ 0.0f, 300.0f }, 5, 22, 130, renderer);
	testLight->setPosition(c2v{ 400.0f, 0.0f });
	testLight->setSize(c2v{ 3.0f, 3.0f });

	m_audioObserver = new AudioObserver();
	m_audioObserver->load();


	m_backgroundSprite = new SpriteComponent(0, 0, 1920, 1080);
	m_backgroundSprite->loadFromFile("assets/cybercity.png", renderer);
	m_backgroundSprite->setPosition(c2v{ 0.0f, 0.0f });
	m_backgroundSprite->setScale(c2v{ 1.5f, 1.6f });

	m_map = new MapLoader();

	m_map->load("testlevel.tmx", renderer);

	m_guns.push_back(new Gun(renderer, 1, 1500, 100));
	m_guns.push_back(new Gun(renderer, 2, 1000, 100));
	m_guns.push_back(new Gun(renderer, 3, 200, 100));
	m_guns.push_back(new Gun(renderer, 4, 500, 100));

	m_camera = new SDL_Rect{ 0, 0, 1200, 700 };
	m_cameraCentre = new c2v{ static_cast<float>(m_camera->x + m_camera->w / 2), static_cast<float>(m_camera->y + m_camera->h / 2) };

	for (Gun * g : m_guns) {
		m_Gunents.push_back((Entity*)g);
		
	}


}

void PlayScreen::initialise(bool online, int size, int num) {
	*m_online = online;

	if (SDL_NumJoysticks() >= 2) {
		m_multiplayer = true;
	}
	else {
		m_multiplayer = false;
	}
	
	if (online) {

		//Place player at the first available spawn point
		for (int i = 0; i < m_map->getSpawnPoints().size(); i++)
		{
			if (m_map->getSpawnPoints().at(i)->first == false)
			{
				m_players.push_back(new Player(m_renderer, m_map->getSpawnPoints().at(i)->second.x, m_map->getSpawnPoints().at(i)->second.y, SDL_GameControllerOpen(0), num, Font));
				m_leftHands.push_back(new Hand(m_renderer, 1, num));
				m_rightHands.push_back(new Hand(m_renderer, 2, num));
				m_map->getSpawnPoints().at(i)->first = true;
				break;
			}
		}	

		m_animationsSys.addEntity((Entity*)m_players[0]);
		m_hs.addEntity((Entity*)m_players[0]);
		m_cs.addEntity((Entity*)m_players[0]);
		m_rs.addEntity((Entity*)m_players[0]);
		m_ps.addEntity((Entity*)m_players[0]);
		m_restartSys.addEntity((Entity*)m_players[0]);
		m_collSys.addEntity((Entity*)m_players[0]);

		m_hs.addEntity((Entity*)m_leftHands[0]);
		m_cs.addEntity((Entity*)m_leftHands[0]);
		m_rs.addEntity((Entity*)m_leftHands[0]);
		m_ps.addEntity((Entity*)m_leftHands[0]);
		m_restartSys.addEntity((Entity*)m_leftHands[0]);
		m_collSys.addEntity((Entity*)m_leftHands[0]);

		m_hs.addEntity((Entity*)m_rightHands[0]);
		m_cs.addEntity((Entity*)m_rightHands[0]);
		m_rs.addEntity((Entity*)m_rightHands[0]);
		m_ps.addEntity((Entity*)m_rightHands[0]);
		m_restartSys.addEntity((Entity*)m_rightHands[0]);
		m_collSys.addEntity((Entity*)m_rightHands[0]);
		
		if (num < size) {
			for (int i = num + 1; i <= size; i++) {
				Player * player = new  Player(m_renderer, 600 + (100 * i), 200, SDL_GameControllerOpen(i), i, Font);
				m_networkCharacters.push_back(player);
				m_leftHands.push_back(new Hand(m_renderer, 1, i));
				m_rightHands.push_back(new Hand(m_renderer, 2, i));
			}
		}

		if (num > 1) {
			for (int i = num - 1; i > 0; i--) { 
				Player * player = new  Player(m_renderer, 600 + (100 * i), 200, SDL_GameControllerOpen(i), i, Font);
				m_networkCharacters.push_back(player);
				m_leftHands.push_back(new Hand(m_renderer, 1, i));
				m_rightHands.push_back(new Hand(m_renderer, 2, i));
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

		for (int i = 0; i < (4 - size); i++) {

			for (int j = 0; j < m_map->getSpawnPoints().size(); j++)
			{
				if (m_map->getSpawnPoints().at(j)->first == false)
				{
					m_aiCharacters.push_back(new AI(m_renderer, m_map->getSpawnPoints().at(j)->second.x, m_map->getSpawnPoints().at(j)->second.y, size));
					m_map->getSpawnPoints().at(j)->first = true;
					
				}
			}
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
					m_aiCharacters.push_back(new AI(m_renderer, m_map->getSpawnPoints().at(j)->second.x, m_map->getSpawnPoints().at(j)->second.y, noOfPlayers));
					m_leftHands.push_back(new Hand(m_renderer, 1, 4));
					m_rightHands.push_back(new Hand(m_renderer, 2, 4));
					m_map->getSpawnPoints().at(j)->first = true;
					noOfPlayers += 1;
				}
			}
		}

		std::cout << noOfPlayers << std::endl;
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
	spawnGuns();
	m_cs.update(event);
	m_collSys.update(m_map->getTiles());
	m_ps.update(m_renderer);
	m_gunSys.update();
	SDL_RenderSetScale(m_renderer, 0.69, 0.5);
	m_ps.bulletUpdate(m_renderer);
	m_grenadeSys.update(m_map->getTiles(), m_aiCharacters, m_players);
	m_ais.update();
	m_ais.receive(m_Gunents, m_playerents);
	m_hs.update();
	//m_animationsSys.update();
	checkRoundOver();
	if (!(*online)) {

	}
	else {
		for (Entity * ent : m_netSystem.m_entities) {
			
			if (client->packet->message == 5) {
				m_netSystem.update(client->packet);

				client->receive();

			}

			
		}
		Entity * ent = (Entity*)m_players[0];
		ControlComponent * cc = (ControlComponent*)ent->getCompByType("CONTROL");
		PositionComponent * pc = (PositionComponent*)ent->getCompByType("POSITION");

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
	}
}

void PlayScreen::render(SDL_Renderer * renderer) {
	m_backgroundSprite->render(m_renderer);
	m_map->draw(m_renderer);
	for (AI * ai : m_aiCharacters) {
		ai->render(m_renderer);
	}
	for (Player *p : m_players) {
		p->render(m_renderer);
	}
	m_rs.render(m_renderer);
	m_ps.bulletRender(m_renderer);
	//m_animationsSys.render();
	testLight->render(m_renderer);
	m_grenadeSys.render();
	m_collSys.render();
	//m_emitter->update();
	if (m_drawRoundText) {
		SDL_RenderCopy(m_renderer, text, NULL, &renderQuad);
	}
}

void PlayScreen::initialiseText(std::string message) {
	round_text = message;
	textSurface = TTF_RenderText_Solid(Font, round_text.c_str(), textColor);
	text = SDL_CreateTextureFromSurface(m_renderer, textSurface);
	int text_width = textSurface->w;
	int text_height = textSurface->h;
	SDL_FreeSurface(textSurface);
	renderQuad = { 150, 200, text_width, text_height };
}

void PlayScreen::spawnGuns() {
	m_gunCounter++;

	if (m_gunCounter > SPAWN_NEW_GUN) {

		int gunType = (rand() % 4) + 1;
		int gunX = (rand() % 1100) + 100;
		Gun * gun = new Gun(m_renderer, gunType, gunX, -100);
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
		m_guns.push_back(gun);
		m_gunCounter = 0;
	}
}

void PlayScreen::deleteGuns() {
	while (m_guns.size() > 4) {
		Gun* gun = m_guns.back();
		m_guns.pop_back();
		m_restartSys.m_entities.pop_back();
		m_gunSys.m_entities.pop_back();
		m_cs.m_entities.pop_back();
		m_ps.m_entities.pop_back();
		m_rs.m_entities.pop_back();
		m_collSys.m_entities.pop_back();

		Entity* ent = (Entity*)gun;
		TagComponent* tc = (TagComponent*)ent->getCompByType("TAG");
		if (tc->getSubTag() == "grenade") {
			m_grenadeSys.m_entities.pop_back();
		}
		delete gun;
	}
}

bool PlayScreen::onlineRoundOver() {
	int dead = 0;
	for (AI * ai : m_aiCharacters) {
		Entity * ent = (Entity *)ai;
		AIComponent * ai = (AIComponent*)ent->getCompByType("AI");
		if (!ai->m_alive) {
			dead++;
		}
	}
	for (Player * p : m_players) {
		Entity * ent = (Entity *)p;
		ControlComponent * control = (ControlComponent*)ent->getCompByType("CONTROL");
		if (!control->getAlive()) {
			dead++;

		}
	}

	if (dead >= 3) {
		if (!m_drawRoundText) {
			initialiseText("Player Wins");
			m_drawRoundText = true;
		}
		return true;
	}
	return false;
}

void PlayScreen::endRound() {
	m_roundCounter++;

	if (m_roundCounter > ROUND_OVER) {
		deleteGuns();
		int randNum = (rand() % 3) + 1;
		m_restartSys.reset(randNum);
		if (randNum == 1) {
			m_map->load("testlevel.tmx", m_renderer);
		}
		else if (randNum == 2) {
			m_map->load("level3.tmx", m_renderer);
		}
		else if (randNum == 3) {
			m_map->load("level4.tmx", m_renderer);
		}
		m_roundCounter = 0;
		m_drawRoundText = false;
	}
}


void PlayScreen::checkRoundOver() {
	bool roundEnd = false;
	if (*m_online) {
		roundEnd = onlineRoundOver();
	}
	else {
		int dead = 0;

		if (!m_multiplayer) {
			Entity * ent = (Entity *)m_players[0];
			ControlComponent * control = (ControlComponent*)ent->getCompByType("CONTROL");
			if (!control->getAlive()) {
				if (!m_drawRoundText) {
					initialiseText("AI Wins");
					m_drawRoundText = true;
				}
				roundEnd = true;

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
			AIComponent * ai = (AIComponent*)ent->getCompByType("AI");
			if (!ai->m_alive) {
				dead++;
			}
		}
		if (dead >= 3) {
			if (!m_drawRoundText) {
				initialiseText("Player Wins");
				m_drawRoundText = true;
			}
			roundEnd = true;
		}
	}

	if (roundEnd) {
		endRound();
	}
}