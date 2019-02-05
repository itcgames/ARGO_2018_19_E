#ifndef CONTROLCOMPONENT_H
#define CONTROLCOMPONENT_H

#include "Components.h"

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

private:

	bool m_left = false;
	bool m_right = false;
	bool m_jump = false;

};
#endif // !CONTROLCOMPONENT_H
