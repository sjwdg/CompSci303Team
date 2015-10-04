#include "UserInterface.h"
#include <iostream>
#include<sstream>
#include<fstream>
#include <string> //dont know if this is needed. We can remove later if not 


//date.h includes the tokenizer, so no need to include it again

using namespace std;


int main(){

    AssignmentList proc;
    UserInterface ui(proc);
    ui.displayProcessMenu();

    system("pause");
    return(0);
};