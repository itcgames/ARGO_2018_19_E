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

	c2v getStartPosition() { m_startingPosition; }
	c2v getCastPosition() { m_castPosition; }

	void setStartPosition(float x1, float y1) { m_startingPosition.x = x1; m_startingPosition.y = y1; }
	void setCastPosition(float x2, float y2) { m_startingPosition.x = x2; m_startingPosition.y = y2; };
	
private:

	c2v m_startingPosition;
	c2v m_castPosition;

};
#endif // !RAYCASTCOMPONENT_H
