#include "Light.h"

Light::Light()
{

}

Light::Light(c2v position, Uint8 r, Uint8 g, Uint8 b, SDL_Renderer* renderer)
{
	m_sprite = new SpriteComponent(0, 0, 512, 512);
	m_sprite->loadFromFile("assets/light.png", renderer);
	m_sprite->setColor(r, g, b);
	m_sprite->setScale(c2v{ 0.2f, 0.2f });
	m_sprite->setPosition(position);
	m_sprite->setBlendMode(SDL_BLENDMODE_ADD);
}

void Light::update()
{

}

void Light::render(SDL_Renderer* renderer)
{
	m_sprite->render(renderer);
}

