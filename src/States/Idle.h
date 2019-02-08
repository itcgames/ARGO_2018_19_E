#pragma once

#include "../Components/StateComponent.h"

class Idle : public StateComponent
{
public:
	Idle() { ; }
	~Idle() { ; }

	void searchGun(Animation * a);
	void dead(Animation * a);
};

