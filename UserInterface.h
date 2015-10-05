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

using namespace std;

class UserInterface
{
private:
    
    int user_input;//menu input or present the menu variable
    AssignmentList li;
    bool isChanged = false;

public:
    UserInterface(AssignmentList process) : li(process) {}//constructor
    UserInterface(){ ; }

    int get_input();
    void displayProcessMenu();
    bool addAssignMainMenu();
    bool editDueDateMainMenu();
    bool editDescMainMenu();
    bool editStatusMainMenu();
    int countNumOfLateAssign();
    void save();
};


#endif