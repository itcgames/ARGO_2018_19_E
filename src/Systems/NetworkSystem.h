#ifndef NETWORKSYSTEM_H
#define NETWORKSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include <string>
#include "../Client/Packet.h"


using namespace std;

class NetworkSystem
{
	std::vector<Entity *> m_entities;

public:
	NetworkSystem();
	void addEntity(Entity * e);
	void update(Packet * p);
private:
};
#endif // !NETWORKSYSTEM_H
