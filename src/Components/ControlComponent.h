#ifndef CONTROLCOMPONENT_H
#define CONTROLCOMPONENT_H

#include "Component.h"

class ControlComponent : public Component
{
public:
	ControlComponent() {}

	std::string m_tag = "CONTROL";

	std::string getType() { return m_tag; }

	bool getLeft() { return m_left;  }
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

private:

	bool m_left = false;
	bool m_right = false;

	bool m_throwWeapon = false;
	bool m_jump = false;

	bool m_fire = false;

	float m_gunAngle = 0.0f;

};
#endif // !CONTROLCOMPONENT_H
