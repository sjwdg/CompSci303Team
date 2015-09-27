#include <iostream>
#include<sstream>
#include<fstream>
#include <string> //dont know if this is needed. We can remove later if not 
#include "Date.h" 
#include "list.h"
//date.h includes the tokenizer, so no need to include it again

using namespace std;

//make an Assignment struct
struct Assignment {
    enum Status{ Assigned, Completed, Late };
    string description;
    Date assignedDate, dueDate;
    Status stat;
    Assignment(Date due, string description, Date assign, string status) :
        dueDate(due), description(description), assignedDate(assign){
        setStat(status);
    };
    friend ostream& operator <<(ostream& out, Assignment& work); //overload to print what we need

    bool operator == (Assignment& other){ return (assignedDate == other.assignedDate); }
    void setStat(string s); // change the status using the string
};

void Assignment ::setStat(string a)
{
    if (a == "assigned" || a == "Assigned") stat = Assigned;
    else if (a == "completed" || a == "Completed") stat = Completed;
    else if (a == "late" || a == "Late") stat = Late;
    else throw std::exception("Invalid status");
}

//if this doesn't work, we can make it a member function. Or, we can manually access the attributes and print in the "save()" body
 ostream& operator <<(ostream& out, const Assignment& work)
{
     //print out the stuff

     cout << work.description << "\n" << "Due: " << work.dueDate << "\n" << "Assigned: " <<work.assignedDate << "\n" << "Status: ";

     switch (work.stat)
     {
     case 0: cout << "Assigned"; break;
     case 1: cout << "Completed"; break;
     case 2: cout << "Late"; break;
     }

     cout << "\n";
     return out;
}



//It doesn't currently insure an int. I'd like that to be added later
int get_input()
{
    int input = 0;
    cin >> input;
    if (!(input > 0 && input < 9))
    {
        cout << "\nError. Please try again.\nYour input: ";
        input = get_input();
    }
        
    return input; 
}



//Each of the following can be fleshed out into a function to be called after the menu is selected from

//display 
/*Iterate though each list with a const iterator. Print resuts to consol*/

void display(const list<Assignment>& assign, const list<Assignment>& complete)
{
    for (list<Assignment>::const_iterator itr = assign.begin(); itr != assign.end(); itr++)
    {
        cout << *itr << endl;
    }

    for (list<Assignment>::const_iterator itr = complete.begin(); itr != complete.end(); itr++)
    {
        cout << *itr << endl;
    }
}



//add
/*Verify the assigment dates and such. If it is all good, continue*/
/*Iterate to the place or use ordered list. Add the Node*/
//WHICH LIST WILL BE DETERMINED BY THE STATUS

void addAssignment(list<Assignment>& chosen, Assignment& a)
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

//wrapper that decides which list to add to 
void addAssignment(list<Assignment>& assigned, list<Assignment>& completed, Assignment& a)
{
    if (a.stat == 0) addAssignment(assigned, a);
    else addAssignment(completed, a);

}

void addAssignment(list<Assignment>& assigned, list<Assignment>& completed)
{
        Date due;
        Date assignDate;
        string d;
        string a;
        string describe;
        string status;
        string junk;
        
        try{

            cout << "When was this assigned?: ";

            try
            {
                getline(cin, a);
                assignDate = Date(a);
            }

            catch (exception e)
            {
                cout << "Invalid Date. \n\n";

                return;
            }


            cout << "When is this due?: ";

            try
            {

                getline(cin, d);
                due = Date(d);
            }

            catch (exception e)
            {
                cout << "Invalid Date. \n\n";
                return;
            }

            if (due < assignDate)
            {


                cout << "Error: Due Date must be after assigned date.";
                return;
            }

            cin.clear();
            cout << "What is the description?: ";



            getline(cin, describe);
            cout << "Is this assigned, completed, or late?: ";
            getline(cin, status);
            if (status == "") return;//no empty status allowed
            status[0] = tolower(status[0]); //make comparison easier at any status check
            if (!(status == "late" || status == "completed" || status == "assigned")) return; //stops if invalid status
            
            addAssignment(assigned, completed, Assignment(due, describe, assignDate, status));

        }

        catch (exception e)
        {
            return; //and exceptions throughout the addAssignment will cause the entire thing to not happen 
        }
}


void load(list<Assignment>& assign, list<Assignment>& completed)
{
    ifstream fin;
    fin.open("AssignmentFile.txt");
    string s;

    while (fin.good())
    {
        getline(fin, s);
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
        addAssignment(assign, completed, d);
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

int main(){

    //we can use a bool to mark whether or not to suggest saving upon exit.
    //at the start, nothing has changed, so no saving needed
    bool beenSaved = true;
    

    // populate the lists

    //Present the Menu
    int user_input = 0;

    //reset the beenSaved to true (necessary if we use 'Add Assignment' to populate lists_
    beenSaved = true;

    list<Assignment> assigned;
    list<Assignment> completed;

    
    load(assigned, completed);

    while (user_input != 8) // 8 means exit, so we exit the loop
    {
        //comments are for the needed input 
        cout << "Select from the following options: \n"
            << "1. Display Assignments \n"  //no needed input
            << "2. Add assignment \n" //get the details (description, dates, status) Status will determine the list
            << "3. Edit a Due Date \n" //get the assigned date and the new due date
            << "4. Edit a description  \n" //get the assigned date and the new descfription
            << "5. Complete an assignment \n" //get the assigned date, then move that one to the completed list
            << "6. Display number of late assignments \n"
            << "7. Record assignment lists \n"
            << "8. Exit \n\n"
            << "Your input: ";

        user_input = get_input(); //gets the users input. Makes sure it's valid

        //use a switch to do one of the actions.
    }


    addAssignment(assigned, completed);
    display(assigned, completed);
    

    system("pause");
};