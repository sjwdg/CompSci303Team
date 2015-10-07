/**************************************************************************************************
Name: David Jones and Susan Warren
Course: CompSci 303
Program: Assignments Program 1
Date: Oct 5, 2015
Description:
Program manages assignment lists. Associated .h file is AssignmentList.h
***************************************************************************************************/

#include "AssignmentList.h"
#include <iostream>
#include<sstream>
#include<fstream>
#include <string>
using namespace std;


AssignmentList::AssignmentList()
{

}


AssignmentList::~AssignmentList()
{
    ;
}



list<Assignment>::iterator AssignmentList::search(list<Assignment>& li, Date d)
{
    list<Assignment>::iterator itr = li.begin();  //This iterator will look through the list 
    if (li.size() == 0) //There is nothing in the list
    {
        itr = li.end(); 
        return itr; //we return itr as li.end() to signify it reached the end without finding the assignedDate match
    }

    while (itr != li.end())
    {
        if (itr->assignedDate == d) return itr; //check the assignedDate of the current node to see if it matches our given date
        ++itr; //if we don't have a match, continue looking
    }
    return itr; //We reached the end. The calling function will check for itr == li.end() to see if there was no find
}


bool AssignmentList::alreadyExists(string assign)
{
    Date d;
    try
    {
        d = Date(assign);
    }
    catch (exception e)
    {
        return false;//error in date then return false
    }

    list<Assignment>::iterator itr = search(assigned, d);
    if (itr != assigned.end()) return true;//found the assignDate in assigned
    itr = search(completed, d); //didn't find in assigned, so lets search completed
    if (itr != completed.end()) return true;//found the assignDate completed
    else return false; //didn't find assignDate to match the desired date
}


bool AssignmentList::isCompleted(string assignDate)
{
    Date d;
    try
    {
        d = Date(assignDate);
    }
    catch (exception e)
    {
        return false;
    }

    list<Assignment>::iterator itr = search(completed, d); //searches through completed for an assignedDate matching d
    if (itr == completed.end()) return false; //didn't find a match, so it isn't in completed
    else return true; // itr isn't completed.end(), so it must be pointing to a match, therefore the assignment exists in completed
}


bool AssignmentList::isAssigned(string assign)
{
    Date d;
    try
    {
        d = Date(assign);
    }
    catch (exception e)
    {
        return false;
    }

    list<Assignment>::iterator itr = search(assigned, d);//searches through assigned for an assignedDate matching d
    if (itr == assigned.end()) return false;//didn't find a match, so it isn't in assigned
    else return true;// itr isn't assigned.end(), so it must be pointing to a match, therefore the assignment exists in assigned
}


string AssignmentList::dateToString(Date& d)
{
    string temp = ""; //will eventually hold the string representing the date in US format


    string s = d.toString();
    String_Tokenizer st(s, "/");
    string month = st.next_token();
    string day = st.next_token();
    string year = st.next_token();
    string result = month + "-" + day + "-" + year;
    return result;
}


string AssignmentList::displayAssignments()
{
    stringstream display; //used to build the entire string being sent to console within UserInterface (the calling function)
    display << "Assigned List" << "\n" << "--------------------" << "\n";

    //iterate through all the assigned list assignments
    for (list<Assignment>::iterator itr = assigned.begin(); itr != assigned.end(); itr++)
    {
        display << *itr << "\n";
    }

    display << "\n" << "Completed List" << "\n" << "--------------------" << "\n";

    //iterate through all of the completed list assignments
    for (list<Assignment>::iterator itr = completed.begin(); itr != completed.end(); itr++)
    {
        display << *itr << "\n";
    }
    string t = display.str(); //get the string from the string stream object
    return t; //return it to the caller 
}


void  AssignmentList::addAssignment(Assignment& a)
{
    if (assigned.empty()) assigned.push_front(a); //if list is empty, simply push_front
    else
    {
        if (assigned.find(a) == assigned.end()) //means that the assignment was not found 
        {
            for (list<Assignment>::iterator itr = assigned.begin(); itr != assigned.end(); ++itr)
            {
                
                if (itr->dueDate > a.dueDate) //find where one is > , if exists
                {
                    assigned.insert(itr, a); //put it where the larger one was
                    return;
                }
            }
        }
        assigned.push_back(a); //none were greater. Just put it at the end
        return;
    }
}


void AssignmentList::addToCompleted(Assignment& a)
{
    if (completed.empty()) completed.push_front(a); //if list is empty, simply push_front
    else
    {
        if (completed.find(a) == completed.end())
        {
            for (list<Assignment>::iterator itr = completed.begin(); itr != completed.end(); ++itr)
            {
                if (itr->dueDate > a.dueDate) //find where one is > , if exists
                {
                    completed.insert(itr, a); //put it where the larger one was
                    return;
                }
            }
        }
        completed.push_back(a); //none were greater. Just put it at the end
        return;
    }
}


bool AssignmentList::addAssignment(string assigned, string describe, string due)
{

    try
    {
        Date dueDate(due);
        Date assignedDate(assigned);

        Assignment newAssignment(dueDate, describe, assigned, "assigned");
        AssignmentList::addAssignment(newAssignment);
    }

    catch (exception e)
    {
        return false; //error occurred, so return false 
    }

    return true; //because no errors occurred

}


void AssignmentList::load()
{
    ifstream fin;
    fin.open("AssignmentFile.txt"); //This file will hold the pre-existing assignments, if applicable. It will also be saved to later

    if (fin.fail())
        cout << "Error. AssignmentFile.txt failed to open";
    //added this error message in because prog is not printing out data

    string s;

    while (getline(fin, s))
    {

        try
        {
            //NOTE: The substrings are to remove extra spaces
            String_Tokenizer st(s, ",");
            string dueString = st.next_token();
            string des(st.next_token());
            string assignString = st.next_token();
            string status(st.next_token());


            des = des.substr(1, des.length()); //subst without the blank space
            Date assignDate(assignString);
            Date due(dueString);

            status = status.substr(1, status.length()); //substr without the blank space
            status[0] = tolower(status[0]); //ensures our checks work regardless of lower or upper case first letter

            if (!(due > assignDate)) return; //return if due date isn't greater than assignment date

            Assignment d(due, des, assignDate, status);
            if (d.stat == 0) addAssignment(d); //status == assigned
            else addToCompleted(d); //status == completed or late
        }
        catch (exception e)
        {
            cout << "\n Input file error: Dropping one assignment \n";
        }
    }
    fin.close();
}


bool AssignmentList::compareDates(string lhs, string rhs)
{
    Date left, right;
    try
    {
        left = Date(lhs);
        right = Date(rhs);
    }
    catch (exception e)
    {
        throw exception("Date entry error");
    }
    if (left > right) return true;
    else return false;
}



bool AssignmentList::editDueDate(string assignedDate, string dueDate)
{

    Date dateOfAssignment;
    Date dateDue;
    
    try
    {

        dateOfAssignment = Date(assignedDate);
        dateDue = Date(dueDate);
    }
    catch (exception e)
    {
        return false; //one of the dates was invalid and threw an exception
    }
    list<Assignment>::iterator itr = search(assigned, dateOfAssignment);
    if (itr == assigned.end()) return false;//if false then assign date not in list
    
    else
    {
        itr->setDueDate(dueDate);
        Assignment temp =*itr;
        addAssignment(temp);
        assigned.remove(*itr);
    }

    return true;

}



bool AssignmentList::editDescription(string assignedDate, string describe)
{
    Date dateOfAssignment;

    try
    {
        dateOfAssignment = Date(assignedDate);
    }
    catch (exception e)
    {
        return false; //date was invalid and threw an exception
    }

    list<Assignment>::iterator itr = search(assigned, dateOfAssignment);
    if (itr == assigned.end()) return false;//if false then assign date not in list

    itr->setDesc(describe);
    return true;

}


bool AssignmentList::completeAssignment(string assignDate, string completeDate)
{

    Date dateOfAssignment;
    Date dateOfCompletion;

    try
    {
        dateOfAssignment = Date(assignDate);
        dateOfCompletion = Date(completeDate);
    }
    catch (exception e)
    {
        return false; //one of the dates was invalid and threw an exception
    }
    list<Assignment>::iterator itr = search(assigned, dateOfAssignment);
    if (itr == assigned.end()) return false;//if false then assign date not in list

    if (dateOfCompletion > itr->dueDate) itr->setStat("late"); //set "late" if completed after due date
    else itr->setStat("completed");                             //set "completed" if completed on or before due date 
    addToCompleted(*itr);
    assigned.remove(*itr);
    return true;
}



int AssignmentList::getNumberLate()
{

    int result = 0;
    for (list < Assignment>::iterator itr = completed.begin(); itr != completed.end(); itr++) //iterate through the completed list
        if (itr->stat == 2) result++; //2 equates to "late" with the Status enum

    return result; //return the number of Assignments in completed list with "late" status
}


bool AssignmentList::save()
{
    //ofstream out("AssignmentFileTest2.txt");
    ofstream out("AssignmentFile.txt"); 

    if (out.fail())
    {
        cout << "Saves failure.\n";
        return false;//failure to save
    }
    if (assigned.size() > 0) //we only start if the list isn't empty
        for (list<Assignment>::iterator itr = assigned.begin(); itr != assigned.end(); itr++)//iterate through assigned and write a line for each assignment
        {
            string assign = dateToString(itr->assignedDate);
            string due = dateToString(itr->dueDate);
            string status = "assigned"; //all statuses in this list are "assigned" so no need to check
            string delim = ", ";

            //result is MM-DD-YYYY, Description, MM-DD-YYYY, Status then an endline
            out << due << delim << itr->description << delim << assign << delim << status << endl;

        }

    if (completed.size() > 0) //we only start if the list isn't empty
        for (list<Assignment>::iterator itr = completed.begin(); itr != completed.end(); itr++) //iterate through completed and write a line for each assignment
        {
            string assign = dateToString(itr->assignedDate);
            string due = dateToString(itr->dueDate);
            string status;
            string delim = ", ";
            //status on each assignment could be 1="completed" or 2="late". check and << accordingly
            if (itr->stat == 1) status = "completed";
            else status = "late";

            //result is MM-DD-YYYY, Description, MM-DD-YYYY, Status then an endline
            out << due << delim << itr->description << delim << assign << delim << status << endl;
        }

    out.close();

    return true;//file has been saved
}