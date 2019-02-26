#include "..\src\Gun.h"
Gun::Gun()
{

}


Gun::Gun(SDL_Renderer* renderer,int gunValue,float xPos,float yPos,int id)
{
	m_tagComponent = new TagComponent("Gun");
	m_tagComponent->setSubTag2(std::to_string(id));

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
		m_spriteComponent->setScale(c2v{ 2.0f, 1.5f });
		this->addComponent(m_spriteComponent);
		m_spriteComponent->loadFromFile("assets/art/character/finished_character_assets/Shotgun3.png", renderer);
		m_tagComponent->setSubTag("shotgun");
		this->addComponent(new CollisionComponent(xPos, yPos, m_spriteComponent->getWidth(), m_spriteComponent->getHeight()));
	}
	else if (gunValue == 3)
	{
		m_spriteComponent = new SpriteComponent(0, 0, 100, 150);
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 2.0f, 2.0f });
		this->addComponent(m_spriteComponent);
		m_spriteComponent->loadFromFile("assets/art/character/finished_character_assets/MiniGun.png", renderer);
		m_tagComponent->setSubTag("juicer");
		this->addComponent(new CollisionComponent(xPos, yPos, m_spriteComponent->getWidth(), m_spriteComponent->getHeight()));
	}
	else if (gunValue == 4)
	{
		m_spriteComponent = new SpriteComponent(0, 0, 150, 200);
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 0.2f, 0.2f });
		this->addComponent(m_spriteComponent);
		m_spriteComponent->loadFromFile("assets/grenade.png", renderer);
		m_tagComponent->setSubTag("grenade");
		this->addComponent(new CollisionComponent(xPos, yPos, m_spriteComponent->getWidth(), m_spriteComponent->getHeight()));
		this->addComponent(new GrenadeComponent());
	}
	else if (gunValue == 5)
	{
		m_spriteComponent = new SpriteComponent(0, 0, 12, 136);
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 2.0f, 2.0f });
		this->addComponent(m_spriteComponent);
		m_spriteComponent->loadFromFile("assets/art/character/finished_character_assets/Katana.png", renderer);
		m_tagComponent->setSubTag("stabbyboy");
		this->addComponent(new CollisionComponent(xPos, yPos, m_spriteComponent->getWidth(), m_spriteComponent->getHeight()));
	}

	this->addComponent(new PositionComponent(xPos, yPos));
	this->addComponent(new ControlComponent());
	this->addComponent(m_tagComponent);
	this->addComponent(new FactoryComponent());


}