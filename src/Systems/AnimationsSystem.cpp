#include "AnimationsSystem.h"

AnimationsSystem::AnimationsSystem() {
}

void AnimationsSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void AnimationsSystem::update() {
	

	for (Entity * entity : m_entities) {

		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
		ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");
		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		AIComponent * ac = (AIComponent*)entity->getCompByType("AI");
		CollisionComponent * coll = (CollisionComponent*)entity->getCompByType("COLLISION");
	
		if (tc->getTag() == "Player")
		{
			if (pc->getX() != lastPos.x && pc->getY() == lastPos.y && pc->getVelX() > 1.0f ||
				pc->getX() != lastPos.x && pc->getY() == lastPos.y && pc->getVelX() < -1.0f)
				
			{
				m_count++;
				if (m_count > 15) {
					auto particle = new ParticleExample();
					particle->setRenderer(m_renderer);
					particle->setStyle(ParticleExample::DIRT);
					particle->setPosition(pc->getX(), pc->getY() + 90);
					m_particleVector.push_back(particle);
					
					m_count = 0;
					
				}
				
			}

			lastPos = { pc->getX(), pc->getY() };

			
			
		}
		
		if (tc->getTag() == "AI_TAG")
		{

		}
	}
}

void AnimationsSystem::setRenderer(SDL_Renderer * renderer)
{
	m_renderer = renderer;
}

void AnimationsSystem::render()
{
	animateExplosion();
}
void AnimationsSystem::animateExplosion()
{ 
	for (int i = 0; i < m_particleVector.size(); ++i)
	{
		m_particleVector[i]->count++;
		
		std::cout << m_particleVector[i]->count << std::endl;

		m_particleVector[i]->setStartSpin(0);
		m_particleVector[i]->setStartSpinVar(90);
		m_particleVector[i]->setEndSpin(90);
		m_particleVector[i]->setDuration(.1);
		m_particleVector[i]->setStartSize(30);
		m_particleVector[i]->setStartSpinVar(90);
		
		
		m_particleVector[i]->update();
		m_particleVector[i]->draw();

		if (m_particleVector[i]->count > 40)
		{
			m_particleVector.erase(m_particleVector.begin() + i);
		}



		
		
	}		
}


double AnimationsSystem::distance(c2v  vecOne, c2v vecTwo)
{
	return std::sqrt((vecOne.x - vecTwo.x) * (vecOne.x - vecTwo.x) + (vecOne.y - vecTwo.y) * (vecOne.y - vecTwo.y));
}






