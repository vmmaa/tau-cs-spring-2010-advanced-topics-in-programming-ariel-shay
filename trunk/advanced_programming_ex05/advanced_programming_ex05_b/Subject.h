/******************************************************************************
 * Exercise 05 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Subject:
 * Header file for the Observer design pattern - subject side. This specific
 * implementation allows notifications to different observers by their type
 *****************************************************************************/

#pragma once
#include <vector>
#include "Definitions.h"
#include "Observer.h"
using namespace std;

class Observer;

class Subject {
public:
	// CTOR, DTOR
	Subject() {}; 
	~Subject(); 

	// methods
	void Attach(Observer* o); 
	void Detach(Observer* o); 
protected:
	// notify a specific type of observers
	void Notify(SubjectMessages message, ObserverType pi_obsType); 
	// notify all observers
	void NotifyAll(SubjectMessages message); 
private: 
	 vector<Observer*> m_observers; 
};