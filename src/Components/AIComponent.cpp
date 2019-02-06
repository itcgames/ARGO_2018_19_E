#include "AIComponent.h"


double AIComponent::distance(c2v  vecOne, c2v vectwo)
{
	return std::sqrt((vecOne.x - vectwo.x) * (vecOne.x - vectwo.x) + (vecOne.y - vectwo.y) * (vecOne.y - vectwo.y));
}


