#pragma once
#ifndef AUDIOOBSERVER_H
#define AUDIOOBSERVER

#include "Observer.h"
#include <map>
#include <SDL.h>
#include <SDL_mixer.h>

class AudioObserver : public Observer
{
public:
	enum SFX
	{
		PISTOL_SHOOT,
		PISTOL_PICKUP,
		GRENADE_EXPLOSION,
		MINIGUN_SHOOT,
		SHOTGUN_SHOOT,
		SHOTGUN_RECHAMBER
	};

	AudioObserver();
	void load();
	//Function to be called when a message is received from the subject
	//\param sfx: Enum of sound effects
	void onNotify(SFX sfx);
private:
	Mix_Chunk* m_pistolShoot = NULL;
	Mix_Chunk* m_pistolPickup = NULL;
	Mix_Chunk* m_grenadeExplosion = NULL;
	Mix_Chunk* m_minigunShoot = NULL;
	Mix_Chunk* m_shotgunShoot = NULL;
	Mix_Chunk* m_shotgunRechamber = NULL;
	//std::shared_ptr<Mix_Music> m_bgm = NULL;
};

#endif