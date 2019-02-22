#ifndef AISYSTEM_H
#define AISYSTEM_H

#include <iostream>
#include <list>
#include <vector>
#include "../Entity.h"
#include "../cute_c2.h"
#include <algorithm>
#include "../Animation.h"
#include "../MapLoader.h"



class AISystem
{
	std::vector<Entity *> m_entities;

	struct Line
	{
		float x1;
		float y1;
		float x2;
		float y2;
	};

public:
	AISystem();

	void renderLine(SDL_Renderer * renderer);
	void addEntity(Entity * e);
	void receive(std::vector<Entity*> guns, std::vector<Entity*> players);
	void recieveLevel(std::vector<std::pair<c2v, std::string>> walkpoints, std::vector<std::pair<c2v, std::string>> jumpPoints, std::vector<std::shared_ptr<Tile>> tiles, int width, int height);
	void update();
	void checkBoundaries(AIComponent * ac);
	void calculateMovePoints(AIComponent * ac);
	void setStartingDirection(AIComponent * ac);
	void checkWalkPoints(AIComponent * AC, PositionComponent * pc);
	void checkJumpPoints(AIComponent * AC, PositionComponent * pc);

	double getAngleToPlayer(c2v pos, std::pair<double, c2v> enemy);
	double distance(c2v  vecOne, c2v vecTwo);


	std::pair<double, c2v> checkClosest(std::vector<std::pair<double, c2v>> distances, std::pair<double, c2v > real);
	std::pair<c2v, std::string> checkPoints(std::vector<std::pair<c2v, std::string>> walkpoints, PositionComponent* pc);

private:	
	std::vector<std::pair<c2v, std::string>> m_pathPoints;
	std::vector<std::pair<c2v, std::string>> m_jumpPoints;
	std::vector<std::pair<double, c2v>> m_dist;
	std::vector<std::shared_ptr<Tile>> m_tiles;


	int m_height;
	int m_width;


	Animation *fsm;

	std::vector<Line*> m_line;
	c2v m_position;
};



#endif // !AISYSTEM_H
