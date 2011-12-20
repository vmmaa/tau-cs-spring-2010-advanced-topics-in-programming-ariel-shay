/******************************************************************************
 * Exercise 06 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Day Source File.
 *****************************************************************************/

#include "stdafx.h"
#include "Day.h"

const string Day::sm_days[5] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday"};

// Operators:
ostream& operator<<(ostream& output, const Day& day)
{
	// print header
	output.fill(' ');
	output	<< Day::sm_days[day.m_dayNumber-1] << ":" << endl
			<< setw(15) << left << "Time"		// time header
			<< setw(20) << left << "Subject"	// subject header
			<< left << "Members" << endl;		// participants header
	output.fill('=');
	output	<< setw(15) << right << " "
			<< setw(20) << right << " "
			<< setw(35) << "" << endl;
	// print all meetings
	for (int i=0; i<day.m_meetings.size(); i++){
		output << (*day.m_meetings[i]);
	}
	output << endl;
	return output;
}
	