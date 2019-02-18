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

void CollisionSystem::update(std::vector<std::shared_ptr<Tile>> tiles) {
	for (Entity * entity : m_entities) {
		
		TagComponent * tag = (TagComponent*)entity->getCompByType("TAG");

		if (tag->getTag() == "Player" || tag->getTag() == "AI_TAG") {
			PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
			CollisionComponent * cc = (CollisionComponent*)entity->getCompByType("COLLISION");

			cc->SetCollPos(pc->getX(), pc->getY());

			for (int i = 0; i < tiles.size(); i++) {
				
					std::string val;
					if (tiles.at(i)->dRect.x >= 0) {
						val = rectCollision(cc->getCollider(), tiles.at(i)->collider);
						if (val != "none") {
							if (val == "top") {
								pc->jumpNum = 0;
								pc->m_allowedJump = true;
								pc->setVelY(0);

								pc->m_onTop = true;
								pc->setY(tiles.at(i)->dRect.y - cc->getH());


							}

							else if (val == "bottom") {
								pc->setVelY(5);
								
							}

							else if (val == "left") {


								pc->setX(tiles.at(i)->dRect.x - cc->getW());

								pc->m_allowedJump = true;
								m_count = 0;

								pc->m_hitLeftSide = true;
							}

							else if (val == "right")
							{
								pc->setX(tiles.at(i)->dRect.x + cc->getW() + 35);
								pc->m_allowedJump = true;
								pc->m_hitRightSide = true;

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
				
					std::string val;
					if (tiles.at(i)->dRect.x >= 0) {
						val = rectCollision(cc->getCollider(), tiles.at(i)->collider);
						if (val != "none") {
							if (val == "top") {
								pc->setVelY(0);
								pc->setY(tiles.at(i)->dRect.y - cc->getH());
								

							}
							else if (val == "bottom") {
								pc->setVelY(5);
								
							}
							else if (val == "right" || val == "left") {
								pc->setVelX(-(pc->getVelX()));
							}


						}

					}



				
			}

			checkBullets(pc, tiles);

		}
		
	}
}

void CollisionSystem::checkBullets(PositionComponent * poc, std::vector<std::shared_ptr<Tile>> tiles) {

	std::vector<Bullet *> * bullets = &poc->bullets;
	
	for (Entity * entity : m_entities) {
		TagComponent * tag = (TagComponent*)entity->getCompByType("TAG");

		if (tag->getTag() == "AI_TAG" || tag->getTag() == "Player") {
			CollisionComponent * cc = (CollisionComponent*)entity->getCompByType("COLLISION");
			PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
			SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");

			if (pc->getY() > 3000 && tag->getTag() == "AI_TAG") {
				AIComponent * ai = (AIComponent*)entity->getCompByType("AI");
				ai->m_alive = false;
			}
			else if (pc->getY() > 3000 && tag->getTag() == "Player") {
				ControlComponent * control = (ControlComponent*)entity->getCompByType("CONTROL");
				control->setAlive(false);
			}
			for (int i = 0; i < bullets->size(); i++) {
				std::string val = rectCollision(cc->getCollider(), bullets->at(i)->collider);
				c2v bPos = bullets->at(i)->m_spriteComponent->getPosition();
				if (bPos.x > 2000 || bPos.x < -200 || bPos.y < -200 || bPos.y > 3000) {
					bullets->erase(bullets->begin() + i);
				}
				if (val != "none") {
					bullets->erase(bullets->begin() + i);
					if (tag->getTag() == "AI_TAG") {
						AIComponent * ai = (AIComponent*)entity->getCompByType("AI");



						if (val == "right") {
							pc->setVelX(40);
							pc->setVelY(-10);
							sc->setRotation(90);
							sc->setColor(255, 40, 40);
							//sc->setBlendMode(SDL_BLENDMODE_ADD);
							ai->hitFromRight = true;
						}
						if (val == "left") {
							pc->setVelX(-40);
							pc->setVelY(-10);
							sc->setRotation(-90);
							sc->setColor(255, 40, 40);
							//sc->setBlendMode(SDL_BLENDMODE_ADD);
							ai->hitFromLeft = true;
						}

						PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
						ai->m_alive = false;	


					}

					// Possible error here

					if (tag->getTag() == "Player") {
						ControlComponent * control = (ControlComponent*)entity->getCompByType("CONTROL");
						control->setAlive(false);
					}
				}


			}
		}

	}


	
	for (int i= 0; i < tiles.size(); i++) {
		std::string val;
		if (tiles.at(i)->dRect.x >= 0) {
			for (int j = 0; j < bullets->size(); j++) {
				val = rectCollision(bullets->at(j)->collider, tiles.at(i)->collider);
				if (val != "none") {

					bullets->erase(bullets->begin() + j);

					auto particle = new ParticleExample();

					particle->setRenderer(m_renderer);
					particle->setStyle(ParticleExample::SMOKE);

					//particle->setPosition((*bullets->begin())->m_spriteComponent->getPosition().x, (*bullets->begin())->m_spriteComponent->getPosition().y);
					//particle->startAnimating = true;
					//m_particles.push_back(particle);
					//bullets->erase(bullets->begin() + i);
				}


			}
		}
	}
}	


void CollisionSystem::setRenderer(SDL_Renderer * renderer)
{
	m_renderer = renderer;
}

void CollisionSystem::animateExplosion()
{

	for (int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i]->count++;


		std::cout << m_particles[i]->count << std::endl;
		m_particles[i]->setStartSpin(0);
		m_particles[i]->setStartSpinVar(0);
		m_particles[i]->setEndSpin(90);
		m_particles[i]->setDuration(.1);
		m_particles[i]->setStartSize(70);
		m_particles[i]->setEndSize(70);
		m_particles[i]->setStartSpinVar(0);


		m_particles[i]->update();
		m_particles[i]->draw();
		
		if (m_particles[i]->count > 5)
		{
			m_particles.erase(m_particles.begin() + i);
			//m_particles.resize(m_particles.size());
		}

	}	
}

void CollisionSystem::render()
{

	animateExplosion();

}