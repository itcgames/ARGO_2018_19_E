#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include "../cute_c2.h"
#include "ControlSystem.h"
#include "../ObserverPattern/Subject.h"
#include "../ObserverPattern/AudioObserver.h"

#include "../ParticleExample.h"


class PhysicsSystem : Subject
{
public:
	std::vector<Entity *> m_entities;
	void recieveLevel(int width, int height);

	c2v Friction;
	c2v gunFriction;
	PhysicsSystem();
	//PhysicsSystem(SDL_Surface* screen);
	void addEntity(Entity * e);
	void update(SDL_Renderer* renderer);
	void bulletUpdate(SDL_Renderer* renderer);
	void bulletRender(SDL_Renderer* renderer);
	void receive(Entity * e);
	double player1PositionX = 0;
	double player1PositionY = 0;
	double player2PositionX = 0;
	double player2PositionY = 0;

	double aiPositionX = 0;
	double aiPositionY = 0;

	//double gunPositionX = 0;
	//double gunPositionY = 0;

	//double angle = 0;


	//double xOffset = 0;
	//double yOffset = 0;

	bool left = false;
	bool right = false;
	SDL_RendererFlip flipval;

	std::vector<Bullet*> pistolBullets;
	std::vector<Bullet*> juicerBullets;
	std::vector<Bullet*> shotgunBullets;
	void animateExplosion(SDL_Renderer * renderer, TagComponent * tc,PositionComponent * pc);


	void setGun(TagComponent *tc,ControlComponent *cc,PositionComponent *pc,SpriteComponent *sc, PositionComponent *ownerPosC, ControlComponent * ownerConC);
	void pickUpAgain(TagComponent *tc,SpriteComponent * sc, CollisionComponent * colisionc);
	void setPlayer1Position(PositionComponent *pc);
	void setPlayer2Position(PositionComponent *pc);
	void throwGunFun(ControlComponent * cc);
	void playerFlip(PositionComponent *pc, SpriteComponent *sc, ControlComponent *cc, TagComponent *tc);
	void launchGun(PositionComponent *pc, TagComponent *tc, CollisionComponent * cc, ControlComponent * ownerConC, TagComponent * ownerTagC);
	void setHandOnGun(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc,PositionComponent *ownerPosC, ControlComponent * ownerConC, PositionComponent * gunPosition);
	void setPlayerGunGot(std::string gun, TagComponent *tagC, std::string gunID);
	void setHandOnPistol(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc,PositionComponent *ownerPosC, ControlComponent * ownerConC, PositionComponent * gunPosition, TagComponent * gunTagC);
	void setHandOnGrenade(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc, ControlComponent * ownerConC, PositionComponent * gunPosition, TagComponent * gunTagC);
	void setHandOnShotgun(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc,TagComponent * tc, PositionComponent *ownerPosC, ControlComponent * ownerConC, TagComponent * gunTagC);
	void setHandOnJuicer(SpriteComponent * sc, PositionComponent *pc, ControlComponent * cc, TagComponent * tc, PositionComponent *ownerPosC, ControlComponent * ownerConC, TagComponent * gunTagC);
	void setHandNormal(SpriteComponent * sc, PositionComponent *pc, PositionComponent *ownerPosC);
	void movePlayer(ControlComponent * cc, PositionComponent *pc, TagComponent *tc);
	void setPosition(PositionComponent * pc);
	void flipNone(SpriteComponent * sc);
	void flipHorizontal(SpriteComponent * sc);
	void updateShooting(SDL_Renderer* renderer, ControlComponent * ownerConC);
	void makeBullets(SDL_Renderer* renderer, TagComponent *tagC,ControlComponent *ownerConC);
	void checkWeaponCollision(CollisionComponent * colc, TagComponent *tagC);
	void setHands(PositionComponent *handOwnerPos, ControlComponent *handOwnerConC, TagComponent * ownerTagC);

	



	std::vector<AudioObserver*> m_audioObservers;
	void registerAudioObserver(AudioObserver* observer);
	void removeAudioObserver(AudioObserver* observer);
	//Function to notify audio observers to play a sound
	void notifyAudioObservers(AudioObserver::SFX sfx);

	std::string gunGot;

	std::string rectCollision(c2AABB A, c2AABB B);


	ParticleExample * p; 
	ParticleExample * flash;


	void setRenderer(SDL_Renderer * renderer);
	SDL_Renderer * m_renderer;
	int m_count = 0;


	PositionComponent * handOwnerPosC;

	int juicerRotationCount = 0;

	float m_grenadeColor = 0;

	int index = -1;

	int m_width;
	int m_height;
};
#endif // !PHYSICSSYSTEM_H
