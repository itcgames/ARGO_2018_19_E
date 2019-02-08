#pragma once

#include "../Components/StateComponent.h"

class SearchEntity : public FState
{
public:
	SearchEntity() { ; }
	~SearchEntity() { ; }

	void attack();
};

