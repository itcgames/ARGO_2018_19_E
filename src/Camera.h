#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "cute_c2.h"
#include "Entity.h"
#include <SDL.h>
#include <iostream>
#include <vector>

#define LEVEL_WIDTH 1750
#define LEVEL_HEIGHT 1400
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700

class Camera
{
public:
	Camera();
	~Camera() {}
	void update(SDL_Rect* focus);
	SDL_Rect* focus(std::vector<c2v> playerPositions);
	SDL_Rect* getCamera() { return this->camera; }

	SDL_Rect* camera;

	SDL_Rect* lookAt;
private:
	
	

	int min_x;
	int min_y;
	int max_x;
	int max_y;

};

#endif 
