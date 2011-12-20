/******************************************************************************
 * Exercise 02 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * cDate_t Class Source File.
 *****************************************************************************/

#include "stdafx.h"
#include "cDate_t.h"

/*************************************************************
*	Assumptions:
*	- valid years are in range 0 < year < 10000 (sm_MAX_YEAR)
*************************************************************/

/**********************
*	static members
**********************/
// static constant date information
const std::string cDate_t::sm_DAY_NAMES[7] =	
				  {"Sunday", "Monday", "Tuesday", "Wednesday",
				   "Thursday", "Friday", "Saturday"};
const std::string cDate_t::sm_MONTH_NAMES[12] =	
				  {"January", "February", "March", "April", "May", "June",
				   "July", "August", "September", "October", "November", "December"};
const int cDate_t::sm_MONTH_NUM_OF_DAYS[2][12] = {
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
const int cDate_t::sm_MAX_YEAR = 10000;

// static modifiable members
int cDate_t::sm_format = 1;

/*******************
*	CTORs, DTORs
*******************/

/**
default CTOR
creates a new cDate_t object initialized to current date (day, month, year)
**/
cDate_t::cDate_t(void){
	setDateByCurrentTime();
};

/**
CTOR with date parameters
creates a new cDate_t object initialized to a given date (day, month, year)
if any of the parameters is illegal, will create default date object
**/
cDate_t::cDate_t(int pi_day, int pi_month, int pi_year):
m_day(pi_day),
m_month(pi_month),
m_year(pi_year),
m_leapYear(isLeap(pi_year)) {
	// check for date validity - month and day are within range
	if (!isDateValid(pi_day, pi_month, pi_year)){
		// date not within range, create default values
		setDateByCurrentTime();
	}
};

/**
copy CTOR
copy constructor for class cDate_t
**/
cDate_t::cDate_t(const cDate_t& pi_date):
	m_day(pi_date.getDay()),
	m_month(pi_date.getMonth()),
	m_year(pi_date.getYear()),
	m_leapYear(pi_date.isLeapYear()){};

/**
default DTOR
**/
cDate_t::~cDate_t(){};

/***************
*	Operators
***************/

/**
Assignment operator
**/
const cDate_t& cDate_t::operator=(const cDate_t& pi_date){
	if (this != &pi_date){
		m_day = pi_date.getDay();
		m_month = pi_date.getMonth();
		m_year = pi_date.getYear();
		m_leapYear = pi_date.isLeapYear();
	}
	return *this;
};

/**************
*	Methods
**************/

// getters and non-modifying methods:

/**
getDay()
returns the day in the month (1-31)
**/
inline int cDate_t::getDay() const{
	return m_day;
};

/**
getMonth()
returns the month (1-12)
**/
inline int cDate_t::getMonth() const{
	return m_month;
};

/**
getYear()
returns the year
**/
inline int cDate_t::getYear() const{
	return m_year;
};

/**
isLeapYear()
return true if the year is leap and false otherwise
the condition for a leaped year is:
**/
inline bool cDate_t::isLeapYear() const{
	return (m_leapYear == 1);
};

/**
getDayOfYear()
returns the day in the year (1-365, or 1-366 in a leap year)
**/
int cDate_t::getDayOfYear() const{
	int dayInYear = 0;
	// sum all days in previous months
	for (int i=0; i<m_month-1; i++){
		dayInYear += sm_MONTH_NUM_OF_DAYS[m_leapYear][i];
	};
	dayInYear += m_day;

	return dayInYear;
};

/**
getNameOfDay()
returns the name of the day (Sunday, Monday,...)
**/
std::string cDate_t::getNameOfDay() const{
	int dayEndOfLastYear = ((m_year-1)*365 + (m_year-1)/4 -
		                   (m_year-1)/100 + (m_year-1)/400) % 7;
	int dayIndex = (dayEndOfLastYear + getDayOfYear()) % 7;
	return sm_DAY_NAMES[dayIndex];
};

/**
getNameOfMonth()
returns the name of the month (January, February,...)
**/
std::string cDate_t::getNameOfMonth() const{		// no inline use due to complexity of using std::string
	return sm_MONTH_NAMES[m_month-1];
};

/**
printDate()
prints the date according to the format (sm_format), set by setDateFormat()
**/
void cDate_t::printDate() const{
	// prepare month string for format 1
	char* mn = new char[4];
	for (int i=0; i<3; i++)
		mn[i] = sm_MONTH_NAMES[m_month-1][i];
	mn[3] = '\0';

	// calculate year 0's padding
	int yearZeroCount = 4, tmp = m_year;
	while (tmp / 10 != 0){
		yearZeroCount--;
		tmp = tmp / 10;
	}
	char* yearZerosPad = new char[yearZeroCount];
	for (int i=0; i<yearZeroCount; i++)
		yearZerosPad[i] = '0';
	yearZerosPad[yearZeroCount-1] = '\0';

	switch (sm_format){
		case 1:
			cout << (m_day < 10? "0":"") << m_day << "/" << mn;
			cout << "/" << yearZerosPad << m_year;
			break;
		case 2:
			cout << (m_day < 10? "0":"") << m_day << "/";
			cout << (m_month < 10? "0":"") << m_month << "/" << yearZerosPad << m_year;
			break;
		case 3:
			cout << (m_month < 10? "0":"") << m_month << "/";
			cout << (m_day < 10? "0":"") << m_day << "/" << yearZerosPad << m_year;
			break;
		default:
			cout << "cDate_t::printDate(): error in date print format\n";
	}

	cout << "\n";
	delete[] mn, yearZerosPad;
};

// setters:

/**
setDateformat(int pi_format)
sets the date format as following:
1 - dd/MMM/yyyy (e.g. 22/Jan/2001)
2 - dd/mm/yyyy (e.g. 22/01/2001, European)
3 - mm/dd/yyyy (e.g. 01/22/2001, American)
the default format is 1
returns 1 on success and 0 on failure (bad input - doesn't change the format)
**/
int cDate_t::setDateFormat(int pi_format){
	if (pi_format < 1 || pi_format > 3)
		return 0;
	else {
		sm_format = pi_format;
		return 1;
	}
};

/**
setDate(int pi_day, int pi_month, int pi_year)
if the given date (day, month, year) is valid, 
sets the date to the new date and returns 1
otherwise the date is not changed and returns 0
**/
int	cDate_t::setDate(int pi_day, int pi_month, int pi_year){
	if (isDateValid(pi_day, pi_month, pi_year)){
		m_day = pi_day;
		m_month = pi_month;
		m_year = pi_year;
		m_leapYear = isLeap(m_year);
		return 1;
	} else return 0;
};

/*************************
*	protected functions
*************************/

/**
getNextDay(int pi_day, int pi_month, int pi_year, int pi_leapYear)
returns reference to a new date of the following day to this
**/
cDate_t cDate_t::getNextDay(int pi_day, int pi_month, int pi_year, int pi_leapYear){
	if (pi_day == cDate_t::sm_MONTH_NUM_OF_DAYS[pi_leapYear][pi_month-1]){	// end of month
		pi_day = 1;
		if (pi_month == 12){ // end of year
			pi_month = 1;
			pi_year++; // the only time year can get to 10,000
		} else {
			pi_month++;
		}
	} else {
		pi_day++;
	}

	// create date object and return result
	//cDate_t res = new cDate_t(pi_day, pi_month, pi_year);
	//return *res;
	cDate_t res = cDate_t(pi_day, pi_month, pi_year);
	return res;
};

/***********************
*	private functions
***********************/

/**
isDateValid()
returns true if the day is valid in the given month, 
the month is valid and the year is in range
**/
bool cDate_t::isDateValid(const int pi_day, const int pi_month, const int pi_year){
	int nLeapYear = isLeap(pi_year);
	return (pi_month >= 1 && pi_month <= 12 &&
			pi_day >= 1 && 
			pi_day <= sm_MONTH_NUM_OF_DAYS[nLeapYear][pi_month - 1] &&
			pi_year > 0 && pi_year < sm_MAX_YEAR);
};

/**
setDateByCurrentTime()
sets the date (day, month, year) according to the current time and date
using <time.h>
**/
void cDate_t::setDateByCurrentTime(){
	// initialize current date (and time)
	time_t		time_date;
	struct tm*	current_time;
	time_date = time(0);
	current_time = localtime(&time_date);

	// set date members
	m_day = current_time->tm_mday;
	m_month = current_time->tm_mon + 1;
	m_year = current_time->tm_year + 1900;
	m_leapYear = isLeap(m_year);
};

/**
isLeap(int pi_year)
returns 1 if the year is leaped and 0 otherwise
**/
int cDate_t::isLeap(int pi_year) const{
	return ((((pi_year % 4 == 0) && (pi_year % 100 != 0)) || (pi_year % 400 == 0)) ? 1 : 0);
};