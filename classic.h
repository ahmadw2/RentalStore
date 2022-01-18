// ------------------------------ classic.h -----------------------------------
// The class 'Classic' is a subclass of class 'Movie'. In addition to inheriting
// all the properties of 'Movie', 'Classic also contains the data items
// 'majorActor' and 'releaseMonth'.
// ----------------------------------------------------------------------------
#ifndef CLASSIC_H
#define CLASSIC_H
#include "movie.h"

class Classic : public Movie {
public:
    Classic();  //Default constructor
    Classic(int stock, string director, string title,
        string majorAct, int releaseMon, int releaseYear);//Constructor w/args
    ~Classic(); //Destructor
    bool getMajorActor(string findActor); //Returns true if findActor found, else false
    int getReleaseMonth(); //Returns release month as int
    Classic* getNextClassic(); //Returns nextClassic pointer
    string getActorString(); //Returns concatenated string of all actors
    string getFirstActorString();//Returns the first actor in list of MajorActors

    void insertMajorActor(string name); //Inserts a new major actor 
    void setReleaseMonth(int month); //Sets releaseMonth as int
    void setNextClassic(Classic* cla); //Sets nextClassic pointer to cla
    void printWithStock(); //Prints with stock
    void print();//Prints title, director, year
    
    //Operator Overloads -> (1) compares release date,(2) majorActor, (3) title
    //If release date, actor and title are all equal the movie is equal however
    //when searching for classics, it only uses the release date and actor
    bool operator<(Classic& cla); 
    bool operator>(Classic& cla);
    bool operator<=(Classic& cla);
    bool operator>=(Classic& cla);
    bool operator==(Classic& cla);
    bool operator!=(Classic& cla);
private:
    //Actor struct contains majorActor name and ptr to next actor
    struct actor {
        string majorActor; //contains majorActor getActorString
        actor* nextActor;  //Points to next majorActor if more than one
    };
    actor* actorHead; //Points to head of majorActor list
    int releaseMonth; //Stores Classic Movie Release Month
    Classic* nextClassic; //Points to the next classic movie
};
#endif