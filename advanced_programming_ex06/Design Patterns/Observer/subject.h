// file name : subject.h

#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
using namespace std;

//========================================================= 

#include "observer.h"

class Subject { 
public: 
	 Subject() {}; 
	 ~Subject() {}; 
	 void Attach(Observer*); 
	 void Detach(Observer*); 
protected:
	 void Notify(); 
private: 
	 vector<Observer*> m_observers; 
};

#endif  