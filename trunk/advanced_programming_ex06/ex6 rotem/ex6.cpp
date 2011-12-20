/*******************************************************************
*	File name:		ex6.cpp
*	Description:	Testing for diary application
*					Testing the functionality of :
*					MeetingTime, Meeting, Day_t and Diary				
*	
*	Authors:		Rotem Druker	(I.D. 021793708)
*					Rotem Shaul		(I.D. 300923661)
*
*	Date:			29/5/2010
*******************************************************************/

#include "stdafx.h"
#include "Diary.h"

int _tmain(int argc, _TCHAR* argv[])
{
	///////////////////////
	// Testing MeetingTime
	///////////////////////
	MeetingTime time1(16,30, 17, 30);
	MeetingTime time2(16,0, 16, 50);
	MeetingTime time3(17, 0, 17, 30);
	MeetingTime time4(16,0, 16,30);
	MeetingTime time3a(17,30, 17,30);
	MeetingTime time3b(17,0, 17,0);
	cout << ((time3 == time3a) ? "t3 = t3a - v" : "t3 != 3a - x") << endl;
	cout << ((time3 == time3b) ? "t3 = t3b - v" : "t3 != 3b - x") << endl;

	cout << time1 << endl;
	cout << time2 << endl;
	cout << ((time1 == time2) ? "t1 = t2 - v" : "t1 != t2 - x") << endl;
	cout << ((time1 == time3) ? "t1 = t3 - v" : "t1 != t3 - x") << endl;
	cout << ((time1 == time4) ? "t1 = t4 - x" : "t1 != t4 - v") << endl;
	cout << ((time1 > time4) ? "t1 > t4 - v" : "t1 !> t4 - x") << endl;
	cout << ((time4 < time1) ? "t4 < t1 - v" : "t4 <! t1 - x") << endl;
	cout << ((time2 < time3) ? "t2 < t3 - v" : "t2 !< t3 - x") << endl;
	cout << ((time3 > time2) ? "t3 > t2 - v" : "t3 !> t2 - x") << endl;

	///////////////////////
	// Testing Meeting
	///////////////////////
	Meeting m1(time1, "First meeting");
	Meeting m2(time2, "Second meeting", 3, "Yossi", "Rita", "Giald");
	Meeting m4(time4, "Fourth meeting", 2, "Rotem", "Irit");
	cout << m1 << endl;
	cout << m2 << endl;
	cout << ((m1 == m2) ? "m1 = m2 - v" : "m1 != m2 - x") << endl;

	///////////////////////
	// Testing Day
	///////////////////////
	Day_t d1("Sunday");
	d1.AddMeeting(&m1);
	cout << "with m1: " << endl;
	cout << d1 << endl;
	d1.AddMeeting(&m2);
	cout << "with m1 after failing to add m2: " << endl;
	cout << d1 << endl;
	d1.AddMeeting(&m4);
	cout << "with m1 and m4: " << endl;
	cout << d1 << endl;	
	m4.ChangeMeetingTime(time3);
	cout << "after failing to change m4 to time of t3: " << endl;
	cout << m4 << endl;
	m1.ChangeMeetingTime(time3);
	cout << "after changing m1 to time of t3: " << endl;
	cout << d1 << endl;	
	d1.DeleteMeeting(&m1);
	cout << "after deleting m1: " << endl;
	cout << d1 << endl;	
	d1.AddMeeting(&m2);
	cout << "after failing to add m2: " << endl;
	cout << d1 << endl;	
	m4.ChangeMeetingTime(time3);
	cout << "after changing m4 to time of t3: " << endl;
	cout << d1 << endl;
	d1.AddMeeting(&m2);
	cout << "after adding m2: " << endl;
	cout << d1 << endl;	

	MeetingTime time5(16,30, 16,45);
	MeetingTime time6(17,15, 18,00);
	d1.CopyMeeting(time5, time6);
	cout << "after trying to move m2 to overlap with m4: " << endl;
	cout << d1 << endl;	
	d1.CopyMeeting(time5, time4);
	cout << "after trying to move m2 to an earlier time: " << endl;
	cout << d1 << endl;	

	Meeting* m5 = d1.FindMeetringByStartTime(16, 15);
	cout << "meeting at	16:15 is: " << endl;
	if (m5)
	{
		cout << *m5 << endl;	
	}
	else
	{
		cout << "N/A" << endl;
	}

	m5 = d1.FindMeetringByStartTime(17, 35);
	cout << "meeting at	17:35 is: " << endl;
	if (m5)
	{
		cout << *m5 << endl;	
	}
	else
	{
		cout << "N/A" << endl;
	}

	m5 = d1.FindMeetringByStartTime(16, 30);
	cout << "meeting at	16:30 is: " << endl;
	if (m5)
	{
		cout << *m5 << endl;	
	}
	else
	{
		cout << "N/A" << endl;
	}

	m5 = d1.FindMeetringByStartTime(17, 0);
	cout << "meeting at	17:00 is: " << endl;
	if (m5)
	{
		cout << *m5 << endl;	
	}
	else
	{
		cout << "N/A" << endl;
	}

	d1.DeleteMeeting(&m1);
	cout << "after trying to delete m1 (which is not scheduled): " << endl;
	cout << d1 << endl;	
	d1.DeleteMeeting(&m4);
	cout << "after deleting m4: " << endl;
	cout << d1 << endl;	
	d1.DeleteMeeting(&m2);
	cout << "after deleting m2 (day should be empty): " << endl;
	cout << d1 << endl;	

	///////////////////////
	// Testing Diary
	///////////////////////
	Diary& diary = Diary::GetObj();
	MeetingTime t1(12,30, 14, 30);
	MeetingTime t2(16,0, 16, 40);
	MeetingTime t3(16,0, 16,30);
	MeetingTime t4(16, 30, 17, 0);
	MeetingTime t5(17, 0, 18, 0);
	MeetingTime t6(18, 30, 19, 0);
	// t1 < t2, t2==t3, t2==t4, t3 < t4, r4 < t5, t5 < t6

	Meeting mt1(t1, "meeting 1");
	mt1.AddParticipant("Rotem");
	mt1.AddParticipant("Yossi");
	Meeting mt2(t2, "meeting 2", 3, "Yossi", "Rita", "Giald");
	Meeting mt3(t3, "meeting 3", 2, "Rotem", "Irit");
	Meeting mt4(t4, "meeting 4");
	Meeting mt5(t5, "meeting 5", 4, "Yossi", "Rita", "Giald", "Obama");
	Meeting mt6(t6, "meeting 6", 1, "Rotem");

	diary.AddMeeting(&mt1, 1);	// m1 on Sunday
	diary.AddMeeting(&mt2, 2);	// m2 on Monday
	cout << "Diary after adding mt1 and mt2: " << endl;
	cout << diary << endl;
	diary.AddMeeting(&mt3, 2);	// m3 overlaps with m2
	cout << "Diary after trying to add mt3 which overlaps with mt2: " << endl;
	cout << diary << endl;
	diary.AddMeeting(&mt3, 7);	// m3 can't be in Saturday
	cout << "Diary after trying to add mt3 on Saturday: " << endl;
	cout << diary << endl;
	diary.CopyMeeting(t2, 2, t3, 6);
	cout << "Diary after trying to reschedule mt2 on Friday: " << endl;
	cout << diary << endl;
	diary.CopyMeeting(t2, 2, t3, 4);
	cout << "Diary after rescheduling mt2 on Wednesday: " << endl;
	cout << diary << endl;
	diary.AddMeeting(&mt3, 3);
	cout << "Diary after adding mt3 on Tuesday: " << endl;
	cout << diary << endl;
	diary.CopyMeeting(t3, 4, t2, 4);
	cout << "Diary after rescheduling mt2 to its' original hour, but still on Wednesday: "
		<< endl;
	cout << diary << endl;
	diary.CopyMeeting(t3, 3, t3, 4);
	cout << "Diary after failing to reschedule mt3 to Wednesday (overlap with mt2): "
		<< endl;
	cout << diary << endl;
	diary.DeleteMeeting(3, 16, 15);
	cout << "Diary after deleting meeting on Tuesday 16:15:" << endl;
	cout << diary << endl;
	diary.AddMeeting(&mt3, 3);	// adding back mt3
	cout << "Diary after adding deleted mt3:" << endl;
	cout << diary << endl;
	diary.DeleteMeeting(3, 16, 0);
	cout << "Diary after deleting meeting on Tuesday 16:00:" << endl;
	cout << diary << endl;
	diary.AddMeeting(&mt3, 3);	// adding back mt3
	cout << "Diary after adding deleted mt3:" << endl;
	cout << diary << endl;
	diary.DeleteMeeting(3, 16, 30);
	cout << "Diary after deleting meeting on Tuesday 16:30:" << endl;
	cout << diary << endl;
	diary.AddMeeting(&mt3, 3);	// adding back mt3
	diary.DeleteMeeting(3, 16, 31);
	cout << "Diary after trying to delete meeting on Tuesday 16:31:" << endl;
	cout << diary << endl;
	diary.DeleteMeeting(1, 16, 15);
	cout << "Diary after trying to delete meeting on Sunday 16:15:" << endl;
	cout << diary << endl;
	diary.DeleteMeeting(&mt2);
	cout << "Diary after deleting mt2:" << endl;
	cout << diary << endl;
	diary.DeleteMeeting(&mt4);
	cout << "Diary after trying to delete mt4:" << endl;
	cout << diary << endl;
	mt1.AddParticipant("Obama");
	cout << "Diary after adding Obama to mt1:" << endl;
	cout << diary << endl;
	return 0;
}

