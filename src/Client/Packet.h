#ifndef PACKAGE_H
#define PACKAGE_H

#include "../cute_c2.h"
#include <iostream>


/*
 * Message Index:
 * 1: number
 * 2: join
 * 3: leave
 * 4: start
 * 5: update
 */

struct Packet
{
	int playerNum;
	int message;
	bool alive;

	c2v position;

	bool left;
	bool right;

	bool throwWeapon;
	bool jump;

	bool fire;

	float gunAngle;

	bool roundOver;

};
#endif // !PACKAGE_H
