#ifndef COMPONENTS_H
#define COMPONENTS_H

class Component
{
public:
	Component() {};
	std::string m_tag = "";
	virtual std::string getType() { return m_tag; }
};
#endif // !COMPONENTS_H

