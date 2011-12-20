/*******************************************************************
*	File name: 		MeetingTime.h
*	Description:	Declaration of the MeetingTime class
*					The class implemenets a Meeting time which contains
*					time interval (in hours and minutes resolution)
*	
*	Authors:		Rotem Druker	(I.D. 021793708)
*					Rotem Shaul		(I.D. 300923661)
*
*	Date:			28/5/2010
*******************************************************************/

#ifndef MEETINGTIME_H
#define MEETINGTIME_H

#pragma once
#include <iostream>
#include <stdio.h>
using namespace std;

class MeetingTime
{
public:
/***************
C'tors / D'tors
***************/
	MeetingTime(int sHour, int sMints,int eHour,int eMints);

	MeetingTime(const MeetingTime& mTime);	 //copy constructor

	virtual ~MeetingTime(void);
	
/*******************
Getters and Setters
*******************/
	int		getStartHour() const	 {return m_sHour; }

	int		getStartMints() const	 {return m_sMints; }

	int		getEndHour() const		{return m_eHour; }

	int		getEndMints() const		{return m_eMints; }

	void setStartTime(int sHour, int sMints);

	void setEndTime(int eHour, int eMints);

	//checks if the time interval of start and end is legal.
	bool	isValid();


/*******************
Operators
*******************/
	// returns true if the timing intervals overlap and false otherwise.
	bool operator==(const MeetingTime& mTime) const;

	bool operator<(const MeetingTime& mTime) const ;

	bool operator>(const MeetingTime& mTime) const;
	
	// for printing the time interval
	friend ostream& operator<< (ostream& os, const MeetingTime& MeetingTime);

protected:

/***************
Data members
***************/
	int m_sHour;
	int m_sMints;
	int m_eHour;
	int m_eMints;
	
/***************
Helper methods
***************/
	/** internal helper methods **/
	bool isLegalTime(int hour, int mints);


};

#endif