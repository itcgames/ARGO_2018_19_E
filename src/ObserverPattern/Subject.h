#pragma once
#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <vector>

class Subject
{
public:
	virtual void registerObserver(Observer* observer) {};
	virtual void removeObserver(Observer* observer) {};
	virtual void notifyObservers() {};
protected:
	std::vector<Observer*> m_observers;

};


#endif
