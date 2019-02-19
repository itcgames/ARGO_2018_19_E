#ifndef TAGCOMPONENT_H
#define TAGCOMPONENT_H

#include "Component.h"
#include <SDL.h>
#include <string.h>

class TagComponent : public Component
{
public:
	TagComponent(std::string name) : tag(name){}

	std::string getTag() { return tag; }
	std::string getSubTag() { return subTag; }
	std::string getSubTag2() { return subTag2; }

	void setSubTag(std::string subName){subTag = subName; }
	void setSubTag2(std::string subName) { subTag2 = subName; }

	std::string m_tag = "TAG";

	std::string gunGot = "none";
	std::string getGunGot() { return gunGot; }
	void setGunGot(std::string string) { gunGot = string; }

	std::string getType() { return m_tag; }

	bool grabbed = false;
	bool grabable = true;
	bool gotGunBool = false;

	

	double grabableCount = 0;
	bool firedBool = false;

	bool getGrabbed() { return grabbed; }
	bool getGrabable() { return grabable; }
	void setGrabbed(bool value) { grabbed = value; }
	void setGrabable(bool value) { grabable = value; };
	void setGrabableCount(double value) { grabableCount = value; }
	void setGotGunBool(bool value) { gotGunBool = value; }
	bool getGotGunBool() { return gotGunBool; }
	void setFiredBool(bool value) { firedBool = value; }
	bool getFiredBool() { return firedBool; }
	double getGrabableCount() { return grabableCount; }

	double xOffset = 0;
	double yOffset = 0;
	double getXOffset() { return xOffset; }
	double getYOffset() { return yOffset; }
	void setXOffset(double value) { xOffset = value; }
	void setYOffset(double value) { yOffset = value; }

	float shotgunTipX;
	float shotgunTipY;
	float getShotgunTipX() { return shotgunTipX; }
	float getShotgunTipY() { return shotgunTipY; }
	void setShotgunTipX(float value) { shotgunTipX = value; }
	void setShotgunTipY(float value) { shotgunTipY = value; }

	float juicerTipX;
	float juicerTipY;
	float getJuicerTipX() { return juicerTipX; }
	float getJuicerTipY() { return juicerTipY; }
	void setJuicerTipX(float value) { juicerTipX = value; }
	void setJuicerTipY(float value) { juicerTipY = value; }

	bool startAnimating = false;
	void setStartAnimating(bool value) { startAnimating = value; }
	bool getStartAnimating() { return startAnimating; }

	c2v juicerExplosionPos;
	void setJuicerExplosionPos(c2v value) { juicerExplosionPos = value; };
	c2v getJuicerExplosionPos() { return juicerExplosionPos; };

private:
	std::string subTag = "None";
	std::string subTag2 = "None";
	std::string tag;
};
#endif // !TAGCOMPONENT_H
