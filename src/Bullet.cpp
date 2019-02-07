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

	collider.min = c2v{ xPos, yPos };
	collider.max = c2v{ xPos + m_spriteComponent->getWidth(), yPos + m_spriteComponent->getHeight() };
}

void Bullet::render(SDL_Renderer* renderer) {

	m_spriteComponent->setPosition(c2v{ m_spriteComponent->getPosition().x + xVel / 5, m_spriteComponent->getPosition().y + yVel /5});
	m_spriteComponent->render(renderer);

	collider.min = c2v{ m_spriteComponent->getPosition().x, m_spriteComponent->getPosition().y };
	collider.max = c2v{ m_spriteComponent->getPosition().x + m_spriteComponent->getWidth(), m_spriteComponent->getPosition().y + m_spriteComponent->getHeight() };
}
