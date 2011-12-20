#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
/*
struct Point {
	float x;
	float y;
};

class Stroke {			// Memento
public:
	Point	beginPoint;
	Point	endPoint;
};

class FactoryStrokes {
public:
	typedef vector<Stroke*>				memento_t;
	typedef vector<Stroke*>::iterator	it_t;

	typedef vector<memento_t*>			mementos_t;		
	typedef vector<memento_t*>::iterator			mit_t;		
	typedef vector<memento_t*>::reverse_iterator	mrit_t;		

	void AddStroke( Stroke* lastStroke ) {
		mrit_t it = m_mementos.rbegin();
		memento_t* lstMemento = *it;
		memento_t newMemento(lstMemento->size());
		copy(lstMemento->begin(),lstMemento->end(),newMemento.begin());
				
		newMemento.push_back(lastStroke);	// save last Stroke
		m_mementos.push_back(&newMemento);	// save new Memento
	}
	
	memento_t* getAllStrokes() {
		memento_t* lstMemento = *(m_mementos.rbegin());
		return lstMemento;
	}
	
	void Undo() {
		if (m_mementos.size() == 0) return;	// if empty
		mit_t lstMemento = m_mementos.end();
		--lstMemento;
		m_mementos.erase(lstMemento);	//remove the last memento		
		//	RefreshPicture();
	}

private:
	mementos_t m_mementos;		// stores all application states
};

int main() {

	return 0;
}

*/


class Number;

class Memento
{
  public:
    Memento(int val)
    {
        _state = val;
    }
  private:
    friend class Number; // not essential, but p287 suggests this
    int _state;
};

class Number
{
  public:
    Number(int value)
    {
        _value = value;
    }
    void dubble()
    {
        _value = 2 * _value;
    }
    void half()
    {
        _value = _value / 2;
    }
    int getValue()
    {
        return _value;
    }
    Memento *createMemento()
    {
        return new Memento(_value);
    }
    void reinstateMemento(Memento *mem)
    {
        _value = mem->_state;
    }
  private:
    int _value;
};

class Command
{
  public:
    typedef void(Number:: *Action)();
    Command(Number *receiver, Action action)
    {
        _receiver = receiver;
        _action = action;
    }
    virtual void execute()
    {
        _mementoList[_numCommands] = _receiver->createMemento();
        _commandList[_numCommands] = this;
        if (_numCommands > _highWater)
          _highWater = _numCommands;
        _numCommands++;
        (_receiver->*_action)();
    }
    static void undo()
    {
        if (_numCommands == 0)
        {
            cout << "*** Attempt to run off the end!! ***" << endl;
            return ;
        }
        _commandList[_numCommands - 1]->_receiver->reinstateMemento
          (_mementoList[_numCommands - 1]);
        _numCommands--;
    }
    void static redo()
    {
        if (_numCommands > _highWater)
        {
            cout << "*** Attempt to run off the end!! ***" << endl;
            return ;
        }
        (_commandList[_numCommands]->_receiver->*(_commandList[_numCommands]
          ->_action))();
        _numCommands++;
    }
  protected:
    Number *_receiver;
    Action _action;
    static Command *_commandList[20];
    static Memento *_mementoList[20];
    static int _numCommands;
    static int _highWater;
};

Command *Command::_commandList[];
Memento *Command::_mementoList[];
int Command::_numCommands = 0;
int Command::_highWater = 0;

int main()
{
  int i;
  cout << "Integer: ";
  cin >> i;
  Number *object = new Number(i);

  Command *commands[3];
  commands[1] = new Command(object, &Number::dubble);
  commands[2] = new Command(object, &Number::half);

  cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
  cin >> i;

  while (i)
  {
    if (i == 3)
      Command::undo();
    else if (i == 4)
      Command::redo();
    else
      commands[i]->execute();
    cout << "   " << object->getValue() << endl;
    cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
    cin >> i;
  }
}
