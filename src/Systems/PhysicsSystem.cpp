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

void PhysicsSystem::setGun(TagComponent * tc,ControlComponent * cc,PositionComponent * pc,SpriteComponent * sc) {
	if (tc->getGrabbed() == true)  // Set the gun to be grabbed
	{
		//x = RCos(Angle)
		//y = RSin(Angle)

		double angleTo = cc->getAngle() + 90;
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
		xOffset = radius * (cos(radAng));
		yOffset = radius * (sin(radAng));

		if (firedCount == 0)
		{
			if (tc->getSubTag() == "juicer")
			{
				if (sc->m_flipValue == SDL_FLIP_NONE)
				{
					pc->setX(playerPositionX - xOffset - 40);  // set gun position + offset for player centre - offset for angle
				}
				else {
					pc->setX(playerPositionX - xOffset - 60);  // set gun position + offset for player centre - offset for angle
				}
			}
			else {
				pc->setX(playerPositionX - xOffset);
			}
			if (tc->getSubTag() == "pistol")
			{
				pc->setX(playerPositionX - xOffset);  // set gun position + offset for player centre - offset for angle
			}
			if (tc->getSubTag() == "pistol" || tc->getSubTag() == "grenade")
			{
				pc->setY(playerPositionY + yOffset);
			}
			else if (tc->getSubTag() == "shotgun")
			{
				pc->setY(playerPositionY - 60 + yOffset);
			}
			else if (tc->getSubTag() == "juicer")
			{
				pc->setY(playerPositionY - 60 + yOffset);
			}
			if (tc->getGrabbed() == true) {
				if(tc->getSubTag() == "juicer")  // Slow down rotation for juicer balance
				{
					double angleTo = cc->getAngle() + 90;
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
					double angleTo = cc->getAngle() + 90;
					double angleDifference = angleTo - angle;
					if (tc->getSubTag() == "shotgun")
					{
						ease = 0.06;
					}

					angle += angleDifference * ease;
					sc->setRotation(-angle + 90); //rotate gun
				}
				else {
					sc->setRotation((cc->getAngle())*-1); //rotate gun
				}
			}
		}
		// Animations for gun recoil
		else
		{
			if (tc->getSubTag() == "pistol" || tc->getSubTag() == "grenade")
			{
				pc->setY(playerPositionY + yOffset);
				if (sc->m_flipValue == SDL_FLIP_NONE)
				{
					pc->setX(playerPositionX - xOffset - (firedCount));  // set gun position + offset for player centre - offset for angle
					sc->rotate(firedCount);
					sc->setRotation((cc->getAngle())*-1 - firedCount); //rotate gun with recoil
				}
				else {
					sc->setRotation((cc->getAngle())*-1 + firedCount); //rotate gun with recoil
					pc->setX(playerPositionX - xOffset + (firedCount));
				}
			}
			else if (tc->getSubTag() == "shotgun")
			{
				pc->setY(playerPositionY -60 + yOffset);
				// Count for recoil animation
				if (shotgunCount < 6)
				{
					shotgunRotationCount = shotgunRotationCount + 3;
				}
				else if (shotgunCount < 20)
				{
					shotgunRotationCount = shotgunRotationCount - 3;
					if (shotgunRotationCount < 0)
					{
						shotgunRotationCount = 0;
					}
				}
				// Count for pump animation;
				if (shotgunCount < 30)
				{
					shotgunPumpCount = shotgunPumpCount + 1;
				}
				else {
					shotgunPumpCount = shotgunPumpCount - 1;
					if (shotgunPumpCount < 0)
					{
						shotgunPumpCount = 0;
					}
				}
		
				if (sc->m_flipValue == SDL_FLIP_NONE)
				{
					pc->setX(playerPositionX - xOffset - (shotgunRotationCount * 1.5));  // set gun position + offset for player centre - offset for angle
					//sc->rotate(firedCount);
					sc->setRotation((cc->getAngle())*-1 - shotgunRotationCount); //rotate gun with recoil
				}
				else {
					pc->setX(playerPositionX - xOffset + (shotgunRotationCount * 1.5));
					sc->setRotation((cc->getAngle())*-1 + shotgunRotationCount); //rotate gun with recoil
				}
			}
			else if (tc->getSubTag() == "juicer")
			{
				pc->setY(playerPositionY - 60 + yOffset);
				if (sc->m_flipValue == SDL_FLIP_NONE)
				{
					pc->setX(playerPositionX - xOffset - 40 - (firedCount));  // set gun position + offset for player centre - offset for angle
					sc->setRotation(-angle + 90 - firedCount); //rotate gun with recoil
				}
				else {
					pc->setX(playerPositionX - xOffset - 60 + (firedCount));  // set gun position + offset for player centre - offset for angle
					sc->setRotation(-angle + 90 + firedCount); //rotate gun with recoil
				}
			}
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
		//gotGun = true;
		setPlayerGunGot(tc->getSubTag());
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
void PhysicsSystem::setPlayerGunGot(std::string gun)
{
	for (Entity * entity : m_entities) {

		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
		if (tc->getTag() == "Player")
		{
			tc->setGunGot(gun);
			tc->setGotGunBool(true);
			if (gun == "none")
			{
				gotGun = false;
				tc->setGotGunBool(false);
			}
		}
		if (tc->getTag() == "Hand")
		{
			tc->setGunGot(gun);
			tc->setGotGunBool(true);
			if (gun == "none")
			{
				gotGun = false;
				tc->setGotGunBool(false);
			}
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
		if (angle < 90)
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

void PhysicsSystem::launchGun(PositionComponent * pc, TagComponent * tc,CollisionComponent * cc) {
	if (tc->getSubTag() == "pistol")
	{
		pc->setVelX(-xOffset / 2.5);
		pc->setVelY(yOffset / 2.5);
		
	}
	else if (tc->getSubTag() == "shotgun")
	{
		pc->setVelX(-xOffset * 2);
		pc->setVelY(yOffset * 2);
	}
	else if (tc->getSubTag() == "juicer")
	{
		float ySpeed = yOffset;
		if (yOffset > 0)
		{
			ySpeed = 0;
		}
		pc->setVelX(-xOffset / 5);
		pc->setVelY(ySpeed / 5);
	}
	else if (tc->getSubTag() == "grenade") {
		pc->setVelX(-xOffset / 2);
		pc->setVelY(yOffset / 2);
	}
	tc->setGrabbed(false);
	tc->setGrabable(false);
	// Start count to make gun grabable again.
	throwGun = false;
	// SET PLAYER GUN FUNCTION
	setPlayerGunGot("none");
}

void PhysicsSystem::setHandOnGrenade(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc) {
	double handAngle = angle - 90;

	sc->setRotation((cc->getAngle())*-1); //rotate hand
	pc->setX(gunPositionX);
	if (handAngle < 0)
	{
		handAngle = handAngle * -1;
	}
	pc->setY(gunPositionY + (handAngle / 5));
}

void PhysicsSystem::setHandOnPistol(SpriteComponent * sc,PositionComponent *pc,ControlComponent * cc)
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
void PhysicsSystem::setHandOnShotgun(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc,TagComponent * tc)
{
	// 386
	if (tc->getSubTag() == "right")
	{
		float radiusHandle = 10;
		float shotgunHandleRadAng = angle * 3.14159265359 / 180;
		//float shotgunTipX = 207.2 * (cos(shotgunRadAng));
		//float shotgunTipY = 207.2 * (sin(shotgunRadAng));
		float shotgunHandleX = radiusHandle * (cos(shotgunHandleRadAng));
		float shotgunHandleY = radiusHandle * (sin(shotgunHandleRadAng));

		sc->setRotation((cc->getAngle())*-1 - shotgunRotationCount); //rotate hand
		if (sc->m_flipValue == SDL_FLIP_NONE)
		{
			pc->setX(playerPositionX + shotgunHandleX - (shotgunRotationCount * 1.5));
		}
		else {
			pc->setX(playerPositionX + shotgunHandleX + (shotgunRotationCount * 1.5));
		}

		//pc->setY(gunPositionY + (handAngle));
		pc->setY(playerPositionY - shotgunHandleY + 25);
	}
	else if (tc->getSubTag() == "left")
	{

		float radiusPump = 55 - (shotgunPumpCount / 2);  // Change the radius so hand moves along radius line and looks like pumping
		float shotgunPumpRadAng = angle * 3.14159265359 / 180;
		//float shotgunTipX = 207.2 * (cos(shotgunRadAng));
		//float shotgunTipY = 207.2 * (sin(shotgunRadAng));
		float shotgunPumpX = radiusPump * (cos(shotgunPumpRadAng));
		float shotgunPumpY = radiusPump * (sin(shotgunPumpRadAng));

		sc->setRotation(((cc->getAngle())*-1 - shotgunRotationCount) - 90); //rotate hand
		if (sc->m_flipValue == SDL_FLIP_NONE)
		{
			pc->setX(playerPositionX - shotgunPumpX - (shotgunRotationCount * 1.5));
		}
		else {
			pc->setX(playerPositionX - shotgunPumpX + (shotgunRotationCount * 1.5));
		}

		//pc->setY(gunPositionY + (handAngle));
		pc->setY(playerPositionY + shotgunPumpY + 25);
	}
}
void PhysicsSystem::setHandOnJuicer(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc, TagComponent * tc)
{
	// 386
	if (tc->getSubTag() == "right")
	{
		float radiusHandle = 40;
		float juicerHandleRadAng = angle * 3.14159265359 / 180;
		//float shotgunTipX = 207.2 * (cos(shotgunRadAng));
		//float shotgunTipY = 207.2 * (sin(shotgunRadAng));
		float juicerHandleX = radiusHandle * (cos(juicerHandleRadAng));
		float juicerHandleY = radiusHandle * (sin(juicerHandleRadAng));

		sc->setRotation((cc->getAngle())*-1 - juicerCount); //rotate hand
		if (sc->m_flipValue == SDL_FLIP_NONE)
		{
			pc->setX(playerPositionX + juicerHandleX - (juicerCount * 1.5));
		}
		else {
			pc->setX(playerPositionX + juicerHandleX + (juicerCount * 1.5));
		}

		//pc->setY(gunPositionY + (handAngle));
		pc->setY(playerPositionY - juicerHandleY + 25);
	}
	else if (tc->getSubTag() == "left")
	{

		float radiusPump = 55 - (shotgunPumpCount);
		float shotgunPumpRadAng = angle * 3.14159265359 / 180;
		//float shotgunTipX = 207.2 * (cos(shotgunRadAng));
		//float shotgunTipY = 207.2 * (sin(shotgunRadAng));
		float shotgunPumpX = radiusPump * (cos(shotgunPumpRadAng));
		float shotgunPumpY = radiusPump * (sin(shotgunPumpRadAng));

		sc->setRotation(((cc->getAngle())*-1 - juicerCount) - 90); //rotate hand
		if (sc->m_flipValue == SDL_FLIP_NONE)
		{
			pc->setX(playerPositionX - shotgunPumpX - (juicerCount * 1.5));
		}
		else {
			pc->setX(playerPositionX - shotgunPumpX + (juicerCount * 1.5));
		}

		//pc->setY(gunPositionY + (handAngle));
		pc->setY(playerPositionY + shotgunPumpY + 25);
	}
}
void PhysicsSystem::setHandNormal(SpriteComponent * sc, PositionComponent *pc)
{
	pc->setX(playerPositionX);
	pc->setY(playerPositionY + 6);
	sc->setRotation(0);
}
void PhysicsSystem::movePlayer(ControlComponent * cc,PositionComponent *pc, TagComponent *tc) {
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
	//std::cout << "JUMP =" << cc->getJump() << std::endl;
	if (cc->getJump() && pc->jumpNum < 2) {
		//std::cout << "Called" << std::endl;
		pc->setVelY(- jumpSpeed);
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

void PhysicsSystem::update() {

	for (Entity * entity : m_entities) {

		TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
		ControlComponent * cc = (ControlComponent*)entity->getCompByType("CONTROL");
		CollisionComponent * colc = (CollisionComponent*)entity->getCompByType("COLLISION");
		PositionComponent * pc = (PositionComponent*)entity->getCompByType("POSITION");
		SpriteComponent * sc = (SpriteComponent*)entity->getCompByType("SPRITE");
		AIComponent * ac = (AIComponent*)entity->getCompByType("AI");


		// check gun player collide
		if (tc->getTag() == "Player")
		{
			gunGot = tc->getGunGot();
			if (tc->getGunGot() == "none")
			{
				tc->setGotGunBool(false);
			}
			playerFlip(pc,sc,cc,tc);  // Flip Player sprite when angle requires it.
			setPlayerPosition(pc);  // Set player position variable for others.
			if (cc->getThrowWeapon() == true && tc->getGotGunBool() == true)  // Check if x is pressed.
			{
				throwGunFun(cc);
			}
			movePlayer(cc,pc,tc);
			setPosition(pc);  // Set the position after movement
			pc->setVelY(pc->getVelY() + Friction.y);  // Friction
		}
		if (tc->getTag() == "Gun")
		{

			

			setGun(tc,cc,pc,sc);
			pickUpAgain(tc);
			if (tc->getGrabbed() == true)
			{
				if (throwGun == true)  // Check if a weapon wants to be thrown
				{
					launchGun(pc, tc,colc);
				}
			}
			if (angle < 90 && tc->getGrabbed() == true) {

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
			if (tc->getGrabbed() == true)
			{
				gunGot = tc->getSubTag();
				// SET PLAYER GUN FUNCTION
				setPlayerGunGot(gunGot);
			}
			if (tc->getSubTag() == "grenade") {
				GrenadeComponent * gc = (GrenadeComponent*)entity->getCompByType("GRENADE");
				
				if (gc->getArmed()) {
					m_grenadeColor += 0.05f;
					//std::cout << m_grenadeColor << std::endl;
					//sc->setColor(255, 255, 100);
					//sc->setAlpha(100);
					gc->setTTL(gc->getTTL() - 1);
					if (gc->getTTL() < 0) {
						gc->setExplode(true);
					}
				}
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
			if (tc->getGotGunBool() == true)
			{
				if (tc->getGunGot() == "pistol")
				{

					setHandOnPistol(sc, pc, cc); // Set hand on gun
				}
				else if (tc->getGunGot() == "shotgun")
				{
					setHandOnShotgun(sc, pc, cc,tc); // Set hand on gun
				}
				else if (tc->getGunGot() == "juicer")
				{
					setHandOnJuicer(sc, pc, cc, tc); // Set hand on gun
				}
				else if (tc->getGunGot() == "grenade") {
					setHandOnGrenade(sc, pc, cc); // Set hand on gun
				}
			}
			else {
				setHandNormal(sc, pc); // Set hand to body
			}
			if (cc->getAngle() < 0 && tc->getGotGunBool() == true)
			{
				flipHorizontal(sc);
			}
			else if(tc->getGotGunBool() == true){
				flipNone(sc);
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

void PhysicsSystem::updateShooting(SDL_Renderer* renderer) {
	for (Entity * entity : m_entities) {
		//std::cout << "Count = " << firedCount << std::endl;

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
			if (cc->getFire())
			{
				if (firedCount == 0)
				{
					tc->setFiredBool(true);
					makeBullets(renderer, tc); // MAKE BULLETS and pass the tag
				}
			}
			if (tc->getFiredBool() == true)
			{
				if (tc->getGunGot() == "pistol")
				{
					if (firedCount < 10)
					{
						firedCount = firedCount + 1;
					}
					else {
						tc->setFiredBool(false);
						firedCount = 0;
					}
				}
				if (tc->getGunGot() == "shotgun")
				{
					if (firedCount < 60)
					{
						firedCount = firedCount + 1;
						shotgunCount = shotgunCount + 1;
					}
					else {
						tc->setFiredBool(false);
						firedCount = 0;
						shotgunCount = 0;
					}
				}
				if (tc->getGunGot() == "juicer")
				{
					if (firedCount < 5)
					{
						firedCount = firedCount + 1;
						juicerCount = juicerCount + 1;
					}
					else {
						tc->setFiredBool(false);
						firedCount = 0;
						shotgunCount = 0;
						juicerCount = 0;
					}
				}
			}
		}
	}
}
void PhysicsSystem::makeBullets(SDL_Renderer* renderer,TagComponent* tagC) {
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
							m_startAnimating = true;

							if (SDL_HapticRumblePlay(haptic, 1, 300) != 0)

							{
								printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
							}

							float shotgunRadAng = angle * 3.14159265359 / 180;
							//float shotgunTipX = 207.2 * (cos(shotgunRadAng));
							//float shotgunTipY = 207.2 * (sin(shotgunRadAng));
							shotgunTipX = 103.6 * (cos(shotgunRadAng));
							shotgunTipY = 103.6 * (sin(shotgunRadAng));
							for (int i = 0; i < 7; i++)
							{
								float random = rand() % 40 - 20;
								float radAng = (angle + random) * 3.14159265359 / 180;
								float radius = 10;
						
								float shotgunXOffset = radius * (cos(radAng));
								float shotgunYOffset = radius * (sin(radAng));

								c2v vector = { -shotgunXOffset,shotgunYOffset };
								float mag = c2Len(vector);
								float unitX = -shotgunXOffset / mag;
								float unitY = shotgunYOffset / mag;
								if (sc->m_flipValue == SDL_FLIP_NONE)
								{
									pc->bullets.push_back(fc->makeBullet(renderer, pc->getX() - shotgunTipX, pc->getY() + shotgunTipY + 70, -(angle - 90), unitX * 80, unitY * 80, 50));
								}
								else {
									pc->bullets.push_back(fc->makeBullet(renderer, pc->getX() - shotgunTipX + 20, pc->getY() + shotgunTipY + 70, -(angle - 90), unitX * 80, unitY * 80, 50));
								}
							}

						}
						else if (tagC->getGunGot() == "pistol")
						{
							//tagC->setFiredBool(false);
							m_startAnimating = true;

							if (SDL_HapticRumblePlay(haptic, .5, 100) != 0)

							{
								printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
							}
							pc->bullets.push_back(fc->makeBullet(renderer, pc->getX(), pc->getY(), -(angle - 90), -xOffset, yOffset, 1000));


						}
						else if (tagC->getGunGot() == "juicer")
						{
							//tagC->setFiredBool(false);
							m_startAnimating = true;

							if (SDL_HapticRumblePlay(haptic, 1, 300) != 0)
							{
								printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
							}
							float juicerRadAng = angle * 3.14159265359 / 180;
							//float shotgunTipX = 207.2 * (cos(shotgunRadAng));
							//float shotgunTipY = 207.2 * (sin(shotgunRadAng));

							juicerTipX = 100 * (cos(juicerRadAng));
							juicerTipY = 100 * (sin(juicerRadAng));


							float random = rand() % 30 - 15;
							float radAng = (angle + random) * 3.14159265359 / 180;
							float radius = 60;


							float juicerXOffset = radius * (cos(radAng));
							float juicerYOffset = radius * (sin(radAng));

							c2v vector = { -juicerXOffset,juicerYOffset };
							float mag = c2Len(vector);
							float unitX = -juicerXOffset / mag;
							float unitY = juicerYOffset / mag;
							if (sc->m_flipValue == SDL_FLIP_NONE)
							{
								pc->bullets.push_back(fc->makeBullet(renderer, pc->getX() - juicerTipX + 60, pc->getY() + juicerTipY + 110, -(angle - 90), unitX * 100, unitY * 80, 200));
							}
							else {
								pc->bullets.push_back(fc->makeBullet(renderer, pc->getX() - juicerTipX + 60, pc->getY() + juicerTipY + 100, -(angle - 90), unitX * 100, unitY * 80, 200));
							}
						}
						else if (tagC->getGunGot() == "grenade")
						{
							GrenadeComponent * gc = (GrenadeComponent*)entity->getCompByType("GRENADE");
							throwGun = true;
							gc->setArmed(true);
							launchGun(pc, tc, colc);

							if (SDL_HapticRumblePlay(haptic, .5, 100) != 0)
							{
								printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
							}
						}
					}
				}
			}
	}
}
void PhysicsSystem::bulletUpdate(SDL_Renderer* renderer) {

	// Increase counts for gun animations after they fired.
	updateShooting(renderer);
}


void PhysicsSystem::bulletRender(SDL_Renderer* renderer) {

	if (m_startAnimating) {
		for (Entity * entity : m_entities) {

			TagComponent * tc = (TagComponent*)entity->getCompByType("TAG");
			
			if (tc->getTag() == "Player")
			{
				animateExplosion(renderer,tc);
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

void PhysicsSystem::animateExplosion(SDL_Renderer * renderer,TagComponent * tc)
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
			p->setPosition(gunPositionX - 15, gunPositionY);
		}
		else
		{
			p->setPosition(gunPositionX + 60, gunPositionY + 10);
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
			flash->setPosition(gunPositionX - shotgunTipX +20, gunPositionY + shotgunTipY + 70);
		}
		else
		{
			flash->setPosition(gunPositionX - shotgunTipX, gunPositionY + shotgunTipY + 70);
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
			flash->setPosition(gunPositionX - juicerTipX + 60, gunPositionY + juicerTipY + 110);
		}
		else
		{
			flash->setPosition(gunPositionX - juicerTipX + 60, gunPositionY + juicerTipY + 110);
		}

		flash->update();
		flash->draw();


	}
	
	
	if (m_count > 15 && tc->getGunGot() == "pistol")
	{
		m_count = 0;
		p->resetSystem();
		m_startAnimating = false;
	}

	else if (m_count > 5 && tc->getGunGot() == "shotgun")
	{
		m_count = 0;
		flash->resetSystem();

		m_startAnimating = false;
	}
	else if (m_count > 5 && tc->getGunGot() == "juicer")
	{
		m_count = 0;
		flash->resetSystem();
		m_startAnimating = false;
	}
}

