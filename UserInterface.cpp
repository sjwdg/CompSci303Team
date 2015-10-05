
#include <iostream>
#include<sstream>
#include<fstream>
#include <string>

#include "UserInterface.h"

using namespace std;


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


void UserInterface::displayProcessMenu()
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
            cout << li.displayAssignments();
            break;

        case 2:
            cout << "\n\n2 - Add assignments was chosen\n\n";
            if (addAssignMainMenu()){ isChanged = true; }
            break;

        case 3:
            cout << "\n\n3 - Edit a Due Date was chosen\n\n";
            if (editDueDateMainMenu()){ isChanged = true; }
            break;

        case 4:
            cout << "\n\n4 - Edit a description was chosen\n\n";
            if (editDescMainMenu()){ isChanged = true; }
            break;

        case 5:
            cout << "\n\n5 - Complete an assignment was chosen\n\n";
            //if (editStatusMainMenu()){ isChanged = true; }
            break;

        case 6:
            cout << "\n\n6 - Display number of late assignments was chosen\n\n";

            break;

        case 7:
            cout << "\n\n7 - Save was chosen\n\n";
            break;

        case 8:
            cout << "\n\n8 - Exit was chosen\n\n";
            exit(0);

        default:
            cout << "\n\nNumber entered is not 1 to 8.\n\n";
        }
    }
}


//this can only add to the assignment list from the main menu Add.
bool UserInterface::addAssignMainMenu()
{
    string newAssignDueDate;
    string newAssignDate;//assignment date for date to be added.
    string describe;
    string status;

    cout << "Note: All assignments added from main menu are automatically given"
        << "\na status of \"assigned\". Status can only be edited from the main "
        << "\nmenu selection 5 (Complete assignment). \n\n";
    cout << "When was this assigned? (mm-dd-yyyy): ";

    getline(cin, newAssignDate);//reads in the assignment date

    //check if duplicate assignment date in list
    if (li.alreadyExists(newAssignDate) != true)
    {
        cout << "Assigned Date Error. Date entered has been used previously. \n";
        return false;
    }

    //ask user for due date and check if valid
    cout << "When is this due? (mm-dd-yyyy): ";

    try
    {
        getline(cin, newAssignDueDate);
        li.compareDates(newAssignDueDate, newAssignDate);
    }

    catch (exception e)
    {
        cout << "Due Date Error. Due date is less than assignment date. \n"; //can be changed
        return false;
    }

    cin.clear();
    cout << "What is the description?: ";

    getline(cin, describe);

    if (describe.length() > 15)
    {
        //ensures less than 15 character description
        cout << "\nError in description. Returning to main menu\n\n";
        return false;
    }
    bool addCheck;
    addCheck = li.addAssignment(newAssignDate, describe, newAssignDueDate);

    if (addCheck)cout << "Added assignment " << newAssignDate << endl;
    else cout << "Failed to add Assignment";

    return addCheck;
}



//changes due date for a specific assignment
bool UserInterface::editDueDateMainMenu()
{
    string dueDate;
    string assignDate;//assignment date for record to be edited.
    string status;
    bool addCheck = false;

    cout << "What is the date for the assignment to be edited? (mm-dd-yyyy): ";

    getline(cin, assignDate);//reads in the assignment date

    //check if duplicate assignment date in list
    if (li.alreadyExists(assignDate) == true)
    {
        if (li.isCompleted(assignDate) == true)
        {
            cout << "Error. Assignment has been completed and information can not be changed. \n";
            return false;
        }
        else
        {
            //ask user for due date and check if valid
            cout << "What is the new due date? (mm-dd-yyyy): ";

            try
            {
                getline(cin, dueDate);
                li.compareDates(dueDate, assignDate);
            }

            catch (exception e)
            {
                cout << "Due Date Error. Due date is less than assignment date. \n"; //can be changed
                return false;
            }

            addCheck = li.editDueDate(assignDate, dueDate);

            if (addCheck) cout << "Edited due date for assignment " << assignDate << endl;
            else cout << "Failed to edit due date for assignment";
            return addCheck;
        }
    }
    else
    {
        cout << "\nAssignment date " << assignDate << " not in list\n";
        return false;//because not in list
    }
   
    return false;
}


//edit a description
/*find the node. edit the description */
bool UserInterface::editDescMainMenu()
{
    string assignDate;
    string desc;//description for record to be edited.
    string status;
    bool addCheck = false;

    cout << "When is the date of the assignment to be edited? (mm-dd-yyyy): ";

    getline(cin, assignDate);//reads in the assignment date

    //check if duplicate assignment date in list
    if (li.alreadyExists(assignDate) == true)
    {
        if (li.isCompleted(assignDate) == true)
        {
            cout << "\nError. Assignment has been completed and information can not be changed. \n";
            return false;
        }
        else
        {
            //ask user description
            cout << "What is the new description?: ";

            getline(cin, desc);

            if (desc.length() > 15)
            {
                //ensures less than 15 character description
                cout << "\nError in description. Returning to main menu\n\n";
                return false;
            }
           
            addCheck = li.editDescription(assignDate, desc);

            if (addCheck) cout << "Edited description for assignment " << assignDate << endl;
            else cout << "Failed to edit description for assignment";
            return addCheck;
        }
    }
    else
    {
        cout << "\nAssignment date " << assignDate << "is not in list\n";
        return false;//because not in list
    }

    return false;
}

//Edit status or Complete Assignment
/*find the assignment in Assigned list. call add on the completed list. Delete from assignment list*/
//bool UserInterface::editStatusMainMenu()
//{
//    string assignDate;
//    string completeDate;//date assignment was completed
//    string dueDate;
//    string status;
//    bool isLate = false;
//    bool addCheck = false;
//
//    cout << "When is the date of the assignment to be edited? (mm-dd-yyyy): ";
//
//    getline(cin, assignDate);//reads in the assignment date
//
//    //check if duplicate assignment date in list
//    if (li.alreadyExists(assignDate) == true)
//    {
//        if (li.isCompleted(assignDate) == true)
//        {
//            cout << "\nError. Assignment has been completed and information can not be changed. \n";
//            return false;
//        }
//        else //valid assignment, start change status process.
//        {
//            //ask user description
//            cout << "What is the date of completion for the assignment? (mm-dd-yyyy): ";
//            //start up coding here again.
//            try
//            {
//                getline(cin, completeDate);
//                li.compareDates(assignDate, completeDate); 
//               
//            }
//
//            catch (exception e)
//            {
//                cout << "\nError. Completion date is less than assignment date. \n"; //can be changed
//                return false;
//            }
//
//            
//            if (li.compareDates(completeDate, getDueDate())//returns true if late
//            {
//                status = "late";
//                cout << "Assignment is late.\n";
//            }
//            else
//            {
//                status = "completed";
//                cout << "Assignment was completed on time.\n";
//            }
//            
//            //save status statement.
//            addCheck = li.completeAssignment(assignDate, status);
//
//            if (addCheck) cout << "Changed status to " << status << " for assignment " << assignDate << " and moved it to completed list." << endl;
//            else cout << "Failed to change status for assignment";
//            return addCheck;
//        }
//    }
//    else
//    {
//        cout << "\nAssignment date " << assignDate << "is not in list\n";
//        return false;//because not in list
//    }
//
//    return false;
//
//}


////Display number of late
///*Iterate through the completed list, incrementing an int to count the late ones*/
//
////Record assignment lists
///*Const Iterate through each, using a ofile stream to record each*/
