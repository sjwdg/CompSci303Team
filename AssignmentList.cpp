

#include "AssignmentList.h"

#include <iostream>
#include<sstream>
#include<fstream>
#include <string>

using namespace std;


AssignmentList::AssignmentList()
{
    load();
    beenSaved = true;
}


AssignmentList::AssignmentList(AssignmentList& other)
{
    assigned = other.assigned;
    completed = other.completed;
    beenSaved = other.beenSaved;

}



AssignmentList::~AssignmentList()
{
    ;
}


//use this to search by assigned date. Can take either list and returns an iterator if it finds the assignment
//should work on empty lists and in the "not found" case
//it will return an iterator that compares as 'true' to any list.end() if no match is found
//pre: valid list and date is passed
//post: iterator is made and is now pointing at a result
//returns: An iterator pointing to a list.end() or to the sought assignment
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

//pre: string is passed representing an assignment date
//post: String is converted to a date, and that assignment date is searched
//returns: true if assignment is in a list, false otherwise
bool AssignmentList::alreadyExists(string assign)
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
    if (itr != assigned.end()) return false;
    itr = search(completed, d);
    if (itr != assigned.end()) return false;
    else return true;

}

//pre: string is passed representing an assignment date
//post: string is made into a date and the assigned list is searched for that assignment date
//returns: true if the assigned date exists in the assigned list, false otherwise
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

//pre: a date is passed
//post: date is converted to string, then tokenized and reassembled with dashes
//returns: string representing date with dashes
string AssignmentList::dateToString(Date& d) 
{
    string temp = "";
    

    string s = d.toString();
    String_Tokenizer st(s, "/");
    string month = st.next_token();
    string day = st.next_token();
    string year = st.next_token();
    string result =  month + "-" +day + "-" + year;
    return result;
}

//display 
/*Iterate though each list with a const iterator. Print resuts to consol*/

//pre: none
//post: For each assignment, a block of text is made 
//returns: a string for the user interface to display
string AssignmentList::displayAssignments() 
{
    stringstream display;
    display << "Assigned List" << "\n" << "--------------------" << "\n";

    //iterate through all the assigned list assignments
    for (list<Assignment>::iterator itr = assigned.begin() ; itr != assigned.end(); itr++)
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
    return t ;
}


//pre: and Assignment is passed that should be added 
//post: The appropriate place is found via iteration and the assignment is placed
//returns: none
void  AssignmentList::addAssignment(Assignment& a)
{
    if (assigned.empty()) assigned.push_front(a); //if list is empty, simply push_front
    else
    {
        if (assigned.find(a) == assigned.end())
        {
            for (list<Assignment>::iterator itr = assigned.begin(); itr != assigned.end(); ++itr)
            {
                if (itr->assignedDate > a.assignedDate) //find where one is > , if exists
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

//pre: assignment is made with correct values and passed
//post: assignment is added to 'completed' list
//returns: none
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

//this can only add to the assignment list.
//pre: correct vales are passed in string form
//post: an assignment is made and passed to the function to add to the lists
//returns: a bool denoting success or failure
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
        return false; //errpr occured, so return false 
    }
    
    return true; //because no errors occured
        
}


//this can add to eitherlist
//We assume that the file is correct, which is reasonable if 
//   we assume this is a program with its own files
//just in case, a line can have an error which would be skipped
//pre: Assignment file is already known. values therein will not contain letters for dates, nor improper data otherwise
//post: The functions to add to lists are used and the lists are populated
//returns: none
void AssignmentList::load()
{
    ifstream fin;
    fin.open("AssignmentFile.txt");
    string s;

    while (getline(fin, s))
    {

        try
        {
            //NOTE: The substrings are to remove extra spaces
            String_Tokenizer st(s, ",");
            Date due(st.next_token());
            string des(st.next_token());
            des = des.substr(1, des.length()); //subst without the blank space
            Date assignDate(st.next_token());
            string status(st.next_token());
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
}

//pre: two strings as dates are passed
//post: exception if dates are invalid, otherwise a bool shows the comparison
//returns: true if lhs > rhs, false otherwise
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