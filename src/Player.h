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

	void render(SDL_Renderer* renderer);

private:
	std::vector<Component*> m_components;
	PositionComponent* positionComp;
	SpriteComponent* m_spriteComponent;
	SpriteComponent* m_spriteComponentHead;
	SpriteComponent* m_spriteComponentLeftFoot;
	SpriteComponent* m_spriteComponentRightFoot;

	int runCount = 0;
	int fallCount = 0;
	bool animationBool = true;
	bool fallingBool = true;

};