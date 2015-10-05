#ifndef USERINTERFACE_H
#define USERINTERFACE_H
/*
starting this file with just a copy of what is before main() in main.cpp file.
We can stage the functions over one by one.  As soon as they are working from
UserInterface then we can take them out of main.cpp.
*/

#include <iostream>
#include<sstream>
#include<fstream>
#include <string>
//#include "list.h"- NOTE: no include guard on list.h file so deleting this.  Is included on Assignment.h file.
#include "AssignmentList.h"
/**************************************************************************************************
Name: Susan Warren and David Jones
Course: CompSci 303
Program: Assignments Program 1
Date: Oct 5, 2015
Description:
Program initiates the main menu from which the user chooses what operation they would like to do.  
The program then processes the choice and asks the user additional questions.

***************************************************************************************************/
using namespace std;

class UserInterface
{
private:
    
    int user_input = 0;//stores menu input or present the menu variable
    AssignmentList li;//assignment object containing assigned and completed lists
    
    bool isChanged = false;
    //tracks if the data has been changed. is true if record has been changed but not saved

public:
    UserInterface(AssignmentList& process):li(process){}
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