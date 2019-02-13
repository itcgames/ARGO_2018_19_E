#ifndef RESTARTSYSTEM_H
#define RESTARTSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include <string>
#include "../MapLoader.h"


using namespace std;

class RestartSystem
{
	std::vector<Entity *> m_entities;

public:
	RestartSystem();
	void addEntity(Entity * e);
	void reset(int level);

private:
	tmx::Map m_map;
};
#endif // !RESTARTSYSTEM_H
