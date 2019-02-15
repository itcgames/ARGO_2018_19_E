#include "AudioManager.h"

AudioManager::AudioManager()
{

}

void AudioManager::update(std::string sfxName)
{
	if (sfxName == "shotgunrechamber")
	{
		Mix_PlayChannel(-1, m_shotgunRechamber, 0);
		
	}

	else if (sfxName == "grenadeexplosion")
	{
		Mix_PlayChannel(-1, m_grenadeExplosion, 0);
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

	m_sfxMap.insert(std::pair<std::string, Mix_Chunk*>("minigunshoot", m_minigunShoot));
	m_sfxMap.insert(std::pair<std::string, Mix_Chunk*>("pistolshoot", m_pistolShoot));
	m_sfxMap.insert(std::pair<std::string, Mix_Chunk*>("pistolpickup", m_pistolPickup));
	m_sfxMap.insert(std::pair<std::string, Mix_Chunk*>("grenadeexplosion", m_grenadeExplosion));
	m_sfxMap.insert(std::pair<std::string, Mix_Chunk*>("shotgunshoot", m_shotgunShoot));
	m_sfxMap.insert(std::pair<std::string, Mix_Chunk*>("shotgunrechamber", m_shotgunRechamber));
}