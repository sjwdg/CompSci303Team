/*
starting this file with just a copy of what is before main() in main.cpp file.
We can stage the functions over one by one.  As soon as they are working from
UserInterface then we can take them out of main.cpp.
*/

#include <iostream>
#include<sstream>
#include<fstream>
#include <string>
#include "Date.h" 
#include "list.h"
#include "Assignment.h"

using namespace std;

class UserInterface
{
private:
    list<Assignment> assigned;
    list<Assignment> completed;
    int user_input = 0;//menu input or present the menu variable
    bool beenSaved = true;

public:
    UserInterface userinterface(list<Assignment>& assigned, list<Assignment>& completed);//constructor


    int get_input();
    void displayProcessMenu(list<Assignment>& assigned, list<Assignment>& completed);
    void addAssignMainMenu(list<Assignment>& assigned, list<Assignment>& completed);

};

//Get input from console.  does not check if input is an int
int UserInterface::get_input()
{
    int input = 0;
    cin >> input;
    if (!(input > 0 && input < 9))
    {
        cout << "\nError. Please try again.Returning to main menu. ";
        cin.ignore();
        return -1;

    }
    cin.ignore(); // fixes so we can use cin again
    return input;
}


void UserInterface::displayProcessMenu(list<Assignment>& assigned, list<Assignment>& completed)
{
    int user_input = 0;
    while (user_input != 8) // 8 means exit, so we exit the loop
    {
        //comments are for the needed input 
        cout << "\nSelect from the following options: \n"
            << "1. Display Assignments \n"  //no needed input
            << "2. Add assignment \n" //get the details (description, dates, status) Status will determine the list
            << "3. Edit a Due Date \n" //get the assigned date and the new due date
            << "4. Edit a description  \n" //get the assigned date and the new descfription
            << "5. Complete an assignment \n" //get the assigned date, then move that one to the completed list
            << "6. Display number of late assignments \n"
            << "7. Save \n"
            << "8. Exit \n\n"
            << "Your input: ";

        user_input = get_input(); //gets the users input. Makes sure it's valid

        //use a switch to do one of the following actions.
        switch (user_input)
        {
        case 1:
            cout << "\n\n1 - Display assignments, was chosen\n\n";
            Assignment::display(assigned, completed);
            break;

        case 2:
            cout << "\n\n2 - Add assignments, was chosen\n\n";
            addAssignMainMenu(assigned, completed);
            break;

        case 3:
            cout << "\n\n3 - Edit a Due Date, was chosen\n\n";
            //ChangedDueDate(assigned);
            break;

        case 4:
            cout << "\n\n4 - Edit a description, was chosen\n\n";
            break;

        case 5:
            cout << "\n\n5 - Complete an assignment, was chosen\n\n";
            break;

        case 6:
            cout << "\n\n6 - Display number of late assignments, was chosen\n\n";
            break;

        case 7:
            cout << "\n\n7 - Save, was chosen\n\n";
            break;

        case 8:
            cout << "\n\n8 - Exit, was chosen\n\n";
            exit(0);

        default:
            cout << "\n\nNumber entered is not 1 to 8.\n\n";
        }
    }
}


//this can only add to the assignment list from the main menu Add.
void UserInterface::addAssignMainMenu(list<Assignment>& assigned, list<Assignment>& completed)
{
    Date due;
    Date assignDate;
    string d;
    string a;
    string describe;
    string status;

    cout << "Note: All assignments added from main menu are automatically given"
        << "\na status of \"assigned\". Status can only be edited from the main "
        << "\nmenu selection 5 (Complete assignment). \n\n";
    cout << "When was this assigned? (mm-dd-yyyy): ";
    try
    {
     
        getline(cin, a);//reads in the assignment date
        assignDate = Date(a);//checks and creates a date object

        //Note there currently is not a check on entering date as a letter.  Letters translates to a 1-1-1 DATE

        //searches assigned and completed list to see if date already exists.
        if (Assignment::search(assigned, assignDate) != assigned.end() || Assignment::search(completed, assignDate) != completed.end())
        {
            cout << "Assignment for date " << assignDate << " already exists. Returning to main menu\n";
            return;
        }
    }
    catch (exception e)
    {
        cout << "\nInvalid Assignment Date. \n\n";

        return;
    }
    cout << "When is this due? (mm-dd-yyyy): ";

    try
    {
        getline(cin, d);
        due = Date(d);
    }

    catch (exception e)
    {
        cout << "\nInvalid Due Date. \n\n";
        return;
    }

    if (due < assignDate)
    {
        cout << "\nError: Due Date must be after assigned date. Returning to main menu.\n\n";
        return;
    }

    cin.clear();
    cout << "What is the description?: ";

    getline(cin, describe);

    if (describe.length() > 15)
    {
        //ensures less than 15 character description
        cout << "\nError in description. Returning to main menu\n\n";
        return;
    }
    Assignment toAdd(due, describe, assignDate, "assigned");
    Assignment::addAssignment(assigned, toAdd);
    cout << "Added assignment " << assignDate << endl;
}



//changes due date for a specific assignment
//ChangedDueDate(list<Assignment>& assigned)
//{

//}
//
//
//
//
////edit a date
///*check the date*/
///*find the node. then change the date*/
//
////edit a description
///*find the node. edit the description */
//
////Edit status or Complete Assignment
///*find the assignment in Assigned list. call add on the completed list. Delete from assignment list*/
//
////Display number of late
///*Iterate through the completed list, incrementing an int to count the late ones*/
//
////Record assignment lists
///*Const Iterate through each, using a ofile stream to record each*/
//
////Exit
///*I guess we could delete the stuff, but that isn't necessary */

