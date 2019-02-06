#ifndef TAGCOMPONENT_H
#define TAGCOMPONENT_H

#include "Component.h"
#include <SDL.h>
#include "../cute_math2d.h"
#include <string.h>

class TagComponent : public Component
{
public:
	TagComponent(std::string name) : tag(name){}

	std::string getTag() { return tag; }

	std::string m_tag = "TAG";

	std::string getType() { return m_tag; }

	bool grabbed = false;

	bool getGrabbed() { return grabbed; }
	void setGrabbed(bool value) { grabbed = value; }



private:
	std::string tag;
};
#endif // !TAGCOMPONENT_H
