#pragma once
#include "Entity.h"
#include <SDL.h>
#include <vector>
#include "Components/SpriteComponent.h"


class Gun : Entity
{
public:
	Gun();
	Gun(SDL_Renderer* renderer);
private:
	std::vector<Component*> m_components;
	SpriteComponent* m_spriteComponent;
};