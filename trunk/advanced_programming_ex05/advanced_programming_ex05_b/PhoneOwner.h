/******************************************************************************
 * Exercise 05 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * PhoneOwner:
 * Header file for the phone owner class, implementing three design patterns:
 * - Observer: observing class phone company for notifications
 * - Bridge: using a specifig logics for phone owner 
 * - Factory: creating instances of the derived classes of an implementation
 *****************************************************************************/

#pragma once
#include "Definitions.h"
#include "Observer.h"
#include "Subject.h"
#include "PhoneOwnerImpl.h"
#include "MobilePhoneOwner.h"
#include "StationaryPhoneOwner.h"
#include <string>
using namespace std;
class PhoneOwnerImpl;

// Base Class - PhoneOwner
class PhoneOwner : public Observer
{ 
	public:
		// CTORs and DTORs
		PhoneOwner(Subject* phoneCompany, const ObserverType type, const string& name);
		PhoneOwner(const PhoneOwner& phoneOwner);
		virtual ~PhoneOwner();

		// Factory Method
		static PhoneOwner* factory(Subject* phoneCompany, ObserverType type, const string& name);

		// Methods:
		virtual void Update(Subject* theChangeSubject, SubjectMessages message);

	protected:
		// Implementations.
		PhoneOwnerImpl* owner;
};