/******************************************************************************
 * Exercise 06 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Meeting Header File.
 *****************************************************************************/

#pragma once
#include <string>
#include <vector>
#include "MeetingTime.h"
using namespace std;

// Meeting Class - Using Factory Method Design Pattern
class Meeting
{ 
	public: 
		// CTORs & DTOR:
		Meeting(int day, int startHour, int startMins, int endHour, int endMins, string subject, int workersNum, string workers[]);
		Meeting(const Meeting& meeting);
		virtual ~Meeting(void) { };

		// Factory Method:
		static Meeting* factory(int day, int startHour, int startMins, int endHour, int endMins,
			string subject, int workersNum, string workers[]);

		// Methods:
		
		// getters:
		virtual int getDay(void) const { return m_day; }
		virtual MeetingTime getMeetingTime(void) const { return m_meetingTime; }
		virtual int getStartHour(void) const { return m_meetingTime.getStartHour(); }
		virtual int getStartMins(void) const { return m_meetingTime.getStartMins(); }
		virtual int getEndHour(void) const { return m_meetingTime.getEndHour(); }
		virtual int getEndMins(void) const { return m_meetingTime.getEndMins(); }
		virtual string getSubject(void) const { return m_subject; }
		virtual vector<string> getWorkers(void) const { return m_workers; }
		
		// setters:
		virtual void setDay(int value) { m_day = value; }
		virtual void setMeetingTime(const MeetingTime& meetingTime) { m_meetingTime = meetingTime; }
		virtual void setStartTime(int startHour, int startMins) { m_meetingTime.setStartTime(startHour,startMins); }
		virtual void setEndTime(int endHour, int endMins) { m_meetingTime.setEndTime(endHour,endMins); }

		// Operators:
		friend ostream& operator<<(ostream& output, const Meeting& meeting);
		bool operator==(const Meeting&) const;

	protected:
		// Members:
			int         m_day;
			MeetingTime	m_meetingTime;
			string      m_subject;
			vector<string> m_workers;
}; 