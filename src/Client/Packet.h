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
 */

struct Packet
{
	int playerNum;
	int message;
	c2v position;
	bool alive;
};
#endif // !PACKAGE_H
