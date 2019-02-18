#ifndef TAGCOMPONENT_H
#define TAGCOMPONENT_H

#include "Component.h"
#include <SDL.h>
#include <string.h>

class TagComponent : public Component
{
public:
	TagComponent(std::string name) : tag(name){}

	std::string getTag() { return tag; }
	std::string getSubTag() { return subTag; }

	void setSubTag(std::string subName){subTag = subName; }

	std::string m_tag = "TAG";

	std::string gunGot = "none";
	std::string getGunGot() { return gunGot; }
	void setGunGot(std::string string) { gunGot = string; }

	std::string getType() { return m_tag; }

	bool grabbed = false;
	bool grabable = true;
	bool gotGunBool = false;

	double grabableCount = 0;
	bool firedBool = false;

	bool getGrabbed() { return grabbed; }
	bool getGrabable() { return grabable; }
	void setGrabbed(bool value) { grabbed = value; }
	void setGrabable(bool value) { grabable = value; }
	void setGrabableCount(double value) { grabableCount = value; }
	void setGotGunBool(bool value) { gotGunBool = value; }
	bool getGotGunBool() { return gotGunBool; }
	void setFiredBool(bool value) { firedBool = value; };
	bool getFiredBool() { return firedBool; };
	double getGrabableCount() { return grabableCount; }



private:
	std::string subTag = "None";
	std::string tag;
};
#endif // !TAGCOMPONENT_H
