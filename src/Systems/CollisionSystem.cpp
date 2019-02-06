#include "CollisionSystem.h"

CollisionSystem::CollisionSystem() {

}

void CollisionSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

int CollisionSystem::rectCollision(c2AABB A, c2AABB B)
{
	int d0 = B.max.x < A.min.x;
	int d1 = A.max.x < B.min.x;
	int d2 = B.max.y < A.min.y;
	int d3 = A.max.y < B.min.y;
	
	return !(d0 | d1 | d2 | d3);
}

void CollisionSystem::update() {
	for (Entity * entity : m_entities) {
		
		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		CollisionComponent * cc = (CollisionComponent*)entity->getCompByType("COLLISION");

		cc->SetCollPos(pc->getX(), pc->getY());

		for (Entity * ent : m_entities) {

			if (entity != ent) {
				CollisionComponent * ccNew = (CollisionComponent*)ent->getCompByType("COLLISION");

				int val = rectCollision(cc->getCollider(), ccNew->getCollider());
				//std::cout << "Collider: " << cc->getCollider().min.x << ", " << cc->getCollider().min.y << std::endl;
				std::cout << val << std::endl;
			}
			
		}
	}
}