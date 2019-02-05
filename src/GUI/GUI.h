#pragma once
#include <SDL.h>
#include <SDL_image.h>

class GUI
{
public:

	virtual void update(double dt) = 0;
	virtual void render(SDL_Renderer * renderer) = 0;
};

