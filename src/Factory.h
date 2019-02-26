#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>

#include "Components/SpriteComponent.h"

class Camera;

class Bullet
{
public:
	Bullet(SDL_Renderer* renderer, float xPos, float yPos, double angle, float xOffset, float yOffset, int ttl);
	~Bullet() {}
	SpriteComponent* m_spriteComponent;
	void render(SDL_Renderer* renderer, Camera* camera);
	float xVel;
	float yVel;

	c2AABB collider;

	int m_ttl = 0;

private:
	//std::vector<Component*> m_components;
	//SpriteComponent* m_spriteComponent;
};


class Factory {
public:
	virtual Bullet* CreateBullet(SDL_Renderer* renderer, float xPos, float yPos, double angle, double xOffset, double yOffset, int ttl) = 0;
};

class BulletFactory : public Factory {
public:
	BulletFactory() {}
	Bullet * CreateBullet(SDL_Renderer* renderer, float xPos, float yPos,double angle, double xOffset, double yOffset, int ttl) {
		return new Bullet(renderer,xPos,yPos,angle,xOffset,yOffset,ttl);
	}
};
