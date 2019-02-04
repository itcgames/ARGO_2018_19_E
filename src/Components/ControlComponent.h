#ifndef CONTROLCOMPONENT_H
#define CONTROLCOMPONENT_H

#include "Components.h"

class ControlComponent : public Component
{
public:
	ControlComponent() {}

	std::string m_tag = "CONTROL";

	std::string getType() { return m_tag; }
private:
	

};
#endif // !CONTROLCOMPONENT_H
