/*******************************************************************
*	File name: 		Day_t.h
*	Description:	Declaration of the Day_t class
*					The class implemenets a Day_t which contains
*					a map of meetings, keyed by their time.
*	
*	Authors:		Rotem Druker	(I.D. 021793708)
*					Rotem Shaul		(I.D. 300923661)
*
*	Date:			28/5/2010
*******************************************************************/

#ifndef DAY_H
#define DAY_H

#pragma once
#include "Observer.h"
#include "Meeting.h"
#include <map>
#include <string>
using namespace std;

typedef pair<MeetingTime,Meeting*> pElem;
typedef map<MeetingTime,Meeting*>::iterator day_elems_iter;

class Day_t : Observer
{
public:
/***************
C'tors / D'tors
***************/
	Day_t(string dayName);

	virtual ~Day_t(void);

/*******************
Getters and Setters
*******************/
	map<MeetingTime,Meeting*>	getMeetings() const		{ return m_meetings; } 

	string						getDayName() const		{ return m_strDayName; }

	// overloading from observer
	virtual string				GetObserverName()		{return getDayName();}

	// Find meeting which takes place in a given time
	Meeting*					FindMeetringByStartTime(int pi_nHour, int pi_nMinutes);

/***************
Modifiers
***************/
	virtual bool AddMeeting(Meeting* pi_Meeting);

	virtual bool DeleteMeeting(Meeting* pi_Meeting);

	virtual bool CopyMeeting(MeetingTime oldTime, MeetingTime newTime);
	
	/* update, subject is expected to be a Meeting object, 
	and NotificationData is expected to be a pointer to it's old MeetingTime value */
	virtual void Update(Subject* theChangeSubject, 
				const void* pio_pNotificationData);

/*******************
Other methods
*******************/

	// for printing the day
	friend ostream& operator<< (ostream& os, const Day_t& pi_Day);

	// fields sizes - for priniting alignment
	const	static	int		TimeFieldWidth;

protected:

/***************
Data members
***************/

	//container holding meetings according to a meeting time key.
	map<MeetingTime,Meeting*> m_meetings;

	string m_strDayName;

/***************
Helper methods
***************/
	day_elems_iter findMeetingByTime(MeetingTime& mTime);

};

#endif