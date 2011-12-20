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
//========================================================= 
#include <vector> 
using namespace std ;
//========================================================= 

class Subject; 

class Observer {
public:
	Observer() {};
	~Observer() {};
	virtual void Update(Subject* theChangeSubject) = 0;
protected:
	Subject*	sbj;
};

#endif
