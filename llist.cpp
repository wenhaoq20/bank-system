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
//  DATE:        April 14, 2021
//
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   This file uses prototypes from the header file llist.h.
//
****************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include "llist.h"

using namespace std;

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   read from the file and store it in the heap.
//
//  Parameters:    NONE
//                 
//  Return values:  0 : success
//
****************************************************************/

int llist ::readfile()
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: readfile\n";
    #endif

    int read = 0;
    int mode = 0;
    int i = 0;
    int acc_num;
    char c;
    char name[25];
    char address[50];
    ifstream file_pointer;

    file_pointer.open(this->filename);

    if (file_pointer.fail())
    {
        read = -1;
    }
    else
    {
        while (file_pointer.good())
        {
            if (mode == 0)
            {
                file_pointer >> acc_num;
                file_pointer.get();
                mode = 1;
            }
            else if (mode == 1)
            {
                file_pointer >> name;
                file_pointer.get();
                mode = 2;
            }
            else if (mode == 2)
            {
                c = file_pointer.get();
                while (c != ';' && i < 50)
                {
                    address[i] = c;
                    i++;
                    c = file_pointer.get();
                }
                address[strlen(address) - 1] = '\0';
                addRecord(acc_num, name, address);
                memset(address, 0, strlen(address));
                i = 0;
                mode = 0;
            }
        }
        file_pointer.close();
    }

    return read;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   write all of the records in the heap to the 
//                 text file.
//
//  Parameters:    NONE
//                 
//  Return values:  0 : success
//
****************************************************************/

int llist ::writefile()
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: writefile\n";
    #endif

    int write = 0;
    record *node = this->start;
    ofstream file_pointer;

    file_pointer.open(this->filename);

    if (file_pointer.fail())
    {
        write = -1;
    }
    else
    {
        while (node != NULL)
        {
            file_pointer << node->accountno << endl;
            file_pointer << node->name << endl;
            file_pointer << node->address << endl;
            file_pointer << ";" << endl;
            node = node->next;
        }
        file_pointer.close();
    }

    return write;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   remove everything from the heap and set start
//                 to NULL.
//
//  Parameters:    NONE
//                 
//  Return values:  NONE
//
****************************************************************/

void llist ::cleanup()
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: cleanup\n";
    #endif

    record *node = this->start;
    while (node != NULL)
    {
        this->start = (this->start)->next;
        delete node;
        node = this->start;
    }
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   constructor for the class llist with no
//                 parameter.
//
//  Parameters:    NONE
//
//  Return values:  NONE
//
****************************************************************/

llist ::llist()
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: llist()\n";
    #endif

    this->start = NULL;
    strcpy(this->filename, "database.txt");
    this->readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   constructor for the class llist with filename
//                 as the parameter.
//
//  Parameters:    filename (char[]): the name of the file.
//
//  Return values:  NONE
//
****************************************************************/

llist ::llist(char filename[])
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: llist(char[])\n";
        cout << "Filename: " << filename << endl;
    #endif

    char tempfile[16];
    int i;

    while (i < 16)
    {
        tempfile[i] = filename[i];
        i++;
    }

    this->start = NULL;
    strcpy(this->filename, tempfile);
    this->readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   a copy constructor for the class llist.
//
//  Parameters:    records (const llist&): reference to the llist
//                 that are being copied.
//
//  Return values:  NONE
//
****************************************************************/

llist ::llist(const llist &records)
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: llist(const llist&)\n";
    #endif

    this->start = NULL;
    record* temp = records.start;

    while (temp != NULL)
    {
        this->addRecord(temp->accountno, temp->name, temp->address);
        temp = temp->next;
    }

    strcpy(this->filename, records.filename);
}

/*****************************************************************
//
//  Function name: ~llist
//
//  DESCRIPTION:   a deconstructor for the class llist that save
//                 to a file and delete everything on heap.
//
//  Parameters:    NONE
//
//  Return values:  NONE
//
****************************************************************/

llist ::~llist()
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: ~llist()\n";
    #endif

    this->writefile();
    this->cleanup();
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   add new user's record to the database.
//
//  Parameters:    number (int): user account number.
//                 name (character[]): user name.
//                 address (character[]): user address.
//                 
//  Return values:  0 : success
//
****************************************************************/

int llist ::addRecord(int number, char name[25], char address[50])
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: addRecord\n";
        cout << "number: " << number << endl;
        cout << "name: " << name << endl;
        cout << "address: " << address << endl;
    #endif

    record *node;
    record *next_node;
    record *temp;
    int added = -1;

    if (this->start == NULL)
    {
        temp = new record;
        temp->accountno = number;
        strncpy(temp->name, name, 25);
        strncpy(temp->address, address, 50);
        temp->next = NULL;
        this->start = temp;
        added = 0;
    }
    else
    {
        next_node = this->start;
        node = this->start;
        while (number > next_node->accountno && next_node->next != NULL)
        {
            next_node = next_node->next;
            if (number >= next_node->accountno)
            {
                node = next_node;
            }
        }
        if (number != node->accountno)
        {
            temp = new record;
            temp->accountno = number;
            strcpy(temp->name, name);
            strcpy(temp->address, address);
            if (next_node == this->start && number < (this->start)->accountno)
            {
                temp->next = node;
                this->start = temp;
            }
            else
            {
                temp->next = node->next;
                node->next = temp;
            }
            added = 0;
        }
    }

    return added;
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Find a user's record in the data base.
//
//  Parameters:    number (int): account number.
//                
//  Return values:  0 : success
//
****************************************************************/

int llist ::findRecord(int number)
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: findRecord\n";
        cout << "number: " << number << endl;
    #endif

    int find = -1;
    record * node;

    if (this->start != NULL)
    {
        node = this->start;
        while (node->next != NULL && node->accountno != number)
        {
            node = node->next;
        }
        if (node->accountno == number)
        {
            cout << "Account number: "<< node->accountno << endl;
            cout << "Name: " << node->name << endl;
            cout << "Address: " << node->address << endl;
            find = 0;
        }
    }

    return find;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   delete a record from the database.
//
//  Parameters:    number (int) : user account number. 
//                 
//  Return values:  0 : success
//
****************************************************************/

int llist ::deleteRecord(int number)
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: deleteRecord\n";
        cout << "number: " << number << endl;
    #endif

    record *node;
    record *next_node;
    int deleted = -1;

    if (this->start != NULL)
    {
        node = this->start;
        next_node = (this->start)->next;
        if (number == node->accountno)
        {
            this->start = next_node;
            delete node;
            deleted = 0;
        }
        else
        {
            while (next_node->next != NULL && number != next_node->accountno)
            {
                node = next_node;
                next_node = node->next;
            }
            if (number == next_node->accountno)
            {
                node->next = next_node->next;
                delete next_node;
                deleted = 0;
            }
        }
    }

    return deleted;
}

/*****************************************************************
//
//  Function name: operator=
//
//  DESCRIPTION:   a overload operator= for the class llist that
//                 copy llist to another llist. 
//
//  Parameters:    records (const llist &): a reference of the
//                 llist that are being copied 
//
//  Return values: *this (llist): the new copied llist
//
****************************************************************/

llist &llist ::operator=(const llist & records)
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: operator=\n";
    #endif

    this->cleanup();
    this->start = NULL;
    record* temp = records.start;

    while (temp != NULL)
    {
        this->addRecord(temp->accountno, temp->name, temp->address);
        temp = temp->next;
    }

    strcpy(this->filename, records.filename);
    return *this;
}

/*****************************************************************
//
//  Function name: operator<<
//
//  DESCRIPTION:   a overload operator<< for the class llist that
//                 prints out all of the records in database.
//
//  Parameters:    outstr (ostream &): a reference to the output
//                 stream
//                 records (const llist&): a reference to the llist
//                 that are being printed
//
//  Return values: outstr (ostream &): a reference to the output
//                 stream
//
****************************************************************/

ostream &operator<<(ostream & outstr, const llist & records)
{
    #ifdef DEBUGMODE
        cout << "*****DEBUG*****\n";
        cout << "Function: operator<<\n";
    #endif

    record *node = records.start;

    if (node == NULL)
    {
        cout << "THE LIST IS EMPTY!!!\n";
    }
    else
    {
        cout << "/**********ALL RECORD**********\n";
        while (node != NULL)
        {
            outstr << "Account number: " << node->accountno << endl;
            outstr << "Name: " <<node->name << endl;
            outstr << "Address: " << node->address << endl;
            outstr << endl;
            node = node->next;
        }
        cout << "******************************/\n";
    }
    return outstr;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Prints all of the records in the database.
//
//  Parameters:    NONE
//                 
//  Return values:  NONE
//
****************************************************************/

void llist ::printAllRecords()
{
    record *node = this->start;

    if (node == NULL)
    {
        cout << "THE LIST IS EMPTY!!!\n";
    }
    else
    {
        cout << "/**********ALL RECORD**********\n";
        while (node != NULL)
        {
            cout << "Account number: " << node->accountno << endl;
            cout << "Name: " <<node->name << endl;
            cout << "Address: " << node->address << endl;
            cout << endl;
            node = node->next;
        }
        cout << "******************************/\n";
    }
}
