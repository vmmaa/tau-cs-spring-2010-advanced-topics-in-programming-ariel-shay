/******************************************************************************
 * Exercise 06 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Day Header File.
 *****************************************************************************/

#pragma once
#include <vector>
#include <strstream>
#include <iomanip>
#include "stdafx.h"
#include "Meeting.h"
#include "MeetingTime.h"
using namespace std;

// Day Class
class Day
{
	friend class Diary; // for convenient meetings visibility
	public: 
		// CTORs & DTOR:
		Day(int dayNumber) : m_dayNumber(dayNumber) { }
		Day(const Day& day);
		virtual ~Day() { m_meetings.clear(); }
		void operator=(Day&) { }

		// Methods:
		virtual int getDay() const { return m_dayNumber; }
		virtual string getName() const { return sm_days[m_dayNumber]; }

		// Operators:
		friend ostream& operator<<(ostream& output, const Day& day);

	protected:
		// Static Members:
		static const string sm_days[5];

		// Members:
		vector<Meeting*> m_meetings;
		int m_dayNumber;
}; 
