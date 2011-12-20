/******************************************************************************
 * Exercise 05 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * MobilePhoneOwner:
 * Header file for a derived implementation of PhoneOwner (extending PhoneOwnerImpl)
 *****************************************************************************/

#pragma once
#include "PhoneOwnerImpl.h"
#include <iostream>
using namespace std;

class MobilePhoneOwner : public PhoneOwnerImpl
{
	public: 
		// CTORs and DTORs.
		MobilePhoneOwner(Subject* company, const string& name):
		PhoneOwnerImpl(company,MOBILE_PHONE_OWNER,name) { }
		MobilePhoneOwner(const MobilePhoneOwner& mobilePhoneOwner);
		~MobilePhoneOwner() { PhoneOwnerImpl::~PhoneOwnerImpl(); }

		// Methods:
		virtual void update(Subject* theChangeSubject, SubjectMessages message);
};	
