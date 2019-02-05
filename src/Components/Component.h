#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>

class Component
{
public:
	Component() {}
	std::string m_tag;
	virtual std::string getType() { return m_tag; }
};
#endif // !COMPONENT_H

