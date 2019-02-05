#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "Component.h"
#include <SDL.h>

class PositionComponent : public Component
{
public:
	PositionComponent(int x, int y) : x(x), y(y){}

	int getX() { return x; }
	int getY() { return y; }


	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }

	std::string m_tag = "POSITION";

	std::string getType() { return m_tag; }

private:
	int x;
	int y;

};
#endif // !POSITIONCOMPONENT_H
