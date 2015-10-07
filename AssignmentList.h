/**************************************************************************************************
Name: David Jones and Susan Warren
Course: CompSci 303
Program: Assignments Program 1
Date: Oct 5, 2015
Description:
Program manages assignment lists. Associated .cpp file is AssignmentList.cpp
***************************************************************************************************/

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

    void addAssignment(Assignment& a); 
    //pre: valid data string exists in file. file is opened and being read. An assignment has been created.
    //Lists have been generated.
    //post: That assignment is added to the Assigned list
    //returns: none

    bool beenSaved;

public:

    AssignmentList();
    //pre: A file AssignmentFile.txt exists and is accessible
    //post: The two list<Assignments> will be populated
    //returns: none


    ~AssignmentList();
    //pre: The list<Assignments> are populated
    //post: deletes lists
    //returns: none

    void load();
    //pre: A file AssignmentFile.txt exists and is accessible
    //post: The two list<Assignments> will be populated
    //returns: none


    bool compareDates(string lhs, string rhs);
    //pre: two strings as US format dates are entered
    //post: strings are converted into dates then compared
    //returns:true if lhs is larger, false otherwise


    bool alreadyExists(string assignedDate);
    //pre: string is passed in format of a US date
    //post: string is converted to a date and that date is used to search for matching assignment date
    //returns: true if assignment of that assignedDate exists, false otherwise


    bool isCompleted(string assignedDate);
    //pre: string is passed in format of a US date
    //post: string is converted to a date and the completed list is searched for matching assignmentDate
    //returns: true if it exists in completed list, false otherwise


    bool isAssigned(string assignedDate);
    //pre: string is passed in format of a US date
    //post: string is converted to a date and the completed list is searched for matching assignmentDate
    //returns:true if it exists in assigned list, false otherwise


    string dateToString(Date& d);
    //pre: Date is passed in US format
    //post: Date is converted into a string of US date format
    //returns: the date represented as a string 


    string displayAssignments();
    //pre: none
    //post: Both lists are iterated through and a string is appended for each Assignment
    //returns: A string representing all assignments and a header for each list 


    bool addAssignment(string assigned, string descibe, string due);
    //pre: valid assignment and due dates are passed as strings and a valid description is passed
    //post: The parameters are used to make a two dates, then an assignment. That assignment is added to the Assigned list
    //returns: true if an assignment was successful, false otherwise


    bool editDueDate(string assignedDate, string dueDate);
    //pre:assignedDate as a string and a new due date is passed, both are valid
    //post: the assignment is found and edited. It is placed in ascending order within the assigned list (ordered by due date)
    //returns: true if successfully edited, false otherwise


    bool editDescription(string assignedDate, string describe);
    //pre:assignedDate as a string and a new description is passed, both are valid
    //post: the assignment is found and edited. 
    //returns: true if successfully edited, false otherwise


    bool completeAssignment(string assignedDate, string completeDate);
   //pre: assignedDate and a date of completion are passed as US formatted strings (both are valid)
   //post: The assignment is found and it is marked "completed" or "late" based on the provided date strings. Removed from assigned, added to completed
   //returns: true if the assignment was completed successfully, false otherwise.

    int getNumberLate();
    //pre:none
    //post: The number of late assignments are counted and stored in an int
    //returns: the number of late assignments

    bool save();
    //pre: none
    //post: The assignment file is overwritten to reflect new values after iterating through each list and writing a line for each assignment
    //returns: true if successful, false otherwise
};

#endif