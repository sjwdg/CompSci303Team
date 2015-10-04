#ifndef ASSIGNMENTLIST_H
#define ASSIGNMENTLIST_H

#include "list.h"
#include "Assignment.h"
#include "Date.h"
class AssignmentList
{
private:
    void addToCompleted(Assignment& a);
    list<Assignment>::iterator search(list<Assignment>& li, Date assignedDate);
    list<Assignment> assigned;
    list<Assignment> completed;
    void load();
    void addAssignment(Assignment& a);
    bool beenSaved;

public:

    AssignmentList();
    AssignmentList(AssignmentList& other);
    ~AssignmentList();

    bool compareDates(string lhs, string rhs);
    bool alreadyExists(string assignedDate);
    bool isCompleted(string assignedDate);
    bool isAssigned(string assignedDate);
    string dateToString(Date& d) ;
    
    
    string displayAssignments() ;
    
    bool addAssignment(string assigned, string descibe, string due);
   /* bool completeAssignment(string assigned); 
    bool editDueDate(string assigned, string due);
    bool editDescription(string assigned, string describe);
    int getNumberLate();*/
};

#endif