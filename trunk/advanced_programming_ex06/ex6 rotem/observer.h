#ifndef OBSERVER_H
#define OBSERVER_H

//========================================================= 
// observer.h 
// 
// The Observer pattern defines an one-to-many dependency between  
// a subject object and any number of observer objects.
// 
// The Observer pattern is also known as Publisher-Subscribes. 
// 
//	Rotem & Rotem addition:
//	1. When observer is updated by the subject, it gets a description 
//	of the update, so it can handle different updates
//  2. Observer will have option to return its' name
//========================================================= 
#include <vector> 
#include <string>
using namespace std ;
//========================================================= 

class Subject; 

class Observer {
public:
	Observer() {};
	~Observer() {};

	// Modified by Rotem & Rotem (added the "update description" argument)
	virtual void Update(Subject* theChangeSubject, 
				const void* pio_pNotificationData) = 0;

	// Added by Rotem & Rotem
	virtual	string	GetObserverName() = 0;
protected:
	Subject*	sbj;
};

#endif
