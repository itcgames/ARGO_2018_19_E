#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem() {
	Friction.x = 0.90;
	Friction.y = 0.98;
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
				double ease = 0.15;
				angle += angleDifference * ease;

				double radAng = angle * 3.14159265359 / 180;
				xOffset = 90 * (cos(radAng));
				yOffset = 90 * (sin(radAng));

				pc->setX(playerPositionX + 50 - xOffset);  // set gun position + offset for player centre - offset for angle
				pc->setY(playerPositionY + 40 + yOffset);

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

			if (aiPositionX >= pc->getX() - 100 && aiPositionX <= pc->getX() + 100)
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
		
		if (tc->getTag() == "Gun" && tc->getGrabbed() == true)
		{
			sc->setRotation((cc->getAngle())*-1); //rotate gun
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
			pc->setY(playerPositionY + 64);
		}
		
		if (tc->getTag() == "Hand" && cc->getAngle() < 0 || tc->getTag() == "Gun" && cc->getAngle() < 0)
		{
			sc->m_flipValue = SDL_FLIP_HORIZONTAL;
			//std::cout << "flip = " << sc->m_flipValue << std::endl;
		}
		else if(tc->getTag() == "Hand" || tc->getTag() == "Gun"){
			sc->m_flipValue = SDL_FLIP_NONE;
		}


		if (tc->getTag() == "Player" || tc->getTag() == "Gun" && gotGun != true)  // bool to check if gun is grabbed so gun falls
		{
			if (pc->getY() <= 500) {
				pc->setVelY(pc->getVelY() + Friction.y);
			}
			else {
				pc->setVelY(0);
			}

			//sc->setRotation((cc->getAngle())*-1);

			if (cc->getAngle() < 0)
			{
				sc->m_flipValue = SDL_FLIP_HORIZONTAL;
			}
			else {
				sc->m_flipValue = SDL_FLIP_NONE;
			}
		}
		
		if (tc->getTag() == "Player")
		{

			if (cc->getLeft()) {
				if (pc->getVelX() > -6.0) {
					pc->setVelX(pc->getVelX() - 1.5);
				}
			}
			if (cc->getRight()) {
				if (pc->getVelX() < 6.0) {
					pc->setVelX(pc->getVelX() + 1.5);
				}
			}
			if (cc->getJump() && pc->getY() >= 500) {
				pc->setVelY(pc->getVelY() - 20);
				pc->setY(500);
				cc->setJump(false);
			}

			if (cc->getAngle() < 0)
			{
				sc->m_flipValue = SDL_FLIP_HORIZONTAL;
			}
			else {
				sc->m_flipValue = SDL_FLIP_NONE;
			}
		}

		if (tc->getTag() == "AI_TAG")
		{
			aiPositionX = pc->getX();
			aiPositionY = pc->getY();
		
			if (ac->getJump() && pc->getY() >= 500) {
				pc->setVelY(pc->getVelY() - 20);
				pc->setY(500);
				ac->setJump(false);
				
			}
			if (pc->getY() <= 500) {
				pc->setVelY(pc->getVelY() + Friction.y);
			}
			else {
				pc->setVelY(0);

			}
		}



		pc->setVelX(pc->getVelX() * Friction.x);

		pc->setX(pc->getX() + pc->getVelX());
		pc->setY(pc->getY() + pc->getVelY());
	}
}

