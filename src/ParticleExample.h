#pragma once
#include "ParticleSystem.h"
#include "SDL_image.h"

class ParticleExample : public ParticleSystem
{
public:
    ParticleExample() {}
    virtual ~ParticleExample() {}

    enum PatticleStyle
    {
        NONE,
        FIRE,
        FIRE_WORK,
        SUN,
        GALAXY,
        FLOWER,
        METEOR,
        SPIRAL,
		DIRT,
        EXPLOSION,
        SMOKE,
        SNOW,
        RAIN,
		GRENADE
    };

    PatticleStyle style_ = NONE;
    void setStyle(PatticleStyle style);
    SDL_Texture* getDefaultTexture()
    {
        static SDL_Texture* t = IMG_LoadTexture(_renderer, "assets/fire.png");
        //printf(SDL_GetError());
        return t;
    }
};
