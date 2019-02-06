#pragma once

#include <SDL.h>
#include <SDL_image.h>

class OptionScreen
{
public:
	OptionScreen();
	~OptionScreen();

	void update(double dt);
	void render(SDL_Renderer * renderer);
private:

};

