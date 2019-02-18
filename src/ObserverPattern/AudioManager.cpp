#include "AudioManager.h"

AudioManager::AudioManager()
{

}

void AudioManager::onNotify(SFX sfx) 
{
	switch (sfx)
	{
	case AudioManager::PISTOL_SHOOT:
		Mix_PlayChannel(-1, m_pistolShoot, 0);
		break;
	case AudioManager::PISTOL_PICKUP:
		Mix_PlayChannel(-1, m_pistolPickup, 0);
		break;
	case AudioManager::GRENADE_EXPLOSION:
		Mix_PlayChannel(-1, m_grenadeExplosion, 0);
		break;
	case AudioManager::MINIGUN_SHOOT:
		Mix_PlayChannel(-1, m_minigunShoot, 0);
		break;
	case AudioManager::SHOTGUN_SHOOT:
		Mix_PlayChannel(-1, m_shotgunShoot, 0);
		break;
	case AudioManager::SHOTGUN_RECHAMBER:
		Mix_PlayChannel(-1, m_shotgunRechamber, 0);
		break;
	default:
		break;
	}
}

void AudioManager::load()
{
	m_minigunShoot = Mix_LoadWAV("assets/sfx/minigunShoot.wav");
	m_pistolShoot = Mix_LoadWAV("assets/sfx/pistolShoot.wav");
	m_pistolPickup = Mix_LoadWAV("assets/sfx/pistolPickup.wav");
	m_grenadeExplosion = Mix_LoadWAV("assets/sfx/grenadeExplosion.wav");
	m_shotgunShoot = Mix_LoadWAV("assets/sfx/shotgunShoot.wav");
	m_shotgunRechamber = Mix_LoadWAV("assets/sfx/ShotgunRechamber.wav");
}