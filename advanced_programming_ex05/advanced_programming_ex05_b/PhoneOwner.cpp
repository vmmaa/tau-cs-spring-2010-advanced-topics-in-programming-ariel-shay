/******************************************************************************
 * Exercise 05 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * PhoneOwner: Source file
 *****************************************************************************/


#include "stdafx.h"
#include "PhoneOwner.h"
#include <iostream>
using namespace std;

// CTORs, DTORs:
PhoneOwner::PhoneOwner(Subject* phoneCompany, ObserverType type, const string& name)
{
	sbj = phoneCompany;
	this->type = type;
	// create a new owner according to type
	if (type == MOBILE_PHONE_OWNER){
		owner = new MobilePhoneOwner(phoneCompany,name);
	}
	if (type == STATIONARY_PHONE_OWNER){
		owner = new StationaryPhoneOwner(phoneCompany,name);
	}
};

PhoneOwner::~PhoneOwner(){
	delete owner;
};

// Methods:

// Factory for creating a new phone owner by a specific implementation and returning it
PhoneOwner* PhoneOwner::factory(Subject* phoneCompany, ObserverType type, const string& name) {
    PhoneOwner* ptrOwner = new PhoneOwner(phoneCompany,type,name);
	return ptrOwner;
}

// Update the implementation owner according to the given subject (phone company) and its message
void PhoneOwner::Update(Subject* theChangeSubject, SubjectMessages message){
	owner->update(theChangeSubject,message);
}
