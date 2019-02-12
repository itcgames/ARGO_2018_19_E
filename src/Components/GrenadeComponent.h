#ifndef GRENADECOMPONENT_H
#define GRENADECOMPONENT_H

#include "Component.h"
#include <SDL.h>
#include <string.h>

class GrenadeComponent : public Component
{
public:
	GrenadeComponent() {}

	bool getArmed() { return m_armed; }
	void setArmed(bool arm) { m_armed = arm; }

	bool getExplode() { return m_explode; }
	void setExplode(bool explode) { m_explode = explode; }

	int getTTL() { return m_time2Live; }
	void setTTL(int time) { m_time2Live = time; }

	std::string m_tag = "GRENADE";

	std::string getType() { return m_tag; }

	

private:
	bool m_armed = false;
	bool m_explode = false;
	int m_time2Live = 300;
};
#endif // !TAGCOMPONENT_H
