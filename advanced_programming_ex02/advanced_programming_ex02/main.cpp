/******************************************************************************
 * Exercise 02 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Main Test File.
 *****************************************************************************/

#include "stdafx.h"
//#include "cTime_t.h"
//#include "cDate_t.h"
#include "cTimeDate_t.h"
#include <iostream>
#include <string>
using namespace std;

/*************************** MAIN TEST PROGRAM *******************************/
int _tmain(int argc, _TCHAR* argv[])
{
	/*******************
	*	cDate_t TESTS	
	*******************/
	cout << "DATE TESTS\n";

	// Initialize test variables
	cDate_t date1;
	cDate_t date2(14,8,1984);
	cDate_t date3 = date1;

	// Tests
	// Test 1: test initialization, ctors, dtors and assignment operator
	cout << "TEST 1: CTORs, DTORs, assignment operator:\n";
	cout << "initialized date1 by default CTOR, date2 by non-default CTOR and date3 by assigning him date1 - should invoke copy CTOR\n";
	cDate_t* p_date1 = &date1;
	cDate_t* p_date2 = &date2;
	cDate_t* p_date3 = &date3;
	cout << "check addresses of date1, date2, date3: " << p_date1 << ", " << p_date2 << ", " << p_date3 << "\n\n";
	
	cDate_t date4(date1);
	cDate_t* p_date4 = &date4;
	cout << "now date4 was initialized by cDate_t date4(date1) - should also invoke copy CTOR\n";
	cout << "check addresses of date1 and date4: " << p_date1 << ", " << p_date4 << "\n";
	cout << "date4: " << date4.getDay() << "/" << date4.getMonth() << "/" << date4.getYear();
	cout << ", year is leaped: " << date4.isLeapYear() << ", day: " << date4.getNameOfDay();
	cout << ", month: " << date4.getNameOfMonth()<< "\n\n";

	cDate_t date5;
	cDate_t* p_date5 = &date5;
	date5 = date1;
	cout << "now date5 was declared and then date1 was assigned into it - should invoke assignment operator\n";
	cout << "check addresses of date1 and date5: " << p_date1 << ", " << p_date5 << "\n";
	cout << "date5: " << date5.getDay() << "/" << date5.getMonth() << "/" << date5.getYear();
	cout << ", year is leaped: " << date5.isLeapYear() << ", day: " << date5.getNameOfDay();
	cout << ", month: " << date5.getNameOfMonth()<< "\n\n";

	// Test 2: test all getters
	cout << "TEST 2: test all getters:\n";
	cout << "first test all getters on date1:\n";
	cout << "date1.getDay(): " << date1.getDay() << "\n";
	cout << "date1.getMonth(): " << date1.getMonth() << "\n";
	cout << "date1.getYear(): " << date1.getYear() << "\n";
	cout << "date1.isLeapYear(): " << date1.isLeapYear() << "\n";
	cout << "date1.getNameOfDay(): " << date1.getNameOfDay() << "\n";
	cout << "date1.getNameOfMonth(): " << date1.getNameOfMonth() << "\n\n";

	cout << "date2 was defined by non default CTOR:\n";
	cout << "date2: " << date2.getDay() << "/" << date2.getMonth() << "/" << date2.getYear();
	cout << ", year is leaped: " << date2.isLeapYear() << ", day: " << date2.getNameOfDay();
	cout << ", month: " << date2.getNameOfMonth()<< "\n\n";

	cout << "date1 was assigned into date3. date3 before change:\n";
	cout << "date3: " << date3.getDay() << "/" << date3.getMonth() << "/" << date3.getYear();
	cout << ", year is leaped: " << date3.isLeapYear() << ", day: " << date3.getNameOfDay();
	cout << ", month: " << date3.getNameOfMonth()<< "\n\n";

	cout << "changing date3:\n";
	cout << "- set bad day: date3.setDate(29,2,2010): " << date3.setDate(29,2,2010) << "\n";
	cout << "- set bad day: date3.setDate(0,2,2010): " << date3.setDate(0,2,2010) << "\n";
	cout << "- set bad day: date3.setDate(70,2,2010): " << date3.setDate(70,2,2010) << "\n";
	cout << "- set bad month: date3.setDate(15,0,2010): " << date3.setDate(15,0,2010) << "\n";
	cout << "- set bad month: date3.setDate(15,13,2010): " << date3.setDate(15,13,2010) << "\n";
	cout << "- set bad year: date3.setDate(15,2,0): " << date3.setDate(15,2,0) << "\n";
	cout << "- set bad year: date3.setDate(15,2,10000): " << date3.setDate(15,2,10000) << "\n";
	cout << "- set bad year: date3.setDate(15,2,9999999): " << date3.setDate(15,2,9999999) << "\n";
	cout << "- set good date: date3.setDate(9,2,987): " << date3.setDate(9,2,987) << "\n\n";

	cout << "check date3 after change:\n";
	cout << "date3: " << date3.getDay() << "/" << date3.getMonth() << "/" << date3.getYear();
	cout << ", year is leaped: " << date3.isLeapYear() << ", day: " << date3.getNameOfDay();
	cout << ", month: " << date3.getNameOfMonth()<< "\n\n";

	cout << "check that date1 wasn't changed:\n";
	cout << "date1: " << date1.getDay() << "/" << date1.getMonth() << "/" << date1.getYear();
	cout << ", year is leaped: " << date1.isLeapYear() << ", day: " << date1.getNameOfDay();
	cout << ", month: " << date1.getNameOfMonth()<< "\n\n";

	// Test 3: print function
	cout << "TEST 3: check print function and format setter:\n";
	cout << "print function:\n";
	date1.printDate(); cout << "\n"; date2.printDate(); date3.printDate(); cout << "\n";
	cout << "set format to 2:\n";
	cout << "date1.setDateFormat(2): " << date1.setDateFormat(2) << "\n";
	date1.printDate(); cout << "\n"; date2.printDate(); date3.printDate(); cout << "\n";
	cout << "set format to 3:\n";
	cout << "date2.setDateFormat(3): " << date2.setDateFormat(3) << "\n";
	date1.printDate(); cout << "\n"; date2.printDate(); date3.printDate(); cout << "\n";
	cout << "set format to 13:\n";
	cout << "date3.setDateFormat(13): " << date3.setDateFormat(13) << "\n";

	// Deallocate memory and end test program
	cout << "dealocating all date variables...\n";

	cout << "Press enter to continue\n";
	getchar();

	/*******************
	*	cTime_t TESTS	
	*******************/
	cout << "TIME TESTS\n";

    // Initialize test variables.
	cTime_t time1;
	cTime_t time2(50,10,0);
	cTime_t time3 = time2;
	cTime_t time4(100,70,10); // invalid, will set to current time.

    // Test 1: Test constructors.
	cout << "TEST #1, Constructors and printing:\n";
	cout << "time1 is current time: ";
	time1.printTime();
	cout << "time2 is 00:10:50: ";
	time2.printTime();
	cout << "time3 is copy-constructed from time2: ";
	time3.printTime();
	cout << "time4 is invalid, thus set as current time: ";
	time4.printTime();

	// Test 2: Test format printing and that copy constructor worked.
	cout << "\nTEST #2, Set printing format to 2, set time and copy consturctor validation:\n";
	time1.setTimeFormat(2);
	time2.setTime(12,12,13);
	time3.setTime(100,12,12); // invalid time, thus will not change.
	time4.setTime(-1,12,12); // invalid time, thus will not change.
	cout << "time1 remains the same: ";
	time1.printTime();
	cout << "time2 becomes 13:12:12: ";
	time2.printTime();
	cout << "time3 gets invalid time, thus will not change: ";
	time3.printTime();
	cout << "time4 gets invalid time, thus will not change: ";
	time4.printTime();

	// Test 3: Getters.
	cout << "\nTEST #3, Getters:\n";
	cout << "Hour of time1: " << time1.getHour() << "\n";
	cout << "Minute of time1: " << time1.getMinute() << "\n";
	cout << "Second of time1: " << time1.getSecond() << "\n";

	// Test 4: More setTime checks.
	cout << "\nTEST #4, setTime checks and printouts.\n";
	time1.setTime(10,10,1);
	time2.setTime(10,10,12);
	time3.setTime(10,10,22);
	time4.setTime(10,10,24);
	cout << "time1 gets 01:10:10: ";
	time1.printTime();
	cout << "time2 gets 12:10:10: ";
	time2.printTime();
	cout << "time2 gets 22:10:10: ";
	time3.printTime();
	cout << "time2 gets 24:10:10, which is invalid, thus will remain: ";
	time4.printTime();
	cout << "Changing format to 1 and 3, thought 3 is invalid thus will remain 1:\n";
	time1.setTimeFormat(1);
	time1.setTimeFormat(3); // keeps format the same.
	time1.printTime();
	time2.printTime();
	time3.printTime();
	time4.printTime();

	// Test 5 : Assignment operator.
	cout << "\nTEST #5, assignment operator. Assinging time2 into time1.\n";
	cout << "time2 originally is 12:10:10.\n";
	time1 = time2;
	cout << "time2 changed to 0:0:0 to see change is not mutual:\n";
	time2.setTime(0,0,0);
	cout << "time1 is: ";
	time1.printTime();
	cout << "time2 is: ";
	time2.printTime();

	// Test 6 : Addition operator.
	cout << "\nTEST #6, Addition operator. time3 = time1 (18:05:04) + time2 (01:01:01).\n";
	cout << "time3 before:\n";
	time3.printTime();
	cout << "adding 18:5:4 to 1:1:1: ";
	time1.setTime(4,5,18);
	time2.setTime(1,1,1);
	time3 = time1 + time2;
	cout << "time3 after:\n";
	time3.printTime();
	cout << "now after addition that makes it pass a day (10:10:10):\n";
	time4.setTime(10,10,10);
	time3 = time3 + time4;
	time3.printTime();

    // Deallocate memory and end test program.

	cout << "Press enter to continue\n";
	getchar();

	/************************
	*	cTimeDate_t TESTS	
	************************/
	cout << "TIME & DATE MUTUAL OBJECT TEST\n";

	// Initialize test variables
	cTimeDate_t time_date1;
	cTimeDate_t time_date2(15,32,23,14,8,1984);
	cTimeDate_t time_date3 = time_date2;
	cTimeDate_t time_date4(100,70,80,62,87,91827); // will be set to current time and date

	// reset print formats
	time_date1.setTimeFormat(1);
	time_date1.setDateFormat(1);

	// Tests
	
	// Test 1: Test constructors
	cout << "TEST #1, Constructors and printing:\n";
	cout << "time_date1 is current time and date:\n";
	time_date1.printTime();
	time_date1.printDate();
	cout << "time_date2 is 23:32:15, 14/8/1984:\n";
	time_date2.printTime();
	time_date2.printDate();
	cout << "time_date3 is copy-constructed from time_date2:\n";
	time_date3.printTime();
	time_date3.printDate();
	cout << "time_date4 is invalid, thus set as current time and date:\n";
	time_date4.printTime();
	time_date4.printDate();

	// Test 2: Test some of the inherited functionality
	cout << "\nTEST #2, partial inherited functionality:\n";
	cout << "cTime_t inherited methods:\n";
	cout << "time_date1.getHour(): " << time_date1.getHour() << "\n";
	cout << "time_date1.getMinute(): " << time_date1.getMinute() << "\n";
	cout << "time_date1.printTime(): "; time_date1.printTime();
	cout << "cDate_t inherited methods:\n";
	cout << "time_date1.getMonth(): " << time_date1.getMonth() << "\n";
	cout << "time_date1.isLeapYear(): " << time_date1.isLeapYear() << "\n";
	cout << "time_date1.printDate(): "; time_date1.printDate();

	// Test 3: Test the modified time addition
	cout << "\nTEST #3, modified time addition (addition operator):\n";
	cout << "\nprint time1: "; time1.printTime();
	cout << "print time_date1:\n- "; time_date1.printTime(); cout << "- "; time_date1.printDate();
	time_date1 = time_date1 + time1;
	cout << "time_date1 after addition with time1:\n- "; time_date1.printTime(); cout << "- "; time_date1.printDate();

	time1.setTime(0,0,20);
	time_date1.setTime(16,32,18);
	time_date1.setDate(28,2,2010);
	cout << "\nprint time1: "; time1.printTime();
	cout << "print time_date1:\n- "; time_date1.printTime(); cout << "- "; time_date1.printDate();
	time_date1 = time_date1 + time1;
	cout << "time_date1 after addition with time1:\n- "; time_date1.printTime(); cout << "- "; time_date1.printDate();

	time1.setTime(0,0,20);
	time_date1.setTime(16,32,18);
	time_date1.setDate(28,2,2000);
	cout << "\nprint time1: "; time1.printTime();
	cout << "print time_date1:\n- "; time_date1.printTime(); cout << "- "; time_date1.printDate();
	time_date1 = time_date1 + time1;
	cout << "time_date1 after addition with time1:\n- "; time_date1.printTime(); cout << "- "; time_date1.printDate();

	time1.setTime(1,0,0);
	time_date1.setTime(59,59,23);
	time_date1.setDate(31,12,2999);
	cout << "\nprint time1: "; time1.printTime();
	cout << "print time_date1:\n- "; time_date1.printTime(); cout << "- "; time_date1.printDate();
	time_date1 = time_date1 + time1;
	cout << "time_date1 after addition with time1:\n- "; time_date1.printTime(); cout << "- "; time_date1.printDate();

	// Deallocate memory and end test program

	cout << "\nAll tests are completed.\n";
	cout << "Press enter to continue\n";
	getchar();
    return (EXIT_SUCCESS);
}
/**************************** END MAIN TEST PROGRAM **************************/