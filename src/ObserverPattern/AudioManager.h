#pragma once
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "Observer.h"
#include <map>
#include <SDL.h>
#include <SDL_mixer.h>

class AudioManager : public Observer
{
public:
	AudioManager();
	void load();
	void update(std::string sfxName);
private:
	std::map<std::string, Mix_Chunk*> m_sfxMap;
	Mix_Chunk* m_pistolShoot = NULL;
	Mix_Chunk* m_pistolPickup = NULL;
	Mix_Chunk* m_grenadeExplosion = NULL;
	Mix_Chunk* m_minigunShoot = NULL;
	Mix_Chunk* m_shotgunShoot = NULL;
	Mix_Chunk* m_shotgunRechamber = NULL;
	//std::shared_ptr<Mix_Music> m_bgm = NULL;
};

#endif