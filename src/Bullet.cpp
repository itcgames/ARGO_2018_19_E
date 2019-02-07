#include "..\src\Factory.h"


Bullet::Bullet(SDL_Renderer* renderer, float xPos, float yPos, double angle, double xOffset, double yOffset)
{
	//Set up Sprite component and add to entity component vector
	m_spriteComponent = new SpriteComponent(0, 0, 210, 295);
	m_spriteComponent->loadFromFile("assets/bullet.png", renderer);
	m_spriteComponent->setPosition(c2v{ xPos, yPos });
	m_spriteComponent->setScale(c2v{0.1f, 0.1f});
	m_spriteComponent->setRotation(angle);
	xVel = xOffset;
	yVel = yOffset;
	std::cout << "Angle = " << angle << std::endl;


	//this->addComponent(new HealthComponent(10));
	//this->addComponent(new TagComponent("Bullet"));
	//this->addComponent(new PositionComponent(600, 200));
	//this->addComponent(new ControlComponent());
	//this->addComponent(new CollisionComponent(300, 500, m_spriteComponent->getWidth(), m_spriteComponent->getHeight()));
}
void Bullet::render(SDL_Renderer* renderer)
{
	m_spriteComponent->setPosition(c2v{ m_spriteComponent->getPosition().x + xVel / 5, m_spriteComponent->getPosition().y + yVel /5});
	m_spriteComponent->render(renderer);
}
