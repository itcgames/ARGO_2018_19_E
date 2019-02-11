#include "PhysicsSystem.h"
PhysicsSystem::PhysicsSystem()
{
	Friction.x = 0.90;
	Friction.y = 0.98;

	

	
	
}

void PhysicsSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void PhysicsSystem::setGun(TagComponent * tc,ControlComponent * cc,PositionComponent * pc,SpriteComponent * sc) {
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
	else if (playerPositionX >= pc->getX() - 50 && playerPositionX <= pc->getX() + 50
		&& playerPositionY >= pc->getY() - 50 && playerPositionY <= pc->getY() + 50
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

void PhysicsSystem::pickUpAgain(TagComponent * tc) {
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
}

// Set the player position variable.
void PhysicsSystem::setPlayerPosition(PositionComponent * pc) {
	playerPositionX = pc->getX();
	playerPositionY = pc->getY();
}
void PhysicsSystem::throwGunFun(ControlComponent * cc) {
	cc->setThrowWeapon(false);
	throwGun = true;
}
void PhysicsSystem::playerFlip(PositionComponent * pc, SpriteComponent * sc, ControlComponent * cc) {
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
	else {
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

void PhysicsSystem::launchGun(PositionComponent * pc,TagComponent * tc) {
	//std::cout << "X = " << -xOffset <<  "Y = " << yOffset << std::endl;
	pc->setVelX(-xOffset / 2);
	pc->setVelY(yOffset / 2);

	tc->setGrabbed(false);
	tc->setGrabable(false); // Start count to make gun grabable again.
	gotGun = false;
	throwGun = false;
}

void PhysicsSystem::setHandOnGun(SpriteComponent * sc,PositionComponent *pc,ControlComponent * cc)
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
void PhysicsSystem::setHandNormal(SpriteComponent * sc, PositionComponent *pc)
{
	pc->setX(playerPositionX);
	pc->setY(playerPositionY + 6);
	sc->setRotation(0);
}
void PhysicsSystem::movePlayer(ControlComponent * cc,PositionComponent *pc) {
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

// Set the position after movement
void PhysicsSystem::setPosition(PositionComponent * pc) {
	pc->setX(pc->getX() + pc->getVelX());
	pc->setY(pc->getY() + pc->getVelY());
}
void PhysicsSystem::flipNone(SpriteComponent * sc) {
	sc->m_flipValue = SDL_FLIP_NONE;
	flipval = sc->m_flipValue;
}

void PhysicsSystem::flipHorizontal(SpriteComponent * sc) {
	sc->m_flipValue = SDL_FLIP_HORIZONTAL;
	flipval = sc->m_flipValue;
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
			playerFlip(pc,sc,cc);  // Flip Player sprite when angle requires it.
			setPlayerPosition(pc);  // Set player position variable for others.
			if (cc->getThrowWeapon() == true && gotGun == true)  // Check if x is pressed.
			{
				throwGunFun(cc);
			}
			movePlayer(cc,pc);
			setPosition(pc);  // Set the position after movement

			pc->setVelY(pc->getVelY() + Friction.y);  // Friction
		}
		if (tc->getTag() == "Gun")
		{
			setGun(tc,cc,pc,sc);
			pickUpAgain(tc);
			if (throwGun == true)  // Check if a weapon wants to be thrown
			{
				launchGun(pc,tc);
			}
			if (tc->getGrabbed() == true && fired == false) {
				sc->setRotation((cc->getAngle())*-1); //rotate gun
			}
			else if (tc->getGrabbed() == true && fired == true) {
				if (sc->m_flipValue == SDL_FLIP_NONE)
				{
					sc->setRotation((cc->getAngle())*-1 - firedCount); //rotate gun with recoil
				}
				else {
					sc->setRotation((cc->getAngle())*-1 + firedCount); //rotate gun with recoil
				}
			}
			if (cc->getAngle() < 0 && gotGun == true) {
				flipHorizontal(sc);
			}
			else if(gotGun == true) {
				flipNone(sc);
			}
			if (gotGun != true)
			{
				pc->setVelY(pc->getVelY() + Friction.y);  // Friction so gun falls when not grabbed
				setPosition(pc);
			}

		}
		
		if (tc->getTag() == "Hand") {
			if (left == true)
			{
				sc->m_flipValue = SDL_FLIP_HORIZONTAL;
			}
			else if (right == true)
			{
				sc->m_flipValue = SDL_FLIP_NONE;
			}
			if (gotGun == true)
			{
				setHandOnGun(sc, pc, cc); // Set hand on gun
			}
			else {
				setHandNormal(sc, pc); // Set hand to body
			}
			if (cc->getAngle() < 0 && gotGun == true)
			{
				flipHorizontal(sc);
			}
			else if(gotGun == true){
				flipNone(sc);
			}
		}
		
	


		

		if (tc->getTag() == "AI_TAG")
		{
			aiPositionX = pc->getX();
			aiPositionY = pc->getY();
				
			pc->setVelY(pc->getVelY() + Friction.y);	
		}

		pc->setVelX(pc->getVelX() * Friction.x);  // Friction
		
		if (tc->getTag() == "AI_TAG")
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
			if (tc->getGrabbed() == true)  // Ensure gun is grabbed before shooting
			{
				if (cc->getFire())
				{
					if (fired == false)
					{

						fired = true;
						m_startAnimating = true;

						if (SDL_HapticRumblePlay(haptic, .5, 100) != 0)

						{
							printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
						}
						pc->bullets.push_back(fc->makeBullet(renderer, pc->getX(), pc->getY(), -(angle - 90), -xOffset, yOffset));
						bullets = pc->bullets;
					}
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
		
		
	}
	if (m_startAnimating) {
		animateExplosion(renderer);
	}
	
}

void PhysicsSystem::setRenderer(SDL_Renderer * renderer)
{
	m_renderer = renderer;
	p = new ParticleExample();
	p->setRenderer(m_renderer);
	p->setStyle(ParticleExample::SMOKE);
}

void PhysicsSystem::animateExplosion(SDL_Renderer * renderer)
{
	m_count++;
	p->setStartSpin(0);
    p->setStartSpinVar(90);
	p->setEndSpin(90);
    p->setDuration(.1);
	p->setStartSize(30);
	p->setStartSpinVar(90);// set the renderer
	if (flipval == SDL_FLIP_HORIZONTAL)
	{
		p->setPosition(gunPositionX - 15, gunPositionY);
		//p->setAngle(-angle);
	}
	else
	{
		p->setPosition(gunPositionX + 60, gunPositionY + 10);
		//p->setAngle(angle);
	}
	
	p->update();
	p->draw();
	
	if (m_count > 15)
	{
		m_count = 0;
		p->resetSystem();
		m_startAnimating = false;
	}
}

