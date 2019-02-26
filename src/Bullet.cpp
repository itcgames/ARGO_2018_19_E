#include "..\src\Factory.h"
#include "Camera.h"


Bullet::Bullet(SDL_Renderer* renderer, float xPos, float yPos, double angle, double xOffset, double yOffset, int ttl)
{
	//Set up Sprite component and add to entity component vector
	m_spriteComponent = new SpriteComponent(0, 0, 210, 295);
	m_spriteComponent->loadFromFile("assets/bullet.png", renderer);
	m_spriteComponent->setPosition(c2v{ xPos, yPos });
	m_spriteComponent->setScale(c2v{0.1f, 0.1f});
	m_spriteComponent->setRotation(angle);
	m_pos = c2v{ xPos, yPos };
	xVel = xOffset;
	yVel = yOffset;

	m_ttl = ttl;

	collider.min = m_pos;
	collider.max = c2v{ m_pos.x + m_spriteComponent->getWidth(), m_pos.y + m_spriteComponent->getHeight() };
}

void Bullet::render(SDL_Renderer* renderer, Camera* camera) {

	collider.min = m_pos;
	collider.max = c2v{ m_pos.x + m_spriteComponent->getWidth(), m_pos.y + m_spriteComponent->getHeight() };

	m_pos = c2v{ m_pos.x + xVel / 5, m_pos.y + yVel / 5 };

	c2v* screenPos = new c2v{ 0, 0 };
	screenPos->x = m_spriteComponent->getPosition().x - camera->getCamera()->x;
	screenPos->y = m_spriteComponent->getPosition().y - camera->getCamera()->y;

	m_spriteComponent->setPosition(c2v{screenPos->x, screenPos->y});
	m_spriteComponent->render(renderer);
	delete screenPos;
	
}

c2v Bullet::getPosition()
{
	return m_pos;
}
