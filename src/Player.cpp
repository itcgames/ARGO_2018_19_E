#include "..\src\Player.h"
Player::Player()
{

}


Player::Player(SDL_Renderer* renderer)
{
	//Set up Sprite component and add to entity component vector
	m_spriteComponent = new SpriteComponent(0, 0, 257, 259);
	m_spriteComponent->loadFromFile("human.png", renderer);
	m_spriteComponent->setPosition(v2(300, 100));
	m_spriteComponent->setScale(v2(0.5f, 0.5f));
	this->addComponent(m_spriteComponent);

	this->addComponent(new HealthComponent(10));
	this->addComponent(new PositionComponent(300, 500));
	this->addComponent(new ControlComponent());
}