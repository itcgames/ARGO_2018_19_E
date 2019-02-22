#include "..\src\Player.h"
Player::Player()
{

}




Player::Player(SDL_Renderer* renderer, float x, float y, SDL_GameController* controller, int index, TTF_Font* font)

{
	Font = font;
	m_renderer = renderer;
	//Set up Sprite component and add to entity component vector
	oldY = 0;
	m_spriteComponent = new SpriteComponent(0, 0, 67, 150);
	m_spriteComponent->loadFromFile("assets/bodyTall.png", renderer);
	m_spriteComponent->setPosition(c2v{ x, y });
	m_spriteComponent->setScale(c2v{0.5f, 0.5f});
	m_spriteComponent->setColor(255, 255, 0);
	this->addComponent(m_spriteComponent);

	m_spriteComponentHead = new SpriteComponent(0, 0, 330, 330);
	if (index == 0)
	{
		m_spriteComponentHead->loadFromFile("assets/assets/art/character/finished_character_assets/headGuy.png", renderer);
	}
	else if (index == 1)
	{
		m_spriteComponentHead->loadFromFile("assets/assets/art/character/finished_character_assets/headGuy2.png", renderer);
	}
	else if (index == 2)
	{
		m_spriteComponentHead->loadFromFile("assets/assets/art/character/finished_character_assets/headGuy3.png", renderer);
	}
	else if (index == 3)
	{
		m_spriteComponentHead->loadFromFile("assets/assets/art/character/finished_character_assets/headGuy4.png", renderer);
	}
	m_spriteComponentHead->setPosition(c2v{ x, y });
	m_spriteComponentHead->setScale(c2v{ 0.2f, 0.28f });


	m_spriteComponentLeftFoot = new SpriteComponent(0, 0, 107, 91);
	m_spriteComponentLeftFoot->loadFromFile("assets/Foot.png", renderer);
	m_spriteComponentLeftFoot->setPosition(c2v{ x, y });
	m_spriteComponentLeftFoot->setScale(c2v{ 0.5f, 0.5f });

	m_spriteComponentRightFoot = new SpriteComponent(0, 0, 107, 91);
	m_spriteComponentRightFoot->loadFromFile("assets/Foot.png", renderer);
	m_spriteComponentRightFoot->setPosition(c2v{ x, y });
	m_spriteComponentRightFoot->setScale(c2v{ 0.5f, 0.5f });

	m_spriteComponentHead->setColor(255, 255, 255);

	m_marker = new SpriteComponent(0, 0, 100, 100);
	m_marker->loadFromFile("assets/marker.png", renderer);
	m_marker->setPosition(c2v{ x, y - 150});
	m_marker->setScale(c2v{ 0.1f, 0.1f });


	this->addComponent(new HealthComponent(10));
	TagComponent * tag = new TagComponent("Player");
	if (index == 0)
	{
		tag->setSubTag("Player1");
		initialiseText(std::to_string(index + 1), m_marker->getPosition().x, m_marker->getPosition().y);
	}
	else if (index == 1)
	{
		tag->setSubTag("Player2");
		initialiseText(std::to_string(index + 1), m_marker->getPosition().x, m_marker->getPosition().y);
	}
	else if (index == 2)
	{
		tag->setSubTag("Player3");
		initialiseText(std::to_string(index + 1), m_marker->getPosition().x, m_marker->getPosition().y);
	}
	else if (index == 3)
	{
		tag->setSubTag("Player4");
		initialiseText(std::to_string(index + 1), m_marker->getPosition().x, m_marker->getPosition().y);
	}
	else {
		tag->setSubTag("AIPlayer");
	}
	this->addComponent(tag);

	positionComp = new PositionComponent(x, y);
	this->addComponent(positionComp);
	controlComp = new ControlComponent();
	controlComp->gGameController = controller;
	controlComp->m_playerNum = index;
	this->addComponent(controlComp);
	this->addComponent(new CollisionComponent(x, y, m_spriteComponent->getWidth(), m_spriteComponent->getHeight()));
}
void Player::render(SDL_Renderer* renderer, Camera* camera) {

	m_marker->setPosition(c2v{ m_spriteComponent->getPosition().x + 17 - (startBalloonCount * 40), m_spriteComponent->getPosition().y - 150 - startBalloonFlightCount });
	m_marker->setScale(c2v{ 0.1f + startBalloonCount, 0.1f + startBalloonCount });
	if (startBalloonCount < 0.8)
	{
		startBalloonCount = startBalloonCount + 0.01;
	}
	else {
		startBalloonFlightCount = startBalloonFlightCount + 5;
	}

	renderQuad.x = m_marker->getPosition().x + (startBalloonCount * 40);
	renderQuad.y = m_marker->getPosition().y + (startBalloonCount * 30);
	renderQuad.w = startBalloonCount * 30;  //30
	renderQuad.h = startBalloonCount * 50;  //50

	if (controlComp->getAlive() == false) {
		if (controlComp->getHitFrom() == "right")
		{
			m_spriteComponentLeftFoot->setPosition(c2v{ m_spriteComponentLeftFoot->getPosition().x + 10, m_spriteComponentLeftFoot->getPosition().y + 10 });
			m_spriteComponentRightFoot->setPosition(c2v{ m_spriteComponentRightFoot->getPosition().x - 10, m_spriteComponentRightFoot->getPosition().y + 10 });
			m_spriteComponentHead->setPosition(c2v{ m_spriteComponentHead->getPosition().x + 10, m_spriteComponentHead->getPosition().y - 10 });

			m_spriteComponentHead->rotate(3);
			m_spriteComponentLeftFoot->rotate(3);
			m_spriteComponentRightFoot->rotate(3);
		}
		else if (controlComp->getHitFrom() == "left")
		{
			m_spriteComponentLeftFoot->setPosition(c2v{ m_spriteComponentLeftFoot->getPosition().x - 10, m_spriteComponentLeftFoot->getPosition().y + 10 });
			m_spriteComponentRightFoot->setPosition(c2v{ m_spriteComponentRightFoot->getPosition().x + 10, m_spriteComponentRightFoot->getPosition().y + 10 });
			m_spriteComponentHead->setPosition(c2v{ m_spriteComponentHead->getPosition().x - 10, m_spriteComponentHead->getPosition().y - 10 });

			m_spriteComponentHead->rotate(-3);
			m_spriteComponentLeftFoot->rotate(-3);
			m_spriteComponentRightFoot->rotate(-3);
		}

		controlComp->setRight(false);
		controlComp->setLeft(false);

	}
	else if (controlComp->getAlive() == true)
	{
		// Animation loop for head when hitting ground
		if (animateHead == true)
		{
			if (totalHeadTime < 20)
			{
				totalHeadTime = totalHeadTime + 1;
				if (headCount > 10)
				{
					animateHeadUp = false;
				}
				else if (headCount < -10)
				{
					animateHeadUp = true;
				}
				if (animateHeadUp == true)
				{
					headCount = headCount + 1;
				}
				else if (animateHeadUp == false)
				{
					headCount = headCount - 1;

				}
			}
			else {
				headCount = 0;
				animateHead = false;
				animateHeadUp = true;
			}
		}
		if (controlComp->getJump())
		{
			rumbleCount = 0;
		}
		newY = positionComp->getVelY();
		if (newY != oldY)
		{
			falling = true;
			oldY = newY;
			if (rumbleCount < .99) {
				rumbleCount += 0.01;
			}
		}
		else {
			if (falling)
			{
				if (SDL_HapticRumblePlay(controlComp->getHaptic(), rumbleCount, 75) != 0)
				{
					printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
				}
				animateHead = true;
				totalHeadTime = 0;
				rumbleCount = 0;
			}
			falling = false;


		}
		m_spriteComponentHead->m_flipValue = m_spriteComponent->m_flipValue;
		m_spriteComponentLeftFoot->m_flipValue = m_spriteComponent->m_flipValue;
		m_spriteComponentRightFoot->m_flipValue = m_spriteComponent->m_flipValue;
		if (m_spriteComponentHead->m_flipValue == SDL_FLIP_NONE)
		{
			m_spriteComponentHead->setPosition(c2v{ positionComp->getX() - 10 + headCount / 2,positionComp->getY() - 75 + headCount });
			m_spriteComponentHead->setRotation(-headCount);

			m_spriteComponentLeftFoot->setPosition(c2v{ positionComp->getX() + runCount,positionComp->getY() + 52 });
			m_spriteComponentLeftFoot->setRotation(-runCount);

			m_spriteComponentRightFoot->setPosition(c2v{ positionComp->getX() - runCount,positionComp->getY() + 52 });
			m_spriteComponentRightFoot->setRotation(runCount);
		}
		else {
			m_spriteComponentHead->setPosition(c2v{ positionComp->getX() - 20 - headCount / 2,positionComp->getY() - 75 + headCount });
			m_spriteComponentHead->setRotation(headCount);

			m_spriteComponentLeftFoot->setPosition(c2v{ positionComp->getX() - 20 + runCount,positionComp->getY() + 52 });  // (Position - player offset + animationCount)
			m_spriteComponentLeftFoot->setRotation(-runCount);

			m_spriteComponentRightFoot->setPosition(c2v{ positionComp->getX() - 20 - runCount,positionComp->getY() + 52 });
			m_spriteComponentRightFoot->setRotation(runCount);
		}

		// Garbage make head go red.
		if (controlComp->getFire())
		{
			m_spriteComponentHead->setColor(255, 255 - firingCount, 255 - firingCount);
			if (firingCount < 255)
			{
				firingCount = firingCount + 1;
			}
		}
		else {
			m_spriteComponentHead->setColor(255, 255, 255);
			firingCount = 0;
		}

		// Checks if guy is moving on y but not x
		//if (positionComp->getVelY() >= 1
			//|| positionComp->getVelY() <= -1 ) 
		if (falling == true) {
			if (fallCount > 20)
			{
				fallingBool = false;
			}
			else if (fallCount < -20)
			{
				fallingBool = true;
			}
			if (fallingBool == true)
			{
				fallCount = fallCount + 3;
			}
			else if (fallingBool == false)
			{
				fallCount = fallCount - 3;

			}
			if (m_spriteComponentHead->m_flipValue == SDL_FLIP_NONE)
			{
				m_spriteComponentLeftFoot->setRotation(45 + fallCount);
				m_spriteComponentRightFoot->setRotation(45 - fallCount);
			}
			else {
				m_spriteComponentLeftFoot->setRotation(-45 + fallCount);
				m_spriteComponentRightFoot->setRotation(-45 - fallCount);
			}
		}
		// If checks if guy is moving on x but not y
		else if (positionComp->getVelX() >= 0.1 && positionComp->getVelY() <= 1 && positionComp->getVelY() >= -1
			|| positionComp->getVelX() <= -0.1 && positionComp->getVelY() <= 1 && positionComp->getVelY() >= -1)
		{
			// Controls what direction the feet move
			if (runCount > 30)
			{
				animationBool = false;
			}
			else if (runCount < -30)
			{
				animationBool = true;
			}
			if (animationBool == true)
			{
				float speed = positionComp->getVelX();
				speed = speed / 2;
				if (speed < 0)
				{
					speed = speed * -1;  // make sure is possitive so dont rip legs apart :).
				}
				runCount = runCount + speed;
			}
			else if (animationBool == false)
			{
				float speed = positionComp->getVelX();
				speed = speed / 2;
				if (speed < 0)
				{
					speed = speed * -1;  // make sure is possitive so dont rip legs apart :).
				}
				runCount = runCount - speed;

			}
			//std::cout << "RUN = " << runCount << std::endl;
			m_spriteComponentLeftFoot->setRotation(-runCount);
			m_spriteComponentRightFoot->setRotation(runCount);
		}
		// Guy is not moving at all.
		else {
			runCount = 0;
		}
	}

	
	//std::cout << "Y = "<< positionComp->getVelY() << std::endl;
	c2v* screenPos = new c2v{ m_spriteComponentHead->getPosition().x - camera->getCamera()->x, m_spriteComponentHead->getPosition().y - camera->getCamera()->y };
	m_spriteComponentHead->setPosition(*screenPos);
	m_spriteComponentHead->render(renderer);

	screenPos->x = static_cast<float>(m_spriteComponentLeftFoot->getPosition().x - camera->getCamera()->x);
	screenPos->y = static_cast<float>(m_spriteComponentLeftFoot->getPosition().y - camera->getCamera()->y);
	m_spriteComponentLeftFoot->setPosition(*screenPos);
	m_spriteComponentLeftFoot->render(renderer);

	screenPos->x = static_cast<float>(m_spriteComponentRightFoot->getPosition().x - camera->getCamera()->x);
	screenPos->y = static_cast<float>(m_spriteComponentRightFoot->getPosition().y - camera->getCamera()->y);
	m_spriteComponentRightFoot->setPosition(*screenPos);
	m_spriteComponentRightFoot->render(renderer);


	m_marker->render(renderer);
	SDL_RenderCopy(m_renderer, text, NULL, &renderQuad);
	delete screenPos;
}

void Player::initialiseText(std::string message, int x, int y) {
	round_text = message;
	textSurface = TTF_RenderText_Solid(Font, round_text.c_str(), textColor);
	text = SDL_CreateTextureFromSurface(m_renderer, textSurface);
	
	int text_width = textSurface->w;
	int text_height = textSurface->h;
	SDL_FreeSurface(textSurface);
	renderQuad = { x, y, 30, 50 };
}
