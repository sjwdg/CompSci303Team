/**************************************************************************************************
Name: David Jones and Susan Warren
Course: CompSci 303
Program: Assignments Program 1
Date: Oct 5, 2015
Description:
Program manages assignment. Associated .cpp file is Assignment.cpp

***************************************************************************************************/

#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
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
        dueDate(due), description(description), assignedDate(assign){setStat(status);};

    void setDueDate(string dDate);//change the due date using a string
    void setDesc(string desc);//change the description using a string.
    void setStat(string s); // change the status using the string

    friend ostream& operator <<(ostream& out, Assignment& work); //overload to print what we need
    friend bool operator == (Assignment& left, const Assignment& other){ return (left.assignedDate == other.assignedDate); }

    /*friend bool operator == (Assignment& left, Assignment& other){ return (left.assignedDate == other.assignedDate); }
*/
    string dateToString(Date& d);

    string getAssignedDate()  { return dateToString(assignedDate); }
    string getDueDate()  { return dateToString(dueDate); }
};


#endif