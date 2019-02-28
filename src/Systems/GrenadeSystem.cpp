#include "GrenadeSystem.h"

GrenadeSystem::GrenadeSystem() {

}

void GrenadeSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void GrenadeSystem::update(std::vector<std::shared_ptr<Tile>> tiles, std::vector<AI *> aiChars, std::vector<Player *> playerChars, Camera * camera) {
	
	
	for (Entity * entity : m_entities) {

		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		GrenadeComponent * gc = (GrenadeComponent*)entity->getCompByType("GRENADE");
		if (gc->getExplode()) {
			explodeX = pc->getX() - camera->getCamera()->x;
			explodeY = pc->getY() - camera->getCamera()->y;
			c2v v2 = { explodeX, explodeY };
			
			for (int i = 0; i < tiles.size(); i++) 
			{
				c2v v1 = { (float)tiles.at(i)->dRect.x + 35 - camera->getCamera()->x, (float)tiles.at(i)->dRect.y + 35 - camera->getCamera()->y };
					
				if (dist(v1, v2) < 250.0) 
				{
					tiles.at(i)->dead = true;
				}
				
			}
			for (AI * ai : aiChars) {
				Entity* ent = (Entity *)ai;
				PositionComponent * aiPC = (PositionComponent*)ent->getCompByType("POSITION");
				SpriteComponent * sc = (SpriteComponent*)ent->getCompByType("SPRITE");
				ControlComponent * comp = (ControlComponent*)ent->getCompByType("CONTROL");
				AIComponent * aiC = (AIComponent*)ent->getCompByType("AI");
				if (dist(c2v{ aiPC->getX(), aiPC->getY() }, v2) < 300) {
					aiPC->setVelX(2000 * (1 / (aiPC->getX() - v2.x)));
					aiPC->setVelY(2000 * (1 / (aiPC->getY() - v2.y)));
					sc->setRotation(90);
					sc->setColor(255, 40, 40);
					comp->setAlive(false);
					sc->setBlendMode(SDL_BLENDMODE_ADD);
				}
			}

			for (Player * player : playerChars) {
				Entity* ent = (Entity *)player;
				PositionComponent * pPC = (PositionComponent*)ent->getCompByType("POSITION");
				SpriteComponent * sc = (SpriteComponent*)ent->getCompByType("SPRITE");
				ControlComponent * pCC = (ControlComponent*)ent->getCompByType("CONTROL");
				if (dist(c2v{ pPC->getX(), pPC->getY() }, v2) < 300) {
					pPC->setVelX(2000 * (1 / (pPC->getX() - v2.x)));
					pPC->setVelY(2000 * (1 / (pPC->getY() - v2.y)));
					sc->setRotation(90);
					sc->setColor(255, 40, 40);
					pCC->setAlive(false);
					sc->setBlendMode(SDL_BLENDMODE_ADD);
				}
			}
			
			// James please add big boom here :)
			pc->setX(-3000);
			pc->setY(-3000);

			m_startAnimating = true;

			gc->setArmed(false);
			gc->setExplode(false);
			
			gc->setTTL(300);
		}
	}

}

void GrenadeSystem::render()
{
	if (m_startAnimating)
	{
		animateExplosion();
	}
}


float GrenadeSystem::dist(c2v v1, c2v v2) {
	float dist = std::sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
	return dist;
}


void GrenadeSystem::animateExplosion()
{
	m_count++;
	explode->setStartSpin(90);
	explode->setEndSpin(90);
	explode->setDuration(.2);
	explode->setStartSize(30);
	explode->setStartSpinVar(180);// set the renderer
	explode->setSpeed(-300);
	explode->setSpeedVar(100);

	explode->setPosition(explodeX, explodeY);
	//p->setAngle(angle);
	explode->update();
	explode->draw();

	//if (SDL_HapticRumblePlay(haptic, .5, 100) != 0)
	//{
	//	printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
	//}

	if (m_count > 30)
	{
		explode->resetSystem();
		m_startAnimating = false;
		m_count = 0;
	}
}


void GrenadeSystem::setRenderer(SDL_Renderer * renderer)
{
	explode = new ParticleExample();
	explode->setRenderer(renderer);
	explode->setStyle(ParticleExample::GRENADE);
}
