#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include "../cute_c2.h"
#include "ControlSystem.h"
#include "../ObserverPattern/Subject.h"

#include "../ParticleExample.h"


class PhysicsSystem : public Subject
{
public:
	std::vector<Entity *> m_entities;

	
	c2v Friction;
	c2v gunFriction;
	PhysicsSystem();
	//PhysicsSystem(SDL_Surface* screen);
	void addEntity(Entity * e);
	void update();
	void bulletUpdate(SDL_Renderer* renderer);
	void bulletRender(SDL_Renderer* renderer);
	void receive(Entity * e);
	double playerPositionX = 0;
	double playerPositionY = 0;

	double aiPositionX = 0;
	double aiPositionY = 0;

	double gunPositionX = 0;
	double gunPositionY = 0;

	double angle = 0;

	bool gotGun = false;

	double xOffset = 0;
	double yOffset = 0;

	bool throwGun = false;

	bool fired = false;
	int firedCount = 0;

	bool left = false;
	bool right = false;
	SDL_RendererFlip flipval;

	std::vector<Bullet*> pistolBullets;
	std::vector<Bullet*> juicerBullets;
	std::vector<Bullet*> shotgunBullets;
	void animateExplosion(SDL_Renderer * renderer, TagComponent * tc);


	void setGun(TagComponent *tc,ControlComponent *cc,PositionComponent *pc,SpriteComponent *sc);
	void pickUpAgain(TagComponent *tc);
	void setPlayerPosition(PositionComponent *pc);
	void throwGunFun(ControlComponent * cc);
	void playerFlip(PositionComponent *pc, SpriteComponent *sc, ControlComponent *cc, TagComponent *tc);
	void launchGun(PositionComponent *pc, TagComponent *tc, CollisionComponent * cc);
	void setHandOnGun(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc);
	void setPlayerGunGot(std::string gun);
	void setHandOnPistol(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc);
	void setHandOnGrenade(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc);
	void setHandOnShotgun(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc,TagComponent * tc);
	void setHandOnJuicer(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc, TagComponent * tc);
	void setHandNormal(SpriteComponent * sc, PositionComponent *pc);
	void movePlayer(ControlComponent * cc, PositionComponent *pc, TagComponent *tc);
	void setPosition(PositionComponent * pc);
	void flipNone(SpriteComponent * sc);
	void flipHorizontal(SpriteComponent * sc);
	void updateShooting(SDL_Renderer* renderer);
	void makeBullets(SDL_Renderer* renderer, TagComponent *tagC);

	std::string gunGot;

	ParticleExample * p; 
	ParticleExample * flash;


	void setRenderer(SDL_Renderer * renderer);
	SDL_Renderer * m_renderer;
	int m_count = 0;
	bool m_startAnimating = false;

	float shotgunTipX;
	float shotgunTipY;

	// variables for shotgun animation
	int shotgunCount = 0;
	int shotgunRotationCount = 0;
	int shotgunPumpCount = 0;

	int juicerCount = 0;
	int juicerRotationCount = 0;

	float juicerTipX = 0;
	float juicerTipY = 0;

	float m_grenadeColor = 0;

	int index = -1;
};
#endif // !PHYSICSSYSTEM_H
