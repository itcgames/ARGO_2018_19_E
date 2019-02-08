#include "CollisionSystem.h"

CollisionSystem::CollisionSystem() {

}

void CollisionSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}



std::string CollisionSystem::rectCollision(c2AABB A, c2AABB B)
{

	float dx = (A.min.x + (A.max.x - A.min.x) / 2) - (B.min.x + (B.max.x - B.min.x) / 2);
	float dy = (A.min.y + (A.max.y - A.min.y) / 2) - (B.min.y + (B.max.y - B.min.y) / 2);
	float width = ((A.max.x - A.min.x) + (B.max.x - B.min.x)) / 2;
	float height = ((A.max.y - A.min.y) + (B.max.y - B.min.y)) / 2;
	float crossWidth = width * dy;
	float crossHeight = height * dx;
	std::string collision = "none";

	if (dx < 0) {
		dx = -dx;
	}
	if (dy < 0) {
		dy = -dy;
	}
	//
	if (dx <= width && dy <= height) {
		if (crossWidth > crossHeight) {
			collision = (crossWidth > (-crossHeight)) ? "bottom" : "left";
		}
		else {
			collision = (crossWidth > (-crossHeight)) ? "right" : "top";
		}
	}
	
	return(collision);
}

void CollisionSystem::update(std::vector<std::vector<Tile*>> tiles) {
	for (Entity * entity : m_entities) {
		
		TagComponent * tag = (TagComponent*)entity->getCompByType("TAG");

		if (tag->getTag() == "Player" || tag->getTag() == "AI_TAG") {
			PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
			CollisionComponent * cc = (CollisionComponent*)entity->getCompByType("COLLISION");

			cc->SetCollPos(pc->getX(), pc->getY());

			for (int i = 0; i < tiles.size(); i++) {
				for (int j = 0; j < tiles[i].size(); j++) {
					std::string val;
					if (tiles[i].at(j)->dRect.x > 0) {
						val = rectCollision(cc->getCollider(), tiles[i].at(j)->collider);
						if (val != "none" ) {
							if (val == "top") {
								pc->m_allowedJump = true;
								pc->setVelY(0);
								pc->setY(tiles[i].at(j)->dRect.y - cc->getH());
								
							}
							else if (val == "bottom") {
								pc->setVelY(5);
							}
							else if (val == "right" || val == "left") {
								pc->setVelX(-(pc->getVelX() * 2));
								pc->m_allowedJump = true;
							}
							
					
						}
						
					}
					

					
				}
			}
		}
		else if (tag->getTag() == "Gun") {
			PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
			CollisionComponent * cc = (CollisionComponent*)entity->getCompByType("COLLISION");

			cc->SetCollPos(pc->getX(), pc->getY());

			for (int i = 0; i < tiles.size(); i++) {
				for (int j = 0; j < tiles[i].size(); j++) {
					std::string val;
					if (tiles[i].at(j)->dRect.x > 0) {
						val = rectCollision(cc->getCollider(), tiles[i].at(j)->collider);
						if (val != "none") {
							if (val == "top") {
								pc->setVelY(0);
								pc->setY(tiles[i].at(j)->dRect.y - cc->getH());

							}
							else if (val == "bottom") {
								pc->setVelY(5);
							}
							else if (val == "right" || val == "left") {
								pc->setVelX(-(pc->getVelX() * 2));
							}


						}

					}



				}
			}

			checkBullets(pc);

		}
		
	}
}

void CollisionSystem::checkBullets(PositionComponent * pc) {
	 
	std::vector<Bullet *> * bullets = &pc->bullets;
	for (Entity * entity : m_entities) {
		TagComponent * tag = (TagComponent*)entity->getCompByType("TAG");

		if (tag->getTag() == "AI_TAG") {
			CollisionComponent * cc = (CollisionComponent*)entity->getCompByType("COLLISION");
			PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
			SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
			for (int i = 0; i < bullets->size(); i++) {
				std::string val = rectCollision(cc->getCollider(), bullets->at(i)->collider);
				if (val != "none") {
					bullets->erase(bullets->begin() + i);
					if (val == "right") {
						pc->setVelX(40);
						pc->setVelY(-10);
						sc->setRotation(90);
						sc->setColor(255, 40, 40);
					}
					if (val == "left") {
						pc->setVelX(-40);
						pc->setVelY(-10);
						sc->setRotation(-90);
						sc->setColor(255, 40, 40);
					}
					if (tag->getTag() == "AI_TAG") {
						AIComponent * ai = (AIComponent*)entity->getCompByType("AI");
						ai->m_alive = false;
					}
				}
				

			}
		}
	}
}