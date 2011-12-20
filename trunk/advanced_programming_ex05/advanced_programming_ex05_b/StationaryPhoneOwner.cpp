/******************************************************************************
 * Exercise 05 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * StationaryPhoneOwner: Source file
 *****************************************************************************/

#pragma once
#include "stdafx.h"
#include "StationaryPhoneOwner.h"
using namespace std;

void StationaryPhoneOwner::update(Subject* theChangeSubject, SubjectMessages message){
	if (theChangeSubject == company){
		if (message == TC_PRICE_CHANGE){
			cout << name << " has recieved a notification for price change." << endl;
		}
		else {
			cout << name << ": unknown notification recieved!" << endl;
		}
	}
}