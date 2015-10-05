#ifndef ASSIGNMENTLIST_H
#define ASSIGNMENTLIST_H

//#include "list.h"- NOTE: no include guard on list.h file so deleting this.  Is included on Assignment.h file.
#include "Assignment.h"
#include "Date.h"
class AssignmentList
{
private:
    void addToCompleted(Assignment& a);
    list<Assignment>::iterator search(list<Assignment>& li, Date assignedDate);
    list<Assignment> assigned;
    list<Assignment> completed;
<<<<<<< HEAD
    
    void addAssignment(Assignment& a);
=======

    void load();
    void addAssignment(Assignment& a);//used for reading from a file.
>>>>>>> 96047b674ac3a605fb31d5eea6d782d0cfa050da
    bool beenSaved;

public:

    AssignmentList();
    ~AssignmentList();

    void load();
    bool compareDates(string lhs, string rhs);
    bool alreadyExists(string assignDate);
    bool isCompleted(string assignDate);
    bool isAssigned(string assignDate);
    string dateToString(Date& d) ;
    
    string displayAssignments() ;

    //used when adding an assignment to an existing list.
    bool addAssignment(string assigned, string descibe, string due);
    bool editDueDate(string assigned, string due);
    bool editDescription(string assigned, string describe);
    bool completeAssignment(string assigned, string completionDate); 
    bool save();

  
    //int getNumberLate();
};

#endif