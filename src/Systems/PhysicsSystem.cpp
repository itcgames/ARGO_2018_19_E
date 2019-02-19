#include "PhysicsSystem.h"
PhysicsSystem::PhysicsSystem()
{
	Friction.x = 0.90;
	Friction.y = 0.98;

	gunFriction.x = 0.97;
	gunFriction.y = 0.96;

}

void PhysicsSystem::addEntity(Entity * e) {
	m_entities.push_back(e);
}

void PhysicsSystem::setGun(TagComponent * tc, ControlComponent * cc, PositionComponent * pc, SpriteComponent * sc, PositionComponent * ownerPosC, ControlComponent * ownerConC) {
	if (tc->getGrabbed() == true)  // Set the gun to be grabbed
	{
		//x = RCos(Angle)
		//y = RSin(Angle)
		double angle = ownerConC->getAngle() + 90;
		double angleTo = ownerConC->getAngle() + 90;
		double angleDifference = angleTo - angle;
		double ease = 0.1;
		if (tc->getSubTag() == "juicer")
		{
			ease = 0.01;
		}
		else if (tc->getSubTag() == "shotgun")
		{
			ease = 0.06;
		}

		angle += angleDifference * ease;

		double radAng = angle * 3.14159265359 / 180;
		double radius = 60;
		if (tc->getSubTag() == "pistol" || tc->getSubTag() == "grenade")
		{
			radius = 60;
		}
		else if (tc->getSubTag() == "shotgun")
		{
			radius = 10;
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
					pc->setX(ownerPosC->getX() - tc->getXOffset() - 40);  // set gun position + offset for player centre - offset for angle
				}
				else {
					pc->setX(ownerPosC->getX() - tc->getXOffset() - 60);  // set gun position + offset for player centre - offset for angle
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
			else if (tc->getSubTag() == "shotgun")
			{
				pc->setY(ownerPosC->getY() - 70 + tc->getYOffset());
			}
			else if (tc->getSubTag() == "juicer")
			{
				pc->setY(ownerPosC->getY() - 60 + tc->getYOffset());

			}
			if (tc->getGrabbed() == true) {
				if (tc->getSubTag() == "juicer")  // Slow down rotation for juicer balance
				{
					double angleTo = ownerConC->getAngle() + 90;
					double angleDifference = angleTo - angle;
					double ease = 0.1;
					if (tc->getSubTag() == "juicer")
					{
						ease = 0.01;
					}

					angle += angleDifference * ease;
					sc->setRotation(-angle + 90); //rotate gun
				}
				else if (tc->getSubTag() == "shotgun")  // Slow down shotgun rotation to make it look nice
				{
					double angleTo = ownerConC->getAngle() + 90;
					double angleDifference = angleTo - angle;
					if (tc->getSubTag() == "shotgun")
					{
						ease = 0.06;
					}

					angle += angleDifference * ease;
					sc->setRotation(-angle + 90); //rotate gun
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
																										 //sc->rotate(ownerPosC->getFiredCount());
					sc->setRotation((ownerConC->getAngle())*-1 - ownerPosC->getFiredCount() / 2); //rotate gun with recoil

				}
				else {
					sc->setRotation((ownerConC->getAngle())*-1 + ownerPosC->getPistolCount()); //rotate gun with recoil
					pc->setX(ownerPosC->getX() - tc->getXOffset() + (ownerPosC->getPistolCount()));
				}
			}
			else if (tc->getSubTag() == "shotgun")
			{
				pc->setY(ownerPosC->getY() - 70 + tc->getYOffset());
				// Count for recoil animation
				if (ownerPosC->getShotgunCount() < 20)
				{
					ownerPosC->setShotgunRotationCount(ownerPosC->getShotgunRotationCount() + 3);
				}
				else if (ownerPosC->getShotgunCount() < 40)
				{
					ownerPosC->setShotgunRotationCount(ownerPosC->getShotgunRotationCount() - 3);
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
					pc->setX(ownerPosC->getX() - tc->getXOffset() - (ownerPosC->getShotgunRotationCount() * 1.5));  // set gun position + offset for player centre - offset for angle
																													//sc->rotate(firedCount);
					sc->setRotation((ownerConC->getAngle())*-1 - ownerPosC->getShotgunRotationCount()); //rotate gun with recoil
				}
				else {
					pc->setX(ownerPosC->getX() - tc->getXOffset() + (ownerPosC->getShotgunRotationCount() * 1.5));
					sc->setRotation((ownerConC->getAngle())*-1 + ownerPosC->getShotgunRotationCount()); //rotate gun with recoil
				}
			}
			else if (tc->getSubTag() == "juicer")
			{
				pc->setY(ownerPosC->getY() - 60 + tc->getYOffset());
				if (sc->m_flipValue == SDL_FLIP_NONE)
				{
					pc->setX(ownerPosC->getX() - tc->getXOffset() - 40 - (ownerPosC->getFiredCount()));  // set gun position + offset for player centre - offset for angle
					sc->setRotation(-angle + 90 - ownerPosC->getFiredCount()); //rotate gun with recoil
				}
				else {
					pc->setX(ownerPosC->getX() - tc->getXOffset() - 60 + (ownerPosC->getFiredCount()));  // set gun position + offset for player centre - offset for angle
					sc->setRotation(-angle + 90 + ownerPosC->getFiredCount()); //rotate gun with recoil
				}
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
void PhysicsSystem::checkWeaponCollision(CollisionComponent * colc, TagComponent * tagc) {
	for (Entity * entity : m_entities) {

		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
		ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");
		CollisionComponent * colisionc = (CollisionComponent*)entity->getCompByType("COLLISION");
		if (tc->getTag() == "Gun")
		{
			std::string val = rectCollision(colc->getCollider(), colisionc->getCollider());
			if (val != "none")
			{
				if (tagc->getGunGot() == "none")
				{
					colisionc->setH(1);
					colisionc->setW(1);
					setPlayerGunGot(tc->getSubTag(), tagc);
					tc->setGrabbed(true);
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
void PhysicsSystem::setPlayerGunGot(std::string gun, TagComponent * tagC)
{
	for (Entity * entity : m_entities) {

		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
		if (tagC->getTag() == "Player")
		{
			tagC->setGunGot(gun);
			tagC->setGotGunBool(true);
			if (gun == "none")
			{
				tagC->setGotGunBool(false);
			}
		}
		if (tc->getTag() == "Hand")
		{
			tc->setGunGot(gun);
			tc->setGotGunBool(true);
			if (gun == "none")
			{
				tc->setGotGunBool(false);
			}
		}
	}
}

// Set the player position variable.
void PhysicsSystem::setPlayer1Position(PositionComponent * pc) {
	player1PositionX = pc->getX();
	player1PositionY = pc->getY();
}
void PhysicsSystem::setPlayer2Position(PositionComponent * pc) {
	player2PositionX = pc->getX();
	player2PositionY = pc->getY();
}
void PhysicsSystem::throwGunFun(ControlComponent * cc) {
	cc->setThrowWeapon(false);
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

void PhysicsSystem::launchGun(PositionComponent * pc, TagComponent * tc, CollisionComponent * cc, ControlComponent * ownerConC, TagComponent * ownerTagC) {
	if (tc->getSubTag() == "pistol")
	{
		pc->setVelX(-tc->getXOffset() / 2.5);
		pc->setVelY(tc->getYOffset() / 2.5);

	}
	else if (tc->getSubTag() == "shotgun")
	{
		pc->setVelX(-tc->getXOffset() * 2);
		pc->setVelY(tc->getYOffset() * 2);
	}
	else if (tc->getSubTag() == "juicer")
	{
		float ySpeed = tc->getYOffset();
		if (tc->getYOffset() > 0)
		{
			ySpeed = 0;
		}
		pc->setVelX(-tc->getXOffset() / 5);
		pc->setVelY(ySpeed / 5);
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
	setPlayerGunGot("none", ownerTagC);  // Fix tc here :)
}

void PhysicsSystem::setHandOnGrenade(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc, ControlComponent * ownerConC, PositionComponent * gunPosition) {
	double handAngle = ownerConC->getAngle() - 90;  // :)

	sc->setRotation((ownerConC->getAngle())*-1); //rotate hand
	pc->setX(gunPosition->getX());
	if (handAngle < 0)
	{
		handAngle = handAngle * -1;
	}
	pc->setY(gunPosition->getY() + (handAngle / 5));
}

void PhysicsSystem::setHandOnPistol(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc, PositionComponent * ownerPosition, ControlComponent * ownerConC, PositionComponent * gunPosition)
{
	double handAngle = ownerConC->getAngle() - 90; // :)

	sc->setRotation((ownerConC->getAngle())*-1); //rotate hand
	pc->setX(gunPosition->getX());
	if (handAngle < 0)
	{
		handAngle = handAngle * -1;
	}
	pc->setY(gunPosition->getY() + (handAngle / 5));
}
void PhysicsSystem::setHandOnShotgun(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc, TagComponent * tc, PositionComponent * ownerPosC, ControlComponent * ownerConC)
{
	// 386
	if (tc->getSubTag2() == "right")
	{
		float radiusHandle = 10;
		float shotgunHandleRadAng = (ownerConC->getAngle() + 90) * 3.14159265359 / 180; // :)
																						//float shotgunTipX = 207.2 * (cos(shotgunRadAng));
																						//float shotgunTipY = 207.2 * (sin(shotgunRadAng));
		float shotgunHandleX = radiusHandle * (cos(shotgunHandleRadAng));
		float shotgunHandleY = radiusHandle * (sin(shotgunHandleRadAng));

		sc->setRotation((ownerConC->getAngle())*-1 - ownerPosC->getShotgunRotationCount()); //rotate hand
		if (sc->m_flipValue == SDL_FLIP_NONE)
		{
			pc->setX(ownerPosC->getX() + shotgunHandleX - (ownerPosC->getShotgunRotationCount() * 1.5));
		}
		else {
			pc->setX(ownerPosC->getX() + shotgunHandleX + (ownerPosC->getShotgunRotationCount() * 1.5));
		}

		//pc->setY(gunPositionY + (handAngle));
		pc->setY(ownerPosC->getY() - shotgunHandleY + 25);
	}
	else if (tc->getSubTag2() == "left")
	{

		float radiusPump = 55 - (ownerPosC->getShotgunPumpCount() * 2.5);  // Change the radius so hand moves along radius line and looks like pumping
		float shotgunPumpRadAng = (ownerConC->getAngle() + 90) * 3.14159265359 / 180;  // :)
																					   //float shotgunTipX = 207.2 * (cos(shotgunRadAng));
																					   //float shotgunTipY = 207.2 * (sin(shotgunRadAng));
		float shotgunPumpX = radiusPump * (cos(shotgunPumpRadAng));
		float shotgunPumpY = radiusPump * (sin(shotgunPumpRadAng));

		sc->setRotation(((ownerConC->getAngle())*-1 - ownerPosC->getShotgunRotationCount()) - 90); //rotate hand
		if (sc->m_flipValue == SDL_FLIP_NONE)
		{
			pc->setX(ownerPosC->getX() - shotgunPumpX - (ownerPosC->getShotgunRotationCount() * 1.5));
		}
		else {
			pc->setX(ownerPosC->getX() - shotgunPumpX + (ownerPosC->getShotgunRotationCount() * 1.5));
		}

		//pc->setY(gunPositionY + (handAngle));
		pc->setY(ownerPosC->getY() + shotgunPumpY + 25);
	}
}
void PhysicsSystem::setHandOnJuicer(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc, TagComponent * tc, PositionComponent * ownerPosC, ControlComponent * ownerConC)
{
	// 386
	if (tc->getSubTag2() == "right")
	{
		float radiusHandle = 40;
		float juicerHandleRadAng = (ownerConC->getAngle() + 90) * 3.14159265359 / 180; // :)
																					   //float shotgunTipX = 207.2 * (cos(shotgunRadAng));
																					   //float shotgunTipY = 207.2 * (sin(shotgunRadAng));
		float juicerHandleX = radiusHandle * (cos(juicerHandleRadAng));
		float juicerHandleY = radiusHandle * (sin(juicerHandleRadAng));

		sc->setRotation((ownerConC->getAngle())*-1 - ownerPosC->getJuicerCount()); //rotate hand
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

		float radiusPump = 55 - (ownerPosC->getShotgunPumpCount());
		float shotgunPumpRadAng = (ownerConC->getAngle() + 90) * 3.14159265359 / 180; // :)
																					  //float shotgunTipX = 207.2 * (cos(shotgunRadAng));
																					  //float shotgunTipY = 207.2 * (sin(shotgunRadAng));
		float shotgunPumpX = radiusPump * (cos(shotgunPumpRadAng));
		float shotgunPumpY = radiusPump * (sin(shotgunPumpRadAng));

		sc->setRotation(((ownerConC->getAngle())*-1 - ownerPosC->getJuicerCount()) - 90); //rotate hand
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
	if (cc->getLeft()) {
		if (pc->getVelX() > -8.0) {
			pc->setVelX(pc->getVelX() - speed);
		}
	}
	if (cc->getRight()) {
		if (pc->getVelX() < 8.0) {
			pc->setVelX(pc->getVelX() + speed);
		}
	}
	if (cc->getJump() && pc->jumpNum < 2) {
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
		ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");
		CollisionComponent * colc = (CollisionComponent*)entity->getCompByType("COLLISION");
		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		AIComponent * ac = (AIComponent*)entity->getCompByType("AI");

		if (tc->getTag() == "Hand" && tc->getSubTag() == ownerTagC->getSubTag()) {
			if (ownerConC->getAngle() + 90 < 90)
			{
				sc->m_flipValue = SDL_FLIP_HORIZONTAL;
			}
			else
			{
				sc->m_flipValue = SDL_FLIP_NONE;
			}
			if (tc->getGotGunBool() == true)
			{
				PositionComponent * gunPos = (PositionComponent*)entity->getCompByType("POSITION");
				for (Entity * entity : m_entities) {
					TagComponent * gunTag = (TagComponent*)entity->getCompByType("TAG");
					if (tc->getGunGot() == gunTag->getTag())  // Finds which gun we have.
					{
						gunPos = (PositionComponent*)entity->getCompByType("POSITION");
					}
				}
				if (tc->getGunGot() == "pistol")
				{
					setHandOnPistol(sc, pc, cc, handOwnerPos, ownerConC, gunPos); // Set hand on gun
				}
				else if (tc->getGunGot() == "shotgun")
				{
					setHandOnShotgun(sc, pc, cc, tc, handOwnerPos, ownerConC); // Set hand on gun
				}
				else if (tc->getGunGot() == "juicer")
				{
					setHandOnJuicer(sc, pc, cc, tc, handOwnerPos, ownerConC); // Set hand on gun
				}
				else if (tc->getGunGot() == "grenade") {
					setHandOnGrenade(sc, pc, cc, ownerConC, gunPos); // Set hand on gun
				}
			}
			else {
				setHandNormal(sc, pc, handOwnerPos); // Set hand to body
			}
			if (cc->getAngle() < 0 && tc->getGotGunBool() == true)
			{
				//flipHorizontal(sc);
			}
			else if (tc->getGotGunBool() == true) {
				//flipNone(sc);
			}
		}
	}
}

void PhysicsSystem::update(SDL_Renderer* renderer) {

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


		// check gun player collide
		if (tc->getTag() == "Player")
		{
			handOwnerPosC = (PositionComponent*)entity->getCompByType("POSITION");
			setHands(handOwnerPosC, ownerConC,ownerTagC);
			checkWeaponCollision(colc,tc);

			if (tc->getGunGot() == "none")
			{
				tc->setGotGunBool(false);
			}
			playerFlip(pc, sc, cc, tc);  // Flip Player sprite when angle requires it.

			if (cc->getThrowWeapon() == true && tc->getGotGunBool() == true)  // Check if x is pressed.
			{
				throwGunFun(cc);
			}
			movePlayer(cc, pc, tc);
			setPosition(pc);  // Set the position after movement
			pc->setVelY(pc->getVelY() + Friction.y);  // Friction
		}
		if (tc->getTag() == "Gun")
		{
			std::string currentGun = tc->getSubTag();
			for (Entity * entity : m_entities) {
				TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
				if (tc->getTag() == "Player")
				{
					if (tc->getGunGot() == currentGun) {
						ownerPosC = (PositionComponent*)entity->getCompByType("POSITION");
						ownerConC = (ControlComponent*)entity->getCompByType("CONTROL");
						ownerTagC = tc;
					}
				}
			}

			updateShooting(renderer, ownerConC);
			setGun(tc, cc, pc, sc, ownerPosC, ownerConC);
			pickUpAgain(tc);
			if (tc->getGrabbed() == true)
			{
				if (ownerConC->getThrowGun() == true)  // Check if a weapon wants to be thrown
				{
					launchGun(pc, tc, colc, ownerConC, ownerTagC);
				}
			}
			if (ownerConC->getAngle() + 90 < 90 && tc->getGrabbed() == true) { // :)

				flipHorizontal(sc);

			}
			else if (tc->getGrabbed() == true) {

				flipNone(sc);

			}
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

		if (tc->getTag() == "AI_TAG")
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
		if (tc->getTag() != "Gun") {
			pc->setVelX(pc->getVelX() * Friction.x);  // Friction
		}
		else {
			pc->setVelX(pc->getVelX() * gunFriction.x);  // Friction
		}


		if (tc->getTag() == "AI_TAG")
		{
			pc->setX(pc->getX() + pc->getVelX());
			pc->setY(pc->getY() + pc->getVelY());
		}

	}
}

void PhysicsSystem::updateShooting(SDL_Renderer* renderer, ControlComponent* ownerConC) {
	for (Entity * entity : m_entities) {

		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");

		// Update all bullets constantly
		if (tc->getSubTag() == "shotgun")
		{
			shotgunBullets = pc->bullets;
		}
		else if (tc->getSubTag() == "pistol")
		{
			pistolBullets = pc->bullets;
		}
		else if (tc->getSubTag() == "juicer")
		{
			juicerBullets = pc->bullets;
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
					else {
						tc->setFiredBool(false);
						pc->setFiredCount(0);
						pc->setPistolCount(0);
					}
				}
				if (tc->getGunGot() == "shotgun")
				{
					if (pc->getFiredCount() < 60)
					{
						pc->setFiredCount(pc->getFiredCount() + 1);
						pc->setShotgunCount(pc->getShotgunCount() + 1);
					}
					else {
						tc->setFiredBool(false);
						pc->setFiredCount(0);
						pc->setShotgunCount(0);
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
	for (Entity * entity : m_entities) {
		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");

		if (tc->getTag() == "Gun" && tagC->getGunGot() == tc->getSubTag())
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

						if (SDL_HapticRumblePlay(ownerConC->getHaptic(), 1, 300) != 0)

						{
							printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
						}

						float shotgunRadAng = (ownerConC->getAngle() + 90) * 3.14159265359 / 180; // :)

						notifyAudioObservers(AudioObserver::SFX::SHOTGUN_SHOOT);

						tagC->setShotgunTipX(100 * (cos(shotgunRadAng)));
						tagC->setShotgunTipY(103.6 * (sin(shotgunRadAng)));

						for (int i = 0; i < 7; i++)
						{

							float random = rand() % 40 - 20;
							float radAng = ((ownerConC->getAngle() + 90) + random) * 3.14159265359 / 180;  // :)
							float radius = 10;

							float shotgunXOffset = radius * (cos(radAng));
							float shotgunYOffset = radius * (sin(radAng));

							c2v vector = { -shotgunXOffset,shotgunYOffset };
							float mag = c2Len(vector);
							float unitX = -shotgunXOffset / mag;
							float unitY = shotgunYOffset / mag;


							if (sc->m_flipValue == SDL_FLIP_NONE)
							{
								pc->bullets.push_back(fc->makeBullet(renderer, pc->getX() - tagC->getShotgunTipX(), pc->getY() + tagC->getShotgunTipY() + 70, -(ownerConC->getAngle() - 180), unitX * 80, unitY * 80, 500)); // :)
							}
							else {

								pc->bullets.push_back(fc->makeBullet(renderer, pc->getX() - tagC->getShotgunTipX() + 20, pc->getY() + tagC->getShotgunTipY() + 70, -(ownerConC->getAngle() - 180), unitX * 80, unitY * 80, 500)); // :)
							}
						}

					}
					else if (tagC->getGunGot() == "pistol")
					{
						//tagC->setFiredBool(false);
						tagC->setStartAnimating(true);

						if (SDL_HapticRumblePlay(ownerConC->getHaptic(), .5, 100) != 0)

						{
							printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
						}

						notifyAudioObservers(AudioObserver::SFX::PISTOL_SHOOT);
						pc->bullets.push_back(fc->makeBullet(renderer, pc->getX(), pc->getY(), -(ownerConC->getAngle() - 180), -tc->getXOffset(), tc->getYOffset(), 1000));  // :)




					}
					else if (tagC->getGunGot() == "juicer")
					{
						//tagC->setFiredBool(false);
						tagC->setStartAnimating(true);

						if (SDL_HapticRumblePlay(ownerConC->getHaptic(), 1, 300) != 0)
						{
							printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
						}
						float juicerRadAng = (ownerConC->getAngle() + 90) * 3.14159265359 / 180;  // :)
																								  //float shotgunTipX = 207.2 * (cos(shotgunRadAng));
																								  //float shotgunTipY = 207.2 * (sin(shotgunRadAng));

						tagC->setJuicerTipX(180 * (cos(juicerRadAng)));
						tagC->setJuicerTipY(200 * (sin(juicerRadAng)));


						float random = rand() % 30 - 15;
						float radAng = ((ownerConC->getAngle() + 90) + random) * 3.14159265359 / 180; // :)
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

							pc->bullets.push_back(fc->makeBullet(renderer, (pc->getX() + 50) - tagC->getJuicerTipX() / 2, pc->getY() + (tagC->getJuicerTipY() * 0.8) + 110, -(ownerConC->getAngle() - 180), unitX * 100, unitY * 80, 200)); // :)
							float x = (pc->getX() + 50) - tagC->getJuicerTipX() / 2;
							float y = pc->getY() + (tagC->getJuicerTipY() * 0.8) + 110;
							tagC->setJuicerExplosionPos(c2v{ x,y });
						}
						else {

							pc->bullets.push_back(fc->makeBullet(renderer, (pc->getX() + 50) - tagC->getJuicerTipX() / 2, pc->getY() + tagC->getJuicerTipY() / 2 + 100, -(ownerConC->getAngle() - 180), unitX * 100, unitY * 80, 200)); // :)
							float x = (pc->getX() + 50) - tagC->getJuicerTipX() / 2;
							float y = pc->getY() + tagC->getJuicerTipY() / 2 + 100;
							tagC->setJuicerExplosionPos(c2v{ x, y });
						}
					}
					else if (tagC->getGunGot() == "grenade")
					{
						GrenadeComponent * gc = (GrenadeComponent*)entity->getCompByType("GRENADE");
						ownerConC->setThrowGun(true);
						gc->setArmed(true);
						launchGun(pc, tc, colc, ownerConC, tagC);

						if (SDL_HapticRumblePlay(ownerConC->getHaptic(), .5, 100) != 0)
						{
							printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
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


void PhysicsSystem::bulletRender(SDL_Renderer* renderer) {


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
		shotgunBullets[i]->render(renderer);
		// create a new particle system pointer


	}
	for (int i = 0; i < pistolBullets.size(); i++)
	{
		pistolBullets[i]->render(renderer);
		// create a new particle system pointer


	}
	for (int i = 0; i < juicerBullets.size(); i++)
	{
		juicerBullets[i]->render(renderer);
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
