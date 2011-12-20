/******************************************************************************
 * Exercise 06 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Diary Header File.
 *****************************************************************************/

#pragma once
#include <vector>
#include <string>
#include <strstream>
#include <iostream>
#include <iomanip>
#include "Day.h"
#include "Meeting.h"
#include "MeetingTime.h"
using namespace std;

// Diary Class - Using Singleton Design Pattern.
class Diary
{ 
	public: 
		// Static Singleton Creation/Destruction:
		static Diary* createDiary() { 
			if (sngPtr == 0) { 
				sngPtr = new Diary();
			} 
			return sngPtr;
		}
		static void Destroy() { delete sngPtr; sngPtr = 0; }

		// Methods:
		virtual int  addMeeting(Meeting* meeting);
		virtual void removeMeeting(const Meeting* meeting);
		virtual void moveMeeting(Meeting* meeting, int newDay, int newHour, int newMins);
		virtual Meeting* findMeeting(int day, int hour, int mins) const;
		virtual void print(void) const;

	protected: 
		// Virtual DTOR:
		virtual ~Diary(void) { m_days.clear(); }

		// Members:
		 vector<Day*> m_days;

		// Singleton Pointer:
		static Diary* sngPtr; 

		// Copy prevention and private CTOR:
		Diary();
		Diary(const Diary&);
		void operator=(Diary&);
}; 
