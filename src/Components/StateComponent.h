#pragma once

#include "SDL.h"
#include "Component.h"
#include "../Animation.h"
#include  <iostream>


class StateComponent : public Component
{
public:


	StateComponent() { ; }
	
	
	std::string m_tag = "STATE";

	std::string getType() { return m_tag; }

	
	virtual void idle(Animation * comp)
	{
		std::cout << "idle" << std::endl;
	}
	virtual void searchGun(Animation * comp)
	{
		std::cout << "Searching for gun" << std::endl;
	}
	virtual void searchEnemy(Animation * comp)
	{
		std::cout << "Searching for Enemy" << std::endl;
	}
	virtual void attack(Animation * comp)
	{
		std::cout << "Attacking Entity" << std::endl;
	}
	virtual void dead(Animation * comp)
	{
		std::cout << "Dead" << std::endl;
	}


};
