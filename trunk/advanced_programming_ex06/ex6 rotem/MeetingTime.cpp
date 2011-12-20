/*******************************************************************
*	File name: 		MeetingTime.cpp
*	Description:	Implementation of the MeetingTime class
*					The class implemenets a Meeting time which contains
*					time interval (in hours and minutes resolution)
*	
*	Authors:		Rotem Druker	(I.D. 021793708)
*					Rotem Shaul		(I.D. 300923661)
*
*	Date:			28/5/2010
*******************************************************************/

#include "MeetingTime.h"
#include <strstream>
#include <iomanip>


MeetingTime::MeetingTime(int sHour, int sMints,int eHour,int eMints)
{
	setStartTime(sHour,sMints);
	setEndTime(eHour,eMints);
}


//copy constructor
MeetingTime::MeetingTime(const MeetingTime& mTime){
	setStartTime(mTime.getStartHour(), mTime.getStartMints());
	setEndTime(mTime.getEndHour(),mTime.getEndMints());
}


MeetingTime::~MeetingTime(void)
{
}


void MeetingTime::setStartTime(int sHour, int sMints){
	m_sHour=sHour;
	m_sMints=sMints;
}


void MeetingTime::setEndTime(int eHour, int eMints) {
	m_eHour=eHour;
	m_eMints=eMints;
}


bool MeetingTime::isValid() {
	/** check basic legality of hour and mints members **/
	if(!isLegalTime(m_sHour, m_sMints) || !isLegalTime(m_eHour, m_eMints)) return false;
	/** check legality in interval sense **/
	if(m_eHour < m_sHour) return false;
	else if (m_eHour == m_sHour && m_eMints <= m_sMints) return false;
	
	return true;
}


bool MeetingTime::isLegalTime(int hour, int mints) {
	if(hour<0 || hour >23) return false;
	if(mints<0 || mints>59) return false;
	return true;
}


bool MeetingTime::operator==(const MeetingTime& mTime) const{
	if((MeetingTime&)(*this)<mTime || (MeetingTime&)(*this)>mTime) 
		return false;
	return true;
}


bool MeetingTime::operator<(const MeetingTime& mTime) const {
	int argStartHour =  mTime.getStartHour();
	int argStartMints = mTime.getStartMints();
	int argEndHour =  mTime.getEndHour();
	int argEndMints = mTime.getEndMints();
	/* my endTime must occur before his startTime
	(exceptional condition: his startTime != his endTime (i.e. nTime is an
	interval and not a point of time...) */
	if(m_eHour < argStartHour || 
		(m_eHour==argStartHour && m_eMints < argStartMints) || 
		((m_eHour==argStartHour && m_eMints == argStartMints) &&
		!((argStartHour == argEndHour) && (argStartMints == argEndMints)) &&
		!((m_eHour == m_sHour) && (m_eMints == m_sMints))))
		return true;
	return false; 
}


bool MeetingTime::operator>(const MeetingTime& mTime) const  {
	int argEndHour = mTime.getEndHour();	
	int argEndMints = mTime.getEndMints();
	int argStartHour =  mTime.getStartHour();
	int argStartMints = mTime.getStartMints();
	/* his endTime must occur before my startTime
	(exceptional condition: his startTime != his endTime (i.e. nTime is an
	interval and not a point of time...) */
	if ((argEndHour < m_sHour) || 
		(argEndHour == m_sHour && argEndMints < m_sMints) ||
		((argEndHour == m_sHour && argEndMints == m_sMints) &&
		!((argStartHour == argEndHour) && (argStartMints == argEndMints)) &&
		!((m_eHour == m_sHour) && (m_eMints == m_sMints))))
		return true;
	return false;
}


// for printing the time interval
ostream& operator<< (ostream& os, const MeetingTime& MeetingTime)
{
	os.fill('0');
	os	<< setw(2) << right << MeetingTime.getStartHour() << ":"  
		<<  setw(2) << right << MeetingTime.getStartMints()
		<<	'-'
		<<  setw(2) << right << MeetingTime.getEndHour()  << ":" 
		<<  setw(2) << right << MeetingTime.getEndMints();
	return os;
}