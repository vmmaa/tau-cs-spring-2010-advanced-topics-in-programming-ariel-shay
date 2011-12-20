#include <list>
#include <iostream>
using namespace std;

class MouseEvent {};

//=======================================================================

class Widget;				// forward declaration

class DialogDirector {
public:
	virtual			~DialogDirector() {}

	virtual void	ShowDialog() {}
    virtual void	WidgetChanged(Widget*) = 0;
 
protected:
					DialogDirector() {}
    virtual void	CreateWidgets() = 0;
};

//=======================================================================
 
class Widget {
public:
					Widget(DialogDirector* dd) : m_director(dd) {}
    virtual void	Changed() { m_director->WidgetChanged(this);}
    virtual void	HandleMouse(MouseEvent& event) { }
private:
    DialogDirector* m_director;
};

//=======================================================================

class ListBox : public Widget {
public:
    ListBox(DialogDirector* dd) : Widget(dd) {}

    virtual const char* GetSelection() { 
							cout << "Select from list: " << endl;
							return 0;
						} 
    virtual void		SetList(list<char*>* listItems) {}
    virtual void		HandleMouse(MouseEvent& event) {
							cout << "Mouse pressed in List" << endl; 
						}
};
 
//=======================================================================

class EntryField : public Widget {
public:
    EntryField(DialogDirector* dd) : Widget(dd) {}

    virtual void			SetText(const char* text) {}
    virtual const char*		GetText() { return 0;}
    virtual void			HandleMouse(MouseEvent& event) {
								cout << "Mouse pressed in EntryField" << endl; 
							}
};
 
//=======================================================================

enum button_e { ok_e, cancel_e };

class Button : public Widget {
public:
    Button(DialogDirector* dd) : Widget(dd) {}

    virtual void		SetText(const char* text) {}
    virtual void		HandleMouse(MouseEvent& event) { Changed();}
}; 
  
//=======================================================================

class FontDialogDirector : public DialogDirector {
public:
				FontDialogDirector() {CreateWidgets(); } 
	virtual		~FontDialogDirector() {
		delete	m_ok;		m_ok		= 0;
		delete	m_cancel;	m_cancel	= 0;
		delete	m_fontList;	m_fontList	= 0;
		delete	m_fontName;	m_fontName	= 0;
	}

	// WidgetChanged ensures that the widgets work together properly:
	virtual void WidgetChanged(Widget* ChangedWidget) {
		if (ChangedWidget == m_fontList) {
			m_fontName->SetText(m_fontList->GetSelection());
		} else if (ChangedWidget == m_ok) {
			cout << "OK button was pressed" << endl;
		} else if (ChangedWidget == m_cancel) {
			cout << "CANCEL button was pressed" << endl;
		}
	}

	virtual Button* getButton(button_e but) {
		if (but == ok_e) return m_ok;
		return m_cancel;
	}

protected:
	virtual void CreateWidgets() {
		m_ok		= new Button(this);
		m_cancel	= new Button(this);
		m_fontList	= new ListBox(this);
		m_fontName	= new EntryField(this);
	}
 
private:
    Button*		m_ok;			// OK button
    Button*		m_cancel;		// CANCEL button
    ListBox*	m_fontList;		// choose from list
    EntryField* m_fontName;
};
 
//=======================================================================
 
int main() {
	FontDialogDirector	fontDirector;
	
	Button*  b = fontDirector.getButton(ok_e);
	fontDirector.WidgetChanged(b);

	return 0;
}

