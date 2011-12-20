#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Observer.h"

class Bank;

class Account: public Observer { 
public: 
			Account (Subject *);// attach to bank 		
			~Account();		// detach from bank 

	void	Update(Subject*);	// update itself 
}; 

#endif
