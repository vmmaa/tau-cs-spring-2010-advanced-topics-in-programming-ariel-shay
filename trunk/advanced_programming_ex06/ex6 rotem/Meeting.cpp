/*******************************************************************
*	File name: 		Meeting.cpp
*	Description:	Implementation of the Meeting class
*					The class implemenets a Meeting which contains
*					time interval, subject, participants, etc.
*	
*	Authors:		Rotem Druker	(I.D. 021793708)
*					Rotem Shaul		(I.D. 300923661)
*
*	Date:			28/5/2010
*******************************************************************/

#include "Meeting.h"
#include <stdarg.h>		// for va_list, va_start, va_end
#include <strstream>
#include <iomanip>

// fields sizes - for priniting
const	int		Meeting::SpaceAfterTimeFiledWith	= 5;
const	int		Meeting::SubjectFieldWith			= 20;
const	int		Meeting::ParticipantsFieldWidth		= 40;


/***************
C'tors / D'tors
***************/
Meeting::Meeting(const MeetingTime& pi_mtTime,  string pi_strSubject)
		: m_mtTime(pi_mtTime), m_strSubject(pi_strSubject)

{
}


Meeting::Meeting(const MeetingTime& pi_mtTime,  string pi_strSubject,
				 int pi_nNumOfParicipants, ...)
		: m_mtTime(pi_mtTime), m_strSubject(pi_strSubject)
{
	va_list Participants;
	va_start(Participants, pi_nNumOfParicipants); 
	for(int i = 0; i < pi_nNumOfParicipants; ++i )
	{
		string p =  va_arg(Participants, char*); 
		AddParticipant(p);
	}
	va_end(Participants);
}


Meeting::~Meeting(void)
{
}


/*******************
Getters and Setters
*******************/

/* Chnage current meeting time */
bool	Meeting::ChangeMeetingTime(MeetingTime pi_mtTime)
{
	if (pi_mtTime.isValid())
	{
		MeetingTime mtOldTime = m_mtTime;	// save old time
		m_mtTime = pi_mtTime;				// update time
		/* notify time has chnage 
		(and send copy of old time, 
		so the notified objects can see the difference) */
		Notify((void*)&mtOldTime);	
		return true;
	}
	return false;
}


/* Indicates wethear 2 meetings intersect */
bool	Meeting::operator==(const Meeting& pi_mtOtherMeeting) const
{
	return (m_mtTime == pi_mtOtherMeeting.GetMeetingTime());
}


// for printing the meeting
ostream& operator<< (ostream& os, const Meeting& pi_mtMeeting)
{
	os.fill(' ');
	os	<< pi_mtMeeting.GetMeetingTime() << setw(Meeting::SpaceAfterTimeFiledWith) 
		<< setfill(' ') << ""
		<< setw(Meeting::SubjectFieldWith) << left << pi_mtMeeting.GetSubject().c_str();

	list<Person> participants = pi_mtMeeting.GetListOfParticipants();
	for (list<Person>::iterator it = participants.begin(); it != participants.end(); it++)
	{
		os << (*it).c_str();
		list<Person>::iterator it2 = it;
		if ((++it2) != participants.end())
		{
			os << ", ";
		}
	}
	return os;
}