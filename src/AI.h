#pragma once
#include "Entity.h"
#include <SDL.h>
#include <vector>
#include "Components/SpriteComponent.h"
#include "Camera.h"


class AI : public Entity
{
public:
	AI();
	AI(SDL_Renderer* renderer,float xPos,float yPos, int noOfPlayers);

	void render(SDL_Renderer* renderer, Camera* camera);
private:
	std::vector<Component*> m_components;
	PositionComponent* positionComp;
	AIComponent* controlComp;
	SpriteComponent* m_spriteComponent;
	SpriteComponent* m_spriteComponentHead;
	SpriteComponent* m_spriteComponentLeftFoot;
	SpriteComponent* m_spriteComponentRightFoot;
	RayCastComponent * m_rayCastComp;
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

	ControlComponent * control;

	float rumbleCount = 0;
};