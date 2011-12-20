/******************************************************************************
 * Exercise 05 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * PhoneOwnerImpl:
 * Header file for an implementation of PhoneOwner, part of the Bridge
 * design pattern.
 *****************************************************************************/

#pragma once
#include "Definitions.h"
#include "Observer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

// Implementation Class - PhoneOwnerImp
class PhoneOwnerImpl
{
	friend class PhoneOwner; // allow PhoneOwner see private members
	public:
		// CTORs and DTORs.
		PhoneOwnerImpl(Subject* pi_company, ObserverType pi_type, const string& pi_name):
		company(pi_company),type(pi_type),name(pi_name) {}
		PhoneOwnerImpl(const PhoneOwnerImpl& phoneOwnerImpl);
		virtual ~PhoneOwnerImpl() {}

		// Methods:
		// virtual interface for the update implementation (mobile / stationary)
		virtual void update(Subject* company, SubjectMessages message) = 0;

	protected:
		// Members:
		Subject* company;
		ObserverType type;
		string name;
};
