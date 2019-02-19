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

	pistol = new Gun(renderer, 1, 1500, 100);
	shotgun = new Gun(renderer, 2, 1000, 100);
	juicer = new Gun(renderer, 3, 200, 100);
	grenade = new Gun(renderer, 4, 500, 100);

	m_camera = new SDL_Rect{ 0, 0, 1200, 700 };
	m_cameraCentre = new c2v{ static_cast<float>(m_camera->x + m_camera->w / 2), static_cast<float>(m_camera->y + m_camera->h / 2) };

	m_ents.push_back((Entity*)pistol);
	m_ents.push_back((Entity*)shotgun);
	m_ents.push_back((Entity*)grenade);
	m_ents.push_back((Entity*)juicer);

}

void PlayScreen::initialise(bool online, int size, int num) {

	
	if (online) {
		m_players.push_back(new Player(m_renderer, 600 + (100 * num), 200, SDL_GameControllerOpen(0), num));

		m_leftHands.push_back(new Hand(m_renderer, 1, num));
		m_rightHands.push_back(new Hand(m_renderer, 2, num));
			

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
				m_networkCharacters.push_back(new Player(m_renderer, 600 + (100 * i), 200, SDL_GameControllerOpen(i), i));
				m_leftHands.push_back(new Hand(m_renderer, 1, i));
				m_rightHands.push_back(new Hand(m_renderer, 2, i));
			}
		}
		if (num > 1) {
			for (int i = num - 1; i > 0; i--) {
				m_networkCharacters.push_back(new Player(m_renderer, 600 + (100 * i), 200, SDL_GameControllerOpen(i), i));
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

		/*for (int i = 0; i < (4 - size); i++) {
		m_aiCharacters.push_back(new AI(m_renderer, 500.0 + (100.0 * i), 100.0));
		}*/

	}
	else {
		for (int i = 0; i < SDL_NumJoysticks(); i++) {
			m_players.push_back(new Player(m_renderer, 600 + (100 * i), 200, SDL_GameControllerOpen(i), i));
			m_leftHands.push_back(new Hand(m_renderer, 1, i));
			m_rightHands.push_back(new Hand(m_renderer, 2, i));
		}

		for (int i = 0; i < (4 - SDL_NumJoysticks()); i++) {
			m_aiCharacters.push_back(new AI(m_renderer, 500.0 + (100.0 * i), 100.0));
			m_leftHands.push_back(new Hand(m_renderer, 1, 4));
			m_rightHands.push_back(new Hand(m_renderer, 2, 4));
		}
		for (Player * net : m_players) {
			m_hs.addEntity((Entity*)net);
			m_rs.addEntity((Entity*)net);
			m_ps.addEntity((Entity*)net);
			m_restartSys.addEntity((Entity*)net);
			m_collSys.addEntity((Entity*)net);
			m_cs.addEntity((Entity*)net);

		}
	
	}

	m_rs.addEntity((Entity*)pistol);
	m_rs.addEntity((Entity*)grenade);
	m_rs.addEntity((Entity*)shotgun);
	m_rs.addEntity((Entity*)juicer);

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

	m_cs.addEntity((Entity*)pistol);
	m_cs.addEntity((Entity*)shotgun);
	m_cs.addEntity((Entity*)juicer);
	m_cs.addEntity((Entity*)grenade);







	m_ps.addEntity((Entity*)pistol);
	m_ps.addEntity((Entity*)shotgun);
	m_ps.addEntity((Entity*)juicer);
	m_ps.addEntity((Entity*)grenade);

	m_ps.registerAudioObserver(m_audioObserver);


	m_guns.addEntity((Entity*)pistol);

	m_guns.addEntity((Entity*)shotgun);
	m_guns.addEntity((Entity*)juicer);

	m_guns.addEntity((Entity*)grenade);

	m_collSys.addEntity((Entity*)pistol);
	m_collSys.addEntity((Entity*)shotgun);
	m_collSys.addEntity((Entity*)juicer);
	m_collSys.addEntity((Entity*)grenade);

	m_grenadeSys.addEntity((Entity*)grenade);



	for (AI * ai : m_aiCharacters) {

		m_collSys.addEntity((Entity*)ai);
		m_ais.addEntity((Entity*)ai);
		m_rs.addEntity((Entity*)ai);
		m_ps.addEntity((Entity*)ai);
		m_restartSys.addEntity((Entity*)ai);
	}


	m_restartSys.addEntity((Entity*)pistol);
	m_restartSys.addEntity((Entity*)shotgun);
	m_restartSys.addEntity((Entity*)juicer);
	m_restartSys.addEntity((Entity*)grenade);

	m_ais.recieveLevel(m_map->getWalkPoints(), m_map->getJumpPoints(), m_map->getWidth(), m_map->getHeight());
	m_ps.setRenderer(m_renderer);
	m_grenadeSys.setRenderer(m_renderer);
	m_collSys.setRenderer(m_renderer);
	m_animationsSys.setRenderer(m_renderer);
}

void PlayScreen::update(bool * online, SDL_Event event, int size, Client * client) {

	if (m_startGame) {

		initialise(*online, size, client->number);
		m_startGame = false;
	}

	m_cs.update(event);
	m_collSys.update(m_map->getTiles());
	m_ps.update(m_renderer);
	m_guns.update();
	SDL_RenderSetScale(m_renderer, 0.69, 0.5);
	m_ps.bulletUpdate(m_renderer);
	m_grenadeSys.update(m_map->getTiles(), m_aiCharacters);
	m_ais.update();
	m_ais.receive(m_ents);
	m_hs.update();
	m_animationsSys.update();
	checkRoundOver();
	if (!(*online)) {

	}
	else {
		if (client->packet->message == 5) {
			m_netSystem.update(client->packet);
		}
		Entity * ent = (Entity*)m_players[0];
		ControlComponent * cc = (ControlComponent*)ent->getCompByType("CONTROL");
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
		client->sendMessage(p);
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
	m_animationsSys.render();
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


void PlayScreen::checkRoundOver() {
	bool roundEnd = false;
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
		roundEnd = true;
	}
	if (roundEnd) {
		m_roundCounter++;

		if (m_roundCounter > ROUND_OVER) {
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
}