/******************************************************************************
 * Exercise 05 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * PhoneCompany:
 * Header file for the phone company class, implementing two design patterns:
 * - singleton
 * - observer (the subject side)
 *****************************************************************************/

#pragma once
#include "stdafx.h"
#include "Definitions.h"
#include "Subject.h"
#include "PhoneOwner.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
using namespace std;

// Singleton Class - PhoneCompany
class PhoneCompany : public Subject
{ 
	public: 
		// Static Singleton Creation/Destruction:
		static PhoneCompany* createObj() { 
			if (sngPtr == 0) { 
				sngPtr = new PhoneCompany;
			} 
			return sngPtr;
		}
		static void Destroy() { delete sngPtr; sngPtr = 0;}

		// Methods:
		void addClient(const ObserverType type, const string& name);
		void notifyPriceChange(void)	{ Subject::NotifyAll(TC_PRICE_CHANGE); };
		void notifyUpgrade(void)		{ Subject::Notify(TC_UPGRADE,MOBILE_PHONE_OWNER); };

	protected: 
		// Virtual DTOR:
		virtual ~PhoneCompany()	{ } 

	private: 
		// Singleton Pointer:
		static PhoneCompany* sngPtr; 

		// Copy prevention and private CTOR:
		PhoneCompany() {}				
		PhoneCompany(const PhoneCompany&);
		void operator=(PhoneCompany&);
}; 
