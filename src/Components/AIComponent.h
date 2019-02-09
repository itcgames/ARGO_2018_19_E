#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "Component.h"
#include "../cute_c2.h"
#include "StateComponent.h"

class AIComponent : public Component
{

	class FState* current;
	class FState* previous;


public:

	AIComponent(int speed) : m_speed(speed) {}

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
