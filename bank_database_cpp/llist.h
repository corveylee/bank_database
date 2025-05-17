#ifndef LLIST_H_
#define LLIST_H_

#include "record.h"
#include <iostream>

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
//  DATE:        April 25, 2025
//
//  FILE:        llist.h
//
//  DESCRIPTION:
//   A header file that has declarations for functions used in 
//   user_interface.c. Functions are listed and explained in the
//   class file that they are used in.
//
****************************************************************/

class llist
{
    private:
        record * start;
        char     filename[20];        
        int      writefile();
        int      readfile();
        void     cleanup();

    public:
        llist();
        llist(char[]);
        llist(const llist &);     // Copy Constructor
        ~llist();
        int addRecord (int, char [ ],char [ ]);
        void printAllRecords();
        int findRecord (int);
        int deleteRecord(int);
        llist& operator=(const llist&); // Overload =
        friend std::ostream& operator<<(std::ostream&, const llist&); // Overload <<
};

#endif
