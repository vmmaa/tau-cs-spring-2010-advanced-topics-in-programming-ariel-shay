/******************************************************************************
 * Exercise 06 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Meeting Source File.
 *****************************************************************************/

#include "stdafx.h"
#include "Meeting.h"

// CTOR:
Meeting::Meeting(int day, int startHour, int startMins, int endHour, int endMins, string subject, int workersNum, string workers[]):
	m_day(day),
	m_meetingTime(MeetingTime(startHour,startMins,endHour,endMins)),
	m_subject(subject)
	{ 
		for (int i = 0; i < workersNum; i++)
		{
			m_workers.push_back(workers[i]);
		}
	};
		
// Factory for creating a new meeting.
Meeting* Meeting::factory(int day, int startHour, int startMins, int endHour, int endMins,
						  string subject, int workersNum, string workers[]) 
{
    Meeting* meeting = new Meeting(day, startHour, startMins, endHour, endMins, subject, workersNum, workers);
	return meeting;
}

// Operators:
ostream& operator<<(ostream& output, const Meeting& meeting)
{
	output	<< setw(15) << left << meeting.getMeetingTime() << "  ";
	output.fill(' ');
	output	<< setw(20) << left << meeting.getSubject();
	int curr_len = 0;
	for (int i=0; i<meeting.getWorkers().size(); i++){
		string worker = meeting.getWorkers()[i];
		curr_len += worker.size();
		if (curr_len >= 35){
			// go down a line and move to participants column
			output	<< endl	<< setw(35) << left << "";
			curr_len = 0;
		}
		output << left << worker << " ";
	}
	output << endl;

	return output;
}

// returns true iff the right hand side meeting is on an overlapping time of this meeting
bool Meeting::operator==(const Meeting& meeting) const
{
	return m_meetingTime.isOverlapping(meeting.getMeetingTime());
}
