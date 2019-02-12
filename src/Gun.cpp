#include "..\src\Gun.h"
Gun::Gun()
{

}


Gun::Gun(SDL_Renderer* renderer,int gunValue,float xPos,float yPos)
{
	m_tagComponent = new TagComponent("Gun");

	if (gunValue == 1)
	{
		m_spriteComponent = new SpriteComponent(0, 0, 210, 295);
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 0.2f, 0.2f });
		this->addComponent(m_spriteComponent);
		m_spriteComponent->loadFromFile("assets/pistol.png", renderer);
		m_tagComponent->setSubTag("pistol");
		this->addComponent(new CollisionComponent(xPos, yPos, m_spriteComponent->getWidth(), m_spriteComponent->getHeight()));
		
	}
	else if(gunValue == 2)
	{
		m_spriteComponent = new SpriteComponent(0, 0, 210, 1036);
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 0.2f, 0.2f });
		this->addComponent(m_spriteComponent);
		m_spriteComponent->loadFromFile("assets/shotgun.png", renderer);
		m_tagComponent->setSubTag("shotgun");
		this->addComponent(new CollisionComponent(xPos, yPos, m_spriteComponent->getWidth(), m_spriteComponent->getHeight()));
	}
	else if (gunValue == 3)
	{
		m_spriteComponent = new SpriteComponent(0, 0, 142, 268);
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 1.0f, 1.0f });
		this->addComponent(m_spriteComponent);
		m_spriteComponent->loadFromFile("assets/JuiceBox.png", renderer);
		m_tagComponent->setSubTag("juicer");
		this->addComponent(new CollisionComponent(xPos, yPos, m_spriteComponent->getWidth(), m_spriteComponent->getHeight()));
	}

	this->addComponent(new PositionComponent(xPos, yPos));
	this->addComponent(new ControlComponent());
	this->addComponent(m_tagComponent);
	this->addComponent(new FactoryComponent());


}