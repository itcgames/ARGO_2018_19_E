#pragma once
#include <SDL.h>

class Animation
{
	class FState* current;
	class FState* previous;
public:
	Animation();
	
	void setCurrent(FState* s);
	void setPrevious(FState* s);
	FState* getCurrent();
	FState* getPrevious();
	void idle();
	void searchGun();
	void searchEnemy();
	void attack();
	void dead();

};
