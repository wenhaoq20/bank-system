/*****************************************************************
//
//  NAME:        Wenhao Qiu
//
//  HOMEWORK:    project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 16, 2021
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   user_interface allows the user to choose multiple menu option
//   and access the database.
//
****************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
#include "llist.h"

using namespace std;

int menuOption(llist &);
int getNumber();
void getName(char[], int);
void getaddress(char[], int);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   A main function that have multiple option, 
//                 and print information about how to use this
//                 program.	
//
//  Parameters:    argc (int) : number of arguments
//                 argv (char*[]): array of arguments
//
//  Return values:  0 : success
//
****************************************************************/

int main(int argc, char *argv[])
{
    llist records;
    int option = 0;

    if (argc > 1)
    {
        cout << "Error! Incorrect Argument!" << endl;
    }
    else
    {
        while (option != 1)
        {
            cout << "\n==========================================\n";
            cout << "Welcome to the Sibyl Bank System.\n";
            cout << "Type in the option name to access the menu.\n";
            cout << "What do you want to do today?\n";
            cout << "==========================================\n";
            cout << "add: Add a new record in the database.\n";
            cout << "printall: Print all records in the database.\n";
            cout << "find: Find record(s) with a specificed account number.\n";
            cout << "delete: Delete exisitng record(s) with a account number.\n";
            cout << "quit: Quit the program.\n";
            cout << "------------------------------------------" << endl;
            option = menuOption(records);
        }
    }

    return 0;
}

/*****************************************************************
//
//  Function name: menuOption
//
//  DESCRIPTION:   A function that ask the user for input, and  
//                 call the menu option based on the input.
//
//  Parameters:    records (llist &): reference to the record
//                 base
//
//  Return values:  0: Display the menu again.
//                  1: Quit the program.
//
****************************************************************/

int menuOption(llist & records)
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: menuOption" << endl;
    #endif

    int check = -1;
    int success;
    char input[100];
    int accNum;
    char name[50];
    char address[100];

    while (check == -1)
    {
        cin.getline(input, 100);
        if (strncmp("add", input, strlen(input)) == 0 && strlen(input) > 0)
        {
            accNum = getNumber();
            getName(name, 26);
            getaddress(address, 50);
            success = records.addRecord(accNum, name, address);
            if (success == 0)
            {
                cout << "SUCCESSFULLY ADD TO RECORD!!!!" << endl;
            }
            else
            {
                cout << "FAIL TO ADD TO RECORD!!!!" << endl;
            }
            check = 0;
        }
        else if (strncmp("printall", input, strlen(input)) == 0 && strlen(input) > 0)
        {
            cout << records;
            check = 0;
        }
        else if (strncmp("find", input, strlen(input)) == 0 && strlen(input) > 0)
        {
            accNum = getNumber();
            success = records.findRecord(accNum);
            if (success == -1)
            {
                cout << "FAIL TO FIND THE RECORD!!!!" << endl;
            }
            check = 0;
        }
        else if (strncmp("delete", input, strlen(input)) == 0 && strlen(input) > 0)
        {
            accNum = getNumber();
            success = records.deleteRecord(accNum);
            if (success == 0)
            {
                cout << "SUCCESSFULLY DELETED THE RECORD!!!!" << endl;
            }
            else
            {
                cout << "FAIL TO DELETE THE RECORD!!!!" << endl;
            }
            check = 0;
        }
        else if (strncmp("quit", input, strlen(input)) == 0 && strlen(input) > 0)
        {
            check = 1;
        }
        else
        {
            cout << "Error! Invalid input" << endl;
        }
    }

    return check;
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   This function ask for the client's address, and 
//                 stores the address information.
//
//  Parameters:    address (char[]) : client's address.
//                 size (int): size of the info array.
//
//  Return values:  NONE
//
****************************************************************/

void getaddress(char address[], int size)
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: getaddress\n";
        cout << "info: " << address << endl;
        cout << "size: " << size << endl;
    #endif

    int check = 0;
    int i = 0;

    cout << "Enter the address information\n";
    cout << "Type ; at the end when you are done inputing information\n";
    cout << "1111 ST CITY STATE;" << endl;

    while (check != 1 && i < size)
    {
        cin.get(address[i]);
        if (address[i] == ';')
        {
            address[i] = '\0';
            check = 1;
        }
        i++;
    }
    cin.get();
}

/*****************************************************************
//
//  Function name: getNumber
//
//  DESCRIPTION:   This function ask for the account number and
//                 check if the account number is valid.
//
//  Parameters:    NONE
//
//  Return values: number (int): the account number.
//
****************************************************************/

int getNumber()
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: getNumber\n";
    #endif

    int number = -1;

    cout << "Please enter an account number\n";
    while (!(cin >> number) || number <= 0)
    {
        cin.clear();
        cin.ignore(10000000, '\n');
        if (number <= 0)
        {
            cout << "Invalid account number!" << endl;
            cout << "Please enter a positive number" << endl;
        }
    }
    cin.ignore(10000000, '\n');
    return number;
}

/*****************************************************************
//
//  Function name: getName
//
//  DESCRIPTION:   This function ask for the client's name and 
//                 store it in the name character array.
//
//  Parameters:    name (char[]) : client's name.
//                 size (int): size of the info array.
//
//  Return values:  NONE
//
****************************************************************/

void getName(char name[], int size)
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: getName\n";
        cout << "name: " << name << endl;
        cout << "size: " << size << endl;
    #endif

    cout << "Please enter the name" << endl;
    cin.getline(name, size);
}
