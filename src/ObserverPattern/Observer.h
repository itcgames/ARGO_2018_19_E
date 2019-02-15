#pragma once
#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer
{
public:
	virtual void update(std::string sfxName) = 0;
private:

};

#endif 