#include <list>
#include <algorithm>
using namespace std;

class Document {
  public:
			Document()	{}
	  void	Open()		{}
	  void	Paste()		{}
};

class Application {
  public:
			Application()		{}
	  void	Add(Document* doc)	{}
};

class Command {
public:
    virtual		~Command() {}

    virtual void Execute() = 0;
protected:
    Command() {}
};

class OpenCommand : public Command {
public:
    OpenCommand(Application* app) { m_application = app;}

	void Action() {}
    virtual void Execute() {
				Document* document = new Document();
				m_application->Add(document);
				document->Open();
		}

private:
    Application*	m_application;
    char*			m_response;
};


class PasteCommand : public Command {
public:
    PasteCommand(Document* doc )	{ m_document = doc;}
	void Action() {Execute();}
    virtual void Execute()			{ m_document->Paste();}
private:
    Document*		m_document;
};


template <class Receiver>
class SimpleCommand : public Command {
public:
    typedef void (Receiver::* Action)();

    SimpleCommand(Receiver* r, Action a) :
        m_receiver(r), m_action(a) { }

		virtual void Execute() { (m_receiver->*m_action)();}
private:
    Action		m_action;
    Receiver*	m_receiver;
};


class MacroCommand : public Command {
public:
    MacroCommand();
    virtual ~MacroCommand();

    virtual void Add(Command* c) { m_cmds.push_back(c);}
    virtual void Remove(Command* c ) {
		    list<Command*>::iterator i = find(m_cmds.begin(),m_cmds.end(),c);
			if (i != m_cmds.end()) m_cmds.erase(i);
		}

    virtual void Execute() {
		    list<Command*>::iterator i;
			for (i = m_cmds.begin(); i != m_cmds.end(); ++i) {
				Command* c = *i;
				c->Execute();
			}
		}
private:
    list<Command*> m_cmds;
};





int main() {

	Document doc; 	
	PasteCommand* receiver = new PasteCommand(&doc);
	Command* cmd = new SimpleCommand<PasteCommand>(receiver, &PasteCommand::Action);
	cmd->Execute();
	return 0;
}

