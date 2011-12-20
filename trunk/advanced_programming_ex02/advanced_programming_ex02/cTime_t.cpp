/******************************************************************************
 * Exercise 02 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * cTime_t Class Source File.
 *****************************************************************************/

#include "stdafx.h"
#include "cTime_t.h"

/********************** cTime_t CLASS IMPLEMENTATION *************************/
/****************************** CTOR & DTOR **********************************/
/* Initialize static members */
int cTime_t::sm_format = 1;

/* CTOR - Default: cTime_t();
 * Sets the time of the new cTime_t object to the current local time.
 */
cTime_t::cTime_t()
{
	setCurrentTime();
}

/* CTOR - Custom: cTime_t(int seconds, int minutes, int hours);
 * Sets the time of the new cTime_t object according to the given arguments.
 * If invalid time, set to current time.
 */
cTime_t::cTime_t(int second, int minute, int hour) 
{
	if (isTimeValid(second, minute, hour))
	{
		m_second = second;
		m_minute = minute;
		m_hour   = hour;
	}
	else
	{
		setCurrentTime();
	}
}

/* CTOR - Copy CTOR: cTime_t(const cTime_t & time);
 * Copy constructor of the cTime_t class.
 */
cTime_t::cTime_t(const cTime_t & time) :
	m_second(time.getSecond()),
	m_minute(time.getMinute()),
	m_hour(time.getHour())
{
}

/* DTOR - ~cTime_t()
 * Destructor for cTime_t objects.
 */
cTime_t::~cTime_t()
{
}

/********************************* METHODS ***********************************/
/* void setCurrentTime();
 * Sets the time of the cTime_t object to the current time.
 */
void cTime_t::setCurrentTime()
{
	time_t time_date        = time(0);
	struct tm* current_time = localtime(&time_date);

	m_second = current_time->tm_sec;
	m_minute = current_time->tm_min;
	m_hour   = current_time->tm_hour;
}

/* int setTime(int nSecond, int nMinute, int nHour);
 * Sets the time of the cTime_t object according to the given arguments.
 * Returns 1 if date is valid. 0 otherwise.
 */
int cTime_t::setTime(int nSecond, int nMinute, int nHour)
{
	if (isTimeValid(nSecond, nMinute, nHour))
	{
		m_second = nSecond;
		m_minute = nMinute;
		m_hour   = nHour;
		return 1;
	}
	return 0;
}

/* int getSecond();
 * Returns the second set in the time object.
 */
inline int cTime_t::getSecond() const
{
	return m_second;
}

/* int getMinute();
 * Returns the minute set in the time object.
 */
inline int cTime_t::getMinute() const
{
	return m_minute;
}

/* int getMinute();
 * Returns the hour set in the time object.
 */
inline int cTime_t::getHour() const
{
	return m_hour;
}

/* int setTimeFormat(int format);
 * Sets the printing format (1 or 2).
 * If invalid format, keep format the same.
 */
int cTime_t::setTimeFormat(int format)
{
	if (format < 1 || format > 2)
	{
		return 0;
	}
	sm_format = format;
	return 1;
}

/* void printTime();
 * Prints the time object according to the saved format format.
 */
void cTime_t::printTime() const
{
	int  hour;
	bool am;
	if ((sm_format == 1 && m_hour < 10) ||
		(sm_format == 2 && m_hour > 0  && m_hour < 10) ||
		(sm_format == 2 && m_hour > 12 && m_hour < 22)) 
		// Pad with zero if single digit.
	{
		cout << "0";
	}

	if (sm_format != 2) // Print hour for format 1.
	{
		cout << m_hour << ":";
	}
	else // Or for format 2.
	{
		hour = (m_hour == 0) ? 12 : m_hour;
		am   = m_hour < 12;
		cout << (m_hour <= 12 ? hour : (hour - 12)) << ":";
	}

	if (m_minute < 10) // Pad with zero if single digit.
	{
		cout << "0";
	}
	cout << m_minute << ":";

	if (m_second < 10) // Pad with zero if single digit.
	{
		cout << "0";
	}

	cout << m_second;

	if (sm_format == 2)
	{
		cout << " " << (am ? "AM" : "PM");
	}

	cout << "\n";
}

/* isTimeValid(int second, int minute, int hour);
 * Checks if the time is valid (returns 1 if it is, 0 otherwise).
 */
int cTime_t::isTimeValid(int second, int minute, int hour) const
{
	if (second > 59 || minute > 59 || hour > 23 || second < 0
		|| minute < 0 || hour < 0) 
	{
		return 0;
	}
	return 1;
}

/******************************** OPERATORS **********************************/
/* Assignment Operator (=) - operator = (const cTime_t& time);
 * Sets the time of the cTime_t object according to the given arguments.
 */
const cTime_t& cTime_t::operator = (const cTime_t & time)
{
	if (this != &time)
	{
		m_second = time.getSecond();
		m_minute = time.getMinute();
		m_hour   = time.getHour();
	}
	return *this;
}

/* Addition Operator (+) - operator + (const cTime_t& time);
 * Adds into the left element the time on the right.
 */
cTime_t cTime_t::operator + (const cTime_t & time)
{
	int second = this->m_second + time.getSecond();
	int minute = this->m_minute + time.getMinute();
	int hour   = this->m_hour + time.getHour();

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
	}
	
	cTime_t result(second, minute, hour);
				   
	return result;
}
       
/******************** END cTime_c CLASS IMPLEMENTATION ***********************/


