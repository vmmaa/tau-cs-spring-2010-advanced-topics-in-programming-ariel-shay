/*******************************************************************
*	File name: 		Diary.cpp
*	Description:	Implementation of the Diary class
*					The class implemenets a weekly diary which contains
*					a list of days and manages their meetings
*					
*					The class is implemented as a singleton
*	
*	Authors:		Rotem Druker	(I.D. 021793708)
*					Rotem Shaul		(I.D. 300923661)
*
*	Date:			28/5/2010
*******************************************************************/

#include "Diary.h"

/************************
Init static Data members
************************/
// The single instance of the class
Diary			Diary::obj;
// cotainer of days
vector<Day_t>	Diary::m_dDays;
// Intialization flag
bool			Diary::m_bInitialized = false;
// Number of days in diary (constant)
const	int		Diary::m_nNumOfDays = 7;
// Names of days (constant)
const string	Diary::m_strDaysNames[] = 
				{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", 
				"Friday", "Saturday"};

/*******************
Getters and Setters
*******************/

// Retrieve the single object of the class
Diary& Diary::GetObj()
{
	Init();
	return obj;
}

/***************
Modifiers
***************/

// Add meeting to a day
bool Diary::AddMeeting(Meeting* pi_Meeting, int pi_nDay)
{
	if (!IsLegalDay(pi_nDay))
	{
		return false;
	}
	return m_dDays[pi_nDay-1 /* zero based */].AddMeeting(pi_Meeting);
}


// Delete a given meeting
bool Diary::DeleteMeeting(Meeting* pi_Meeting)
{
	for (int nIndex = 0; nIndex < m_nNumOfDays; nIndex++)
	{
		if (IsLegalDay(nIndex+1))
		{
			if (m_dDays[nIndex].DeleteMeeting(pi_Meeting))
			{
				return true;
			}
		}
	}
	return false;
}


// Delete meeting at specified time
bool Diary::DeleteMeeting(int pi_nDay, int pi_nHour, int pi_nMinutes)
{
	// find meeting to delete
	Meeting*	mtMeetingToDelete = FindMeetringByStartTime(pi_nDay, pi_nHour, pi_nMinutes);
	if (!mtMeetingToDelete)
	{
		return false;
	}
	// delete
	return (DeleteMeeting(mtMeetingToDelete));

}


/* Change time of meeting which takes place in a specified day and time,
to a new day and time */
bool Diary::CopyMeeting(MeetingTime oldTime, int pi_nOldDay, 
						MeetingTime newTime, int pi_nNewDay)
{
	// legal days ?
	if (!IsLegalDay(pi_nOldDay) || !IsLegalDay(pi_nNewDay))
	{
		return false;
	}

	// Change time in same day ?
	if (pi_nOldDay == pi_nNewDay)
	{
		return m_dDays[pi_nOldDay-1  /* zero based */].CopyMeeting(oldTime, newTime);
	}

	// Get meeting object, in order to manipulate it
	Meeting* meeting = m_dDays[pi_nOldDay-1  /* zero based */].FindMeetringByStartTime(
		oldTime.getStartHour(), oldTime.getStartMints());
	if (meeting == NULL)
	{
		return false;
	}
	// delete meeting from old day
	MeetingTime mtOriginalTime = meeting->GetMeetingTime(); // for rollback...
	bool bDeleted = m_dDays[pi_nOldDay-1  /* zero based */].DeleteMeeting(meeting);
	if (!bDeleted)
	{
		return false;
	}
	// change time of meeting
	bool bChanged = meeting->ChangeMeetingTime(newTime);
	if (!bChanged)
	{
		return false;
	}
	// try to add to new day
	bool bAdded = m_dDays[pi_nNewDay-1 /* zero based */].AddMeeting(meeting);
	if (!bAdded)
	{
		// failed to add to new day, set back old time and add back to old day
		meeting->ChangeMeetingTime(mtOriginalTime);
		m_dDays[pi_nOldDay-1 /* zero based */].AddMeeting(meeting);
		return false;		// transaction failed... (rolled back)
	}
	return true;
}


// Find meeting which takes place in a given time
Meeting*	Diary::FindMeetringByStartTime(int pi_nDay, int pi_nHour, int pi_nMinutes)
{
	if (!IsLegalDay(pi_nDay))
	{
		return NULL;
	}
	return m_dDays[pi_nDay-1  /* zero based */].FindMeetringByStartTime(pi_nHour, 
																		pi_nMinutes);
}

/***************
Helper methods
***************/

// Initialize the single instance of the class
void		Diary::Init()
{
	if (m_bInitialized)
	{
		return;
	}
	for (int nIndex = 0; nIndex < m_nNumOfDays; nIndex++)
	{
		Day_t dCurrDay(m_strDaysNames[nIndex]);
		m_dDays.push_back(dCurrDay);
	}
	m_bInitialized = true;
}


bool	Diary::IsLegalDay(int pi_nDay)
{
	return (pi_nDay >= 1 && pi_nDay < 6);
}


// for printing the diary
ostream& operator<< (ostream& os, const  Diary& diary)
{
	for (int nIndex = 0; nIndex < diary.m_nNumOfDays; nIndex++)
	{
		os << ((diary.GetDays())[nIndex]) << endl;
	}
	return os;
}