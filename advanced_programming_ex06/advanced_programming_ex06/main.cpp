/******************************************************************************
 * Exercise 06 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Tests Program.
 *****************************************************************************/

#include "stdafx.h"
#include "Diary.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;

Diary* Diary::sngPtr;

int main(void)
{
	// Create singleton diary.
	cout << "Creating single Diary" << endl;
	Diary *d = Diary::createDiary();

	// Creates four meetings. Workers are given by their ID number (int from 0 to 9).
	string people1[] = {"Shay", "Rami", "Prosper", "Elena", "Moshe 1", "Moshe 2", "Moshe 3", "Moshe4", "Moshe 5", "Moshe 6"};
	string people2[] = {"Bublik", "Shay"};
	string people3[] = {"Ariel", "Simon", "Zelda"};
	string people4[] = {"Rami", "Bublik", "Obama"};
	Meeting* meetingA = Meeting::factory(1, 10, 20, 12, 40, "Meeting", 10, people1);
	Meeting* meetingA2 = Meeting::factory(1, 13, 17, 18, 0, "Another Meeting", 10, people1);
	Meeting* meetingA3 = Meeting::factory(1, 8, 00, 8, 30, "First Meeting", 10, people1);
	Meeting* meetingB = Meeting::factory(2, 11, 15, 13, 0, "Potatoes", 2, people2);
	Meeting* meetingC = Meeting::factory(4, 0, 5,  20, 30, "Nachoes", 3, people3);
	Meeting* meetingD = Meeting::factory(5, 2, 45,  4, 50, "Computers", 3, people4);

	// Adding meetings.
	d->addMeeting(meetingA);
	d->addMeeting(meetingA2);
	d->addMeeting(meetingA3);
	d->addMeeting(meetingB);
	d->addMeeting(meetingC);
	d->addMeeting(meetingD);

	// Printing diary after first addition.
	cout << "TEST #1: Added 6 normal meetings and printing them." << endl << endl;
	d->print();

	// Erasing one meeting.
	cout << "TEST #2: Erase one meeting" << endl << endl;
	d->removeMeeting(meetingA);
	d->print();

	// Find a meeting.
	cout << "TEST #3: finding a meeting which doesn't exists." << endl;
	Meeting* meetingE = d->findMeeting(3, 8, 20);
	cout << "Finding meeting on Tuesday at 8, should return 0 (null): " << meetingE << endl << endl;
	Meeting* meetingF = d->findMeeting(2, 12, 10);
	cout << "TEST #4: finding a meeting that do exist." << endl;
	cout << "Finding meeting on Monday at 12:10, should return meeting: " << endl << (*meetingF) << endl << endl;

	// Change meeting.
	cout << "TEST #5: changing meeting to an illegal new day and time." << endl;
	d->moveMeeting(meetingB, 3, 23, 10);
	d->print();

	cout << "TEST #6: changing meeting to a new legal day and time." << endl;
	d->moveMeeting(meetingB, 3, 10, 40);
	d->print();

	// Trying to add a meeting with crossing schedule.
	Meeting* meetingG = Meeting::factory(5, 3, 25, 8, 10, "Meeting2", 4, people1); 
	cout << "TEST #7: trying to add a meeting with crossing schedule." << endl;
	d->addMeeting(meetingG);

	// Destruction.
	Diary::Destroy();
	delete meetingA;
	delete meetingA2;
	delete meetingA3;
	delete meetingB;
	delete meetingC;
	delete meetingD;
	delete meetingE;
	delete meetingG;

	getchar();
	return 0;
}