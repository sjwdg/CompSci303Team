/**************************************************************************************************
Name: David Jones and Susan Warren
Course: CompSci 303
Program: Assignments Program 1
Date: Oct 5, 2015
Description:
Program manages assignment records, assigned list of assignments, and completed list of assignments.
***************************************************************************************************/

#include "UserInterface.h"
#include <iostream>
#include<sstream>
#include<fstream>
#include <string> 
//date.h includes the tokenizer, so no need to include it again

using namespace std;


int main(){

    AssignmentList proc;//create lists
    proc.load();//load data from input file
    UserInterface ui(proc);//create main menu

    ui.displayProcessMenu();//run main menu to manage data eg edit, add, or save files.


    system("pause");
    return(0);
};