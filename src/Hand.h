#pragma once
#include "Entity.h"
#include <SDL.h>
#include <vector>
#include "Components/SpriteComponent.h"


class Hand : Entity
{
public:
	Hand();
	Hand(SDL_Renderer* renderer,int handValue);
private:
	std::vector<Component*> m_components;
	SpriteComponent* m_spriteComponent;
	TagComponent* m_tagComponent;
};