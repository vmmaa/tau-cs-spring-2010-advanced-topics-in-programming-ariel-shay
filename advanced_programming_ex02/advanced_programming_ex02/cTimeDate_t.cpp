/******************************************************************************
 * Exercise 02 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * cTimeDate_t Class Source File.
 *****************************************************************************/

#include "stdafx.h"
#include "cTimeDate_t.h"

/*******************
*	CTORs, DTORs
*******************/

/**
default CTOR
creates a new cTimeDate_t object initialized to current local time and date
**/
cTimeDate_t::cTimeDate_t(void):
	cTime_t(),
	cDate_t(){};

/**
CTOR with time and date parameters
creates a new cTimeDate_t object initialized to a given time and date (seconds, minutes, hours, day, month, year)
if any of the parameters of time or date is illegal, will create default time or date object correspondly
**/
cTimeDate_t::cTimeDate_t(int pi_second, int pi_minute, int pi_hour, int pi_day, int pi_month, int pi_year):
	cTime_t(pi_second,pi_minute,pi_hour),
	cDate_t(pi_day,pi_month,pi_year){};

/**
copy CTOR
copy constructor for class cTimeDate_t
**/
cTimeDate_t::cTimeDate_t(const cTimeDate_t& pi_time_date){
	m_second = pi_time_date.getSecond();
	m_minute = pi_time_date.getMinute();
	m_hour = pi_time_date.getHour();
	m_day = pi_time_date.getDay();
	m_month = pi_time_date.getMonth();
	m_year = pi_time_date.getYear();
	m_leapYear = pi_time_date.isLeapYear();
};

/**
default DTOR
**/
cTimeDate_t::~cTimeDate_t(){};

/***************
*	Operators
***************/

/**
Assignment operator
**/
const cTimeDate_t& cTimeDate_t::operator=(const cTimeDate_t& pi_time_date){
	if (this != &pi_time_date){
		m_second = pi_time_date.getSecond();
		m_minute = pi_time_date.getMinute();
		m_hour   = pi_time_date.getHour();
		m_day = pi_time_date.getDay();
		m_month = pi_time_date.getMonth();
		m_year = pi_time_date.getYear();
		m_leapYear = pi_time_date.isLeapYear();
	}
	return *this;
};

/**
Addition operator with a new time object (BONUS SECTION).
**/
cTimeDate_t cTimeDate_t::operator + (const cTime_t & pi_time)
{
	cDate_t day;
	int second = this->m_second + pi_time.getSecond();
	int minute = this->m_minute + pi_time.getMinute();
	int hour   = this->m_hour + pi_time.getHour();

	if (second > 59)
	{
		second -= 60;
		minute++;
	}
	if (minute > 59)
	{
		minute -= 60;
		hour++;
	}
	if (hour > 23)
	{
		hour -= 24;
		day = cDate_t::getNextDay(this->m_day,this->m_month,this->m_year,this->m_leapYear);
	}
	else 
	{
		day.setDate(this->m_day, this->m_month, this->m_year);
	}
	
	cTimeDate_t result(second, minute, hour,
		               day.getDay(), day.getMonth(), day.getYear());

	return result;
}
