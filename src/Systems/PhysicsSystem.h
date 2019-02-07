#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include "../cute_c2.h"

class PhysicsSystem
{
public:
	std::vector<Entity *> m_entities;

	
	c2v Friction;

	PhysicsSystem();
	void addEntity(Entity * e);
	void update();
	void bulletUpdate(SDL_Renderer* renderer);
	void bulletRender(SDL_Renderer* renderer);
	void receive(Entity * e);
	double playerPositionX = 0;
	double playerPositionY = 0;

	double aiPositionX = 0;
	double aiPositionY = 0;

	double gunPositionX = 0;
	double gunPositionY = 0;

	double angle = 0;

	bool gotGun = false;

	double xOffset = 0;
	double yOffset = 0;

	bool throwGun = false;

	bool fired = false;
	int firedCount = 0;

	std::vector<Bullet*> bullets;
};
#endif // !PHYSICSSYSTEM_H
