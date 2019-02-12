#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <SDL.h>
#include "cute_c2.h"
#include "Components/SpriteComponent.h"

class Light
{
public:
	Light();
	Light(c2v position, Uint8 r, Uint8 g, Uint8 b, SDL_Renderer* renderer);
	
	void update();
	void render(SDL_Renderer* renderer);
	SpriteComponent* getSprite();
private:
	SpriteComponent* m_sprite;

};

#endif // !LIGHT_H

