#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "Component.h"
#include <SDL.h>
#include "../cute_c2.h"

class CollisionComponent : public Component
{
public:
	CollisionComponent(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {
		collider = { c2v{x, y}, c2v{ x + w, y + h} };
		
	}

	float getX() { return x; }
	float getY() { return y; }

	void setX(float x) { this->x = x; }
	void setY(int y) { this->y = y; }

	float getW() { return w; }
	float getH() { return h; }

	void setW(float w) { this->w = w; }
	void setH(int h) { this->h = h; }

	void setColliding(bool coll) { this->m_colliding = coll; }
	bool getColliding() { return m_colliding; }

	c2AABB getCollider() { return collider; }

	void SetCollPos(float x, float y) {
		this->x = x;
		this->y = y;
		collider.min = c2v{ x, y };
		collider.max = c2v{ x + w, y + h };
	}

	std::string m_tag = "COLLISION";

	std::string getType() { return m_tag; }

private:
	float x;
	float y;
	float w;
	float h;

	bool m_colliding = false;


	c2AABB collider;

};
#endif // !POSITIONCOMPONENT_H

