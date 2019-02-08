#include "SearchGun.h"
#include "SearchEntity.h"
#include "Dead.h"


void SearchGun::searchEntity(Animation * a)
{
	a->setCurrent(new SearchEntity());
}

void SearchGun::dead(Animation * a)
{
	a->setCurrent(new Dead());
}