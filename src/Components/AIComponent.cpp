#include "AIComponent.h"


double AIComponent::distance(c2v  vecOne, float x, float y)
{
	return std::sqrt((vecOne.x - x) * (vecOne.x - x) + (vecOne.y - y) * (vecOne.y - y));
}


void AIComponent::setCurrent(State* s)
{
	current = s;
}
State* AIComponent::getCurrent()
{
	return current;
}
void AIComponent::setPrevious(State* s)
{
	previous = s;
}

State* AIComponent::getPrevious()
{
	return previous;
}
void AIComponent::idle()
{
	current->idle(this);
}

void AIComponent::searchGun()
{
	current->searchGun(this);
}

void AIComponent::searchEntity()
{
	current->searchEntity(this);
}

void AIComponent::attack()
{
	current->attack(this);
}

void AIComponent::dead()
{
	current->dead(this);
}

