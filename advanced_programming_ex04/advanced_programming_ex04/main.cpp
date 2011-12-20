/******************************************************************************
 * Exercise 04 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * tContainer_t - Header File.
 *****************************************************************************/

#include "stdafx.h"
#include "tContainer_t.h"
#include <iostream>

int main(void)
{
	// Operator +=.
	// Memory leaks - not offical.
	
	// Initialize Variables.
	int *a = new int(1);
	int *b = new int(2);
	int *c = new int(3);
	int *d = new int(4);
	int *e = new int(5);
	int *f = new int(6);
	int *a1 = new int(7);
	int *b1 = new int(8);
	tContainer_t<int, vector<int*>> container1;
	tContainer_t<int, list<int*>>   container2;
	tContainer_t<int, vector<int*>> container3;

	// 1. isEmpty and insert.
	cout << "TEST #1 - isEmpty() and insert()." << endl;
	cout << "QUERY: Is container1 empty? " << (container1.isEmpty() ? "TRUE" : "FALSE") << endl;
	cout << "QUERY: Is container2 empty? " << (container2.isEmpty() ? "TRUE" : "FALSE") << endl;
	cout << "ACTION: Inserting elements to both containers." << endl;
	container1.insert(a);
	container1.insert(b);
	container1.insert(c);
	container2.insert(d);
	container2.insert(e);
	container2.insert(f);
	cout << "QUERY: Is container1 empty? " << (container1.isEmpty() ? "TRUE" : "FALSE") << endl;
	cout << "QUERY: Is container2 empty? " << (container2.isEmpty() ? "TRUE" : "FALSE") << endl;
	cout << endl;

	// 2. Queries (size, first, last).
	cout << "TEST #2 - getLength(), getFirst() and getLast()." << endl;
	cout << "QUERY: Size of container1 (should be 3): " << container1.getLength() << endl;
	cout << "QUERY: Size of container2 (should be 3): " << container1.getLength() << endl;
	cout << "QUERY: First of container1 (should be 1): " << *container1.getFirst() << endl;
	cout << "QUERY: First of container2 (should be 4): " << *container2.getFirst() << endl;
	cout << "QUERY: Last of container1 (should be 3): " << *container1.getLast() << endl;
	cout << "QUERY: Last of container2 (should be 6): " << *container2.getLast() << endl;
	cout << endl;

	// 3. [] Operator.
	cout << "TEST #3 - [] Operator." << endl;
	cout << "QUERY: Index 0 at container1 (should be 1): " << *container1[0] << endl;
	cout << "QUERY: Index 3 at container2 (should be 6): " << *container2[0] << endl;
	cout << "QUERY: Index 4 at container2 (should throw exception): ";
	try { cout << *container2[4]; } 
	catch (exception ex) { cout << "Out of bounds." << endl; }
	cout << "QUERY: Index -1 at container1 (should throw exception): ";
	try { cout << *container1[-1]; } 
	catch (exception ex) { cout << "Out of bounds." << endl; }
	cout << endl;

	// 4. Find.
	cout << "TEST #4 - Find." << endl;
	cout << "ACTION: Find value 1 at container1 (should be 1): " << *container1.find(1) << endl;
	cout << "ACTION: Find value 4 at container1 (should be NULL): " << container1.find(4) << endl;
	cout << "ACTION: Find value 1 at container2 (should be NULL): " << container2.find(1) << endl;
	cout << "ACTION: Find value 4 at container2 (should be 4): " << *container2.find(4) << endl;
	cout << endl;

	// 5. Remove.
	cout << "TEST #5 - Remove." << endl;
	cout << "ACTION: Remove value 1 at container1 (should be 1): " << *container1.remove(1) << endl;
	cout << "QUERY: Check value at index 0 (was 1, now should be 2): " << *container1[0] << endl;
	cout << "QUERY: Check new size (should be 2): " << container1.getLength() << endl;
	cout << "QUERY: Check that the removed value wasn't destroyed (should be 1): " << *a << endl;
	cout << "ACTION: Remove value 1 at container2 (should be NULL): " << container1.remove(1) << endl;
	cout << endl;

	// 6. RemoveAll.
	cout << "TEST #6 - RemoveAll." << endl;
	cout << "ACTION: Remove all elements from container1." << endl;
	container1.removeAll();
	cout << "QUERY: Check if container1 is empty: " << (container1.isEmpty() ? "TRUE" : "FALSE") << endl;
	cout << "QUERY: Check that b retained its value outside of container1 (should be 2): " << *b << endl;
	cout << "QUERY: Check that c retained its value outside of container1 (should be 3): " << *c << endl;
	cout << "ACTION: Refilling container1." << endl;
	container1.insert(a);
	container1.insert(b);
	container1.insert(c);
	cout << endl;

	// 7. RemoveAndDelete.
	cout << "TEST #7 - RemoveAndDelete." << endl;
	cout << "ACTION: Delete 3 (c) from container1." << endl;
	cout << "ACTION: Delete 6 (f) from container2." << endl;
	container1.removeAndDelete(3);
	container2.removeAndDelete(6);
	cout << "QUERY: Check that c is garbage (was 3): " << *c << endl;
	cout << "QUERY: Check that f is garbage (was 6):  " << *f << endl;
	cout << "QUERY: Check new size of container1 (should be 2): " << container1.getLength() << endl;
	cout << "QUERY: Check new size of container2 (should be 2): " << container1.getLength() << endl;
	cout << endl;

	// 8. += Operator.
	cout << "TEST #8 - += Operator." << endl;
	cout << "ACTION: Add a1 (7) and b1 (8) to container." << endl;
	container3.insert(a1);
	container3.insert(b1);
	cout << "ACTION: Merge container3 into container1." << endl;
	container1 += container3;
	cout << "QUERY: Check new size of container3 (should be 0): " << container3.getLength() << endl;
	cout << "QUERY: Check new size of container1 (should be 4): " << container1.getLength() << endl;
	cout << "QUERY: Value at index 0 of container1 (should be 1): " << *container1[0] << endl;
	cout << "QUERY: Value at index 1 of container1 (should be 2): " << *container1[1] << endl;
	cout << "QUERY: Value at index 2 of container1 (should be 7): " << *container1[2] << endl;
	cout << "QUERY: Value at index 3 of container1 (should be 8): " << *container1[3] << endl;
	cout << endl;

	cout << "TESTS COMPLETED!" << endl;

	// End (c and f were already deleted).
	delete a;
	delete b;
	delete d;
	delete e;
	delete a1;
	delete b1;
	getchar();

	return 0;
}

