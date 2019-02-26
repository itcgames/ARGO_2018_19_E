#ifndef RAYCASTCOMPONENT_H
#define RAYCASTCOMPONENT_H

#include "Component.h"
#include "../cute_c2.h"
#include <vector>

class RayCastComponent : public Component
{
public:

	std::string m_tag = "Ray";
	std::string getType() { return m_tag; }

	RayCastComponent() { ; }

	c2v getStartPosition() { return m_startingPosition; }
	c2v getCastPosition() { return m_castPosition; }

	void setStartPosition(float x1, float y1) { m_startingPosition.x = x1; m_startingPosition.y = y1; }
	void setCastPosition(float x2, float y2) { m_castPosition.x = x2; m_castPosition.y = y2; };
	
private:

	c2v m_startingPosition = { 0,0 };
	c2v m_castPosition = { 0,0 };

};
#endif // !RAYCASTCOMPONENT_H
