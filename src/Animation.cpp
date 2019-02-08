#include "Animation.h"
#include "States/Idle.h"


Animation::Animation()
{
	current = new Idle();
}

void Animation::setCurrent(FState* s)
{
	current = s;
}

FState* Animation::getCurrent()
{
	return current;
}

void Animation::setPrevious(FState* s)
{
	previous = s;
}

FState* Animation::getPrevious()
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