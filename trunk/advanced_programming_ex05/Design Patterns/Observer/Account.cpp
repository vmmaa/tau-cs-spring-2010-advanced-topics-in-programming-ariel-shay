#include "Account.h"
#include "Bank.h"

#include <iostream>
using namespace std;

Account::Account(Subject* s) { 
	sbj = s; 
	sbj ->Attach(this); 
} 

Account::~Account() { 
	 sbj ->Detach(this); 
} 

void Account::Update (Subject* ChngSubject) { 
	if (ChngSubject == sbj ) {
		cout << "Account is updated " << endl;
	}
} 

