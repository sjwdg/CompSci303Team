/**************************************************************************************************
Name: Susan Warren and David Jones
Course: CompSci 303
Program: Assignments Program 1
Date: Oct 5, 2015
Description:
Program initiates the main menu from which the user chooses what operation they would like to do.
The program then processes the choice and asks the user additional questions. Associated .cpp file is 
UserInterface.cpp
***************************************************************************************************/

#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <iostream>
#include<sstream>
#include<fstream>
#include <string>

//#include "list.h"- NOTE: no include guard on list.h file so do not add this.  Is included on Assignment.h file.

#include "AssignmentList.h"

using namespace std;

class UserInterface
{
private:

    int user_input = 0;//stores menu input or present the menu variable
    AssignmentList li;//assignment object containing assigned and completed lists

    bool isChanged = false;
    //tracks if the data has been changed. is true if record has been changed but not saved

public:
    UserInterface(AssignmentList& process) :li(process){}
    /*
    pre: data has been loaded from a file.
    post: a UserInterface object has been created.
    return: none.
    */

    UserInterface(){ ; }
    /*
    pre: constructor has been called.
    post: a UserInterface object has been created.
    return: none.
    */


    int get_input();
    /*
    pre: constructor has been called, file has been opened, data has been read, lists of assignments have been generated. Menu has printed to console, user has been asked for input.
    post: User input is read.
    return: int for user choice
    */


    void displayProcessMenu();
    /*
    pre: file has been read, lists and assignments have been generated.
    post: main menu has printed to screen, user input for operation has been read
    return: none.
    */


    void switchMainMenu(int user_input);
    /*
    pre: main menu has printed to screen. User has entered a number for the operation they wish to do.
    post: process is started for main menu choice.
    return: none.
    */
   
   
    bool addAssignMainMenu();
    /*
    pre: main menu has printed to screen. User has entered a number 2 for adding a assignment.
    post: user has provided assignment date, due date, and description.  program has made validation checks on dates and descriptions. If data is valid then program creates a assignment and loads it into the assigned list.
    return: true if added assignment to assigned list
            false if data was bad or assignment was not added.
    */


    bool editDueDateMainMenu();
    /*
    pre: main menu has printed to screen. User has entered a number 3 for editing the due date of an existing date.  Assignment is in the assigned list.
    post : user has provided assignment date and new due date. Program has made validation checks on dates. If dates are valid, the assignment exists, and the assignment is not in the completed list then program edits the due date for the assignment associated with the assignment date.  The modified assignment is inserted into the assigned list in ascending order by due date.
    return : true if added assignment to assigned list
             false if data was bad or assignment was not modified.
       */


    bool editDescMainMenu();
    /*
    pre: main menu has printed to screen. User has entered a number 4 for editing the description of an existing date.  Assignment is in the assigned list.
    post : user has provided assignment date and new description. Program has made validation checks on date and description. If dates is valid, the assignment exists, and the assignment is not in the completed list then program edits the description for the assignment associated with the assignment date.  
    return : true if description is modified
    false if description was bad or not modified.
    */


    bool editStatusMainMenu();
    /*
    pre: main menu has printed to screen. User has entered a number 5 for editing the status of an existing date.  Assignment is in the assigned list.
    post : user has provided assignment date and completion date. Program has made validation checks on dates. If dates are valid, the assignment exists, and the assignment is not in the completed list then program edits the completion date for the assignment associated with the assignment date.  The status is changed to "late" if the due date has passed and "completed" if it has not passed.  The modified assignment is removed from the assigned list and is inserted into the completed list in ascending order by due date.
    return : true if assignment added to completed list and status modified.
    false if data was bad or assignment was not modified.
    */

};

#endif