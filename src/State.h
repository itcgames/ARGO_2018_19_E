#pragma once

#include "Components/StateComponent.h"

class SearchGun : public State
{
public:
	SearchGun();
	~SearchGun();

	void searchEntity();
	void dead();
};

class SearchEntity : public State
{
public:
	SearchEntity();
	~SearchEntity();

	void attack();
};

class Dead : public State
{
public:

	Dead();
	~Dead();


};

class Attack : public State
{
public:

	Attack();
	~Attack();

};