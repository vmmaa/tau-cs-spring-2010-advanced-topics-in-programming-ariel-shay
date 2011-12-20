/******************************************************************************
 * Exercise 05 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * MobilePhoneOwner: Source file
 *****************************************************************************/

#pragma once
#include "stdafx.h"
#include "MobilePhoneOwner.h"
using namespace std;

void MobilePhoneOwner::update(Subject* theChangeSubject, SubjectMessages message){
	if (theChangeSubject == company){
		if (message == TC_PRICE_CHANGE){
			cout << name << " has recieved a notification for price change." << endl;
		}
		else if (message == TC_UPGRADE){
			cout << name << " has recieved a notification for an upgrade." << endl;
		}
		else {
			cout << name << ": unknown notification recieved!" << endl;
		}
	}
}