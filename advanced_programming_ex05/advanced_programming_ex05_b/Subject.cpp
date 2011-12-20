/******************************************************************************
 * Exercise 05 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Subject: Source file
 *****************************************************************************/

#include "stdafx.h"
#include "Subject.h"
using namespace std;

// Methods

Subject::~Subject()
{
	for (int i = 0; i < m_observers.size(); i++)
	{
		delete m_observers[i];
	}
}

/* ***************
 * Attach, Detach 
 *****************/

// Attach an observer to this subject
void Subject::Attach (Observer* o) { 
	 m_observers.push_back(o); 
} 

// Detach an observer from this subject
void Subject::Detach (Observer* o) { 
    int count = m_observers.size(); 
	int i; 
	for (i = 0; i < count; i++) { 
		if(m_observers[i] == o) 
			break; 
	} 
	if(i < count) {
		m_observers.erase(m_observers.begin() + i); 
	}
} 

/* ***************
 * Notifications
 *****************/

// Notify all observers of this type with the given message
void Subject::Notify(SubjectMessages message, ObserverType pi_obsType){ 
    int count = m_observers.size();
	for (int i = 0; i < count; i++) {
		if ((m_observers[i])->type == pi_obsType) (m_observers[i])->Update(this,message);
	}
}

// Notify all observers with the given message
void Subject::NotifyAll(SubjectMessages message){
	int count = m_observers.size();
	for (int i = 0; i < count; i++) {
		(m_observers[i])->Update(this,message);
	}
}
