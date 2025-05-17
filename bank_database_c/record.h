#ifndef RECORD_H_
#define RECORD_H_

/*****************************************************************
//
//  NAME:        Corvey Lee
//
//  HOMEWORK:    1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        February 15, 2025
//
//  FILE:        record.h
//
//  DESCRIPTION:
//   A record structure that holds an account number, name,
//   address, and another record that is linked. 
//
****************************************************************/

struct record
{
    int                accountno;
    char               name[25];
    char               address[45];
    struct record*     next;
};

#endif
