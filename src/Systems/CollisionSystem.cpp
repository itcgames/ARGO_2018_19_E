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
					if (tiles[i].at(j)->dRect.x >= 0) {
						val = rectCollision(cc->getCollider(), tiles[i].at(j)->collider);
						if (val != "none" ) {
							if (val == "top") {
								pc->m_allowedJump = true;
								pc->setVelY(0);
								pc->setY(tiles[i].at(j)->dRect.y - cc->getH());
								
								
							}
							else if (val == "bottom") {
								pc->setVelY(5);
								m_count = 0;
							/*	if (SDL_HapticRumblePlay(haptic, 0.5, 75) != 0 && tag->getTag() == "Player")
								{
									printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
								}*/
							}
							else if (val == "left") {
								//pc->setVelX(-(pc->getVelX() * 1.1));
								pc->setX(tiles[i].at(j)->dRect.x - cc->getW() - 5);
								pc->m_allowedJump = true;
								pc->m_hitSide = true;
								m_count = 0;
							}
							else if (val == "right")
							{
								pc->setX(tiles[i].at(j)->dRect.x + cc->getW() + 35);
								pc->m_allowedJump = true;
								pc->m_hitSide = true;
								m_count = 0;
							}
							/*	if (SDL_HapticRumblePlay(haptic, 0.5, 75) != 0 && tag->getTag() == "Player")
								{
									printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
								}*/
							
							
					
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
					if (tiles[i].at(j)->dRect.x >= 0) {
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
								pc->setVelX(-(pc->getVelX() * 3));
							}


						}

					}



				}
			}

			checkBullets(pc, tiles);

		}
		
	}
}

void CollisionSystem::checkBullets(PositionComponent * poc, std::vector<std::vector<Tile*>> tiles) {

	std::vector<Bullet *> * bullets = &poc->bullets;
	for (Entity * entity : m_entities) {
		TagComponent * tag = (TagComponent*)entity->getCompByType("TAG");

		if (tag->getTag() == "AI_TAG") {
			CollisionComponent * cc = (CollisionComponent*)entity->getCompByType("COLLISION");
			PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
			SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
			for (int i = 0; i < bullets->size(); i++) {
				std::string val = rectCollision(cc->getCollider(), bullets->at(i)->collider);
				c2v bPos = bullets->at(i)->m_spriteComponent->getPosition();
				if (bPos.x > 2000 || bPos.x < -200 || bPos.y < -200 || bPos.y > 1400) {
					bullets->erase(bullets->begin() + i);
				}
				if (val != "none") {
					bullets->erase(bullets->begin() + i);
					if (val == "right") {
						pc->setVelX(40);
						pc->setVelY(-10);
						sc->setRotation(90);
						sc->setColor(255, 40, 40);
						sc->setBlendMode(SDL_BLENDMODE_ADD);
					}
					if (val == "left") {
						pc->setVelX(-40);
						pc->setVelY(-10);
						sc->setRotation(-90);
						sc->setColor(255, 40, 40);
						sc->setBlendMode(SDL_BLENDMODE_ADD);
					}
					if (tag->getTag() == "AI_TAG") {
						AIComponent * ai = (AIComponent*)entity->getCompByType("AI");
						ai->m_alive = false;
					}
				}


			}
		}

	}

	
	for (int j = 0; j < tiles.size(); j++) {
		for (int k = 0; k < tiles[j].size(); k++) {
			std::string val;
			if (tiles[j].at(k)->dRect.x >= 0) {
				for (int i = 0; i < bullets->size(); i++) {
					val = rectCollision(bullets->at(i)->collider, tiles[j].at(k)->collider);
					if (val != "none") {
						bullets->erase(bullets->begin() + i);
						std::cout << "Delete" << std::endl;
					}
				}

			}



		}
	}
	
}