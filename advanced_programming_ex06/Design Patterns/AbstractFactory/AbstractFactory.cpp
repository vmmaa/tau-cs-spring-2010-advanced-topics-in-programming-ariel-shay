#include <iostream>
#include <string>
using namespace std;

class InputDevice {
public:
	virtual void DisplayDevice () = 0 ;
};

class OutputDevice {
public:
	virtual void DisplayDevice () = 0 ;
};

class IBMKeyboard : public InputDevice {
public:
	void DisplayDevice () {
		cout << "IBMKeyboard" << endl ;
	} 
};

class IBMPrinter : public OutputDevice {
public:
	void DisplayDevice () {
		cout << "IBMPrinter" << endl; 
	}
};



class SamsungMouse : public InputDevice {
public:
	void DisplayDevice () {
		cout << "SamsungMouse" << endl ;
	}
};

class SamsungMonitor : public OutputDevice {
public:
	void DisplayDevice () {
		cout << "SamsungMonitor" << endl ;
	}
};



class DeviceFactory {
public:
	virtual  InputDevice*	FInputDevice () = 0;
	virtual  OutputDevice*	FOutputDevice () = 0;
};


class IBMDeviceFactory : public DeviceFactory {
public:
	InputDevice* FInputDevice () {
		return new IBMKeyboard ;
	}
	OutputDevice* FOutputDevice () {
		return new IBMPrinter ;
	}
};

class SamsungDeviceFactory : public DeviceFactory {
public:
	InputDevice* FInputDevice () {
		return new SamsungMouse ;
	}

	OutputDevice* FOutputDevice () {
		return new SamsungMonitor ;
	}

};

//---------------------------------------------------

int main() {
	DeviceFactory*	df = new IBMDeviceFactory ;
	InputDevice*	Id ;
	Id = df -> FInputDevice () ;
	Id -> DisplayDevice () ;
	return 0;
}
