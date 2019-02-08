#include "..\src\Player.h"
Player::Player()
{

}




Player::Player(SDL_Renderer* renderer)
{
	//Set up Sprite component and add to entity component vector

	m_spriteComponent = new SpriteComponent(0, 0, 67, 94);
	m_spriteComponent->loadFromFile("assets/body.png", renderer);
	m_spriteComponent->setPosition(c2v{ 600, 200 });
	m_spriteComponent->setScale(c2v{0.5f, 0.5f});
	m_spriteComponent->setColor(255, 255, 0);
	this->addComponent(m_spriteComponent);

	m_spriteComponentHead = new SpriteComponent(0, 0, 107, 91);
	m_spriteComponentHead->loadFromFile("assets/Head2.png", renderer);
	m_spriteComponentHead->setPosition(c2v{ 600, 200 });
	m_spriteComponentHead->setScale(c2v{ 0.5f, 0.5f });
	m_spriteComponentHead->setColor(255, 255, 255);
	m_spriteComponentHead->render(renderer);


	this->addComponent(new HealthComponent(10));
	this->addComponent(new TagComponent("Player"));

	positionComp = new PositionComponent(100, 100);
	this->addComponent(positionComp);
	this->addComponent(new ControlComponent());
	this->addComponent(new CollisionComponent(300, 500, m_spriteComponent->getWidth(), m_spriteComponent->getHeight()));
}
void Player::render(SDL_Renderer* renderer) {
	m_spriteComponentHead->m_flipValue = m_spriteComponent->m_flipValue;
	if (m_spriteComponentHead->m_flipValue == SDL_FLIP_NONE)
	{
		m_spriteComponentHead->setPosition(c2v{ positionComp->getX(),positionComp->getY() - 50 });
	}
	else {
		m_spriteComponentHead->setPosition(c2v{ positionComp->getX() - 20,positionComp->getY() - 50 });
	}
	m_spriteComponentHead->render(renderer);
}