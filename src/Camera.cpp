#include "Camera.h"

Camera::Camera() 
{
	camera = new SDL_Rect();
	lookAt = new SDL_Rect();
	this->camera->x = 0;
	this->camera->y = 0;
	this->camera->w = SCREEN_WIDTH;
	this->camera->h = SCREEN_HEIGHT;
}

void Camera:: update(SDL_Rect* focus) 
{

	//Set the Camera Bounding Box (this box is bound of GameObjects)
	this->camera->x = (focus->x) - SCREEN_WIDTH / 2;
	this->camera->y = (focus->y) - SCREEN_HEIGHT / 2;

	if (this->camera->x < -300) {
		this->camera->x = -300;
	}
	if (this->camera->y < -300) {
		this->camera->y = -300;
	}
	if (this->camera->x > this->camera->w) {
		this->camera->x = LEVEL_WIDTH - this->camera->w;
	}
	if (this->camera->y > this->camera->h) {
		this->camera->y = LEVEL_HEIGHT - this->camera->h;
	}
}

// The SDL_Rect enclosing the four players
SDL_Rect* Camera::focus(std::vector<c2v> playerPositions) 
{
	min_x = playerPositions.at(0).x;
	min_y = playerPositions.at(0).y;
	max_x = playerPositions.at(0).x;
	max_y = playerPositions.at(0).y;

	for (int i = 1; i < playerPositions.size(); i++)
	{
		(min_x > playerPositions.at(i).x) ? min_x = playerPositions.at(i).x : -150;
		(max_x < playerPositions.at(i).x) ? max_x = playerPositions.at(i).x : SCREEN_WIDTH;
		(min_y > playerPositions.at(i).y) ? min_y = playerPositions.at(i).y : -150;
		(max_y < playerPositions.at(i).y) ? max_y = playerPositions.at(i).y : SCREEN_HEIGHT;
	}

	lookAt->x = min_x;
	lookAt->y = min_y;
	lookAt->w = max_x - min_x;
	lookAt->h = max_y - min_y;

	return lookAt;
}