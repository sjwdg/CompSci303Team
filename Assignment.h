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

   

    //display 
    /*Iterate though each list with a const iterator. Print resuts to consol*/
    static void display(const list<Assignment>& assign, const list<Assignment>& complete);
    
    //    //add from file
    //    /*Verify the assigment dates and such. If it is all good, continue*/
    //    /*Iterate to the place. Add the Node*/
    //    //WHICH LIST WILL BE DETERMINED BY THE STATUS
    static void addAssignment(list<Assignment>& chosen, Assignment& a);

    
    //changes due date for a specific assignment
    //ChangedDueDate(list<Assignment>& assigned)
    //{
    //
    //}


    //this can add to either list
    //We assume that the file is correct, which is reasonable if 
    //   we assume this is a program with its own files
    static void load(list<Assignment>& assign, list<Assignment>& completed);
    

    //edit a date
    /*check the date*/
    /*find the node. then change the date*/

    //edit a description
    /*find the node. edit the description */

    //Complete Assignment
    /*find the assignment in Assigned list. call add on the completed list. Delete from assignment list*/

    //Display number of late
    /*Iterate through the completed list, incrementing an int to count the late ones*/

    //Record assignment lists
    /*Const Iterate through each, using a ofile stream to record each*/

    //Exit
    /*I guess we could delete the stuff, but that isn't necessary */


};
#endif