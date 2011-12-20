/******************************************************************************
 * Exercise 06 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * MeetingTime Source File.
 *****************************************************************************/

#include "stdafx.h"
#include "MeetingTime.h"

// CTORs and DTORs:

// default CTOR
MeetingTime::MeetingTime(int startHour, int startMins, int endHour, int endMins):
	m_startHour(startHour),
	m_startMins(startMins),
	m_endHour(endHour),
	m_endMins(endMins)
	{}

// copy CTOR
MeetingTime::MeetingTime(const MeetingTime & meetingTime){
	setStartTime(meetingTime.getStartHour(),meetingTime.getStartMins());
	setEndTime(meetingTime.getEndHour(),meetingTime.getEndMins());
};

// setters:
// setter for start time (only if valid time)
void MeetingTime::setStartTime(int startHour, int startMins){
	if (isValidTime(startHour,startMins)){
		m_startHour = startHour;
		m_startMins = startMins;
	}
}

// setter for end time (only if valid time)
void MeetingTime::setEndTime(int endHour, int endMins){
	if (isValidTime(endHour,endMins)){
		m_endHour = endHour;
		m_endMins = endMins;
	}
}

// more methods:

// returns true iff this meeting time overlaps the given meeting time
bool MeetingTime::isOverlapping(const MeetingTime & otherTime) const{
	return
		// this start time is before the given end time, and this end time is after the given end time
		((m_startHour < otherTime.getEndHour() || (m_startHour == otherTime.getEndHour() && m_startMins < otherTime.getEndMins())) &&
		(otherTime.getEndHour() < m_endHour || (otherTime.getEndHour() == m_endHour && otherTime.getEndMins() < m_endMins)))
		
		||

		// or the other way around
		((otherTime.getStartHour() < m_endHour || (otherTime.getStartHour() == m_endHour && otherTime.getStartMins() < m_endMins)) &&
		(m_endHour < otherTime.getEndHour() || (m_endHour == otherTime.getEndHour() && m_endMins < otherTime.getEndMins()))
		);
}

// returns true iff the meeting time is valid, i.e. the times are valid and start time < end time
bool MeetingTime::isValidMeetingTime() const{
	return (
		isValidTime(m_startHour,m_startMins) &&
		isValidTime(m_endHour,m_endMins) &&
		(m_startHour < m_endHour || (m_startHour == m_endHour && m_startMins < m_endMins)));
	// doesn't allow meetings until 00:00 the next day
}

// Operators:

// ostream for printing
ostream& operator<<(ostream& os, const MeetingTime& meetingTime)
{
	// fixed length: 13 characters
	os.fill('0');
	os	<< setw(2) << right << meetingTime.getStartHour() << ":"  
		<<  setw(2) << right << meetingTime.getStartMins()
		<<	" - "
		<<  setw(2) << right << meetingTime.getEndHour()  << ":" 
		<<  setw(2) << right << meetingTime.getEndMins();
	return os;
};

// equality operator - returns true iff the given meeting time is EXACTLY the same
bool MeetingTime::operator==(const MeetingTime& meetingTime) const{
	return (
		m_startHour == meetingTime.getStartHour() &&
		m_startMins == meetingTime.getStartMins() &&
		m_endHour == meetingTime.getEndHour() &&
		m_endMins == meetingTime.getEndMins());
};

// Helping methods:

// returns true iff the time is valid
bool MeetingTime::isValidTime(int hour, int mins) const{
	return (hour >= 0 && hour <= 23 && mins >= 0 && mins <= 59);
}
