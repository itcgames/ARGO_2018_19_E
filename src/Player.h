#pragma once
#include "Entity.h"
#include <SDL.h>
#include <vector>
#include "Components/SpriteComponent.h"
#include "Systems/ControlSystem.h"
#include "Camera.h"

#include <SDL_ttf.h>

class Player : public Entity
{
public:
	Player();
	Player(SDL_Renderer* renderer, float x, float y, SDL_GameController* controller, int index, TTF_Font* font);

	void initialiseText(std::string message, int x, int y);
	void render(SDL_Renderer* renderer, Camera* camera);
	void renderMarker(SDL_Renderer* renderer);

	int m_index = -1;

	bool startDeath = false;
private:
	float startBalloonCount = 0.0f;
	float totalBalloonCount = 0.0f;
	bool balloonDeflate = false;
	std::vector<Component*> m_components;
	PositionComponent* positionComp;
	ControlComponent* controlComp;
	SpriteComponent* m_spriteComponent;
	SpriteComponent* m_spriteComponentHead;
	SpriteComponent* m_spriteComponentHead2;
	SpriteComponent* m_spriteComponentHead3;
	SpriteComponent* m_spriteComponentHead4;
	SpriteComponent* m_spriteComponentHead5;
	SpriteComponent* m_spriteComponentHead6;
	SpriteComponent* m_spriteComponentHeadNorm;
	SpriteComponent* m_spriteComponentCrown;
	SpriteComponent* m_spriteComponentLeftFoot;
	SpriteComponent* m_spriteComponentRightFoot;
	SpriteComponent* m_marker;

	TagComponent * tag;

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
	
	std::string round_text;
	SDL_Texture* text;
	SDL_Rect renderQuad;
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Surface * textSurface = new SDL_Surface;
	SDL_Renderer * m_renderer;
	TTF_Font* Font;

	float rumbleCount = 0;

	int offSet = 1;
	int randNum = 0;
};