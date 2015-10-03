#ifndef ASSIGNMENTLIST_H
#define ASSIGNMENTLIST_H

#include <iostream>
#include<sstream>
#include<fstream>
#include <string> //dont know if this is needed. We can remove later if not 
#include "Date.h" 
#include "list.h"
//date.h includes the tokenizer, so no need to include it again

using namespace std;
struct Assignment
{

    enum status{ Assigned, Completed, Late };
    string description;
    Date assignedDate, dueDate;
    status stat;

    Assignment(Date due, string description, Date assign, string status) :
        dueDate(due), description(description), assignedDate(assign)
    {
        setStat(status);
    };

    void setStat(string s); // change the status using the string

    friend ostream& operator <<(ostream& out, Assignment& work); //overload to print what we need

    friend bool operator == (Assignment& left, Assignment& other){ return (left.assignedDate == other.assignedDate); }
    //Compare values



    //use this to search by assigned date. Can take either list and returns an iterator if it finds the assignment
    //should work on empty lists and in the "not found" case
    //it will return an iterator that compares as 'true' to any list.end() if no match is found
    static list<Assignment>::iterator search(list<Assignment>& li, Date d);

   

    //print to console display  
    /*Iterate though each list with a const iterator. Print resuts to consol*/
    static void display(const list<Assignment>& assign, const list<Assignment>& complete);
    
    //    //add from file
    //    /*Verify the assigment dates and such. If it is all good, continue*/
    //    /*Iterate to the place. Add the Node*/
    //    //WHICH LIST WILL BE DETERMINED BY THE STATUS
    //return true of list is changed.
    static bool addAssignment(list<Assignment>& chosen, Assignment& a);


    //We assume that the file is correct, which is reasonable if 
    //we assume this is a program with its own files
    static bool load(list<Assignment>& assign, list<Assignment>& completed);
    

    /*changes due date for a specific assignment
    returns */
    static bool editDueDate(list<Assignment>& assigned, Date& assignedDate, Date& dueDate);

    //edit a description.   
    /*find the node. edit the description */
    static bool editDesc(list<Assignment>& assigned, Date& assignDate, string description);
   

    //Complete Assignment
    /*find the assignment in Assigned list. call add on the completed list. Delete from assignment list*/
    static bool  editStatus(list<Assignment>& assigned, list<Assignment>& completed, Date& assignDate, Date& statusAsDate);

    //Display number of late
    /*Iterate through the completed list, incrementing an int to count the late ones*/
    static int getNumberLate(list<Assignment>& completed);
   

   
    //Record assignment lists 
    /*Const Iterate through each, using a ofile stream to record each*/
    //???????????????????????


    


};
#endif