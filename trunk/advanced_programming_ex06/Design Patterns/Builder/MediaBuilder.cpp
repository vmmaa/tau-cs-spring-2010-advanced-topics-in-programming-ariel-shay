#include <string>
#include <list>
#include <iostream>
using namespace std;


class MediaItem;

class Media {
public:
	void add(const MediaItem& medItem);
	string MediaName() const;
protected:
	string	mediaName;

};


class Book		: public Media {};

class Magazine	: public Media {};

class WebSite	: public Media {};




// We have different kinds of media items:

class MediaItem {
public:
			MediaItem(const string& i) { item = i; }
			MediaItem(const char*   i) { item = i; }
	string	ItemName() const { return item; }
private: 
	string item;
};

class Chapter : public MediaItem {
public: 
	Chapter(const string& i) : MediaItem(i) { }
};

class Article : public MediaItem {
public: 
	Article(const string& i) : MediaItem(i) { }
};

class WebItem : public MediaItem {
public: 
	WebItem(const string& i) : MediaItem(i) { }
};

void Media::add(const MediaItem& medItem) { mediaName = medItem.ItemName();}
string Media::MediaName() const { return mediaName;}


// the same basic construction steps - buildBasic -> AddMediaItem -> getReadyMedia :

class MediaBuilder {
public:
	virtual void	buildBase()							= 0;
	virtual void	addMediaItem(const MediaItem& item) = 0;
	virtual Media*	getReadyMedia()						= 0;
};

 

class BookBuilder : public MediaBuilder {
public:
	void buildBase() {
		cout << endl << "Building book " << endl;
		b = new Book();
  }

	void addMediaItem(const MediaItem& chapter) {
		cout << "Adding chapter " << chapter.ItemName() << endl;
		b->add(chapter);
  }

	Media* getReadyMedia() { return b; }

private: 
	  Book*		b;
};  

 

class MagazineBuilder : public MediaBuilder {

public: 
	void buildBase() {
		cout << endl << "Building magazine " << endl;
		m = new Magazine();
	}

	void addMediaItem(const MediaItem& article) {
		cout << "Adding article " << article.ItemName().c_str() << endl;
		m->add(article);
	}

	Media* getReadyMedia() { 
		return m; 
	}
private: 
	Magazine*	m;
};  

 

class WebSiteBuilder : public MediaBuilder {
public:
	void buildBase() {
		cout << endl << "Building web site " << endl;
		w = new WebSite();
	}

	void addMediaItem(const MediaItem& webItem) {
		cout << "Adding web item " << webItem.ItemName().c_str() << endl;
		w->add(webItem);
	}

	Media*	getReadyMedia() { 
		return w; 
	}
private:
	WebSite*	w;
};  

 

class MediaDirector { // a.k.a. "Context"
public:
	MediaDirector(const MediaBuilder* pmb) {
		mb = (MediaBuilder*)pmb; 
	}

	Media* produceMedia(const list<MediaItem>& lst) {
		list<MediaItem>::const_iterator it; 
		mb->buildBase();
		for( it = lst.begin(); it != lst.end(); ++it ) {
			mb->addMediaItem(*it);
		}

		return mb->getReadyMedia();
	}
private:
	MediaBuilder* mb;
};



class BuildMedia {
public:
	BuildMedia() {
		lst.push_back("item1");
		lst.push_back("item2");
		lst.push_back("item3");
		lst.push_back("item4");
	}

	void testBook() {
		MediaDirector buildBook = MediaDirector( new BookBuilder);
		Media* book = buildBook.produceMedia(lst);
  }

	void testMagazine() {
		MediaDirector buildMagazine = MediaDirector( new MagazineBuilder);
		Media* magazine = buildMagazine.produceMedia(lst);
  }

	void testWebSite() {
		MediaDirector buildWebSite = MediaDirector( new WebSiteBuilder);
		Media* webSite = buildWebSite.produceMedia(lst);
	}
private:
	
	list<MediaItem>  lst;
};





int main() {
	BuildMedia bldMedia;
	bldMedia.testBook();
	bldMedia.testMagazine();
	bldMedia.testWebSite();

	return 0;
} 

