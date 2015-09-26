/*
#include <queue>
#include <string>
#include <iostream>
using namespace std;

int main()
{

    queue<string> customers;
    string name;
    int choice_num = 0;
    string choices[] = {
        "push", "front", "pop", "size", "quit" };//array of strings
    const int NUM_CHOICES = 5;

    while (choice_num < NUM_CHOICES -1 )
    {
        cout << "\nselect an operation on customer queue\n";
        for (int i = 0; i < NUM_CHOICES; i++)
        {
            cout << i << ": " << choices[i]<< endl;
        }
        cin >> choice_num;
        switch (choice_num)
        {
        case 0:
            cout << "Enter new customer's name\n";
            cin >> name;
            customers.push(name);
        case 1:
            cout << "Customer " << customers.front() << " is next in line\n";
                break;
        case 2:
            cout << "Customer " << customers.front() << " is removed from list\n";
            customers.pop();
            break;
        case 3:
            cout << "Size of line is " << customers.size() << endl;
            break;
        case 4:
            cout << "Leaving customer queue.\n"
                << "Number of customers in queue is " << customers.size()
                << endl;
            break;
        default:
            cout << "Invalid selection\n";
            break;
        }
    }
    system("pause");
    return 0;
};
*/