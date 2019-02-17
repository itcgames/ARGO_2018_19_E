#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "Component.h"
#include <SDL.h>
#include "../cute_c2.h"
#include "../Factory.h"

class PositionComponent : public Component
{
public:
	PositionComponent(float x, float y) : x(x), y(y), startX(x), startY(y){}

	float getX() { return x; }
	float getY() { return y; }


	void setX(float x) { this->x = x; }
	void setY(int y) { this->y = y; }

	float getVelX() { return vel.x; }
	float getVelY() { return vel.y; }

	
	void setVelX(float x) { 
		vel.x = x; 
	}
	void setVelY(float y) { vel.y = y; }

	std::string m_tag = "POSITION";

	std::string getType() { return m_tag; }

	c2v vel = { 0,0 };

	bool m_allowedJump = true;
	bool m_hitRightSide = false;
	bool m_hitLeftSide = false;

	std::vector<Bullet*> bullets;

	float startX;
	float startY;

	int jumpNum = 0;

	int firedCount = 0;
	void setFiredCount(int value) { firedCount = value; }
	int getFiredCount() { return firedCount; }

	int pistolCount = 0;
	void setPistolCount(int value) { pistolCount = value; }
	int getPistolCount() { return pistolCount; }

	int shotgunCount = 0;
	void setShotgunCount(int value) { shotgunCount = value; }
	int getShotgunCount() { return shotgunCount; }

	int juicerCount = 0;
	void setJuicerCount(int value) { juicerCount = value; }
	int getJuicerCount() { return juicerCount; }

	int shotgunRotationCount = 0;
	void setShotgunRotationCount(int value) { shotgunRotationCount = value; }
	int getShotgunRotationCount() { return shotgunRotationCount; }

	int shotgunPumpCount = 0;
	void setShotgunPumpCount(int value) { shotgunPumpCount = value; }
	int getShotgunPumpCount() { return shotgunPumpCount; }
	
private:
	float x;
	float y;

};
#endif // !POSITIONCOMPONENT_H
