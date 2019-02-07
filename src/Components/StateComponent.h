#pragma once

#include "SDL.h"
#include "Component.h"
#include "AIComponent.h"
#include  <iostream>

class AIComponent;

class State : public Component
{
public:

	std::string m_tag = "State";

	std::string getType() { return m_tag; }

	virtual void idle(AIComponent * comp)
	{
		std::cout << "idle" << std::endl;
	}
	virtual void searchGun(AIComponent * comp)
	{
		std::cout << "Searching for gun" << std::endl;
	}
	virtual void searchEntity(AIComponent * comp)
	{
		std::cout << "Searching for Entity" << std::endl;
	}
	virtual void attack(AIComponent * comp)
	{
		std::cout << "Attacking Entity" << std::endl;
	}
	virtual void dead(AIComponent * comp)
	{
		std::cout << "Dead" << std::endl;
	}


};
