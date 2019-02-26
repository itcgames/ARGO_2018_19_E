#include "..\src\Hand.h"
Hand::Hand()
{

}


Hand::Hand(SDL_Renderer* renderer,int handValue,int index)
{
	//Set up Sprite component and add to entity component vector

	m_spriteComponent = new SpriteComponent(0, 0, 61, 58);
	m_spriteComponent->loadFromFile("assets/Hand.png", renderer);
	m_spriteComponent->setPosition(c2v{300, 100});
	m_spriteComponent->setScale(c2v{ 0.5f, 0.5f });
	this->addComponent(m_spriteComponent);

	this->addComponent(new HealthComponent(10));
	m_tagComponent = new TagComponent("Hand");
	if (handValue == 1)
	{
		m_tagComponent->setSubTag2("right");
	}
	else if (handValue == 2) {
		m_tagComponent->setSubTag2("left");
	}
	if (index == 0)
	{
		m_tagComponent->setSubTag("Player 1");
	}
	else if (index == 1)
	{
		m_tagComponent->setSubTag("Player 2");
	}
	else if (index == 2)
	{
		m_tagComponent->setSubTag("Player 3");
	}
	else if (index == 3)
	{
		m_tagComponent->setSubTag("Player 4");
	}
	else {
		m_tagComponent->setSubTag("AIPlayer");
	}
	this->addComponent(m_tagComponent);
	this->addComponent(new PositionComponent(300, 500));
	this->addComponent(new ControlComponent());
}