/******************************************************************************
 * Exercise 05 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Observer:
 * Header file for the Observer design pattern - observer side. This specific
 * implementation allows notifications to different observers by their type
 * with a specific message from the subject
 *****************************************************************************/

#pragma once
#include "Definitions.h"
#include "Subject.h"
#include <vector>
using namespace std ;

class Subject;

class Observer {
friend class Subject; // allow Subject see type
public:
	// CTOR, DTOR
	Observer() {};
	virtual ~Observer() {sbj = NULL;};

	// methods
	// update an observer with the given subject and its message
	virtual void Update(Subject* theChangeSubject, SubjectMessages message) = 0;
protected:
	Subject*		sbj;
	ObserverType	type;
};