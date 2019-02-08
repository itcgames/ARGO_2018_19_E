#pragma once

#include "../Components/StateComponent.h"

class SearchEntity : public StateComponent
{
public:
	SearchEntity() { ; }
	~SearchEntity() { ; }

	void attack();
};

