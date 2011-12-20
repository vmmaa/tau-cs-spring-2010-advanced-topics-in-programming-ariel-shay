/******************************************************************************
 * Exercise 02 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * cDate_t Class Header File.
 *****************************************************************************/

#pragma once
#include <time.h>
#include <iostream>
using namespace std;

class cDate_t{
public:
	// CTORs, DTORs
	cDate_t(void);										// default CTOR
	cDate_t(int pi_day, int pi_month, int pi_year);		// CTOR with parameters
	cDate_t(const cDate_t& pi_date);					// copy CTOR
	~cDate_t(void);										// default DTOR

	// Operators:
	const cDate_t& operator=(const cDate_t& pi_date);

	// Methods:
	// getters and non-modifying methods:
	inline int getDay() const;
	inline int getMonth() const;
	inline int getYear() const;
	inline bool isLeapYear() const;
	
	int getDayOfYear() const;
	std::string getNameOfDay() const;
	std::string getNameOfMonth() const;
	void printDate() const;

	// setters:
	int setDateFormat(int pi_format);
	int	setDate(int pi_day, int pi_month, int pi_year);

protected:
	// static members
	static const std::string sm_DAY_NAMES[7];
	static const std::string sm_MONTH_NAMES[12];
	static const int sm_MONTH_NUM_OF_DAYS[2][12];
	static int sm_format;

	// dynamic members
	int		m_day, m_month, m_year;
	int		m_leapYear;

	// protected functions
	static cDate_t getNextDay(int pi_day, int pi_month, int pi_year, int pi_leapYear);	// for bonus

private:
	// private static members
	static const int sm_MAX_YEAR;

	// private functions
	bool isDateValid(const int, const int, const int);
	void setDateByCurrentTime();
	int isLeap(int) const;
};