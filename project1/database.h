#ifndef DATABASE_H_
#define DATABASE_H_

#include "record.h"

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
//  FILE:        database.h
//
//  DESCRIPTION:
//   A header file that has declarations for functions used in 
//   user_interface.c. Functions are listed and explained in the
//   class file that they are used in.
//
****************************************************************/

int addRecord (struct record **, int, char [ ],char [ ]);
void printAllRecords(struct record *);
int findRecord (struct record *, int);
int deleteRecord(struct record **, int);
int writefile(struct record *, char []);
int readfile(struct record **, char []);
void cleanup(struct record **);

#endif
