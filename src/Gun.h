#pragma once
#include "Entity.h"
#include <SDL.h>
#include <vector>
#include "Components/SpriteComponent.h"


class Gun : Entity
{
public:
	Gun();
	Gun(SDL_Renderer* renderer,int gunValue,float xPos,float yPos, int id,SDL_Texture * gunTexture);
	TagComponent* m_tagComponent;
	CollisionComponent* m_collisionComponent;
	SpriteComponent* m_spriteComponent;

	void setGunAs(SDL_Renderer* renderer, int gunValue, float xPos, float yPos, int id, SpriteComponent * gunTexture);
private:
	std::vector<Component*> m_components;
};