#ifndef DISPLAYCOMPONENT_H
#define DISPLAYCOMPONENT_H

#include "Component.h"
#include <SDL.h>
#include <iostream>

class DisplayComponent: public Component
{
public:
	DisplayComponent(SDL_Rect & screenRect) : m_rect(&screenRect){}


	SDL_Rect * getScreenRect() { return m_rect; }
	std::string m_tag = "DISPLAY";

	std::string getType() { return m_tag; }
private:
	SDL_Rect * m_rect;

};

#endif