#include "Animation.h"
#include "States/Idle.h"


Animation::Animation()
{
	current = new Idle();
}

void Animation::setCurrent(StateComponent* s)
{
	current = s;
}

StateComponent* Animation::getCurrent()
{
	return current;
}

void Animation::setPrevious(StateComponent* s)
{
	previous = s;
}

StateComponent* Animation::getPrevious()
{
	return previous;
}

void Animation::idle()
{
	current->idle(this);
}

void Animation::searchGun()
{
	current->searchGun(this);
}

void Animation::searchEnemy()
{
	current->searchGun(this);
}

void Animation::attack()
{
	current->attack(this);
}

void Animation::dead()
{
	current->dead(this);
}