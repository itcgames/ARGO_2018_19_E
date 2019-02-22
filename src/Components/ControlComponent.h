#ifndef CONTROLCOMPONENT_H
#define CONTROLCOMPONENT_H

#include "Component.h"
#include "../ParticleExample.h"

class ControlComponent : public Component
{
public:
	ControlComponent() {}

	std::string m_tag = "CONTROL";

	std::string getType() { return m_tag; }

	bool getLeft() { return m_left;  }
	void setLeft(bool left) { m_left = left; }

	bool getRight() { return m_right; }
	void setRight(bool right) { m_right = right; }

	bool getJump() { return m_jump; }
	void setJump(bool jump) { m_jump = jump; }

	float getAngle() { return m_gunAngle; }
	void setAngle(float angle) { m_gunAngle = angle; }

	bool getThrowWeapon() { return m_throwWeapon; }
	void setThrowWeapon(bool tw) { m_throwWeapon = tw; }

	bool getFire() { return m_fire; }
	void setFire(bool fire) { m_fire = fire; }

	bool getAlive() { return m_alive; }
	void setAlive(bool alive) { m_alive = alive; }

	SDL_GameController* gGameController = NULL;

	SDL_Haptic * haptic;
	void setHaptic(SDL_Haptic * value) { haptic = value; }
	SDL_Haptic * getHaptic() { return haptic; }
	bool m_init = false;

	int aIndex = 0;
	int xIndex = 0;


	int m_count = 0;
	c2v lastPos = { 0,0 };

	bool throwGun = false;

	bool getThrowGun() { return throwGun; }
	void setThrowGun(bool value) { throwGun = value; }

	std::string hitFrom = "";
	std::string getHitFrom() { return hitFrom; }
	void setHitFrom(std::string value) { hitFrom = value; }

	std::vector<ParticleExample*> m_particleVector;

	int m_playerNum;

	float getCurrentAngle() { return m_currentAngle; }
	void setCurrentAngle(float angle) { m_currentAngle = angle; }

private:

	bool m_left = false;
	bool m_right = false;

	bool m_throwWeapon = false;
	bool m_jump = false;

	bool m_fire = false;

	float m_gunAngle = 90.0f;

	bool m_alive = true;

	float m_currentAngle = 0.0f;
};
#endif // !CONTROLCOMPONENT_H
