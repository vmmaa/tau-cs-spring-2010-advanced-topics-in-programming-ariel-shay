/******************************************************************************
 * Exercise 05 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * PhoneCompany: Source file
 *****************************************************************************/

#include "stdafx.h"
#include "PhoneCompany.h"
using namespace std;

// Add a client to the company
void PhoneCompany::addClient(const ObserverType type, const string& name){
	PhoneOwner *po = PhoneOwner::factory(this,type,name);
	Subject::Attach(po);
}
