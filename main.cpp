/**************************************************************************************************
Name: David Jones and Susan Warren
Course: CompSci 303
Program: Assignments Program 1
Date: Oct 5, 2015
Description:
Program manages assignment records, assigned list of assignments, and completed list of assignments.


Assumptions:
    •	Program automatically throws away a bad data line when reading from an input  file
    •	User inputs correct data type in correct format
    •	description is 15 characters or less in size
    •	For new records assigned date, due date, assignment description, and status will be entered in at same time from the main menu.
    •	A completion date or status will not be entered in the add assignment at the main menu by the user.  The status will automatically be set to “assigned” and inserted in the assigned list.  Any completion or late status must be entered using the “Complete assignment” selection at the main menu
    •	Entries have unique assignment dates.  There will not be any duplicate assignment dates.
    •	Exit will not automatically save data.  Data must be saved using Save.
    •	Date check is not against what current real time date is
    •	All dates are shown in US date format
    •	An assignment cannot be moved from the completed list back to the assigned list.
    •	Due date, description, and status edits:
        o	Due dates, descriptions, and status cannot be changed once assignment has been moved to the completed list.
        o	Status as read from the file will be a string describing the status and not a date.
        o	A completion date will be entered from the main menu by the user and will be a date. The date is then compared to the due date to determine if the status is late or completed. After the comparison status is stored in the record as a string.  The status date is not retained.
    •	 “Save” at the main menu overwrites the competed assignment file
    •	Each list has been maintained so that each list is ordered from earliest to latest due date.
    •	All data after initial installation from file remains sorted by due date
    •	Data for each assignment will be displayed in a line format with headers. Format to display assignments is as follows:
            List Name
            Due: mm-dd-yyyy
            Description: xxxxxxxxxxxxxxx
            Assigned: mm-dd-yyyy
            Status: xxxxxxxx

References
    •	Phone Book program
        -main.cpp
        -vector_Based_Phone_Dirctory.h
        -User_Interface.h

Program credits
    •	Source code from Dr Kuhail or Objects, Abstraction, Data Structures, and Design Using C++
        o	Date.h
        o	const_list_iterator.h
        o	list.h
        o	list_iterator.h
        o	StringTokenizer.h


Algorithm:
1.	Data stored in the assignment is structured as follows:
    a.	The information per assignment record is stored all in one line. Each data value is separated from the next by a comma then a space.
    b.	The order is of data values in a record is dueDate, description, assignedDate, status
    c.	Example 2-11-2015, linked lists, 2-2-2015, late

2.	The program will function as follows:
    a.	When the program starts up the following:
        i.	 two doubly-linked lists with iterators will be generated
            1.	Assigned assignments list
                a.	Consists of all assignments that have been assigned
            2.	Completed assignments list
                a.	Consists of all assignments that are:
                    i.	Completed
                    ii.	Late
        ii.	A variable will be generated that tracts that data modification has occurred will be set:
            1.	Variable set to:
                a.	True
                    i.	Program initialized
                    ii.	Whenever Save is used or Exit is confirmed.
                b.	False
                    i.	Valid assignment data is read from a file
                    ii.	Whenever assignment data is entered or edited.
    b.	The information furnished when the assignment is first entered will be as follows:
        i.	assignedDate – date assignment was assigned, date is in US format
        ii.	dueDate - date assignment is due, date is in US format
        iii.	description – description of assignment, description is in string format 15 chars in length
        iv.	status – enum type that stores as a string the following one of the following  status states:
            1.	assigned
            2.	completed
            3.	late
    c.	The assignments in both lists will be sorted and stored by due date in the following order: year number, month number and day number.
    d.	Initial assignments will be entered by using a file.  After file has been loaded then all other entries are by user via console menu.
        i.	On startup the program will:
            1.	Check if the data file name is valid
            2.	Open the file
                 a.	Error message to console if file does not open.
            3.	Set variable tracking changes to false
            4.	Start reading data lines
            5.	Program will check to make sure:
                a.	The assignment date is valid
                    i.	date has been provided
                    ii.	date is not duplicated.
                    iii.	Is a valid month, day, or year value
                    iv.	date is in US format
                b.	description is valid
                    i.	description is a string of length 15 or less.
                c.	The due date is valid
                    i.	date has been provided
                    ii.	Is a valid month, day, or year value
                    iii.	date is in US format
                    iv.	due date is not less than assigned date
                d.	status is valid.
                    Note that status as read from the file is a string  and not a date. The sting will be items listed below.
                    i.	is an string indicating the status is
                        1.	assigned
                        2.	completed
                        3.	late
        6.	If valid the program will create a node for each assignment date and assign the node to the correct list based on assignment status and placed in the list in order based on assignment date.
        7.	If not valid the program will:
            i.	print to console an error message that data line is bad.
            ii.	automatically throw bad line away
            iii.	continue reading assignment data lines
e.	If the initial data input from the file is valid then the program will prompt the user enter a number for what action they would like to do
    i.	The following text will print to the console to for this choice:
        “Select from the following options:”
        “1. Display assignments”
        ”2. Add assignment”
        “3. Edit a due date”
        “4. Edit a description”
        “5. Complete an assignment”
        “6. Display number of late assignments”
        ”7. Save”
        “8. Exit”
        “Your input:”

f.	Based on what the user entered the following will happen:
    i.	If the choice was 1. Display assignments
        1.	A list will be printed to the console that consists of both the assignment list and the completed list.  The criteria and order for printing is as follows:
            a.	Each list will be printed separately to the console and will be ordered by from earliest to latest due date.
            b.	The program will first print the assigned list and then the completed list.
            c.	The print format for each record printed to console will be as follows:
                List Name
                Due: mm-dd-yyyy
                Description: xxxxxxxxxxxxxxx
                Assigned: mm-dd-yyyy
                Status: xxxxxxxx

    ii.	If the choice was 2. Add assignment
        1.	Console prompts User to enter the assignment date:
        2.	Verify that the assigned date is valid as follows:
            a.	Date is not a valid date if
                i.	Is not US format
                ii.	Is not a valid month, day, or year value
                iii.	Assigned date already exists in either list
                Note: program will not check if the entered date is valid against a real time date
        3.	The program will search both the assigned and completed assignments lists to see if there is a duplicate assignment date
            a.	If there is a duplicate assignment date then the program will not change date but will:
                i.	 issue a warning to the console “Assign Date Error. Date entered has been used previously”.
                ii.	return to main menu.
            b.	If there is not a duplicate assignment date,
                i.	the program will:
                    1.	prompt the user to enter in the due date
                         a.	Verify if due date is not a valid date if:
                            i.	Is not US format
                            ii.	Is not a valid month, day, or year value
                            iii.	Due date is less than the assigned date
                            Note: program will not check if the entered date is valid against a real time date
                        b.	If the due date is valid the program will store the due date in variable newAssignDueDate
                ii.	prompt the user to enter in the description.
                    1.	verify if the description is valid
                        a.	15 characters or less.
                    2.	If the description is valid the program will store the description in variable describe.
                    3.	If the description is not valid then the program will:
                        a.	Print error message to console
                            i.	“Error in description. Returning to main menu”
                            ii.	Returns to main menu
                    4.	If the description is not valid then the program will:
                        a.	Print error message to console
                            i.	“Error in due date. Exiting to main menu”
                        b.	Returns to the main menu
            c.	if there is Not a duplicate assignment date and the rest of the data entered is valid then the program will:
                i.	create a double linked node
                ii.	set variable to track if there are changes to save to true.
                iii.	create a new string consisting of existing values formatted as follows.
                    1.	The information categories will be separated by commas and spaces
                    2.	dueDate, description, assignedDate, status
                    3.	status will be automatically set to “assigned”
                iv.	save the new string in the new node as data
                v.	insert node in assigned list in ascending order based on the due date.
                vi.	returns to main menu once new node has been added to a list.

    iii.	If the choice was 3. Edit a due date
        1.	Program requires due date to be in US date format
        2.	Assignments that are in the completed list cannot have their data changed.
        3.	Program prompts User for assigned date of assignment to be edited.
            a.	Runs assignment dates checks as list in ii.
        4.	Program then searches the assigned and competed lists for assignment date to see if assignment exists
            a.	If assignment does not exist an error message is generated and printed to console.
                i.	Program exists to main menu
            b.	If assignment does exist then program
                i.	brings back iterator location  information for the node
                ii.	if assignment status is completed then the program:
                    1.	prints error to console
                    2.	returns to main menu.
            c.	If assignment is in assigned list then the program:
                i.	 allows the due date to be change
                ii.	Prompts the user for a new due date and:
                    1.	Verifies if due date is an invalid date if:
                        a.	Is not US format
                        b.	Is not a valid month, day, or year value
                        c.	Due date is less than the assigned date
                    Note: program will not check if the entered date is valid against a real time date
                    2.	If due date is an invalid date then the program will:
                        a.	Print error message to console
                            i.	“Error in due date. Exiting to main menu”
                            ii.	Returns to the main menu
                    3.	If due date is valid date and the status is assigned then the program will:
                        a.	Modifies the due date section of the node’s current data string with the new description
                        b.	Saves the modified string to the data string in the node
                        c.	Changes the position of the assignment in the list so that the list retains its sort by due date order.
                        d.	Sets changed variable to true.
                        e.	Returns to main menu

    iv.	If the choice was 4. Edit a description
    1.	Program prompts User for assigned date of assignment to be edited.
        a.	Runs assignment dates checks as list in ii.
    2.	Assignments that are in the completed list cannot have their data changed.
    3.	Program then searches both lists for assignment date to see if assignment exists
        a.	If assignment does not exist an error message is generated.
            i.	Print out to console - “Assignment date is not valid. Returning to main menu”
            ii.	Program exists to main menu
        b.	If assignment does exist then program
            i.	brings back iterator location  information for the node
            ii.	If the assignment is in the completed list then the program:
                1.	Prints to console “Assignment is completed. Description cannot be changed. Exiting to main menu.”
                2.	Returns to main menu
            iii.	If the assignment status is in the assigned list  then the program:
                1.	Prompts user to enter new description
                2.	Verifies if string length is 15 characters or less
                    a.	If string length is too long then the program
                        i.	Prints error message to console
                        ii.	Returns to main menu
                    b.	If the string is <= to 15 characters then the program:
                        i.	Modifies the description section of the nodes current data string with the new description
                        ii.	Saves the modified string to the data string in the node
                        iii.	Sets changed variable to true
                        iv.	Returns to main menu

v.	If the choice was 5. Complete an assignment
    1.	Program prompts User for assigned date of assignment to be edited.
        a.	Runs assignment dates checks as list in ii.
    2.	Program then searches assignment list for assignment date to see if assignment exists
    a.	If assignment does not exist then the program:
        i.	Prints error message to console.
        ii.	Returns to main menu
    b.	If assignment date record exists and the node is in the completed list then program:
        1.	Prints error message to console
        2.	Returns to main menu
    c.	If the assignments exist and the node is in the assigned list then the program:
        i.	brings back iterator location  information for the node
        ii.	Prompts user to enter a date of when the assignments was completed
        iii.	The program verifies if the completed date is not valid.
            1.	Is not US format
            2.	Is not a valid month, day, or year value
            3.	Completed date is less than the assigned date
        iv.	If the completed date is an invalid date then the program will:
            1.	Print error message to console
            2.	Returns to the main menu
        v.	If the completed date is valid then the program
            1.	compares completedDate against dueDate
                a.	if completedDate <= to dueDate then the program:
                    i.	modifies status portion of the string data stored in the node as “completed”
                b.	if completedDate > to dueDate then the program:
                    i.	modifies status portion of the string data stored in the node as “late”
            2.	saves the modified string to the node
            3.	moves the node to the completed list in order of it’s due date
            4.	deletes the assignment out of the assigned list
            5.	sets the changed variable to true.
            6.	returns to the main menu

vi.	If the choice was 6. Display number of late assignments
    1.	The Program
        a.	prompts user to save all changes
        b.	searches the completed list for “late” assignment status & counts them
        c.	Prints the following output to the console xxx is the number of late assignments
            i.	“Number of late assignments is xxxx”
        d.	Returns to main menu

vii.	If the choice was 7. Save
    1.	Saves the changes to the data to a file named AssignmentData.txt
    2.	Save overwrites the assignment file whenever there are changes to the data.
    3.	Sets changed variable to false
    4.	Returns to main menu once Save has been executed

viii.	If the choice was 7. Exit
    1.	Program will start exiting
    2.	the program will check to see if the data has been saved since the last change.
        a.	If beenSaved is False then the program will:
            i.	Print to console “Data has not been saved. Returning to main menu”
            ii.	return user to main menu
        b.	If beenSaved is True then the program will
            i.	Print to console “Now exiting program”
            ii.	Exit.

ix.	If the choice was invalid (not a number that is 1 thru 8) then the program:
    1.	prints to console:
        a.	“Number entered is not 1 to 8.  Please try again.”
        b.	Returns to main menu
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