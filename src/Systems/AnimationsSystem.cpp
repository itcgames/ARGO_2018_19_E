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
			//std::cout << cc->m_particleVector.size() << std::endl;
			if (pc->getX() != cc->lastPos.x && pc->getY() == cc->lastPos.y && pc->getVelX() > 1.0f ||
				pc->getX() != cc->lastPos.x && pc->getY() == cc->lastPos.y && pc->getVelX() < -1.0f)
				
			{
				cc->m_count++;
				if (cc->m_count > 15) {
					auto particle = new ParticleExample();
					particle->setRenderer(m_renderer);
					particle->setStyle(ParticleExample::DIRT);
					particle->setPosition(pc->getX(), pc->getY() + 90);
					cc->m_particleVector.push_back(particle);
					
					cc->m_count = 0;
					
				}	
			}
			cc->lastPos = { pc->getX(), pc->getY() };
		}
		
		//if (tc->getTag() == "AI_TAG")
		//{
		//	if (pc->getX() != ac->lastPos.x && pc->getY() == ac->lastPos.y && pc->getVelX() > 1.0f ||
		//		pc->getX() != ac->lastPos.x && pc->getY() == ac->lastPos.y && pc->getVelX() < -1.0f)

		//	{
		//		ac->m_count++;
		//		if (ac->m_count > 15) {
		//			auto particle = new ParticleExample();
		//			particle->setRenderer(m_renderer);
		//			particle->setStyle(ParticleExample::DIRT);
		//			particle->setPosition(pc->getX(), pc->getY() + 90);
		//			ac->m_particleVector.push_back(particle);

		//			ac->m_count = 0;
		//			//std::cout << ac->m_particleVector.size() << std::endl;
		//		}
		//	}
		//	ac->lastPos = { pc->getX(), pc->getY() };
		//}
	}
}

void AnimationsSystem::setRenderer(SDL_Renderer * renderer)
{
	m_renderer = renderer;
}

void AnimationsSystem::render()
{
	for (Entity * entity : m_entities) {

		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
		ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");
		AIComponent * ac = (AIComponent*)entity->getCompByType("AI");

		if (tc->getTag() == "Player")
		{
			animateExplosion(cc->m_particleVector);
		}

	//	/*if (tc->getTag() == "AI_TAG")
	//	{
	//		animateExplosion(ac->m_particleVector);
	//	}*/
	}
	
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

		if (vec[i]->count > 40)
		{
			std::cout << "erased" << std::endl;
			vec.erase(vec.begin() + i);
		}	
	}		
}


double AnimationsSystem::distance(c2v  vecOne, c2v vecTwo)
{
	return std::sqrt((vecOne.x - vecTwo.x) * (vecOne.x - vecTwo.x) + (vecOne.y - vecTwo.y) * (vecOne.y - vecTwo.y));
}






