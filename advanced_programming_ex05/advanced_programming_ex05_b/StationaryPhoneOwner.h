/******************************************************************************
 * Exercise 05 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * StationaryPhoneOwner:
 * Header file for a derived implementation of PhoneOwner (extending PhoneOwnerImpl)
 *****************************************************************************/

#pragma once
#include "PhoneOwnerImpl.h"
#include <iostream>
using namespace std;

class StationaryPhoneOwner : public PhoneOwnerImpl
{
	public: 
		// CTORs and DTORs.
		StationaryPhoneOwner(Subject* company, const string& name):
		PhoneOwnerImpl(company,STATIONARY_PHONE_OWNER,name) { }
		StationaryPhoneOwner(const StationaryPhoneOwner& stationaryPhoneOwner);
		~StationaryPhoneOwner() { PhoneOwnerImpl::~PhoneOwnerImpl(); }

		// Methods:
		virtual void update(Subject* theChangeSubject, SubjectMessages message);
};	
