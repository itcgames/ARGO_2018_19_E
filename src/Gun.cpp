#include "..\src\Gun.h"
Gun::Gun()
{

}


Gun::Gun(SDL_Renderer* renderer,int gunValue,float xPos,float yPos,int id,SDL_Texture * gunTexture)
{
	m_tagComponent = new TagComponent("Gun");
	m_tagComponent->setSubTag2(std::to_string(id));

	if (gunValue == 1)
	{
		m_spriteComponent = new SpriteComponent(0, 0, 210, 295);
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 0.2f, 0.2f });
		m_spriteComponent->setTexture(gunTexture,210,295);
		this->addComponent(m_spriteComponent);
		m_tagComponent->setSubTag("pistol");
		m_collisionComponent = new CollisionComponent(xPos, yPos, m_spriteComponent->getWidth(), m_spriteComponent->getHeight());
		this->addComponent(m_collisionComponent);
		
	}
	else if(gunValue == 2)
	{
		m_spriteComponent = new SpriteComponent(0, 0, 34, 140);
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 2.0f, 1.5f });
		m_spriteComponent->setTexture(gunTexture,34,140);
		this->addComponent(m_spriteComponent);
		m_tagComponent->setSubTag("shotgun");
		m_collisionComponent = new CollisionComponent(xPos, yPos, m_spriteComponent->getWidth(), m_spriteComponent->getHeight());
		this->addComponent(m_collisionComponent);
	}
	else if (gunValue == 3)
	{
		m_spriteComponent = new SpriteComponent(0, 0, 100, 150);
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 2.0f, 2.0f });
		m_spriteComponent->setTexture(gunTexture,100,150);
		this->addComponent(m_spriteComponent);
		m_tagComponent->setSubTag("juicer");
		m_collisionComponent = new CollisionComponent(xPos, yPos, m_spriteComponent->getWidth(), m_spriteComponent->getHeight());
		this->addComponent(m_collisionComponent);
	}
	else if (gunValue == 4)
	{
		m_spriteComponent = new SpriteComponent(0, 0, 150, 200);
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 0.2f, 0.2f });
		m_spriteComponent->setTexture(gunTexture,150,200);
		this->addComponent(m_spriteComponent);
		m_tagComponent->setSubTag("grenade");
		m_collisionComponent = new CollisionComponent(xPos, yPos, m_spriteComponent->getWidth(), m_spriteComponent->getHeight());
		this->addComponent(m_collisionComponent);
		this->addComponent(new GrenadeComponent());
	}
	else if (gunValue == 5)
	{
		m_spriteComponent = new SpriteComponent(0, 0, 12, 136);
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 2.0f, 2.0f });
		m_spriteComponent->setTexture(gunTexture,12,136);
		this->addComponent(m_spriteComponent);
		m_tagComponent->setSubTag("stabbyboy");
		m_collisionComponent = new CollisionComponent(xPos, yPos, m_spriteComponent->getWidth(), m_spriteComponent->getHeight());
		this->addComponent(m_collisionComponent);
	}

	m_positionComponent = new PositionComponent(xPos, yPos);
	this->addComponent(m_positionComponent);
	this->addComponent(new ControlComponent());
	this->addComponent(m_tagComponent);
	this->addComponent(new FactoryComponent());


}

void Gun::setGunAs(SDL_Renderer* renderer, int gunValue, float xPos, float yPos, int id, SpriteComponent * gunSprite) {

	std::cout << "X = " << xPos << std::endl;
	m_tagComponent->setSubTag2(std::to_string(id));
	m_positionComponent->setX(xPos);
	m_positionComponent->setY(yPos);
	if (gunValue == 1)
	{
		m_spriteComponent->setSRect(gunSprite->getSRect());
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 0.2f, 0.2f });
		m_spriteComponent->setTexture(gunSprite->getTexture(), 210, 295);
		m_tagComponent->setSubTag("pistol");
		m_collisionComponent->setW(m_spriteComponent->getWidth());
		m_collisionComponent->setH(m_spriteComponent->getHeight());
		m_collisionComponent->setX(xPos);
		m_collisionComponent->setY(yPos);
	}
	else if (gunValue == 2)
	{
		m_spriteComponent->setSRect(gunSprite->getSRect());
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 2.0f, 1.5f });
		m_spriteComponent->setTexture(gunSprite->getTexture(), 34, 140);
		m_tagComponent->setSubTag("shotgun");
		m_collisionComponent->setW(m_spriteComponent->getWidth());
		m_collisionComponent->setH(m_spriteComponent->getHeight());
		m_collisionComponent->setX(xPos);
		m_collisionComponent->setY(yPos);
	}
	else if (gunValue == 3)
	{
		m_spriteComponent->setSRect(gunSprite->getSRect());
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 2.0f, 2.0f });
		m_spriteComponent->setTexture(gunSprite->getTexture(), 100, 150);
		m_tagComponent->setSubTag("juicer");
		m_collisionComponent->setW(m_spriteComponent->getWidth());
		m_collisionComponent->setH(m_spriteComponent->getHeight());
		m_collisionComponent->setX(xPos);
		m_collisionComponent->setY(yPos);
	}
	else if (gunValue == 4)
	{
		m_spriteComponent->setSRect(gunSprite->getSRect());
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 0.2f, 0.2f });
		m_spriteComponent->setTexture(gunSprite->getTexture(), 150, 200);
		m_tagComponent->setSubTag("grenade");
		m_collisionComponent->setW(m_spriteComponent->getWidth());
		m_collisionComponent->setH(m_spriteComponent->getHeight());
		m_collisionComponent->setX(xPos);
		m_collisionComponent->setY(yPos);
		this->addComponent(new GrenadeComponent());
	}
	else if (gunValue == 5)
	{
		m_spriteComponent->setSRect(gunSprite->getSRect());
		m_spriteComponent->setPosition(c2v{ xPos, yPos });
		m_spriteComponent->setScale(c2v{ 2.0f, 2.0f });
		m_spriteComponent->setTexture(gunSprite->getTexture(), 12, 136);
		m_tagComponent->setSubTag("stabbyboy");
		m_collisionComponent->setW(m_spriteComponent->getWidth());
		m_collisionComponent->setH(m_spriteComponent->getHeight());
		m_collisionComponent->setX(xPos);
		m_collisionComponent->setY(yPos);

	}
}