#pragma once

#include "Components/StateComponent.h"

class SearchGun : public FState
{
public:
	SearchGun();
	~SearchGun();

	void searchEntity();
	void dead();
};

class SearchEntity : public FState
{
public:
	SearchEntity();
	~SearchEntity();

	void attack();
};

class Dead : public FState
{
public:

	Dead();
	~Dead();


};

class Attack : public FState
{
public:

	Attack();
	~Attack();

};