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
//  FILE:        record.h
//
//  DESCRIPTION:
//   A header file declares the struct for record structure.
//
****************************************************************/

#ifndef record_h
#define record_h

struct record
{
    int                accountno;
    char               name[25];
    char               address[50];
    struct record*     next;
};

#endif
