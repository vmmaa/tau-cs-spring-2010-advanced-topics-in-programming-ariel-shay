/******************************************************************************
 * Exercise 06 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Diary Source File.
 *****************************************************************************/

#include "stdafx.h"
#include "Diary.h"
using namespace std;

// CTOR:
Diary::Diary()
{
	for (int i = 1; i < 6; i++)
	{
		m_days.push_back(new Day(i));
	}
}

// Adds meeting by pointer. Returns 1 on success, 0 on failure.
int Diary::addMeeting(Meeting* meeting)
{
	int day = meeting->getDay();
	if (day >= 6)
	{ 
		cout << "Unable to add new meetings on Friday or Sautrday." << endl;
		return 0;
	}
	if (!meeting->getMeetingTime().isValidMeetingTime())
	{
		cout << "Meeting has invalid time (non-legal time / ending time before starting time)." << endl;
		return 0;
	}

	// if passed criteria, check if new meeting is not overlapping any other meeting in this day.
	for (int i = 0; i < (int) m_days[day-1]->m_meetings.size(); i++)
	{
		if (*m_days[day-1]->m_meetings[i] == *meeting)	// using Meeting == operator
		{
			cout << "A meeting overlapping the given day and time exists, cannot set meeting." << endl;
			return 0;
		}
	}

	// safe to insert meeting into day schedule, sorted by hours
	if (m_days[day-1]->m_meetings.empty()){
		m_days[day-1]->m_meetings.push_back(meeting);
	} else {
		vector<Meeting*>::iterator it = m_days[day-1]->m_meetings.begin();
		vector<Meeting*>::iterator vec_end = m_days[day-1]->m_meetings.end();
		// get to the position to insert the new meeting into
		while (it != vec_end && (*it)->getStartHour() < meeting->getStartHour()) it++;
		m_days[day-1]->m_meetings.insert(it,meeting);
	}
	
	return 1;
}

// Removes meeting by pointer.
void Diary::removeMeeting(const Meeting* meeting)
{
	int day = meeting->getDay();
	MeetingTime thisTime = meeting->getMeetingTime();
	for (int i = 0; i < (int) m_days[day-1]->m_meetings.size(); i++)
	{
		MeetingTime thatTime = m_days[day-1]->m_meetings[i]->getMeetingTime();
		if (thisTime == thatTime)
		{
			m_days[day-1]->m_meetings.erase(m_days[day-1]->m_meetings.begin()+i);
			break;
		}
	}
}

// Finds meeting according to day and time. Returns pointer to meeting found overlapping the
// given day and time, or NULL if didn't find such meeting.
Meeting* Diary::findMeeting(int day, int hour, int mins) const
{
	MeetingTime givenTime = MeetingTime(hour,mins,hour,mins); // create a "0-time" interval to check overlapping time-frames later
	for (int i = 0; i < (int) m_days[day-1]->m_meetings.size(); i++)
	{
		MeetingTime meetingTime = m_days[day-1]->m_meetings[i]->getMeetingTime();
		if (meetingTime.isOverlapping(givenTime))
		{
			return m_days[day-1]->m_meetings[i];
		}
	}
	return NULL;
}

// Moves meeting to new day and time. Meeting length remains the same.
void Diary::moveMeeting(Meeting* meeting, int newDay, int newHour, int newMins)
{
	if (newDay >=6)
	{
		cout << "Unable to move meetings to Friday or Sautrday." << endl;
	}
	else
	{
		int hour_length = meeting->getEndHour() - meeting->getStartHour();
		int mins_length = meeting->getEndMins() - meeting->getStartMins();
		if (mins_length < 0){
			hour_length -= 1;
			mins_length += 60;
		}
		// calculate new ending time
		int newEndHour = newHour + hour_length;
		int newEndMins = newMins + mins_length;
		if (newEndMins >= 60){
			newEndHour += 1;
			newEndMins -= 60;
		}
		// check validity of new ending time
		if (newEndHour >= 24)
		{
			cout << "Unable to move meeting so it crosses 2 days." << endl;
		}
		else
		{
			// saving for backup incase adding fails.
			int oldDay = meeting->getDay();
			MeetingTime oldTime = meeting->getMeetingTime();
			removeMeeting(meeting);

			meeting->setDay(newDay);
			MeetingTime newTime = MeetingTime(newHour,newMins,newEndHour,newEndMins);
			meeting->setMeetingTime(newTime);
			if (!addMeeting(meeting))
			{
				meeting->setDay(oldDay);
				meeting->setMeetingTime(oldTime);
				addMeeting(meeting);
			}
		}
		
	}
}

// Print Method:
void Diary::print(void) const
{
	ostrstream output;
	output << "DIARY FOR THIS WEEK" << endl;
	for (int i = 0; i < (int)m_days.size(); i++)
	{
		output << (*m_days[i]) << endl;
	}
	output << ends;
	cout << output.str() << endl;
}