#ifndef SUBJECT_H
#define SUBJECT_H

//=========================================================================
// subject.h 
// 
// Implements a subject as part of an Observer pattern
// 
//	Rotem & Rotem addition:
//	1. The Notify method gets a description of the update 
//	(to be passed to the observer) 
//=========================================================================

#include <vector>
#include <string>
using namespace std;

//========================================================= 

#include "observer.h"

class Subject { 
public: 
	 Subject() {}; 
	 ~Subject() {}; 
	 void Attach(Observer*); 
	 void Detach(Observer*); 
protected:
	 void Notify(void* pio_pNotificationParam);

private: 
	 vector<Observer*> m_observers; 
};

#endif