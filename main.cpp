#include <iostream>
#include<sstream>
#include<fstream>
#include <string> //dont know if this is needed. We can remove later if not 
#include "UserInterface.h"
#include "Assignment.h"
//date.h includes the tokenizer, so no need to include it again

using namespace std;


int main(){

    //used to mark whether or not to suggest saving upon exit.
    //at the start, nothing has changed, so no saving needed



    //creates assigned and completed lists
    list<Assignment> assigned;
    list<Assignment> completed;


    Assignment::load(assigned, completed);//read input file
    UserInterface userinterface(assigned, completed);
    UserInterface::displayProcessMenu(assigned, completed);



    system("pause");
    return(0);
};