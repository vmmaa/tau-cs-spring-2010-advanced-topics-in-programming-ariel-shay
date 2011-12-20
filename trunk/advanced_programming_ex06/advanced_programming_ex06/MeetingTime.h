/******************************************************************************
 * Exercise 06 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * MeetingTime Header File.
 *****************************************************************************/

#pragma once
#include <strstream>
#include <iostream>
#include <stdio.h>
#include <iomanip>
using namespace std;

class MeetingTime
{
	public:
		// CTORs and DTORs:
		MeetingTime(int startHour, int startMins, int endHour, int endMins);
		MeetingTime(const MeetingTime & meetingTime);
		virtual ~MeetingTime() {};
		
		// getters:
		int getStartHour() const	{ return m_startHour; }
		int getStartMins() const	{ return m_startMins; }
		int getEndHour() const		{ return m_endHour; }
		int getEndMins() const		{ return m_endMins; }

		// setters:
		void setStartTime(int startHour, int startMins);
		void setEndTime(int endHour, int endMins);

		// more methods:
		bool isOverlapping(const MeetingTime & meetingTime) const;
		bool isValidMeetingTime() const;

		// operators:
		bool operator==(const MeetingTime& meetingTime) const;
		friend ostream& operator<<(ostream& os, const MeetingTime& meetingTime);
	
	protected:
		// members:
		int m_startHour;
		int m_startMins;
		int m_endHour;
		int m_endMins;

		// helping function
		bool isValidTime(int hour, int mins) const;
};
