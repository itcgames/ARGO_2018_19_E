#pragma once
#include "../Components/StateComponent.h"

class SearchGun : public StateComponent
{
public:
	SearchGun() { ; }
	~SearchGun() { ; }

	void searchEntity(Animation * a);
	void dead(Animation * a);
};

