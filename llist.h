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
//  FILE:        llist.h
//
//  DESCRIPTION:
//   A header file declares the class for llist.
//
****************************************************************/

#ifndef llist_h
#define llist_h

#include <iostream>
#include "record.h"

using namespace std;

class llist
{
private:
    record *    start;
    char        filename[16];
    int         readfile();
    int         writefile();
    void        cleanup();

public:
    llist();
    llist(char[]);
    llist(const llist &);
    ~llist();
    int addRecord(int, char[], char[]);
    int findRecord(int);
    int deleteRecord(int);
    void printAllRecords();
    llist & operator = (const llist &);
    friend ostream & operator <<(ostream &, const llist &);
};

#endif
