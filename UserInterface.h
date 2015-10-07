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
    precondition: data has been loaded from a file.
    post condition: a UserInterface object has been created.
    return: none.
    */


    UserInterface(){ ; }
    void switchMainMenu(int user_input);
    int get_input();
    void displayProcessMenu();
    bool addAssignMainMenu();
    bool editDueDateMainMenu();
    bool editDescMainMenu();
    bool editStatusMainMenu();

};

#endif