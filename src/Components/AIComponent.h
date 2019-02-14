#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "Component.h"
#include "../cute_c2.h"
#include "StateComponent.h"
#include <vector>

class AIComponent : public Component
{

	class FState* current;
	class FState* previous;


public:

	AIComponent(int speed) : m_speed(speed) { closestWalkPoint = std::make_pair(c2v{ 0,0 }, "LEFT"); }

	int getSpeed() { return m_speed; }
	void setSpeed(int speed) { m_speed = speed; }

	std::string m_tag = "AI";

	std::string getType() { return m_tag; }

	bool getLeft() { return m_left; }
	void setLeft(bool left) { m_left = left; }

	bool getRight() { return m_right; }
	void setRight(bool right) { m_right = right; }

	bool getJump() { return m_jump; }
	void setJump(bool jump) { m_jump = jump; }

	float getAngle() { return m_gunAngle; }
	void setAngle(float angle) { m_gunAngle = angle; }

	bool getThrowWeapon() { return m_throwWeapon; }
	void setThrowWeapon(bool tw) { m_throwWeapon = tw; }

	bool getFire() { return m_fire; }
	void setFire(bool fire) { m_fire = fire; }

	bool checkGun() { return m_gun; }
	void setGun(bool has) { m_gun = has; }

	double distance(c2v v1, float x, float y);

	bool m_alive = true;

	bool hitFromLeft = false;
	bool hitFromRight = false;
	
	bool facingleft = false;
	bool facingRight = false;

	bool checkGunDirection = true;

	bool jumping = false;

	bool set = false;
	c2v closestEnemy;

	std::pair<c2v, std::string> closestWalkPoint;
	std::pair<c2v, std::string> closestJumpPoint;

	std::vector<std::pair<c2v, std::string>> curWalkPoints;
	std::vector<std::pair<c2v, std::string>> curJumpPoints;

	float oldYVel = 0;
	float newYVel = 0;

	bool m_gunInSight = false;

	c2v curPosition = { 0,0 };
	c2v lastPosition = { 0,0 };

	bool m_landed;


	std::vector<std::pair<double, c2v>> m_distances;

	std::string direction = "";
	std::pair<double, c2v> m_realDist;

private:

	bool m_left = false;
	bool m_right = false;


	

	bool m_throwWeapon = false;
	bool m_jump = false;

	bool m_fire = false;

	float m_gunAngle = 0.0f;

	float m_speed;

	bool m_gun = false;

};
#endif // !CONTROLCOMPONENT_H
