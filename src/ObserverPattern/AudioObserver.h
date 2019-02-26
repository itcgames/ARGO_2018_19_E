#pragma once
#ifndef AUDIOOBSERVER_H
#define AUDIOOBSERVER

#include "Observer.h"
#include <map>
#include <SDL.h>
#include <SDL_mixer.h>


//Observer for playing audio
//To add a sound effect, add a name for it to the enum, create a Mix_Chunk pointer for it and add it to the switch statement in the notify method.
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
		SWORD_SLASH,
		WEAPON_THROW
	};

	AudioObserver();
	//Load all resources
	void load();
	//Function to be called when a message is received from the subject
	//\param sfx: Enum of sound effects
	void onNotify(SFX sfx);
	void StartBGM(int bgmSong);
private:
	Mix_Chunk* m_pistolShoot = NULL;
	Mix_Chunk* m_pistolPickup = NULL;
	Mix_Chunk* m_grenadeExplosion = NULL;
	Mix_Chunk* m_minigunShoot = NULL;
	Mix_Chunk* m_shotgunShoot = NULL;
	Mix_Chunk* m_swordSlash = NULL;
	Mix_Chunk* m_weaponThrow = NULL;
	Mix_Music* m_bgm1 = NULL;
	Mix_Music* m_bgm2 = NULL;
	Mix_Music* m_bgm3 = NULL;
	Mix_Music* m_bgm4 = NULL;
};

#endif