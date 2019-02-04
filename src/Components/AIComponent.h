#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "Components.h"

class AIComponent : public Component
{
public:
	AIComponent(int speed) : m_speed(speed) {}

	int getSpeed() { return m_speed; }
	void setSpeed(int speed) { m_speed = speed; }

	std::string m_tag = "AI";

	std::string getType() { return m_tag; }

private:
	int m_speed;

};
#endif // !CONTROLCOMPONENT_H
