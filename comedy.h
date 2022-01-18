// -------------------------------- comedy.h ----------------------------------
// The class 'Comedy' is a subclass of the class 'Movie'. It inherits
// all the properties of 'Movie'.
// ----------------------------------------------------------------------------
#ifndef COMEDY
#define COMEDY
#include "movie.h"

class Comedy : public Movie {
	friend ostream& operator<<(ostream&, Comedy&); //Prints title, director, year
public:
	Comedy();//Default constructor
	Comedy(int stock, string director, string title, int year);//Constructor w/params
	~Comedy(); //Destructor - class currently has no dynamic allocations
	Comedy* getNextComedy(); //Returns the pointer nextComedy
	void setNextComedy(Comedy* com);//Sets the pointer nextComedy
	
  //Operator overloads compare Comedies by Title, then year released
  bool operator<(Comedy& com);
	bool operator>(Comedy& com);
	bool operator<=(Comedy& com);
	bool operator>=(Comedy& com);
	bool operator==(Comedy& com);
	bool operator!=(Comedy& com);
	
  void print();//Prints title, director, and year
  
private:
	Comedy* nextComedy;//Points to the next Comedy in list
};
#endif