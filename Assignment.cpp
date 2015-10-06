
#include <iostream>
#include<sstream>
#include<fstream>
#include <string> //dont know if this is needed. We can remove later if not 
#include "Date.h" 
#include "list.h"
#include "Assignment.h"
//date.h includes the tokenizer, so no need to include it again

using namespace std;

//change the due date using a string converted to a Date.
void Assignment::setDueDate(string dDate)
{
    dueDate = Date(dDate);
}


//change the description using a string.
void Assignment::setDesc(string desc)
{
    description = desc;
}


    //the lowercase first letter is guaranteed from user entry, and assumed from the input file
    //this function uses the string parameter in the Assignment constructor to set the status 
    void Assignment::setStat(string a)
    {
        if (a == "assigned") stat = Assigned;
        else if (a == "completed") stat = Completed;
        else stat = Late;
    }


    //if this doesn't work, we can make it a member function. Or, we can manually access the attributes and print in the "save()" body
    ostream& operator <<(ostream& out,  Assignment& work)
    {
        //print out the stuff
        out << "Due: " << work.getDueDate() << endl
            << "Description: " << work.description << endl
            << "Assigned: " << work.getAssignedDate() << endl
            << "Status: ";

        switch (work.stat)
        {
        case 0: out << "Assigned"; break;
        case 1: out << "Completed"; break;
        case 2: out << "Late"; break;
        }

        out << "\n";
        return out;
    }

    string Assignment::dateToString(Date& d)
    {
        string temp = "";


        string s = d.toString();
        String_Tokenizer st(s, "/");
        string month = st.next_token();
        string day = st.next_token();
        string year = st.next_token();
        string result = month + "-" + day + "-" + year;
        return result;
    }
