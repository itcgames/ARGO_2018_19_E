#include "..\src\Hand.h"
Hand::Hand()
{

}


Hand::Hand(SDL_Renderer* renderer)
{
	//Set up Sprite component and add to entity component vector

	m_spriteComponent = new SpriteComponent(0, 0, 257, 259);
	m_spriteComponent->loadFromFile("assets/Hand.png", renderer);
	m_spriteComponent->setPosition(c2v{300, 100});
	m_spriteComponent->setScale(c2v{ 0.5f, 0.5f });
	this->addComponent(m_spriteComponent);

	this->addComponent(new HealthComponent(10));
	this->addComponent(new TagComponent("Hand"));
	this->addComponent(new PositionComponent(300, 500));
	this->addComponent(new ControlComponent());
}