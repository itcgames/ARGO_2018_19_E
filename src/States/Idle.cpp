#include "Idle.h"
#include "SearchGun.h"
#include "Dead.h"


void Idle::searchGun(Animation * a)
{
	a->setCurrent(new SearchGun());
}


void Idle::dead(Animation * a)
{
	a->setCurrent(new Dead());
}