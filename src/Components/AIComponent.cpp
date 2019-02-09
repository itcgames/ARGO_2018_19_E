#include "AIComponent.h"


double AIComponent::distance(c2v  vecOne, float x, float y)
{
	return std::sqrt((vecOne.x - x) * (vecOne.x - x) + (vecOne.y - y) * (vecOne.y - y));
}



