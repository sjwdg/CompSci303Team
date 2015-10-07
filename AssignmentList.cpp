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

    beenSaved = true;
}


AssignmentList::~AssignmentList()
{
    ;
}



list<Assignment>::iterator AssignmentList::search(list<Assignment>& li, Date d)
{
    list<Assignment>::iterator itr = li.begin();
    if (li.size() == 0)
    {
        itr = li.end();
        return itr;
    }

    while (itr != li.end())
    {
        if (itr->assignedDate == d) return itr;
        ++itr;
    }
    return itr;
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
    itr = search(completed, d);
    if (itr != completed.end()) return true;//found the assignDate completed
    else return false; //didn't find assignDate


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

    list<Assignment>::iterator itr = search(completed, d);
    if (itr == completed.end()) return false;
    else return true;
    return false;
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

    list<Assignment>::iterator itr = search(assigned, d);
    if (itr == assigned.end()) return false;
    else return true;
}


string AssignmentList::dateToString(Date& d)
{
    string temp = "";


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
    stringstream display;
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
    string t = display.str();
    return t;
}


void  AssignmentList::addAssignment(Assignment& a)
{
    if (assigned.empty()) assigned.push_front(a); //if list is empty, simply push_front
    else
    {
        if (assigned.find(a) == assigned.end())
        {
            for (list<Assignment>::iterator itr = assigned.begin(); itr != assigned.end(); ++itr)
            {
                //if (itr->assignedDate > a.assignedDate) //find where one is > , if exists
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
                if (itr->assignedDate > a.assignedDate) //find where one is > , if exists
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
    fin.open("AssignmentFile.txt");

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
            //cout << "reading assignDate " << assignString << endl;
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
    
    if (compareDates(dueDate, assignedDate) == false)
    {
        throw std::exception("Bad due date or assigned date");
        return false;
    }

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

    if (compareDates(completeDate, assignDate) == false)
    {
        throw std::exception("Bad completion date or assigned date");
        return false;
    }

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

    if (dateOfCompletion > itr->dueDate) itr->setStat("late");
    else itr->setStat("complete");
    addToCompleted(*itr);
    assigned.remove(*itr);
    return true;
}



int AssignmentList::getNumberLate()
{

    int result = 0;
    for (list < Assignment>::iterator itr = completed.begin(); itr != completed.end(); itr++)
        if (itr->stat == 2) result++; //2 equates to "late" with the Status enum

    return result;
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
        for (list<Assignment>::iterator itr = assigned.begin(); itr != assigned.end(); itr++)
        {
            string assign = dateToString(itr->assignedDate);
            string due = dateToString(itr->dueDate);
            string status = "assigned";
            string delim = ", ";

            out << due << delim << itr->description << delim << assign << delim << status << endl;

        }

    if (completed.size() > 0) //we only start if the list isn't empty
        for (list<Assignment>::iterator itr = completed.begin(); itr != completed.end(); itr++)
        {
            string assign = dateToString(itr->assignedDate);
            string due = dateToString(itr->dueDate);
            string status;
            string delim = ", ";
            if (itr->stat == 1) status = "completed";
            else status = "late";

            out << due << delim << itr->description << delim << assign << delim << status << endl;
        }

    out.close();

    return true;//file has been saved
}






