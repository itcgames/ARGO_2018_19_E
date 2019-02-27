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
private:
	std::vector<Component*> m_components;
	SpriteComponent* m_spriteComponent;
	TagComponent* m_tagComponent;
};