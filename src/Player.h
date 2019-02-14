#pragma once
#include "Entity.h"
#include <SDL.h>
#include <vector>
#include "Components/SpriteComponent.h"
#include "Systems/ControlSystem.h"


class Player : Entity
{
public:
	Player();
	Player(SDL_Renderer* renderer, float x, float y, SDL_GameController* controller);

	void render(SDL_Renderer* renderer);

private:
	std::vector<Component*> m_components;
	PositionComponent* positionComp;
	ControlComponent* controlComp;
	SpriteComponent* m_spriteComponent;
	SpriteComponent* m_spriteComponentHead;
	SpriteComponent* m_spriteComponentLeftFoot;
	SpriteComponent* m_spriteComponentRightFoot;

	int runCount = 0;
	int fallCount = 0;
	int headCount = 0;
	int totalHeadTime = 0;

	bool animateHead = false;
	bool animateHeadUp = true;

	int firingCount = 0;

	bool animationBool = true;
	bool fallingBool = true;
	float oldY = 0;
	float newY = 0;
	bool falling = false;
	


	float rumbleCount = 0;
};