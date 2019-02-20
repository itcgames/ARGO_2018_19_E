#ifndef GUNSYSTEM_H
#define GUNSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include <string>

using namespace std;

class GunSystem
{
public:
	GunSystem();
	void addEntity(Entity * e);
	void update();

	std::vector<Entity *> m_entities;
private:

};
#endif // !GUNSYSTEM_H
