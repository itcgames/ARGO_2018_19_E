#pragma once
#include "../Components/StateComponent.h"

class SearchGun : public FState
{
public:
	SearchGun() { ; }
	~SearchGun() { ; }

	void searchEntity(Animation * a);
	void dead(Animation * a);
};

