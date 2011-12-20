// file name : observer.cpp 

#include "subject.h" 

//-----------------------------------------------------------------------------
// Attach
//-----------------------------------------------------------------------------
void Subject::Attach (Observer* o) { 
	 m_observers.push_back(o); 
} 

//-----------------------------------------------------------------------------
// Detach
//-----------------------------------------------------------------------------
void Subject::Detach (Observer* o) { 
    int count = m_observers.size(); 
	int i; 
	for (i = 0; i < count; i++) { 
		if(m_observers[i] == o) 
			break; 
	} 
	if(i < count) {
		m_observers.erase(m_observers.begin() + i); 
	}
} 

//-----------------------------------------------------------------------------
// Notify
//-----------------------------------------------------------------------------
void Subject::Notify () { 
    int count = m_observers.size(); 
	for (int i = 0; i < count; i++) {
		(m_observers[i])->Update(this); 
	}
}
