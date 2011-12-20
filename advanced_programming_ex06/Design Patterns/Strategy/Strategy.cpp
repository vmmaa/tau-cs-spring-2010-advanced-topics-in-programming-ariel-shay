
#include <iostream>
#include <string>
using namespace std;


struct ProtocolMsg {};

struct PDU : public ProtocolMsg {};

struct TCPIPcmnd : public ProtocolMsg {};

class ApplicMsg {};

//---------------------------------------------------------------------

enum prot_e { prot_beg =-1, snmp_e, tcpip_e, prot_end };

typedef void (*ProtFunc)(ApplicMsg* , ProtocolMsg*& );

ProtFunc ProtFunctions[prot_end-prot_beg-1];


//---------------------------------------------------------------------
// Protocols 
//---------------------------------------------------------------------

template <int N>
class Protocol  {
public:
	static void send( ApplicMsg* msg,ProtocolMsg*& protMsg) {
	}
};

template<> class Protocol<snmp_e>  {
public:
	static void send( ApplicMsg* msg,ProtocolMsg*& protMsg) {
		cout << "SNMP protocol" << endl;
	}
};

template<> class Protocol<tcpip_e> {
public:
	static void send( ApplicMsg* msg,ProtocolMsg*& protMsg) {
		cout << "TCPIP protocol" << endl;
	}
};


//---------------------------------------------------------------------
// Applications 
//---------------------------------------------------------------------

prot_e getType() {
	cout << "Enter type [0/1] : ";
	int type;
	cin >> type;
	return (prot_e)type;

}

class Mediation {
public:
	static void send(ApplicMsg* msg,ProtocolMsg*& protMsg) {
		cout << "Mediation --> ";
		int type = getType();
		ProtFunctions[type](msg,protMsg);
	}
};

class FaultMng {
public:
	static void send(ApplicMsg* msg,ProtocolMsg*& protMsg) {
		cout << "Fault Management --> ";
		int type = getType();
		ProtFunctions[type](msg,protMsg);
	}
};

template <class Application>
class ApplicMng {
public:
	static void send(ApplicMsg* msg,ProtocolMsg*& protMsg) {
		Application::send(msg,protMsg);
	}	
};

//---------------------------------------------------------------------
// main 
//---------------------------------------------------------------------

int main(){
	ProtFunctions[snmp_e]	= Protocol<snmp_e>::send;
	ProtFunctions[tcpip_e]	= Protocol<tcpip_e>::send;

	ApplicMsg		msg;
	ProtocolMsg*	pdu  = new PDU;
	ProtocolMsg*	cmnd = new TCPIPcmnd;

	ApplicMng<Mediation>::send(&msg, pdu);
	ApplicMng<FaultMng> ::send(&msg,cmnd);
    return 0;
}

//=============================================================================================

