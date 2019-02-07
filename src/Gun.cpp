#include "..\src\Gun.h"
Gun::Gun()
{

}


Gun::Gun(SDL_Renderer* renderer)
{
	//Set up Sprite component and add to entity component vector
	m_spriteComponent = new SpriteComponent(0, 0, 210, 295);
	m_spriteComponent->loadFromFile("assets/pistol.png", renderer);
	m_spriteComponent->setPosition(c2v{ 200, 100 });
	m_spriteComponent->setScale(c2v{ 0.2f, 0.2f });
	this->addComponent(m_spriteComponent);

	//this->addComponent(new HealthComponent(10));
	this->addComponent(new PositionComponent(200, 100));
	this->addComponent(new ControlComponent());
	this->addComponent(new TagComponent("Gun"));
	this->addComponent(new FactoryComponent());
}
