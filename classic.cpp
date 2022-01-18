// ------------------------------ classic.cpp -----------------------------------
// The class 'Classic' is a subclass of the class 'Movie'. It inherits
// all the properties of 'Movie'.
// ----------------------------------------------------------------------------
#include "classic.h"
// ------------------------------- constructor --------------------------------
Classic::Classic() {
	setYear(0);
	setDirector("");
	setTitle("");
	setStock(0);
	setReleaseMonth(0);
	actorHead = nullptr;
  nextClassic = nullptr;
}
// --------------------------- constructor w/params ---------------------------
Classic::Classic(int stock, string director, string title, string majorAct, int releaseMon, int releaseYear) {
	setYear(releaseYear);
	setReleaseMonth(releaseMon);
	setDirector(director);
	setTitle(title);
	setStock(stock);
  //Initialize a new actor pointer
	actor* newActorPtr = new actor;
	newActorPtr->majorActor = majorAct;
	newActorPtr->nextActor = nullptr;
	actorHead = newActorPtr;
  nextClassic = nullptr;
}
// ------------------------------- destructor --------------------------------
Classic::~Classic() {
	if (actorHead == nullptr) {
		return;
	}
	else {
		actor* currPtr = actorHead;
		actor* deletePtr = nullptr;
		while (currPtr != nullptr) {
			deletePtr = currPtr;
			currPtr = currPtr->nextActor;
			delete deletePtr;
		}
		return;
	}
}
// --------------------------- getMajorActor ---------------------------------
// Description: returns true if the findActor is found in the list of 
//              majorActors actor nodes.
// ---------------------------------------------------------------------------
bool Classic::getMajorActor(string findActor) {
	//return actorNode->majorActor;
	string strOut;
	actor* tmpPtr = actorHead;
	while (tmpPtr != nullptr) {
		if (findActor == tmpPtr->majorActor) {
			return true;
		}
		tmpPtr = tmpPtr->nextActor;
	}
	return false;
}
// ----------------------getFirstActorString ---------------------------------
// Description: returns majorActor name pointed to by actorHead
// ---------------------------------------------------------------------------
string Classic::getFirstActorString() {
	string firstActor = "";
	if (this->actorHead == nullptr) {
		return firstActor;
	}
	else {
		firstActor = this->actorHead->majorActor;
		return firstActor;
	}
}
// ---------------------------getActorString ---------------------------------
// Description: returns a string of all actorNodes starting from actorHead
//              concatenated as one string. Used for boolean operator Overloads
//              so that classics can be sorted by majorActor names
// ---------------------------------------------------------------------------
string Classic::getActorString() {
	string strOut;
	actor* tmpPtr = actorHead;
	while (tmpPtr != nullptr) {
		strOut += tmpPtr->majorActor;
		tmpPtr = tmpPtr->nextActor;
	}
	return strOut;
}
// -------------------------- insertMajorActor -------------------------------
// Description: inserts name into the actor list by creating a new actor nodes
//              Will insert in alphabetical order by first-last name
// ---------------------------------------------------------------------------
void Classic::insertMajorActor(string name) {
	//Create newActorPtr
	actor* newActorPtr = new actor;
	newActorPtr->majorActor = name;
	newActorPtr->nextActor = nullptr;

	//(CASE 1) if no major actors so far in movie, then add
	if (actorHead == nullptr) {
		actorHead = newActorPtr;
		return;
	}
	//(CASE 2) IF ONE MAJOR ACTOR
	else if (actorHead != nullptr && actorHead->nextActor == nullptr) {
		//if equal/actor already exists, then deallocate, return
		if (actorHead->majorActor == name) {
			delete newActorPtr;
			return;
		}
		//if greater than, put behind
		else if (actorHead->majorActor < name) {
			actorHead->nextActor = newActorPtr;
		}
		//if less than, put before
		else if (actorHead->majorActor > name) {
			actorHead->nextActor = nullptr;
			newActorPtr->nextActor = actorHead;
			actorHead = newActorPtr;
		}
	}
	//(CASE 3) LIST HAS MORE THAN ONE NODE
	else if (actorHead != nullptr && actorHead->nextActor != nullptr) {
		//Create temp pointer for list traversal
		actor* tmpPtr = actorHead;
		while (tmpPtr->nextActor != nullptr) {
			//If found, then just return and deallocate
			if (tmpPtr->majorActor == name) {
				delete newActorPtr;
				return;
			}
			else if (tmpPtr->majorActor < name && tmpPtr->nextActor->majorActor > name) {
				newActorPtr->nextActor = tmpPtr->nextActor;
				tmpPtr->nextActor = newActorPtr;
				return;
			}
			else {
				tmpPtr = tmpPtr->nextActor;
				continue;
			}
		}
		if (tmpPtr->majorActor == name) {
			delete newActorPtr;
			return;
		}
		else { tmpPtr->nextActor = newActorPtr; }

		return;
	}
}
// ---------------------------getReleaseMonth ---------------------------------
// Description: returns release month as into
// ---------------------------------------------------------------------------
int Classic::getReleaseMonth() {
	return releaseMonth;
}
// ---------------------------setReleaseMonth ---------------------------------
// Description: sets releaseMonth as int equal to month
// ---------------------------------------------------------------------------
void Classic::setReleaseMonth(int month) {
	releaseMonth = month;
}
// -------------------------- getNextClassic ---------------------------------
// Description: returns the pointer to the nextClassic object
// ---------------------------------------------------------------------------
Classic* Classic::getNextClassic() {
	Classic* classicPtr = nextClassic;
	return classicPtr;
}
void Classic::setNextClassic(Classic* cla) {
	nextClassic = cla;
}

// ------------------------------- Operator Overloads --------------------------------
// ------------------------------ operator< -----------------------------------
// Description: (1) compares release date,(2) majorActor, (3) title
//              If release date, actor and title are all equal the movie is equal 
//              however when searching for classics, it only uses the release date 
//              and actor
// ----------------------------------------------------------------------------
bool Classic::operator<(Classic& cla) {
	if (*this == cla) {
		return false;
	}
	if (this->getYear() < cla.getYear()) {
		return true;
	}
	else if (this->getYear() == cla.getYear() &&
		this->getReleaseMonth() < cla.getReleaseMonth()) {
		return true;
	}
	else if (this->getYear() == cla.getYear() &&
		this->getReleaseMonth() == cla.getReleaseMonth() &&
		this->getActorString() == cla.getActorString()) {
		return this->getTitle() < cla.getTitle();
	}
	else if (this->getYear() == cla.getYear() &&
		this->getReleaseMonth() == cla.getReleaseMonth()) {
		return this->getActorString() < cla.getActorString();
	}
	return false;
}
// ------------------------------ operator> -----------------------------------
// Description: (1) compares release date,(2) majorActor, (3) title
//              If release date, actor and title are all equal the movie is equal 
//              however when searching for classics, it only uses the release date 
//              and actor
// ----------------------------------------------------------------------------
bool Classic::operator>(Classic& cla) {
	if (*this == cla) {
		return false;
	}
	if (this->getYear() > cla.getYear()) {
		return true;
	}
	else if (this->getYear() == cla.getYear() &&
		this->getReleaseMonth() > cla.getReleaseMonth()) {
		return true;
	}
	else if (this->getYear() == cla.getYear() &&
		this->getReleaseMonth() == cla.getReleaseMonth() &&
		this->getActorString() == cla.getActorString()) {
		return this->getTitle() > cla.getTitle();
	}
	else if (this->getYear() == cla.getYear() &&
		this->getReleaseMonth() == cla.getReleaseMonth()) {
		return this->getActorString() > cla.getActorString();
	}
	return false;
}
// ------------------------------ operator<= -----------------------------------
// Description: (1) compares release date,(2) majorActor, (3) title
//              If release date, actor and title are all equal the movie is equal 
//              however when searching for classics, it only uses the release date 
//              and actor
// ----------------------------------------------------------------------------
bool Classic::operator<=(Classic& cla) {
	if (*this < cla || *this == cla) {
		return true;
	}
	return false;
}
// ------------------------------ operator>= -----------------------------------
// Description: (1) compares release date,(2) majorActor, (3) title
//              If release date, actor and title are all equal the movie is equal 
//              however when searching for classics, it only uses the release date 
//              and actor
// ----------------------------------------------------------------------------
bool Classic::operator>=(Classic& cla) {
	if (*this > cla || *this == cla) {
		return true;
	}
	return false;
}
// ------------------------------ operator== -----------------------------------
// Description: (1) compares release date,(2) majorActor, (3) title, (4) director
//              
// ----------------------------------------------------------------------------
bool Classic::operator==(Classic& cla) {
	if (this->getTitle() == cla.getTitle() &&
		this->getDirector() == cla.getDirector() &&
		this->getYear() == cla.getYear() &&
		this->getReleaseMonth() == cla.getReleaseMonth()) {
		return true;
	}
	return false;
}
// ------------------------------ operator== -----------------------------------
// Description: (1) compares release date,(2) majorActor, (3) title, (4) director
//              
// ----------------------------------------------------------------------------
bool Classic::operator!=(Classic& cla) {
	return (!(*this == cla));
}
// -------------------------- printWithStock ----------------------------------
// Description: prints movie data and stock for inventory function
// ----------------------------------------------------------------------------
void Classic::printWithStock() {
	cout << setw(5) << getStock() << setw(20) << getDirector() << setw(35) << getTitle() << setw(20) << getFirstActorString() << setw(8)
		<< getReleaseMonth() << ", "<< getYear();
}

// ------------------------------ print ---------------------------------------
// Description: prints movie data with genre
// ----------------------------------------------------------------------------
void Classic::print(){
  cout << "C, " << getTitle() << ", " << getDirector() << ", " << getYear();
}