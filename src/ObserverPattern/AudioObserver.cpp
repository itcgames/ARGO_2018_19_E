#include "AudioObserver.h"

AudioObserver::AudioObserver()
{

}

void AudioObserver::StartBGM(int bgmSong)
{
	switch (bgmSong)
	{
	case 0:
		Mix_PlayMusic(m_bgm1, -1);
		break;
	case 1:
		Mix_PlayMusic(m_bgm2, -1);
		break;
	case 2:
		Mix_PlayMusic(m_bgm3, -1);
		break;
	case 3:
		Mix_PlayMusic(m_bgm4, -1);
		break;
	}
}

void AudioObserver::onNotify(SFX sfx)
{
	switch (sfx)
	{
	case AudioObserver::PISTOL_SHOOT:
		Mix_PlayChannel(-1, m_pistolShoot, 0);
		break;
	case AudioObserver::PISTOL_PICKUP:
		Mix_PlayChannel(-1, m_pistolPickup, 0);
		break;
	case AudioObserver::GRENADE_EXPLOSION:
		Mix_PlayChannel(-1, m_grenadeExplosion, 0);
		break;
	case AudioObserver::MINIGUN_SHOOT:
		Mix_PlayChannel(-1, m_minigunShoot, 0);
		break;
	case AudioObserver::SHOTGUN_SHOOT:
		Mix_PlayChannel(-1, m_shotgunShoot, 0);
		break;
	case AudioObserver::SWORD_SLASH:
		Mix_PlayChannel(-1, m_swordSlash, 0);
		break;
	case AudioObserver::WEAPON_THROW:
		Mix_PlayChannel(-1, m_weaponThrow, 0);
	default:
		break;
	}
}

void AudioObserver::load()
{
	m_minigunShoot = Mix_LoadWAV("assets/sfx/minigunShoot.wav");
	m_pistolShoot = Mix_LoadWAV("assets/sfx/pistolShoot.wav");
	m_pistolPickup = Mix_LoadWAV("assets/sfx/pistolPickup.wav");
	m_grenadeExplosion = Mix_LoadWAV("assets/sfx/grenadeExplosion.wav");
	m_shotgunShoot = Mix_LoadWAV("assets/sfx/shotgunShoot.wav");
	m_swordSlash = Mix_LoadWAV("assets/sfx/swordSlash.wav");
	m_weaponThrow = Mix_LoadWAV("assets/sfx/weaponThrow.wav");

	Mix_VolumeChunk(m_swordSlash, 150);
	
	m_bgm1 = Mix_LoadMUS("assets/sfx/bgm1.wav");
	m_bgm2 = Mix_LoadMUS("assets/sfx/happy.wav");
	Mix_VolumeMusic(25);
}