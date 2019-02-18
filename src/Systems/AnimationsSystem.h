#ifndef ANIMATIONSSYSTEM_H
#define ANIMATIONSSYSTEM_H

#include <iostream>
#include <vector>
#include "../Entity.h"
#include "../cute_c2.h"
#include <algorithm>



class AnimationsSystem
{
	std::vector<Entity *> m_entities;


public:
	AnimationsSystem();
	void addEntity(Entity * e);
	void update();
	void render();
	double distance(c2v  vecOne, c2v vecTwo);
	void setRenderer(SDL_Renderer * renderer);
	void animateExplosion(std::vector<ParticleExample*> vec);
	std::vector<ParticleExample*> getVector();
	void setVector(std::vector<ParticleExample*> vec);
	void call();
private:
	SDL_Renderer * m_renderer;
	c2v lastPos = { 0,0 };
	std::vector<ParticleExample*> m_vector;
	int m_count = 0;


	int erased = 0;
};



#endif // !ANIMATIONSSYSTEM_H
