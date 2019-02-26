#include "..\src\Factory.h"
#include "Camera.h"


Bullet::Bullet(SDL_Renderer* renderer, float xPos, float yPos, double angle, double xOffset, double yOffset, int ttl,SDL_Texture * bulletTexture)

{
	//Set up Sprite component and add to entity component vector
	m_spriteComponent = new SpriteComponent(0, 0, 210, 295);
	//m_spriteComponent->loadFromFile("assets/bullet.png", renderer);
	m_spriteComponent->setTexture(bulletTexture, 94, 274);
	m_spriteComponent->setPosition(c2v{ xPos, yPos });
	m_spriteComponent->setScale(c2v{0.1f, 0.1f});
	m_spriteComponent->setRotation(angle);
	xVel = xOffset;
	yVel = yOffset;

	m_ttl = ttl;

	collider.min = c2v{ xPos, yPos };
	collider.max = c2v{ xPos + m_spriteComponent->getWidth(), yPos + m_spriteComponent->getHeight() };
}

void Bullet::render(SDL_Renderer* renderer, Camera* camera) {

	collider.min = c2v{ m_spriteComponent->getPosition().x, m_spriteComponent->getPosition().y };
	collider.max = c2v{ m_spriteComponent->getPosition().x + m_spriteComponent->getWidth(), m_spriteComponent->getPosition().y + m_spriteComponent->getHeight() };

	c2v* screenPos = new c2v{ 0, 0 };
	screenPos->x = m_spriteComponent->getPosition().x - camera->getCamera()->x;
	screenPos->y = m_spriteComponent->getPosition().y - camera->getCamera()->y;

	m_spriteComponent->setPosition(c2v{ m_spriteComponent->getPosition().x + xVel / 5, m_spriteComponent->getPosition().y + yVel / 5 });
	//m_spriteComponent->setPosition(*screenPos);
	m_spriteComponent->render(renderer);
	delete screenPos;
	
}
