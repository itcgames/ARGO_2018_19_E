#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include "Components/SpriteComponent.h"


class Bullet
{
public:
	Bullet(SDL_Renderer* renderer, float xPos, float yPos, double angle, double xOffset, double yOffset);
	~Bullet() { delete m_spriteComponent; delete this; }
	SpriteComponent* m_spriteComponent;
	void render(SDL_Renderer* renderer);
	float xVel;
	float yVel;

	c2AABB collider;

private:
	//std::vector<Component*> m_components;
	//SpriteComponent* m_spriteComponent;
};


class Factory {
public:
	virtual Bullet* CreateBullet(SDL_Renderer* renderer, float xPos, float yPos, double angle, double xOffset, double yOffset) = 0;
};

class BulletFactory : public Factory {
public:
	BulletFactory() {}
	Bullet * CreateBullet(SDL_Renderer* renderer, float xPos, float yPos,double angle, double xOffset, double yOffset) {
		return new Bullet(renderer,xPos,yPos,angle,xOffset,yOffset);
	}
};
