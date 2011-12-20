/******************************************************************************
 * Exercise 02 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * cTimeDate_t Class Header File.
 *****************************************************************************/

#pragma once
#include "cTime_t.h"
#include "cDate_t.h"
using namespace std;

/* NOTE: We did the bonus section by overriding the + operator
 * When adding a cTime_t object into a cTimmeDate_t object,
 * and not with a function of some sort... */

class cTimeDate_t: public cTime_t, public cDate_t{
public:

	// CTORs, DTORs
	cTimeDate_t(void);
	cTimeDate_t(int, int, int, int, int, int);
	cTimeDate_t(const cTimeDate_t& pi_time_date);
	~cTimeDate_t(void);

	// Operators:
	const cTimeDate_t& operator=(const cTimeDate_t& pi_time_date);
	cTimeDate_t operator + (const cTime_t & pi_time);

	// Methods: no new methods, everything is inherited.
	
private:
	// class members: no new class members
	// private functions: no private functions
};