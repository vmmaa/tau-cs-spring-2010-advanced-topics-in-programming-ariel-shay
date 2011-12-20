/******************************************************************************
 * Exercise 02 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * cTime_t Class Header File.
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace std;

// TODO: print functions as stream function or normal "print"?
// TODO: addition is done in + operator or function?

/********************** cTime_t CLASS DEFINITION *****************************/
class cTime_t
{
    public:
        // CTOR & DTOR:
            cTime_t();
			cTime_t(int second, int minute, int hour);
			cTime_t(const cTime_t & time);     
           ~cTime_t();

        // Methods:
			int  setTime(int nSecond, int nMinute, int nHour);
			inline int  getSecond() const;
			inline int  getMinute() const;
			inline int  getHour() const;
			int  setTimeFormat(int format);
			void printTime() const;

		// Operators:
			const cTime_t & operator = (const cTime_t & time);
			cTime_t operator + (const cTime_t & time);

	protected:
		// Static Class Members:
			static int sm_format;
        // Class Members:
			int m_second;
			int m_minute;
			int m_hour;       

    private:
		// Private methods:
			int isTimeValid(int second, int minute, int hour) const;
			void setCurrentTime();
 };
/******************** END cTime_c CLASS DEFINITION ***************************/