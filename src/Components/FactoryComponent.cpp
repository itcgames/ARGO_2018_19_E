#include "FactoryComponent.h"

FactoryComponent::FactoryComponent()
{

}

std::string FactoryComponent::getType()
{
	return m_tag;
}

Bullet* FactoryComponent::makeBullet(SDL_Renderer* renderer, float xPos, float yPos, double angle, double xOffset, double yOffset, int ttl,SDL_Texture * bulletTexture)
{
	return factory->CreateBullet(renderer, xPos, yPos, angle, xOffset, yOffset, ttl,bulletTexture);
}