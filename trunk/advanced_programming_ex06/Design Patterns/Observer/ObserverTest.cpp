#include "Bank.h" 
#include "Account.h" 
#include "Newspaper.h" 

int main() { 
	Bank		bnk; 
	Account		account(& bnk); 
	Newspaper 	paper(& bnk); 
	bnk.ChangePercent();	// trigger
	// subject state change and update all it's observers
}

