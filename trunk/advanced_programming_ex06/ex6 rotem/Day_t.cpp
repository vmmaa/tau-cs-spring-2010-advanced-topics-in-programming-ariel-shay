/*******************************************************************
*	File name: 		Day_t.cpp
*	Description:	Implementation of the Day_t class
*					The class implemenets a Day_t which contains
*					a map of meetings, keyed by their time.
*	
*	Authors:		Rotem Druker	(I.D. 021793708)
*					Rotem Shaul		(I.D. 300923661)
*
*	Date:			28/5/2010
*******************************************************************/

#include "Day_t.h"
#include <strstream>
#include <iomanip>

const	int		Day_t::TimeFieldWidth		= 11; // 11 for xx:yy-ww:zz

Day_t::Day_t(string dayName)
{
	m_strDayName = dayName;
}

Day_t::~Day_t(void)
{
	 // detach all meetings from subject
	for (day_elems_iter it = m_meetings.begin(); it != m_meetings.end(); it++){
		it->second->Detach(this);
	}
}


bool Day_t::AddMeeting(Meeting* pi_Meeting){
	// preparing return value object for insert.
	pair<map<MeetingTime,Meeting*>::iterator,bool> ret;
	MeetingTime mTime = pi_Meeting->GetMeetingTime();
	ret = m_meetings.insert(pElem(mTime,pi_Meeting));
	/* if succeeded adding, we observe the meeting 
	 (to know if its' time is changed) */
	if(ret.second == true ) {
		pi_Meeting->Attach(this);
		return true;
	}
	// an overlapping meeting already exists.
	return false;
}


bool Day_t::CopyMeeting(MeetingTime oldTime, MeetingTime newTime){
	day_elems_iter it = findMeetingByTime(oldTime);
	// copy only upon finding.
	if(it != m_meetings.end()){
			it->second->ChangeMeetingTime(newTime);
			return true;
	}
	// non existant meeting, can not change.
	return false;
}


bool Day_t::DeleteMeeting(Meeting* pi_Meeting)
{
	day_elems_iter it = findMeetingByTime((MeetingTime)(pi_Meeting->GetMeetingTime()));
	// delete only upon finding.
	if(it != m_meetings.end()){
		// is this is the same meeting ?
		if (it->second == pi_Meeting)
		{
			// m_meetings from subject
			it->second->Detach(this);
			// erase from meeting list
			m_meetings.erase(it);
			return true;
		}
	}
	// deletion failed.
	return false;
}


Meeting*	Day_t::FindMeetringByStartTime(int pi_nHour, int pi_nMinutes)
{
	MeetingTime time(pi_nHour, pi_nMinutes, pi_nHour, pi_nMinutes);
	day_elems_iter it = findMeetingByTime(time);
	if (it != m_meetings.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}


void Day_t::Update(Subject* theChangeSubject, 
					const void* pio_pNotificationData)
{
	Meeting* ptr_Meeting = (Meeting*) theChangeSubject;
	MeetingTime* ptr_oldMeetingTime = (MeetingTime*) pio_pNotificationData;
	MeetingTime newMeetingTime = ptr_Meeting->GetMeetingTime();
	
	day_elems_iter it = findMeetingByTime(newMeetingTime);
	/* if there is another meeting scheduled at the new meeting time, 
	we disallow meeting time change by restoring the meetings time to oldTime */
	if(it != m_meetings.end()){
		/* is this is a different meeting ? 
		 (or same meeting which we try to reschedule to a new time which overlaps
		 with the old one) */
		if (it->second != ptr_Meeting)
		{
			ptr_Meeting->SetMeetingTime(*ptr_oldMeetingTime);
		}
	}
	/* newTime is available, we remove the meeting from the mapping of the old key
		and insert it once again with the proper key */
	else {
		it = findMeetingByTime(*ptr_oldMeetingTime);
		// erase from meeting list
		m_meetings.erase(it);
		// insert meeting once again
		m_meetings.insert(pElem(newMeetingTime, ptr_Meeting));
	}
}


 day_elems_iter Day_t::findMeetingByTime(MeetingTime& mTime){
	 return m_meetings.find(mTime);
 }


 ostream& operator<< (ostream& os, const Day_t& pi_Day)
 {
	 int dayColumnWidth = Day_t::TimeFieldWidth + Meeting::SpaceAfterTimeFiledWith;
	 map<MeetingTime,Meeting*> meetings = pi_Day.getMeetings();
	 os	<< setw(dayColumnWidth) << left << setfill(' ') << pi_Day.getDayName()
		<< setw(Meeting::SubjectFieldWith) << left << "Subject"
		<< setw(Meeting::ParticipantsFieldWidth) << left << "Participants" <<  endl;

	 for( day_elems_iter it = meetings.begin(); it != meetings.end(); it++)
	 {
		 os << (*(it->second)) << endl;
     }
	 os << endl;
	return os;
 }