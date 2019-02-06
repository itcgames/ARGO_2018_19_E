#pragma once
#include "Entity.h"
#include <SDL.h>
#include <vector>
#include "Components/SpriteComponent.h"


class Player : Entity
{
public:
	Player();
	Player(SDL_Renderer* renderer);

private:
	std::vector<Component*> m_components;
	SpriteComponent* m_spriteComponent;
	SpriteComponent* m_spriteComponent2;
};