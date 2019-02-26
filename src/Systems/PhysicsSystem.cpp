#include "PhysicsSystem.h"
PhysicsSystem::PhysicsSystem()
{
	Friction.x = 0.90;
	Friction.y = 0.98;

	gunFriction.x = 0.97;
	gunFriction.y = 0.96;

	srand(1);

}

void PhysicsSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void PhysicsSystem::setGun(TagComponent * tc, ControlComponent * cc, PositionComponent * pc, SpriteComponent * sc, PositionComponent * ownerPosC, ControlComponent * ownerConC) {
	if (tc->getGrabbed() == true)  // Set the gun to be grabbed
	{
		//x = RCos(Angle)
		//y = RSin(Angle)
		double angle = tc->getPreviousAngle();
		double angleTo = ownerConC->getAngle() + 90;
		double angleDifference = angleTo - angle;
		double ease = 0.1;
		if (tc->getSubTag() == "juicer")
		{
			ease = 0.01;
		}
		else if (tc->getSubTag() == "shotgun")
		{
			ease = 0.04;
		}


		angle += angleDifference;

		// Code to snap to certain set rotations.
		double snapAngle = angleTo + 90;
		double deadSize = 15;
		double RotateAllowed = 45;

		if (tc->getSubTag() == "juicer")
		{
			RotateAllowed = 45;
			// Cap rotation for juicer so cant shoot up and down
			if (snapAngle <= 90 - RotateAllowed)
			{
				angle = 0 - RotateAllowed;
			}
			else if (snapAngle >= 90 + RotateAllowed && snapAngle < 180)
			{
				angle = 0 + RotateAllowed;
			}
			else if (snapAngle >= 270 + RotateAllowed)
			{
				angle = 180 + RotateAllowed;
			}
			else if (snapAngle <= 270 - RotateAllowed && snapAngle >= 180)
			{
				angle = 180 - RotateAllowed;
			}

			// Snap left,right,up,down

			if (snapAngle >= 90 - deadSize && snapAngle <= 90 + deadSize)
			{
				angle = 0;
			}
			else if (snapAngle >= 270 - deadSize && snapAngle <= 270 + deadSize)
			{
				angle = 180;
			}
		}
		else if (tc->getSubTag() == "shotgun")
		{
			RotateAllowed = 55;
			// Cap rotation for juicer so cant shoot up and down
			if (snapAngle <= 90 - RotateAllowed)
			{
				angle = 0 - RotateAllowed;
			}
			else if (snapAngle >= 90 + RotateAllowed && snapAngle < 180)
			{
				angle = 0 + RotateAllowed;
			}
			else if (snapAngle >= 270 + RotateAllowed)
			{
				angle = 180 + RotateAllowed;
			}
			else if (snapAngle <= 270 - RotateAllowed && snapAngle >= 180)
			{
				angle = 180 - RotateAllowed;
			}

			// Snap left,right,up,down

			if (snapAngle >= 90 - deadSize && snapAngle <= 90 + deadSize)
			{
				angle = 0;
			}
			else if (snapAngle >= 270 - deadSize && snapAngle <= 270 + deadSize)
			{
				angle = 180;
			}
		}
		else {
			if (snapAngle <= 0 + deadSize || snapAngle >= 360 - deadSize)
			{
				angle = 270;
			}
			else if (snapAngle >= 90 - deadSize && snapAngle <= 90 + deadSize)
			{
				angle = 0;
			}
			else if (snapAngle >= 180 - deadSize && snapAngle <= 180 + deadSize)
			{
				angle = 90;
			}
			else if (snapAngle >= 270 - deadSize && snapAngle <= 270 + deadSize)
			{
				angle = 180;
			}
		}


		ownerConC->setCurrentAngle(angle - 90);
		tc->setAngle(angle);

		

		double radAng = angle * 3.14159265359 / 180;
		double radius = 60;
		if (tc->getSubTag() == "pistol" || tc->getSubTag() == "grenade")
		{
			radius = 60;
		}
		if (tc->getSubTag() == "stabbyboy")
		{
			radius = 60;
		}
		else if (tc->getSubTag() == "shotgun")
		{
			radius = 30;
		}
		else if (tc->getSubTag() == "juicer")
		{
			radius = 60;
		}
		tc->setXOffset(radius * (cos(radAng)));
		tc->setYOffset(radius * (sin(radAng)));
		if (ownerPosC->getFiredCount() == 0)
		{
			if (tc->getSubTag() == "juicer")
			{
				if (sc->m_flipValue == SDL_FLIP_NONE)
				{
					pc->setX(ownerPosC->getX() - tc->getXOffset() - 80);  // set gun position + offset for player centre - offset for angle
				}
				else {
					pc->setX(ownerPosC->getX() - tc->getXOffset() - 80);  // set gun position + offset for player centre - offset for angle
				}
			}
			else if (tc->getSubTag() == "shotgun"){
				if (sc->m_flipValue == SDL_FLIP_NONE)
				{
					pc->setX(ownerPosC->getX() + tc->getXOffset() + 50);
				}
				else {
					pc->setX(ownerPosC->getX() - tc->getXOffset() - 20);
				}
			}
			else {
				pc->setX(ownerPosC->getX() - tc->getXOffset());
			}
			if (tc->getSubTag() == "pistol")
			{
				pc->setX(ownerPosC->getX() - tc->getXOffset());  // set gun position + offset for player centre - offset for angle
			}
			if (tc->getSubTag() == "pistol" || tc->getSubTag() == "grenade")
			{
				pc->setY(ownerPosC->getY() + tc->getYOffset());
			}
			if (tc->getSubTag() == "stabbyboy")
			{
				pc->setX(ownerPosC->getX() - tc->getXOffset() * 2);  // set gun position + offset for player centre - offset for angle
			}
			if (tc->getSubTag() == "stabbyboy")
			{
				pc->setY(ownerPosC->getY() + (tc->getYOffset() * 2) - 100);
			}
			else if (tc->getSubTag() == "shotgun")
			{
				pc->setY(ownerPosC->getY() - 55 + tc->getYOffset());
			}
			else if (tc->getSubTag() == "juicer")
			{
				pc->setY(ownerPosC->getY() - 100 + tc->getYOffset());

			}
			if (tc->getGrabbed() == true) {
				if (tc->getSubTag() == "juicer")  // Slow down rotation for juicer balance
				{
					double angleTo = ownerConC->getCurrentAngle();
					double angleDifference = angleTo - tc->getPreviousAngle();
					double ease = 0.01;
					float previousAngle = tc->getPreviousAngle();
					//tc->setPreviousAngle(previousAngle += angleDifference * ease);
					tc->setPreviousAngle(previousAngle += angleDifference);
					sc->setRotation(-tc->getPreviousAngle()); //rotate gun
				}
				else if (tc->getSubTag() == "pistol")  // Slow down rotation for juicer balance
				{
					double angleTo = ownerConC->getCurrentAngle();
					double angleDifference = angleTo - tc->getPreviousAngle();
					double ease = 0.1;
					float previousAngle = tc->getPreviousAngle();
					//tc->setPreviousAngle(previousAngle += angleDifference * ease);
					tc->setPreviousAngle(previousAngle += angleDifference);
					sc->setRotation(-tc->getPreviousAngle()); //rotate gun
				}
				else if (tc->getSubTag() == "grenade")  // Slow down rotation for juicer balance
				{
					double angleTo = ownerConC->getCurrentAngle();
					double angleDifference = angleTo - tc->getPreviousAngle();
					double ease = 0.2;
					float previousAngle = tc->getPreviousAngle();
					//tc->setPreviousAngle(previousAngle += angleDifference * ease);
					tc->setPreviousAngle(previousAngle += angleDifference);
					sc->setRotation(-tc->getPreviousAngle()); //rotate gun
				}
				else if (tc->getSubTag() == "shotgun")  // Slow down shotgun rotation to make it look nice
				{
					double angleTo = ownerConC->getCurrentAngle();
					double angleDifference = angleTo - tc->getPreviousAngle();
					double ease = 0.04;
					float previousAngle = tc->getPreviousAngle();
					//tc->setPreviousAngle(previousAngle += angleDifference * ease);
					tc->setPreviousAngle(previousAngle += angleDifference);
					sc->setRotation(-tc->getPreviousAngle()); //rotate gun
				}
				else if (tc->getSubTag() == "stabbyboy")  // Slow down rotation for juicer balance
				{
					double angleTo = ownerConC->getCurrentAngle();
					double angleDifference = angleTo - tc->getPreviousAngle();
					double ease = 0.1;
					float previousAngle = tc->getPreviousAngle();
					//tc->setPreviousAngle(previousAngle += angleDifference * ease);
					tc->setPreviousAngle(previousAngle += angleDifference);
					sc->setRotation(-tc->getPreviousAngle()); //rotate gun
				}
				else {
					sc->setRotation((ownerConC->getAngle())*-1); //rotate gun
				}
			}
		}
		// Animations for gun recoil
		else
		{
			if (tc->getSubTag() == "pistol" || tc->getSubTag() == "grenade")
			{
				pc->setY(ownerPosC->getY() + tc->getYOffset());
				if (sc->m_flipValue == SDL_FLIP_NONE)
				{

					pc->setX(ownerPosC->getX() - tc->getXOffset() - (ownerPosC->getPistolCount()) / 2);  // set gun position + offset for player centre - offset for angle
					sc->setRotation(-tc->getPreviousAngle() - ownerPosC->getPistolCount()); //rotate gun with recoil

				}
				else {
					pc->setX(ownerPosC->getX() - tc->getXOffset() + (ownerPosC->getPistolCount()));
					sc->setRotation(-tc->getPreviousAngle() + ownerPosC->getPistolCount()); //rotate gun with recoil
				}
				double angleTo = ownerConC->getCurrentAngle();
				double angleDifference = angleTo - tc->getPreviousAngle();
				double ease = 0.1;
				float previousAngle = tc->getPreviousAngle();
				tc->setPreviousAngle(previousAngle += angleDifference);
				//sc->setRotation(-tc->getPreviousAngle()); //rotate gun
			}
			else if (tc->getSubTag() == "shotgun")
			{
			
				pc->setY(ownerPosC->getY() - 55 + tc->getYOffset());
				// Count for recoil animation
				if (ownerPosC->getShotgunCount() < 15)
				{
					ownerPosC->setShotgunRotationCount(ownerPosC->getShotgunRotationCount() + 3);
				}
				else
				{
					ownerPosC->setShotgunRotationCount(ownerPosC->getShotgunRotationCount() - 1);
					if (ownerPosC->getShotgunRotationCount() < 0)
					{
						ownerPosC->setShotgunRotationCount(0);
					}
				}
				// Count for pump animation;
				if (ownerPosC->getShotgunCount() < 30)
				{
					ownerPosC->setShotgunPumpCount(ownerPosC->getShotgunPumpCount() + 1);
				}
				else {
					ownerPosC->setShotgunPumpCount(ownerPosC->getShotgunPumpCount() - 1);
				}
				if (ownerPosC->getShotgunPumpCount() < 0)
				{
					ownerPosC->setShotgunPumpCount(0);
				}

				if (sc->m_flipValue == SDL_FLIP_NONE)
				{
					pc->setX(ownerPosC->getX() + tc->getXOffset() - (ownerPosC->getShotgunRotationCount() * 1.5) + 50);
					sc->setRotation(-(ownerConC->getAngle()) - ownerPosC->getShotgunRotationCount()); //rotate gun with recoil
				}
				else {
					pc->setX(ownerPosC->getX() - tc->getXOffset() + (ownerPosC->getShotgunRotationCount() * 1.5) - 20);
					sc->setRotation(-(ownerConC->getAngle()) + ownerPosC->getShotgunRotationCount()); //rotate gun with recoil
				}
				double angleTo = ownerConC->getCurrentAngle();
				double angleDifference = angleTo - tc->getPreviousAngle();
				double ease = 0.04;
				float previousAngle = tc->getPreviousAngle();
				tc->setPreviousAngle(previousAngle += angleDifference);
			}
			else if (tc->getSubTag() == "juicer")
			{
				pc->setY(ownerPosC->getY() - 100 + tc->getYOffset());
				if (sc->m_flipValue == SDL_FLIP_NONE)
				{
					pc->setX(ownerPosC->getX() - tc->getXOffset() - 80 - (ownerPosC->getFiredCount()));  // set gun position + offset for player centre - offset for angle
					sc->setRotation(-angle + 90 - ownerPosC->getFiredCount()); //rotate gun with recoil
				}
				else {
					pc->setX(ownerPosC->getX() - tc->getXOffset() - 80 + (ownerPosC->getFiredCount()));  // set gun position + offset for player centre - offset for angle
					sc->setRotation(-angle + 90 + ownerPosC->getFiredCount()); //rotate gun with recoil
				}
				double angleTo = ownerConC->getCurrentAngle();
				double angleDifference = angleTo - tc->getPreviousAngle();
				double ease = 0.01;
		
				float previousAngle = tc->getPreviousAngle();
				//tc->setPreviousAngle(previousAngle += angleDifference * ease);
				tc->setPreviousAngle(previousAngle += angleDifference);
			}
		}

	}

	if (aiPositionX >= pc->getX() - 100 && aiPositionX <= pc->getX() + 100
		&& aiPositionY >= pc->getY() && aiPositionY <= pc->getY() + 100)
	{
		//pc->setX(aiPositionX);
		//pc->setY(aiPositionY);
	}
}
void PhysicsSystem::checkWeaponCollision(CollisionComponent * colc, TagComponent * tagc, ControlComponent * ownerConC) {
	for (Entity * entity : m_entities) {

		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
		ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");
		CollisionComponent * colisionc = (CollisionComponent*)entity->getCompByType("COLLISION");
		if (tc->getTag() == "Gun" && tc->getGrabable() == false && tc->getGrabbed() == true && tc->getSubTag() == "stabbyboy")
		{
			std::string val = rectCollision(colc->getCollider(), colisionc->getCollider());
			if (val != "none")
			{
				if (tc->getSubTag2() != tagc->getGunGotID())
				{
					ownerConC->setAlive(false);
				}
			}
		}
		if (tc->getTag() == "Gun" && tc->getGrabable() == true && tc->getGrabbed() == false)
		{
			std::string val = rectCollision(colc->getCollider(), colisionc->getCollider());
			if (val != "none")
			{
				if (tagc->getGunGot() == "none")
				{
					if (tc->getSubTag() != "stabbyboy")
					{
						colisionc->setH(0);
						colisionc->setW(0);
					}
					setPlayerGunGot(tc->getSubTag(), tagc,tc->getSubTag2());
					tc->setGrabbed(true);
					tc->setGrabable(false);
				}
			}
		}
	}
}
std::string PhysicsSystem::rectCollision(c2AABB A, c2AABB B)
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
			collision = (crossWidth >(-crossHeight)) ? "bottom" : "left";
		}
		else {
			collision = (crossWidth > (-crossHeight)) ? "right" : "top";
		}
	}

	return(collision);
}

void PhysicsSystem::pickUpAgain(TagComponent * tc, SpriteComponent * sc, CollisionComponent * colisionc) {
	// Increase grabable count to allow thrown gun to be picked up again.
	if (tc->getGrabable() == false && tc->getGrabbed() == false)
	{
		if (tc->getGrabableCount() > 10)
		{
			tc->setGrabable(true);
			tc->setGrabableCount(0);
			colisionc->setW(sc->getWidth());
			colisionc->setH(sc->getHeight());
		}
		else
		{
			tc->setGrabableCount(tc->getGrabableCount() + 1);
		}
	}
}
void PhysicsSystem::setPlayerGunGot(std::string gun, TagComponent * tagC, std::string gunID)
{
	for (Entity * entity : m_entities) {

		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
		if (tagC->getTag() == "Player" && tagC->getGunGot() != gun)
		{
			tagC->setGunGot(gun);
			tagC->setGunGotID(gunID);
			tagC->setGotGunBool(true);
			if (gun == "none")
			{
				tagC->setGotGunBool(false);
				tagC->setGunGotID("0");
			}
		}
		if (tc->getTag() == "Hand" && tc->getSubTag() == tagC->getSubTag())
		{
			tc->setGunGot(gun);
			tc->setGunGotID(gunID);
			tc->setGotGunBool(true);
			if (gun == "none")
			{
				tc->setGotGunBool(false);
				tc->setGunGotID("0");
			}
		}
	}
}

//// Set the player position variable.
//void PhysicsSystem::setPlayer1Position(PositionComponent * pc) {
//	player1PositionX = pc->getX();
//	player1PositionY = pc->getY();
//}
//void PhysicsSystem::setPlayer2Position(PositionComponent * pc) {
//	player2PositionX = pc->getX();
//	player2PositionY = pc->getY();
//}
void PhysicsSystem::throwGunFun(ControlComponent * cc) {
	//cc->setThrowWeapon(false);
	cc->setThrowGun(true);
}
void PhysicsSystem::playerFlip(PositionComponent * pc, SpriteComponent * sc, ControlComponent * cc, TagComponent * tc) {
	if (tc->getGunGot() == "none")
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

		if (tc->getSubTag2() == "AI_Player")

		{
		
			if (cc->getAngle() + 90 > -90)  // Could be wrong
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
		else {

			if (cc->getAngle() + 90 < 90)  // Could be wrong
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
}

void PhysicsSystem::launchGun(PositionComponent * pc, TagComponent * tc, CollisionComponent * cc, ControlComponent * ownerConC, TagComponent * ownerTagC) {
	if (tc->getSubTag() == "pistol")
	{
		pc->setVelX(-tc->getXOffset() / 3);
		pc->setVelY(-15);	
	}
	else if (tc->getSubTag() == "shotgun")
	{
		pc->setVelX(-tc->getXOffset() * 2);		
		pc->setVelY(-15);

	}
	else if (tc->getSubTag() == "juicer")
	{
		pc->setVelX(-tc->getXOffset() / 5);
		pc->setVelY(-20);
	}
	else if (tc->getSubTag() == "grenade") {
		pc->setVelX(-tc->getXOffset() / 2);
		pc->setVelY(tc->getYOffset() / 2);
	}
	tc->setGrabbed(false);
	tc->setGrabable(false);
	// Start count to make gun grabable again.
	ownerConC->setThrowGun(false);
	// SET PLAYER GUN FUNCTION
	setPlayerGunGot("none", ownerTagC,"0");  // Fix tc here :)
}

void PhysicsSystem::setHandOnGrenade(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc, ControlComponent * ownerConC, PositionComponent * gunPosition, TagComponent * gunTagC) {
	double handAngle = gunTagC->getAngle();  // :)

	sc->setRotation(gunTagC->getAngle()*-1); //rotate hand
	pc->setX(gunPosition->getX());
	if (handAngle < 0)
	{
		handAngle = handAngle * -1;
	}
	pc->setY(gunPosition->getY() + (handAngle / 5));
}

void PhysicsSystem::setHandOnPistol(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc, PositionComponent * ownerPosition, ControlComponent * ownerConC, PositionComponent * gunPosition, TagComponent * gunTagC)
{
	double handAngle = gunTagC->getAngle(); // :)

	sc->setRotation((gunTagC->getAngle() - 90)*-1); //rotate hand

	if (sc->m_flipValue == SDL_FLIP_HORIZONTAL)
	{
		if (handAngle < 0)
		{
			pc->setX(gunPosition->getX() + 20 + (handAngle / 10));
			pc->setY(gunPosition->getY() + 20 - (handAngle / 8));
		}
		else {
			pc->setX(gunPosition->getX() + 20 - (handAngle / 10));
			pc->setY(gunPosition->getY() + 20 - (handAngle / 15));
		}
	}
	else {
		pc->setX(gunPosition->getX());
		pc->setY(gunPosition->getY() + (handAngle / 8));
	}
	if (handAngle < 0)
	{
		handAngle = handAngle * -1;
	}
}
void PhysicsSystem::setHandOnStabby(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc, PositionComponent * ownerPosition, ControlComponent * ownerConC, PositionComponent * gunPosition, TagComponent * gunTagC)
{
	double handAngle = gunTagC->getAngle(); // :)

	if (handAngle <= 0) // Make hands look right for top left
	{
		handAngle = handAngle + 270;
	}

	float radiusHandle = 50;
	float HandleRadAng = (gunTagC->getAngle()) * 3.14159265359 / 180; // :)
																			 //float shotgunTipX = 207.2 * (cos(shotgunRadAng));
																			 //float shotgunTipY = 207.2 * (sin(shotgunRadAng));
	float HandleX = radiusHandle * (cos(HandleRadAng));
	float HandleY = radiusHandle * (sin(HandleRadAng));
	
	if (sc->m_flipValue == SDL_FLIP_NONE)
	{
		sc->setRotation(((gunTagC->getAngle() - 90)*-1) + 90); //rotate hand
	}
	else {
		sc->setRotation(((gunTagC->getAngle() - 90)*-1) - 90); //rotate hand
	}

	if (sc->m_flipValue == SDL_FLIP_HORIZONTAL)
	{

			pc->setX(ownerPosition->getX() - HandleX);
			pc->setY(ownerPosition->getY() + HandleY + (handAngle / 10));
		
	}
	else {
		pc->setX(ownerPosition->getX() - HandleX);
		pc->setY(ownerPosition->getY() + HandleY + (handAngle / 10));
	}
	if (handAngle < 0)
	{
		handAngle = handAngle * -1;
	}
}
void PhysicsSystem::setHandOnShotgun(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc, TagComponent * tc, PositionComponent * ownerPosC, ControlComponent * ownerConC, TagComponent * gunTagC)
{
	// 386
	if (tc->getSubTag2() == "right")
	{
		float radiusHandle = 50;
		float shotgunHandleRadAng = (gunTagC->getAngle()) * 3.14159265359 / 180; // :)
																						//float shotgunTipX = 207.2 * (cos(shotgunRadAng));
																						//float shotgunTipY = 207.2 * (sin(shotgunRadAng));
		float shotgunHandleX = radiusHandle * (cos(shotgunHandleRadAng));
		float shotgunHandleY = radiusHandle * (sin(shotgunHandleRadAng));

		sc->setRotation((gunTagC->getAngle() - 90)*-1 - ownerPosC->getShotgunRotationCount()); //rotate hand
		if (sc->m_flipValue == SDL_FLIP_NONE)
		{
			pc->setX(ownerPosC->getX() + 33 + shotgunHandleX - (ownerPosC->getShotgunRotationCount() * 1.5));
		}
		else {
			pc->setX(ownerPosC->getX() - 33 + shotgunHandleX + (ownerPosC->getShotgunRotationCount() * 1.5));
		}

		//pc->setY(gunPositionY + (handAngle));
		pc->setY(ownerPosC->getY() - shotgunHandleY + 25);
	}
	else if (tc->getSubTag2() == "left")
	{

		float radiusPump = 50 - (ownerPosC->getShotgunPumpCount() * 2.5);  // Change the radius so hand moves along radius line and looks like pumping
		float shotgunPumpRadAng = (gunTagC->getAngle()) * 3.14159265359 / 180;  // :)
																					   //float shotgunTipX = 207.2 * (cos(shotgunRadAng));
																					   //float shotgunTipY = 207.2 * (sin(shotgunRadAng));
		float shotgunPumpX = radiusPump * (cos(shotgunPumpRadAng));
		float shotgunPumpY = radiusPump * (sin(shotgunPumpRadAng));

		sc->setRotation(((gunTagC->getAngle() + 90)*-1 - ownerPosC->getShotgunRotationCount()) - 90); //rotate hand
		if (sc->m_flipValue == SDL_FLIP_NONE)
		{
			pc->setX(ownerPosC->getX() - (shotgunPumpX - 20) - (ownerPosC->getShotgunRotationCount() * 1.5));
		}
		else {
			pc->setX(ownerPosC->getX() - (shotgunPumpX + 20) + (ownerPosC->getShotgunRotationCount() * 1.5));
		}

		//pc->setY(gunPositionY + (handAngle));
		pc->setY(ownerPosC->getY() + shotgunPumpY + 25);
	}
}
void PhysicsSystem::setHandOnJuicer(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc, TagComponent * tc, PositionComponent * ownerPosC, ControlComponent * ownerConC, TagComponent * gunTagC)
{
	// 386
	if (tc->getSubTag2() == "right")
	{
		float radiusHandle = 40;
		float juicerHandleRadAng = (gunTagC->getAngle()) * 3.14159265359 / 180; // :)
																					   //float shotgunTipX = 207.2 * (cos(shotgunRadAng));
																					   //float shotgunTipY = 207.2 * (sin(shotgunRadAng));
		float juicerHandleX = radiusHandle * (cos(juicerHandleRadAng));
		float juicerHandleY = radiusHandle * (sin(juicerHandleRadAng));

		sc->setRotation((gunTagC->getAngle()-90)*-1 - ownerPosC->getJuicerCount()); //rotate hand
		if (sc->m_flipValue == SDL_FLIP_NONE)
		{
			pc->setX(ownerPosC->getX() + juicerHandleX - (ownerPosC->getJuicerCount() * 1.5));
		}
		else {
			pc->setX(ownerPosC->getX() + juicerHandleX + (ownerPosC->getJuicerCount() * 1.5));
		}

		//pc->setY(gunPositionY + (handAngle));
		pc->setY(ownerPosC->getY() - juicerHandleY + 25);
	}
	else if (tc->getSubTag2() == "left")
	{

		float radiusPump = 45 - (ownerPosC->getJuicerCount());
		float shotgunPumpRadAng = (gunTagC->getAngle()) * 3.14159265359 / 180; // :)
																					  //float shotgunTipX = 207.2 * (cos(shotgunRadAng));
																					  //float shotgunTipY = 207.2 * (sin(shotgunRadAng));
		float shotgunPumpX = radiusPump * (cos(shotgunPumpRadAng));
		float shotgunPumpY = radiusPump * (sin(shotgunPumpRadAng)) - 20;

		sc->setRotation(((gunTagC->getAngle() - 90)*-1 - ownerPosC->getJuicerCount()) - 90); //rotate hand
		if (sc->m_flipValue == SDL_FLIP_NONE)
		{
			pc->setX(ownerPosC->getX() - shotgunPumpX - (ownerPosC->getJuicerCount() * 1.5));
		}
		else {
			pc->setX(ownerPosC->getX() - shotgunPumpX + (ownerPosC->getJuicerCount() * 1.5));
		}

		//pc->setY(gunPositionY + (handAngle));
		pc->setY(ownerPosC->getY() + shotgunPumpY + 25);
	}
}
void PhysicsSystem::setHandNormal(SpriteComponent * sc, PositionComponent *pc, PositionComponent * ownerPosC)
{
	pc->setX(ownerPosC->getX());
	pc->setY(ownerPosC->getY() + 6);
	if (ownerPosC->getVelX() >= 0)
	{
		sc->m_flipValue = SDL_FLIP_NONE;
	}
	else {
		sc->m_flipValue = SDL_FLIP_HORIZONTAL;
	}
	sc->setRotation(0);
}
void PhysicsSystem::movePlayer(ControlComponent * cc, PositionComponent *pc, TagComponent *tc) {
	float speed = 1.5;
	float jumpSpeed = 20;

	if (tc->getGunGot() == "juicer")
	{
		speed = 0.5;
		jumpSpeed = 10;
	}
	if (tc->getGunGot() == "stabbyboy")
	{
		speed = 3.0;
		jumpSpeed = 20;
	}
	if (pc->getX() > 100) {
		if (cc->getLeft()) {
			if (pc->getVelX() > -8.0) {
				pc->setVelX(pc->getVelX() - speed);
			}
		}
	}
	if (pc->getX() < m_width - 150) {
		if (cc->getRight()) {

			if (pc->getVelX() < 8.0) {
				pc->setVelX(pc->getVelX() + speed);
			}
		}
	}
	if (cc->getJump() && pc->jumpNum < 2) {
		pc->setVelY(-jumpSpeed);
		cc->setJump(false);
		pc->m_allowedJump = false;
		pc->jumpNum++;
	}
	else if (cc->getJump() && pc->jumpNum < 3 && tc->getGunGot() == "stabbyboy")
	{
		pc->setVelY(-jumpSpeed);
		cc->setJump(false);
		pc->m_allowedJump = false;
		pc->jumpNum++;
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
void PhysicsSystem::setHands(PositionComponent * handOwnerPos, ControlComponent * ownerConC, TagComponent * ownerTagC) {
	for (Entity * entity : m_entities) {

		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");

		if (tc->getTag() == "Hand" && tc->getSubTag() == ownerTagC->getSubTag()) {
			ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");
			CollisionComponent * colc = (CollisionComponent*)entity->getCompByType("COLLISION");
			PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
			SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
			AIComponent * ac = (AIComponent*)entity->getCompByType("AI");
			TagComponent * gunGotTag = (TagComponent*)entity->getCompByType("TAG");
			if (tc->getGotGunBool() == true)
			{
				if (ownerConC->getAngle() + 90 < 90)
				{
					sc->m_flipValue = SDL_FLIP_HORIZONTAL;
				}
				else
				{
					sc->m_flipValue = SDL_FLIP_NONE;
				}
				PositionComponent * gunPos = (PositionComponent*)entity->getCompByType("POSITION");
				for (Entity * entity : m_entities) {
					TagComponent * gunTag = (TagComponent*)entity->getCompByType("TAG");
					if (tc->getGunGotID() == gunTag->getSubTag2())  // Finds which gun we have.
					{
						//std::cout << "TAG1 = " << tc->getTag() << "TAG2 = " << gunTag->getSubTag2() << "ID = " << tc->getGunGotID() << std::endl;
						gunPos = (PositionComponent*)entity->getCompByType("POSITION");
						gunGotTag = gunTag;
					}
				}
				if (tc->getGunGot() == "pistol")
				{
					setHandOnPistol(sc, pc, cc, handOwnerPos, ownerConC, gunPos,gunGotTag); // Set hand on gun
				}
				else if (tc->getGunGot() == "stabbyboy")
				{
					setHandOnStabby(sc, pc, cc, handOwnerPos, ownerConC, gunPos, gunGotTag); // Set hand on gun
				}
				else if (tc->getGunGot() == "shotgun")
				{
					setHandOnShotgun(sc, pc, cc, tc, handOwnerPos, ownerConC, gunGotTag); // Set hand on gun
				}
				else if (tc->getGunGot() == "juicer")
				{
					setHandOnJuicer(sc, pc, cc, tc, handOwnerPos, ownerConC, gunGotTag); // Set hand on gun
				}
				else if (tc->getGunGot() == "grenade") {
					setHandOnGrenade(sc, pc, cc, ownerConC, gunPos, gunGotTag); // Set hand on gun
				}
			}
			else {
				setHandNormal(sc, pc, handOwnerPos); // Set hand to body
			}
		}
	}
}


void PhysicsSystem::update(SDL_Renderer* renderer) {
		randomJuice = rand() % 30 - 15;
		startRoundCount = startRoundCount + 1;

		for (Entity * entity : m_entities) {

			TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
			ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");
			CollisionComponent * colc = (CollisionComponent*)entity->getCompByType("COLLISION");
			PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
			SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
			AIComponent * ac = (AIComponent*)entity->getCompByType("AI");

			PositionComponent * ownerPosC = (PositionComponent*)entity->getCompByType("POSITION");
			ControlComponent * ownerConC = (ControlComponent*)entity->getCompByType("CONTROL");
			TagComponent * ownerTagC = (TagComponent*)entity->getCompByType("TAG");
			SpriteComponent * ownerSpriteC = (SpriteComponent*)entity->getCompByType("SPRITE");

			if (startRoundCount >= 100)
			{
				// check gun player collide
				if (tc->getTag() == "Player" && cc->getAlive() == true)
				{
					handOwnerPosC = (PositionComponent*)entity->getCompByType("POSITION");
					setHands(handOwnerPosC, ownerConC, ownerTagC);
					checkWeaponCollision(colc, tc,ownerConC);

					if (tc->getGunGot() == "none")
					{
						tc->setGotGunBool(false);
					}
					playerFlip(pc, sc, cc, tc);  // Flip Player sprite when angle requires it.

					if (cc->getThrowWeapon() == true && tc->getGotGunBool() == true)  // Check if x is pressed.
					{
						throwGunFun(cc);
					}

					if (tc->getSubTag2() != "AI_Player")
					{
						movePlayer(cc, pc, tc);
						// Set the position after movement
						if (pc->getVelY() < 40)  // Cap Y to stop falling through floor
						{
							pc->setVelY(pc->getVelY() + Friction.y);  // Friction
						}
						setPosition(pc);
					}


				}
				else if (tc->getTag() == "Player" && cc->getAlive() == false)
				{
					throwGunFun(cc);
				}
				if (tc->getSubTag2() == "AI_Player")
				{
					aiPositionX = pc->getX();
					aiPositionY = pc->getY();


					if (ac->getDoubleJump())
					{
						pc->setVelY(-30);
						ac->setDoubleJump(false);
					}

					if (ac->getJump() && pc->jumpNum < 2) {
						pc->setVelY(-20);
						ac->setJump(false);
						pc->m_allowedJump = false;
						pc->jumpNum++;
					}

					if (ac->getLeft()) {
						if (pc->getVelX() > -8.0) {
							pc->setVelX(pc->getVelX() - 1.5);
						}
					}
					if (ac->getRight()) {
						if (pc->getVelX() < 8.0) {
							pc->setVelX(pc->getVelX() + 1.5);
						}
					}

					pc->setVelY(pc->getVelY() + Friction.y);

				}
				if (tc->getSubTag2() == "AI_Player")
				{
					pc->setX(pc->getX() + pc->getVelX());
					pc->setY(pc->getY() + pc->getVelY());
				}
			}

			if (tc->getTag() == "Gun")
			{
				std::string currentGun = tc->getSubTag2();
				for (Entity * entity : m_entities) {
					TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
					if (tc->getTag() == "Player")
					{
						if (tc->getGunGotID() == currentGun) {
							ownerPosC = (PositionComponent*)entity->getCompByType("POSITION");
							ownerConC = (ControlComponent*)entity->getCompByType("CONTROL");
							ownerSpriteC = (SpriteComponent*)entity->getCompByType("SPRITE");
							ownerTagC = tc;
						}
					}
				}

				updateShooting(renderer, ownerConC);
				setGun(tc, cc, pc, sc, ownerPosC, ownerConC);
				pickUpAgain(tc, sc, colc);
				if (tc->getGrabbed() == true)
				{
					if (ownerConC->getThrowGun() == true)  // Check if a weapon wants to be thrown
					{
						launchGun(pc, tc, colc, ownerConC, ownerTagC);
					}
				}
				if (tc->getAngle() < 90 && tc->getGrabbed() == true) {

					flipHorizontal(sc);

				}
				else if (tc->getGrabbed() == true) {

					flipNone(sc);

				}
				if (tc->getGrabbed() == true) { // :)

					sc->m_flipValue = ownerSpriteC->m_flipValue;

				}
				//	else if (tc->getGrabbed() == true) {

						//flipNone(sc);

					//}
				if (tc->getGrabbed() != true)
				{
					if (pc->getVelY() < 8) {
						pc->setVelY(pc->getVelY() + gunFriction.y);  // Friction so gun falls when not grabbed

					}
					setPosition(pc);
				}
				if (tc->getSubTag() == "grenade") {
					GrenadeComponent * gc = (GrenadeComponent*)entity->getCompByType("GRENADE");

					if (gc->getArmed()) {
						m_grenadeColor += 0.05f;
						//sc->setColor(255, 255, 100);
						//sc->setAlpha(100);
						gc->setTTL(gc->getTTL() - 1);
						if (gc->getTTL() < 0) {
							gc->setExplode(true);
						}
					}
				}

			}

			if (tc->getTag() != "Gun") {
				pc->setVelX(pc->getVelX() * Friction.x);  // Friction
			}
			else {
				pc->setVelX(pc->getVelX() * gunFriction.x);  // Friction
			}



		}
}

void PhysicsSystem::updateShooting(SDL_Renderer* renderer, ControlComponent* ownerConC) {
	shotgunBullets.clear();
	pistolBullets.clear();
	juicerBullets.clear();

	for (Entity * entity : m_entities) {

		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");

		// Update all bullets constantly
		if (tc->getSubTag() == "shotgun")
		{
			for (Bullet * b : pc->bullets)
			{
				shotgunBullets.push_back(b);
			}
		}
		else if (tc->getSubTag() == "pistol")
		{
			for (Bullet * b : pc->bullets)
			{
				pistolBullets.push_back(b);
			}
		}
		else if (tc->getSubTag() == "juicer")
		{
			for (Bullet * b : pc->bullets)
			{
				juicerBullets.push_back(b);
			}
		}
		for (int i = 0; i < pc->bullets.size(); i++) {
			pc->bullets.at(i)->m_ttl--;
			if (pc->bullets.at(i)->m_ttl < 0) {
				pc->bullets.erase(pc->bullets.begin() + i);
			}
		}
		if (tc->getTag() == "Player")
		{
			if (cc->getFire() && tc->getGunGot() != "none")
			{
				if (pc->getFiredCount() == 0)
				{
					tc->setFiredBool(true);

					makeBullets(renderer, tc, cc); // MAKE BULLETS and pass the tag
				}
			}
			if (tc->getFiredBool() == true)
			{
				if (tc->getGunGot() == "pistol")
				{
					if (pc->getFiredCount() <= 20)
					{
						pc->setFiredCount(pc->getFiredCount() + 1);
						pc->setPistolCount(pc->getPistolCount() + 1);
					}
					else if (pc->getFiredCount() > 20 && pc->getFiredCount() < 40)
					{
						pc->setFiredCount(pc->getFiredCount() + 1);
						pc->setPistolCount(pc->getPistolCount() - 1);
					}
					else if (pc->getFiredCount() < 80) {
						pc->setFiredCount(pc->getFiredCount() + 1);
						pc->setPistolCount(0);
					}
					else{
						tc->setFiredBool(false);
						pc->setFiredCount(0);
						pc->setPistolCount(0);
					}
				}
				if (tc->getGunGot() == "shotgun")
				{
					if (pc->getFiredCount() < 120)
					{
						pc->setFiredCount(pc->getFiredCount() + 1);
						pc->setShotgunCount(pc->getShotgunCount() + 1);
					}
					else {
						tc->setFiredBool(false);
						pc->setFiredCount(0);
						pc->setShotgunCount(0);
						pc->setShotgunPumpCount(0);
						pc->setShotgunRotationCount(0);
					}
				}
				if (tc->getGunGot() == "juicer")
				{
					if (pc->getFiredCount() < 5)
					{
						pc->setFiredCount(pc->getFiredCount() + 1);
						pc->setJuicerCount(pc->getJuicerCount() + 1);
					}
					else {
						tc->setFiredBool(false);
						pc->setFiredCount(0);
						pc->setShotgunCount(0);
						pc->setJuicerCount(0);
					}
				}
			}
		}
	}
}
void PhysicsSystem::makeBullets(SDL_Renderer* renderer, TagComponent* tagC, ControlComponent* ownerConC) {
	if (bulletTextureLoaded == false)
	{
		bulletTextureSpriteComp = new SpriteComponent(0, 0, 210, 295);
		bulletTextureSpriteComp->loadFromFile("assets/bullet.png", renderer);
		//m_spriteComponent->loadFromFile("assets/bullet.png", renderer);
		//m_spriteComponent->setTexture(bulletTexture, 94, 274);
		bulletTextureSpriteComp->setPosition(c2v{999999, 999999 });
		bulletTextureSpriteComp->setScale(c2v{ 0.1f, 0.1f });
		bulletTextureSpriteComp->setRotation(90);
		bulletTextureLoaded = true;
	}

	for (Entity * entity : m_entities) {
		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");

		if (tc->getTag() == "Gun" && tagC->getGunGotID() == tc->getSubTag2())
		{

			FactoryComponent * fc = (FactoryComponent*)entity->getCompByType("FACTORY");
			ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");
			CollisionComponent * colc = (CollisionComponent*)entity->getCompByType("COLLISION");
			PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
			SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
			if (tc->getGrabbed() == true)  // Ensure gun is grabbed before shooting
			{
				if (tagC->getFiredBool() == true)
				{
					if (tagC->getGunGot() == "shotgun")
					{
						//tagC->setFiredBool(false);
						tagC->setStartAnimating(true);

						if (tagC->getSubTag2() != "AI_Player")
						{
							if (SDL_HapticRumblePlay(ownerConC->getHaptic(), 1, 300) != 0)
							{
								printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
							}
						}

						float shotgunRadAng = (tc->getAngle()) * 3.14159265359 / 180; // :)

						notifyAudioObservers(AudioObserver::SFX::SHOTGUN_SHOOT);

						tagC->setShotgunTipX(100 * (cos(shotgunRadAng)));
						tagC->setShotgunTipY(103.6 * (sin(shotgunRadAng)));

						for (int i = 0; i < 7; i++)
						{
							float random = rand() % 40 - 20;
							float radAng = ((tc->getAngle()) + random) * 3.14159265359 / 180;  // :)
							float radius = 10;

							float shotgunXOffset = radius * (cos(radAng));
							float shotgunYOffset = radius * (sin(radAng));

							c2v vector = { -shotgunXOffset,shotgunYOffset };
							float mag = c2Len(vector);
							float unitX = -shotgunXOffset / mag;
							float unitY = shotgunYOffset / mag;


							if (sc->m_flipValue == SDL_FLIP_NONE)
							{
								pc->bullets.push_back(fc->makeBullet(renderer, pc->getX() - tagC->getShotgunTipX(), pc->getY() + tagC->getShotgunTipY() + 70, -(tc->getAngle() - 270), unitX * 80, unitY * 80, 100,bulletTextureSpriteComp->getTexture())); // :)
							}
							else {

								pc->bullets.push_back(fc->makeBullet(renderer, pc->getX() - tagC->getShotgunTipX() + 20, pc->getY() + tagC->getShotgunTipY() + 70, -(tc->getAngle() - 270), unitX * 80, unitY * 80, 100, bulletTextureSpriteComp->getTexture())); // :)
							}
						}

					}
					else if (tagC->getGunGot() == "pistol")
					{
						//tagC->setFiredBool(false);
						tagC->setStartAnimating(true);

						if (tagC->getSubTag2() != "AI_Player")
						{
							if (SDL_HapticRumblePlay(ownerConC->getHaptic(), .5, 100) != 0)

							{
								printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
							}
						}

						notifyAudioObservers(AudioObserver::SFX::PISTOL_SHOOT);
						pc->bullets.push_back(fc->makeBullet(renderer, pc->getX(), pc->getY(), -(tc->getAngle() - 90), -tc->getXOffset(), tc->getYOffset(), 1000, bulletTextureSpriteComp->getTexture()));  // :)




					}
					else if (tagC->getGunGot() == "juicer")
					{
						//tagC->setFiredBool(false);
						tagC->setStartAnimating(true);

						if (tagC->getSubTag2() != "AI_Player")
						{
							if (SDL_HapticRumblePlay(ownerConC->getHaptic(), 1, 300) != 0)
							{
								printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
							}
						}
						float juicerRadAng = (tc->getAngle()) * 3.14159265359 / 180;  // :)
																								  //float shotgunTipX = 207.2 * (cos(shotgunRadAng));
																								  //float shotgunTipY = 207.2 * (sin(shotgunRadAng));

						tagC->setJuicerTipX(180 * (cos(juicerRadAng)));
						tagC->setJuicerTipY(200 * (sin(juicerRadAng)));

						float radAng = ((tc->getAngle()) + randomJuice) * 3.14159265359 / 180; // :)
						float radius = 60;


						float juicerXOffset = radius * (cos(radAng));
						float juicerYOffset = radius * (sin(radAng));

						c2v vector = { -juicerXOffset,juicerYOffset };
						float mag = c2Len(vector);
						float unitX = -juicerXOffset / mag;
						float unitY = juicerYOffset / mag;
						notifyAudioObservers(AudioObserver::SFX::MINIGUN_SHOOT);
						if (sc->m_flipValue == SDL_FLIP_NONE)
						{

							pc->bullets.push_back(fc->makeBullet(renderer, (pc->getX() + 100) - tagC->getJuicerTipX() / 2, pc->getY() + (tagC->getJuicerTipY() * 0.8) + 140, -(tc->getAngle() - 270), unitX * 100, unitY * 80, 200, bulletTextureSpriteComp->getTexture())); // :)
							float x = (pc->getX() + 100) - tagC->getJuicerTipX() / 2;
							float y = pc->getY() + (tagC->getJuicerTipY() * 0.8) + 140;
							tagC->setJuicerExplosionPos(c2v{ x,y });
						}
						else {

							//pc->bullets.push_back(fc->makeBullet(renderer, (pc->getX() + 80) - tagC->getJuicerTipX() / 2, pc->getY() + tagC->getJuicerTipY() / 2 + 140, -(tc->getAngle() - 270), unitX * 100, unitY * 80, 200)); // :)
							//float x = (pc->getX() + 80) - tagC->getJuicerTipX() / 2;
							//float y = pc->getY() + tagC->getJuicerTipY() / 2 + 140;
							pc->bullets.push_back(fc->makeBullet(renderer, (pc->getX() + 100) - tagC->getJuicerTipX() / 2, pc->getY() + (tagC->getJuicerTipY() * 0.8) + 140, -(tc->getAngle() - 270), unitX * 100, unitY * 80, 200, bulletTextureSpriteComp->getTexture())); // :)
							float x = (pc->getX() + 100) - tagC->getJuicerTipX() / 2;
							float y = pc->getY() + (tagC->getJuicerTipY() * 0.8) + 140;
							tagC->setJuicerExplosionPos(c2v{ x, y });
						}
					}
					else if (tagC->getGunGot() == "grenade")
					{
						GrenadeComponent * gc = (GrenadeComponent*)entity->getCompByType("GRENADE");
						ownerConC->setThrowGun(true);
						gc->setArmed(true);
						launchGun(pc, tc, colc, ownerConC, tagC);

						if (tagC->getSubTag2() != "AI_Player")
						{
							if (SDL_HapticRumblePlay(ownerConC->getHaptic(), .5, 100) != 0)
							{
								printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
							}
						}

						//notifyAudioObservers(AudioObserver::SFX::GRENADE_EXPLOSION);

					}
				}
			}
		}
	}
}
void PhysicsSystem::bulletUpdate(SDL_Renderer* renderer) {

	// Increase counts for gun animations after they fired.
}


void PhysicsSystem::bulletRender(SDL_Renderer* renderer, Camera* camera) {

	for (Entity * entity : m_entities) {

		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");

		if (tc->getTag() == "Player")
		{
			if (tc->getStartAnimating() == true) {
				PositionComponent * gunPos = (PositionComponent*)entity->getCompByType("POSITION");
				for (Entity * entity : m_entities) {
					TagComponent * gunTag = (TagComponent*)entity->getCompByType("TAG");
					if (tc->getGunGot() == gunTag->getTag())
					{
						gunPos = (PositionComponent*)entity->getCompByType("POSITION");
					}
				}
				animateExplosion(renderer, tc, gunPos);
			}
		}
	}


	for (int i = 0; i < shotgunBullets.size(); i++)
	{
		shotgunBullets[i]->render(renderer, camera);
		// create a new particle system pointer


	}
	for (int i = 0; i < pistolBullets.size(); i++)
	{
		pistolBullets[i]->render(renderer, camera);
		// create a new particle system pointer


	}
	for (int i = 0; i < juicerBullets.size(); i++)
	{
		juicerBullets[i]->render(renderer, camera);
		// create a new particle system pointer


	}


}

void PhysicsSystem::setRenderer(SDL_Renderer * renderer)
{
	m_renderer = renderer;

	p = new ParticleExample();
	p->setRenderer(m_renderer);
	p->setStyle(ParticleExample::SMOKE);

	flash = new ParticleExample();
	flash->setRenderer(m_renderer);
	flash->setStyle(ParticleExample::EXPLOSION);

}

void PhysicsSystem::animateExplosion(SDL_Renderer * renderer, TagComponent * tc, PositionComponent * pc)
{
	m_count++;

	if (tc->getGunGot() == "pistol")
	{
		p->setStartSpin(0);
		p->setStartSpinVar(90);
		p->setEndSpin(90);
		p->setDuration(.1);
		p->setStartSize(30);
		p->setStartSpinVar(90);

		if (flipval == SDL_FLIP_HORIZONTAL)
		{
			p->setPosition(pc->getX() - 15, pc->getY());
		}
		else
		{
			p->setPosition(pc->getX() + 60, pc->getY() + 10);

		}

		p->update();
		p->draw();
	}
	if (tc->getGunGot() == "shotgun")
	{
		flash->setStartSpin(0);
		flash->setStartSpinVar(0);
		flash->setEndSpin(90);
		flash->setDuration(.1);
		flash->setStartSize(5);
		flash->setEndSize(10);
		flash->setStartSpinVar(0);


		if (flipval == SDL_FLIP_HORIZONTAL)
		{
			flash->setPosition(pc->getX() - tc->getShotgunTipX() + 20, pc->getY() + tc->getShotgunTipY());


			//pc->getX() - shotgunTipX + 20, pc->getY() + shotgunTipY + 70
		}
		else
		{
			flash->setPosition(pc->getX() - tc->getShotgunTipX(), pc->getY() + tc->getShotgunTipY());


			//pc->getX() - shotgunTipX + 20, pc->getY() + shotgunTipY + 70
		}

		flash->update();
		flash->draw();


	}
	else if (tc->getGunGot() == "juicer")
	{
		flash->setStartSpin(0);
		flash->setStartSpinVar(0);
		flash->setEndSpin(90);
		flash->setDuration(.1);
		flash->setStartSize(20);
		flash->setEndSize(20);
		flash->setStartSpinVar(0);


		if (flipval == SDL_FLIP_HORIZONTAL)
		{
			flash->setPosition(tc->getJuicerExplosionPos().x, tc->getJuicerExplosionPos().y);
		}
		else
		{
			flash->setPosition(tc->getJuicerExplosionPos().x, tc->getJuicerExplosionPos().y);
		}

		flash->update();
		flash->draw();


	}


	if (m_count > 15 && tc->getGunGot() == "pistol")
	{
		m_count = 0;
		p->resetSystem();
		tc->setStartAnimating(false);
	}

	else if (m_count > 5 && tc->getGunGot() == "shotgun")
	{
		m_count = 0;
		flash->resetSystem();

		tc->setStartAnimating(false);
	}
	else if (m_count > 5 && tc->getGunGot() == "juicer")
	{
		m_count = 0;
		flash->resetSystem();

		tc->setStartAnimating(false);
	}
}

void PhysicsSystem::notifyAudioObservers(AudioObserver::SFX sfx)
{
	if (m_audioObservers.size() > 0)
	{
		for (int i = 0; i < m_audioObservers.size(); i++)
		{
			m_audioObservers.at(i)->onNotify(sfx);
		}
	}
}

void PhysicsSystem::registerAudioObserver(AudioObserver* audioObserver)
{
	m_audioObservers.push_back(audioObserver);
}

void PhysicsSystem::recieveLevel(int width, int height)
{
	m_width = width;
	m_height = height;
}