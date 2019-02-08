#include "PhysicsSystem.h"
PhysicsSystem::PhysicsSystem()
{
	Friction.x = 0.90;
	Friction.y = 0.98;

	p = new ParticleExample();

	
	
}

void PhysicsSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void PhysicsSystem::update() {

	for (Entity * entity : m_entities) {

		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
		ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");
		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		AIComponent * ac = (AIComponent*)entity->getCompByType("AI");

		
		// Flip Player and hands while no gun equiped.
		if (tc->getTag() == "Player")
		{
			if (gotGun == false)
			{
				if (pc->getVelX() >= 0)
				{
					sc->m_flipValue = SDL_FLIP_NONE;
					right = true;  // bools used to flip hands properly while no gun grabbed.
					left = false;
				}
				else {
					sc->m_flipValue = SDL_FLIP_HORIZONTAL;
					left = true;
					right = false;
				}
			}
			else{
				if (cc->getAngle() < 0)
				{
					sc->m_flipValue = SDL_FLIP_HORIZONTAL;
					left = false;
					right = false;
				}
				else {
					sc->m_flipValue = SDL_FLIP_NONE;
					left = false;
					right = false;
				}
			}
		}
		if (tc->getTag() == "Hand")
		{
			if (left == true)
			{
				sc->m_flipValue = SDL_FLIP_HORIZONTAL;
			}
			else if (right == true)
			{
				sc->m_flipValue = SDL_FLIP_NONE;
			}
		}

		// check gun player collide
		if (tc->getTag() == "Player")
		{
			playerPositionX = pc->getX();
			playerPositionY = pc->getY();
		}
		if (tc->getTag() == "Gun")
		{
	
			if (tc->getGrabbed() == true)  // Set the gun to be grabbed
			{
				//x = RCos(Angle)
				//y = RSin(Angle)

				double angleTo = cc->getAngle() + 90;
				double angleDifference = angleTo - angle;
				double ease = 0.1;
				angle += angleDifference * ease;

				double radAng = angle * 3.14159265359 / 180;
				xOffset = 90 * (cos(radAng));
				yOffset = 90 * (sin(radAng));

				if (fired == false)
				{
					pc->setX(playerPositionX - xOffset);  // set gun position + offset for player centre - offset for angle
					pc->setY(playerPositionY + yOffset);
				}
				else
				{
					if (sc->m_flipValue == SDL_FLIP_NONE)
					{
						pc->setX(playerPositionX - xOffset - (firedCount));  // set gun position + offset for player centre - offset for angle
						sc->rotate(firedCount);
					}
					else
					{
						pc->setX(playerPositionX - xOffset + (firedCount));
					}
					pc->setY(playerPositionY + yOffset);
				}

				// Get positions for hands to get on gun.
				gunPositionX = pc->getX();
				gunPositionY = pc->getY();
			}
			// Check if player collides with gun and if they dont already have a gun
			else if (playerPositionX >= pc->getX() - 100 && playerPositionX <= pc->getX() + 100 
				&& playerPositionY >= pc->getY() - 100 && playerPositionY <= pc->getY() + 100 
				&& gotGun == false && tc->getGrabable() == true)
			{
				tc->setGrabbed(true);
				pc->setVelX(0);
				pc->setVelY(0);
				gotGun = true;
			}

			if (aiPositionX >= pc->getX() - 100 && aiPositionX <= pc->getX() + 100
				&& aiPositionY >= pc->getY() && aiPositionY <= pc->getY() + 100)
			{
				pc->setX(aiPositionX);
				pc->setY(aiPositionY);
			}
		}
		if (tc->getTag() == "Player" && cc->getThrowWeapon() == true && gotGun == true)  // Check if x is pressed.
		{
			cc->setThrowWeapon(false);
			//std::cout << "GOT = " << gotGun << std::endl;
			throwGun = true;
		}
		
		if (tc->getTag() == "Gun" && throwGun == true)  // Check if a weapon wants to be thrown
		{
			//std::cout << "X = " << -xOffset <<  "Y = " << yOffset << std::endl;
			pc->setVelX(-xOffset / 2);
			pc->setVelY(yOffset / 2);
			
			tc->setGrabbed(false);
			tc->setGrabable(false); // Start count to make gun grabable again.
			gotGun = false;
			throwGun = false;
		}

		// Increase grabable count to allow thrown gun to be picked up again.
		if (tc->getGrabable() == false)
		{
			if (tc->getGrabableCount() > 30)
			{
				tc->setGrabable(true);
				tc->setGrabableCount(0);
			}
			else
			{
				tc->setGrabableCount(tc->getGrabableCount() + 1);
			}
		}
		
		if (tc->getTag() == "Gun" && tc->getGrabbed() == true && fired == false)
		{
			//m_emitter->draw();
			//m_emitter->update();
			sc->setRotation((cc->getAngle())*-1); //rotate gun
		}
		else if (tc->getTag() == "Gun" && tc->getGrabbed() == true && fired == true) // Pistol recoil rotate
		{
			if (sc->m_flipValue == SDL_FLIP_NONE)
			{
				sc->setRotation((cc->getAngle())*-1 - firedCount); //rotate gun
			}
			else {
				sc->setRotation((cc->getAngle())*-1 + firedCount); //rotate gun
			}
		}
		if (tc->getTag() == "Hand" && gotGun == true) // Set hand on gun
		{
			
			double handAngle = angle - 90;
			
			sc->setRotation((cc->getAngle())*-1); //rotate hand
			pc->setX(gunPositionX);
			if (handAngle < 0)
			{
				handAngle = handAngle * -1;
			}
			pc->setY(gunPositionY + (handAngle / 5));
		}
		else if (tc->getTag() == "Hand") // Set hand to body
		{
			pc->setX(playerPositionX);
			pc->setY(playerPositionY + 6);
		}
		
		if (tc->getTag() == "Hand" && cc->getAngle() < 0 && gotGun == true|| tc->getTag() == "Gun" && cc->getAngle() < 0 && gotGun == true)
		{
			sc->m_flipValue = SDL_FLIP_HORIZONTAL;
			//std::cout << "flip = " << sc->m_flipValue << std::endl;
		}
		else if(tc->getTag() == "Hand" && gotGun == true || tc->getTag() == "Gun" && gotGun == true){
			sc->m_flipValue = SDL_FLIP_NONE;
		}


		if (tc->getTag() == "Player" || tc->getTag() == "Gun" && gotGun != true)  // bool to check if gun is grabbed so gun falls
		{
			pc->setVelY(pc->getVelY() + Friction.y);
		

			//sc->setRotation((cc->getAngle())*-1);

		}
		
		if (tc->getTag() == "Player")
		{

			if (cc->getLeft()) {
				if (pc->getVelX() > -8.0) {
					pc->setVelX(pc->getVelX() - 1.5);
				}
			}
			if (cc->getRight()) {
				if (pc->getVelX() < 8.0) {
					pc->setVelX(pc->getVelX() + 1.5);
				}
			}
			if (cc->getJump() && pc->m_allowedJump) {
				pc->setVelY(pc->getVelY() - 20);
				cc->setJump(false);
				pc->m_allowedJump = false;
			}

			
		}

		if (tc->getTag() == "AI_TAG")
		{
			aiPositionX = pc->getX();
			aiPositionY = pc->getY();
		
		
			
			pc->setVelY(pc->getVelY() + Friction.y);
			
		}



		pc->setVelX(pc->getVelX() * Friction.x);
		
		if (tc->getTag() == "Player" || tc->getTag() == "AI_TAG")
		{
			pc->setX(pc->getX() + pc->getVelX());
			pc->setY(pc->getY() + pc->getVelY());
		}
		
	}
}

void PhysicsSystem::bulletUpdate(SDL_Renderer* renderer) {
	if (fired == true)
	{
		if (firedCount < 10)
		{
			firedCount = firedCount + 1;
		}
		else {
			fired = false;
			firedCount = 0;
		}
	}
	for (Entity * entity : m_entities) {
		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
		if (tc->getTag() == "Gun")
		{
			FactoryComponent * fc = (FactoryComponent*)entity->getCompByType("FACTORY");
			ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");
			PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");

			if (cc->getFire())
			{
				if (fired == false)
				{
					fired = true;
					//bullets.push_back(fc->makeBullet(renderer, pc->getX(), pc->getY(), (cc->getAngle())*-1, -xOffset, yOffset));
					if (SDL_HapticRumblePlay(haptic, 0.5, 100) != 0)
					{
						printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
					}
					pc->bullets.push_back(fc->makeBullet(renderer, pc->getX(), pc->getY(), - (angle - 90), -xOffset, yOffset));
					bullets = pc->bullets;

				
				}

			}

		}
	}
}
void PhysicsSystem::bulletRender(SDL_Renderer* renderer) {
		
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->render(renderer);
		      // create a new particle system pointer
		
		animateExplosion(renderer);
		
		
	}
}

void PhysicsSystem::animateExplosion(SDL_Renderer * renderer)
{
	p->setRenderer(renderer);
	p->setStyle(ParticleExample::SMOKE);    // set the example effects
	p->setStartSpin(0);
	p->setStartSpinVar(90);
	p->setEndSpin(90);
	p->setDuration(.1);
	p->setStartSpinVar(90);// set the renderer
	p->setPosition(playerPositionX - xOffset, playerPositionY);              // set the position
	p->setStyle(ParticleExample::PatticleStyle(9));
	p->draw();

	
}

