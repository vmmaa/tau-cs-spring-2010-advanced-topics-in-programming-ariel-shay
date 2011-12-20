
class VisualComponent;

class Window {
  public:
	  void SetContents (VisualComponent* contents) {}
};


class VisualComponent {
public:
    VisualComponent() {}

    virtual void Draw() {}
    virtual void Resize() {}
};


class Decorator : public VisualComponent {
public:
    Decorator(VisualComponent* vc) { m_component = vc;}
    virtual void Draw()		{ if (m_component)  m_component->Draw();}
    virtual void Resize()	{ m_component->Resize();}
private:
    VisualComponent* m_component;
};

class BorderDecorator : public Decorator {
public:
    BorderDecorator(VisualComponent* vc, int borderWidth ) 
		: Decorator(vc), m_width(borderWidth) {}

    virtual void Draw() {
		Decorator::Draw();
		DrawBorder(m_width);
	}
private:
    void DrawBorder(int) {}
private:
    int m_width;
};

class ScrollDecorator : public Decorator {
public:
    ScrollDecorator(VisualComponent* vc) 
		: Decorator(vc) {}
};

class TextView : public VisualComponent {
};

//------------------------------------------------

int main () {
	Window*		window		= new Window;
	TextView	textView;
	
	ScrollDecorator sd(&textView);
	ScrollDecorator sd1;
	ScrollDecorator sd(&textView);
	BorderDecorator bd(&sd,1);
	window->SetContents(&bd);

	return 0;
}


