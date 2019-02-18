#include "AnimationsSystem.h"

AnimationsSystem::AnimationsSystem() {
}

void AnimationsSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void AnimationsSystem::render(SDL_Renderer * renderer) {
	

	for (Entity * entity : m_entities) {

		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
		ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");
		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		AIComponent * ac = (AIComponent*)entity->getCompByType("AI");
		CollisionComponent * coll = (CollisionComponent*)entity->getCompByType("COLLISION");
	
		if (tc->getTag() == "Player")
		{
			if (pc->getX() != lastPos.x && pc->getY() == lastPos.y)
			{
				m_count++;
				if (m_count > 10) {
					auto particle = new ParticleExample();
					particle->setRenderer(renderer);
					particle->setStyle(ParticleExample::SMOKE);
					particle->setPosition(pc->getX(), pc->getY() + 70);
					cc->m_particleVector.push_back(particle);
					
					m_count = 0;
					
				}
				
			}

			lastPos = { pc->getX(), pc->getY() };

			
			animateExplosion(cc->m_particleVector);
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

void AnimationsSystem::animateExplosion(std::vector<ParticleExample*> vec)
{ 
	for (int i = 0; i < vec.size(); ++i)
	{
		vec[i]->count++;
		
		std::cout << vec[i]->count << std::endl;

		vec[i]->setStartSpin(0);
		vec[i]->setStartSpinVar(90);
		vec[i]->setEndSpin(90);
		vec[i]->setDuration(.1);
		vec[i]->setStartSize(30);
		vec[i]->setStartSpinVar(90);
		
		
		vec[i]->update();
		vec[i]->draw();

		if (vec[i]->count > 5)
		{
			vec.erase(vec.begin() + i);		
		}



		
		
	}		
}


double AnimationsSystem::distance(c2v  vecOne, c2v vecTwo)
{
	return std::sqrt((vecOne.x - vecTwo.x) * (vecOne.x - vecTwo.x) + (vecOne.y - vecTwo.y) * (vecOne.y - vecTwo.y));
}






