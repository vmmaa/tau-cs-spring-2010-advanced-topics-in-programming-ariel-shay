#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class String {
public:
	String(const char* s) {
		str = new char[strlen(s)+1];
		strcpy(str,s);
	}
	bool operator>(const String& other) const 
		{ return str[0] > other.str[0];}
	bool operator<(const String& other) const 
		{ return str[0] < other.str[0];}
private:
	char* str;
};

// Existing target interface
class Comparator {
public:
	virtual int compare(const String& s1, const String& s2) {
		int res;
		if		( s1 > s2 ) res =  1;
		else if ( s1 < s2 ) res = -1;
		else				res = 0;
		cout << "Old Result = " << res << endl;
		return res;
	}
};

class Array {
public:
	static void sort(String* a, Comparator& c) 
		{ c.compare(a[0], a[1]);}
};


// Adapter 
class NewComparator : public Comparator {
public:
	virtual int compare(const String& s1, const String& s2) {
		int res;
		if		(s1 > s2)	res = 5;
		else if (s1 < s2)	res = -5;
		else				res = 0;
		cout << "New Result = " << res << endl;

		return res;
	}
};

int main() {
	String str[2] = {"Yosi","Rita"};
	Comparator oc;
	Array::sort((String*)str, oc);

	NewComparator nc;
	Array::sort((String*)str, nc);

	return 0;
}

