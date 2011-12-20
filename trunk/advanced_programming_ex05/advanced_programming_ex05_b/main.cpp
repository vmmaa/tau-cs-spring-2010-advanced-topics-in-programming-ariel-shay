/******************************************************************************
 * Exercise 05 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Phone Company Program - Tests Program.
 *****************************************************************************/

#include "stdafx.h"
#include "Definitions.h"
#include "PhoneCompany.h"
#include "PhoneOwner.h"
#include <iostream>
using namespace std;

PhoneCompany* PhoneCompany::sngPtr;

int main(void){
//int _tmain(int argc, _TCHAR* argv[]){
	cout << "Creating single Phone Company" << endl;
	PhoneCompany *pc = PhoneCompany::createObj();

	cout << "Adding 2 staionary clients (Shay and Ariel)." << endl;
	pc->addClient(STATIONARY_PHONE_OWNER, "Shay");
	pc->addClient(STATIONARY_PHONE_OWNER, "Ariel");

	cout << "Adding 2 mobile clients (Eran and Jospeh)." << endl << endl;
	pc->addClient(MOBILE_PHONE_OWNER, "Eran");
	pc->addClient(MOBILE_PHONE_OWNER, "Joseph");

	cout << "NOTE: Upon notification, clients will print what they observed." << endl;

	cout << "Changing price. Shay, Ariel, Eran and Joseph (all customers) should print message." << endl;
	pc->notifyPriceChange();

	cout << endl << "Notifying for upgrade. Eran and Joseph (mobile customers) should print message." << endl;
	pc->notifyUpgrade();

	cout << endl << "Test is over. DESTROYING PHONE COMPANY." << endl;
	PhoneCompany::Destroy();

	getchar();
	return 0;
}
