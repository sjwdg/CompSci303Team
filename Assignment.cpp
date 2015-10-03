
#include <iostream>
#include<sstream>
#include<fstream>
#include <string> //dont know if this is needed. We can remove later if not 
#include "Date.h" 
#include "list.h"
#include "Assignment.h"
//date.h includes the tokenizer, so no need to include it again

using namespace std;

  

    //the lowercase first letter is guaranteed from user entry, and assumed from the input file
    //this function uses the string parameter in the Assignment constructor to set the status 
    void Assignment::setStat(string a)
    {
        if (a == "assigned") stat = Assigned;
        else if (a == "completed") stat = Completed;
        else stat = Late;
    }


    //if this doesn't work, we can make it a member function. Or, we can manually access the attributes and print in the "save()" body
    ostream& operator <<(ostream& out, const Assignment& work)
    {
        //print out the stuff

        cout << "Due: " << work.dueDate << endl
            << "Description: " << work.description << endl
            << "Assigned: " << work.assignedDate << endl
            << "Status: ";

        switch (work.stat)
        {
        case 0: cout << "Assigned"; break;
        case 1: cout << "Completed"; break;
        case 2: cout << "Late"; break;
        }

        cout << "\n";
        return out;
    }

    

    //use this to search by assigned date. Can take either list and returns an iterator if it finds the assignment
    //should work on empty lists and in the "not found" case
    //it will return an iterator that compares as 'true' to any list.end() if no match is found
    list<Assignment>::iterator Assignment::search(list<Assignment>& li, Date d)
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


    //display 
    /*Iterate though each list with a const iterator. Print resuts to consol*/
    void Assignment::display(const list<Assignment>& assign, const list<Assignment>& complete)
    {
        cout << "Assigned List" << endl << "----------------------------" << endl;

        for (list<Assignment>::const_iterator itr = assign.begin(); itr != assign.end(); itr++)
        {
            cout << *itr << endl;
        }

        cout << endl << "Completed List" << endl << "----------------------------" << endl;

        for (list<Assignment>::const_iterator itr = complete.begin(); itr != complete.end(); itr++)
        {
            cout << *itr << endl;
        }
    }


    //    //add from file
    //    /*Verify the assigment dates and such. If it is all good, continue*/
    //    /*Iterate to the place. Add the Node*/
    //    //WHICH LIST WILL BE DETERMINED BY THE STATUS
    void Assignment::addAssignment(list<Assignment>& chosen, Assignment& a)
    {
        if (chosen.empty()) chosen.push_front(a); //if list is empty, simply push_front
        else
        {
            if (chosen.find(a) == chosen.end())
            {
                for (list<Assignment>::iterator itr = chosen.begin(); itr != chosen.end(); ++itr)
                {
                    if (itr->assignedDate > a.assignedDate) //find where one is > , if exists
                    {
                        chosen.insert(itr, a); //put it where the larger one was
                        return;
                    }
                }
            }
            chosen.push_back(a); //none were greater. Just put it at the end
            return;
        }
    }


    //changes due date for a specific assignment
    //ChangedDueDate(list<Assignment>& assigned)
    //{
    //
    //}


    //this can add to either list
    //We assume that the file is correct, which is reasonable if 
    //   we assume this is a program with its own files
    void Assignment::load(list<Assignment>& assign, list<Assignment>& completed)
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
                des = des.substr(1, des.length());
                Date assignDate(st.next_token());
                string status(st.next_token());
                status = status.substr(1, status.length());
                status[0] = tolower(status[0]);

                if (due < assignDate) return;

                Assignment d(due, des, assignDate, status);
                if (d.stat == 0) addAssignment(assign, d); //status == assigned
                else addAssignment(completed, d); //status == completed or late
            }
            catch (exception e)
            {
                cout << "\n Input file error: Dropping one assignment \n";
            }
        }
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


//};
