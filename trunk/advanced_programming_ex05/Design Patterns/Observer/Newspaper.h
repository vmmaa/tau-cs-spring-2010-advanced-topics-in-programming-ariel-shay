#ifndef NEWSPAPER_H
#define NEWSPAPER_H
#include "Observer.h"

class Bank;

class Newspaper: public Observer {
public:
			Newspaper(Subject *);	// attach to bank	
			~Newspaper();			// detach from bank

    void	Update(Subject*);		// update itself
}; 

#endif

