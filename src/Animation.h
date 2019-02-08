#pragma once
#include <SDL.h>

class Animation
{
	class StateComponent* current;
	class StateComponent* previous;
public:
	Animation();
	
	void setCurrent(StateComponent* s);
	void setPrevious(StateComponent* s);
	StateComponent* getCurrent();
	StateComponent* getPrevious();
	void idle();
	void searchGun();
	void searchEnemy();
	void attack();
	void dead();

};
