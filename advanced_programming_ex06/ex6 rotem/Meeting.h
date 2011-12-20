/*******************************************************************
*	File name: 		Meeting.h
*	Description:	Declaration of the Meeting class
*					The class implemenets a Meeting which contains
*					time interval, subject, participants, etc.
*	
*	Authors:		Rotem Druker	(I.D. 021793708)
*					Rotem Shaul		(I.D. 300923661)
*
*	Date:			28/5/2010
*******************************************************************/

#ifndef MEETING_H
#define MEETING_H

#pragma once

#include <list>
#include "MeetingTime.h"
#include "Subject.h"
using namespace std;

typedef string Person;

class Meeting : public Subject
{
public:

/***************
C'tors / D'tors
***************/
	Meeting(const MeetingTime& pi_mtTime, string pi_strSubject = "");

	Meeting(const MeetingTime& pi_mtTime, string pi_strSubject, int pi_nNumOfParicipants, ...);

	virtual ~Meeting(void);

/*******************
Getters and Setters
*******************/
	string				GetSubject()	const					{return m_strSubject;}

	void				SetSubject(string pi_strSubject)		{m_strSubject = pi_strSubject;}

	list<Person>		GetListOfParticipants()	const			{return m_prParticipants;}

	void				AddParticipant(Person pi_prPerson)		{m_prParticipants.push_back(pi_prPerson);}

	const MeetingTime&	GetMeetingTime()	const				{return m_mtTime;}

	void				SetMeetingTime(MeetingTime pi_mtTime)	{m_mtTime = pi_mtTime;}

	/* Chnage current meeting time */
	virtual	bool		ChangeMeetingTime(MeetingTime pi_mtTime);

/*******************
Other methods
*******************/

	/* Indicates wethear 2 meetings intersect */
	virtual bool		operator==(const Meeting& pi_mtOtherMeeting) const; 

	// for printing the meeting
	friend				ostream& operator<< (ostream& os, const Meeting& pi_mtMeeting);

	// fields sizes - for priniting alignment
	const	static	int		SpaceAfterTimeFiledWith;
	const	static	int		SubjectFieldWith;
	const	static	int		ParticipantsFieldWidth;

protected:

/***************
Data members
***************/
	string			m_strSubject;

	list<Person>	m_prParticipants;

	MeetingTime		m_mtTime;

};

#endif