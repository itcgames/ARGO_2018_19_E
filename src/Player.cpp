#include "..\src\Player.h"
Player::Player()
{

}




Player::Player(SDL_Renderer* renderer)
{
	//Set up Sprite component and add to entity component vector

	m_spriteComponent = new SpriteComponent(0, 0, 67, 150);
	m_spriteComponent->loadFromFile("assets/bodyTall.png", renderer);
	m_spriteComponent->setPosition(c2v{ 600, 200 });
	m_spriteComponent->setScale(c2v{0.5f, 0.5f});
	this->addComponent(m_spriteComponent);

	m_spriteComponentHead = new SpriteComponent(0, 0, 107, 91);
	m_spriteComponentHead->loadFromFile("assets/Head2.png", renderer);
	m_spriteComponentHead->setPosition(c2v{ 600, 200 });
	m_spriteComponentHead->setScale(c2v{ 0.5f, 0.5f });

	m_spriteComponentLeftFoot = new SpriteComponent(0, 0, 107, 91);
	m_spriteComponentLeftFoot->loadFromFile("assets/Foot.png", renderer);
	m_spriteComponentLeftFoot->setPosition(c2v{ 600, 200 });
	m_spriteComponentLeftFoot->setScale(c2v{ 0.5f, 0.5f });

	m_spriteComponentRightFoot = new SpriteComponent(0, 0, 107, 91);
	m_spriteComponentRightFoot->loadFromFile("assets/Foot.png", renderer);
	m_spriteComponentRightFoot->setPosition(c2v{ 600, 200 });
	m_spriteComponentRightFoot->setScale(c2v{ 0.5f, 0.5f });


	this->addComponent(new HealthComponent(10));
	this->addComponent(new TagComponent("Player"));

	positionComp = new PositionComponent(100, 100);
	this->addComponent(positionComp);
	this->addComponent(new ControlComponent());
	this->addComponent(new CollisionComponent(300, 500, m_spriteComponent->getWidth(), m_spriteComponent->getHeight()));
}
void Player::render(SDL_Renderer* renderer) {
	m_spriteComponentHead->m_flipValue = m_spriteComponent->m_flipValue;
	m_spriteComponentLeftFoot->m_flipValue = m_spriteComponent->m_flipValue;
	m_spriteComponentRightFoot->m_flipValue = m_spriteComponent->m_flipValue;
	if (m_spriteComponentHead->m_flipValue == SDL_FLIP_NONE)
	{
		m_spriteComponentHead->setPosition(c2v{ positionComp->getX(),positionComp->getY() - 50 });
		m_spriteComponentLeftFoot->setPosition(c2v{ positionComp->getX() + runCount,positionComp->getY() + 52});
		m_spriteComponentLeftFoot->setRotation(-runCount);
		m_spriteComponentRightFoot->setPosition(c2v{ positionComp->getX() - runCount,positionComp->getY() + 52});
		m_spriteComponentRightFoot->setRotation(runCount);
	}
	else {
		m_spriteComponentHead->setPosition(c2v{ positionComp->getX() - 20,positionComp->getY() - 50 });
		m_spriteComponentLeftFoot->setPosition(c2v{ positionComp->getX() - 20 + runCount,positionComp->getY() + 52});  // (Position - player offset + animationCount)
		m_spriteComponentLeftFoot->setRotation(-runCount);
		m_spriteComponentRightFoot->setPosition(c2v{ positionComp->getX() - 20 - runCount,positionComp->getY() + 52});
		m_spriteComponentRightFoot->setRotation(runCount);
	}
	m_spriteComponentHead->render(renderer);
	m_spriteComponentLeftFoot->render(renderer);
	m_spriteComponentRightFoot->render(renderer);

	if (positionComp->getVelX() >= 0.1 || positionComp->getVelX() <= -0.1)
	{
		if (runCount > 30)
		{
			animationBool = false;
		}
		if (runCount < -30)
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
	}
	else {
		runCount = 0;
	}

}