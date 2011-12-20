/*******************************************************************
*	File name: 		Diary.h
*	Description:	Declaration of the Diary class
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

#pragma once

#include <vector>
#include <string>
#include "Day_t.h"

using namespace std;

// reference based singleton implementation
class Diary
{
public:

/*******************
Getters and Setters
*******************/
	// Retrieve the single instance of the class
	static Diary&	GetObj();

	vector<Day_t>	GetDays()	const	{return m_dDays;}

/***************
Modifiers
***************/
	// Add meeting to a day
	virtual bool AddMeeting(Meeting* pi_Meeting, int pi_nDay);

	// Delete a given meeting
	virtual bool DeleteMeeting(Meeting* pi_Meeting);

	// Delete meeting at specified time
	virtual bool DeleteMeeting(int pi_nDay, int pi_nHour, int pi_nMinutes);

	/* Change time of meeting which takes place in a specified day and time,
	to a new day and time */
	virtual bool CopyMeeting(MeetingTime oldTime, int pi_nOldDay, 
							MeetingTime newTime, int pi_nNewDay);

/*******************
Other methods
*******************/

	// Find meeting which takes place in a given time
	Meeting*	FindMeetringByStartTime(int pi_nDay, int pi_nHour, int pi_nMinutes);

	// for printing the diary
	friend ostream& operator<< (ostream& os, const Diary& diary);


private:
/************************
Singleton declarations
************************/
	static Diary	obj;

	Diary()			{ }					// PRIVATE!!! 
	Diary			(const Diary&);		// no copy 
	void			operator=(Diary&);	// no copy 

protected:

/***************
Helper methods
***************/
	static			void		Init();

	virtual			bool		IsLegalDay(int pi_nDay);

/***************
Data members
***************/
	// cotainer of days
	static			vector<Day_t>		m_dDays;

	// Intialization flag
	static			bool				m_bInitialized;

	// Number of days in diary (constant)
	static	const	int					m_nNumOfDays;

	// Names of days (constant)
	static	const	string				m_strDaysNames[];
};