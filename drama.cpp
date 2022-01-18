// ------------------------------ drama.cpp -----------------------------------
// The class 'Drama' is a subclass of the class 'Movie'. It inherits
// all the properties of 'Movie'.
// ----------------------------------------------------------------------------
#include "drama.h"

// --------------------------- default constructor -----------------------------
Drama::Drama(){
  setTitle(""); // stores title of the movie
  setDirector(""); // stores director's name
  setStock(0); // stores the stock
  setYear(0); // stores the year the movie was released
  nextDrama = NULL;
}

// ------------------------------- constructor --------------------------------
Drama::Drama(int stock, string director, string title, int year){
  setTitle(title); // stores title of the movie
  setDirector(director); // stores director's name
  setStock(stock); // stores the stock
  setYear(year); // stores the year the movie was released
  nextDrama = NULL;
}

// ------------------------------- destructor --------------------------------
Drama::~Drama(){

}

// ------------------------------ operator<< ----------------------------------
// Description: Prints the movie's title, director and release year.
// ----------------------------------------------------------------------------
ostream& operator<<(ostream& output, Drama& d) {
  output << d.getTitle() << ", " << d.getDirector() << ", " << d.getYear() 
  << endl;
	return output;
}

// ------------------------------ operator< -----------------------------------
// Description: Return true if current object director name comes before param
//              director. False otherwise.
// ----------------------------------------------------------------------------
bool Drama::operator<(Drama& movie){
  if(getDirector() != movie.getDirector()){
    return getDirector() < movie.getDirector();
  }
  return getTitle() < getTitle();
}

// ------------------------------ operator> -----------------------------------
// Description: Return true if current object director name comes after param
//              director alphabetically. False otherwise.
// ----------------------------------------------------------------------------
bool Drama::operator>(Drama& movie){
  if(getDirector() != movie.getDirector()){
    return getDirector() > movie.getDirector();
  }
  return getTitle() > getTitle();
}

// ----------------------------- operator<= -----------------------------------
// Description: Return true if current object director name comes before or 
//              equal to param director. False otherwise.
// ----------------------------------------------------------------------------
bool Drama::operator<=(Drama& movie){
  if(*this == movie || *this < movie){
    return true;
  }
  return false;
}

// ----------------------------- operator>= -----------------------------------
// Description: Return true if current object director name comes after or  
//              equals param director alphabetically. False otherwise.
// ----------------------------------------------------------------------------
bool Drama::operator>=(Drama& movie){
  if(*this == movie || *this > movie){
    return true;
  }
  return false;
}

// ----------------------------- operator== -----------------------------------
// Description: Return true if current object director name equals param 
//              director False otherwise.
// ----------------------------------------------------------------------------
bool Drama::operator==(Drama& movie){
  if(getDirector() == movie.getDirector() && getTitle() == movie.getTitle()){
    return true;
  }
  return false;
}

// ----------------------------- operator!= -----------------------------------
// Description: Return true if current object director name doesn't equal param
//              director. False otherwise.
// ----------------------------------------------------------------------------
bool Drama::operator!=(Drama& movie){
  if(*this == movie){
    return false;
  }
  return true;
}

// --------------------------- getNextDrama -----------------------------------
// Description: returns the pointer to the nextDrama object
// ----------------------------------------------------------------------------
Drama* Drama::getNextDrama(){
  Drama *current = nextDrama;
  return current;
}

// --------------------------- setNextDrama -----------------------------------
// Description: sets the pointer of the nextDrama object
// ----------------------------------------------------------------------------
void Drama::setNextDrama(Drama* d){
  nextDrama = d;
} 

// ------------------------------ print ---------------------------------------
// Description: prints movie data with genre
// ----------------------------------------------------------------------------
void Drama::print(){
  cout << "D, " << getTitle() << ", " << getDirector() << ", " << getYear();
}