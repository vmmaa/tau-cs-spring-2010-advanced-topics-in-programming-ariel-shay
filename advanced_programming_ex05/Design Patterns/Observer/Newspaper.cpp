#include "Newspaper.h"
#include "Bank.h"

#include <iostream>
using namespace std;

Newspaper:: Newspaper(Subject* s) { 
	sbj = s; 
	sbj ->Attach(this); 
} 

Newspaper::~Newspaper() { 
	 sbj ->Detach(this); 
} 

void Newspaper ::Update (Subject* ChngSubject) { 
	if (ChngSubject == sbj ) {
		cout << "Newspaper is informed " << endl; 
	}
} 
