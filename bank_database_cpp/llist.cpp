/*****************************************************************
//  NAME:        Corvey Lee
//
//  HOMEWORK:    Project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 25, 2025
//
//  FILE:        database.cpp
//
//  DESCRIPTION:
//    Database cpp file that includes functions for manipulating
//    records. Includes an add, printall, find, and delete 
//    functions.
//
****************************************************************/

#include "record.h"
#include "llist.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Empty constructor for the llist class
//
//  Parameters:    None
//
****************************************************************/

llist::llist()
{
    char thisfile[] = "bankdatabase.txt";
    strncpy(filename, thisfile, 25);
    start = NULL;
    llist::readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Constructor for the llist class that 
//                 accepts a filename.
//                 
//  Parameters:    filename (char[]): The name of the file to
//                 be read from.
//
****************************************************************/

llist::llist(char filename[])
{
    strncpy(this -> filename, filename, 25);
    llist::readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Copy constructor of the llist class
//                 
//  Parameters:    const llist orig : The original llist object
//                 that will be copied to.
//
****************************************************************/

llist::llist(const llist &orig)
{
    start = NULL;
    strncpy(filename, orig.filename, sizeof(filename) - 1);
    filename[sizeof(filename) - 1] = '\0';

    if (orig.start == NULL)
    {
        return;
    }

    start = new record;
    *start = *orig.start;
    start->next = NULL;
 
    record* currentSrc = orig.start->next;
    record* currentDest = start;
    
    while (currentSrc != NULL) 
    {
        currentDest -> next = new record;
        currentDest = currentDest -> next;
        *currentDest = *currentSrc;
        currentDest->next = NULL;
        currentSrc = currentSrc->next;
    }   
}

/*****************************************************************
//
//  Function name: ~llist
//
//  DESCRIPTION:   Destructor for the object of this class
//
//  Parameters:    None
//
****************************************************************/

llist::~llist()
{
    llist::writefile();
    llist::cleanup();
}

/*****************************************************************
//
//  Function name: llist& operator=
//
//  DESCRIPTION:   Overload of the equal operator to allow llist
//                 objects to be set equal to eachother.
//
//  Parameters:    origlist (const llist &): The original list
//                 to be copied from.
//
//  Return Values: llist& : The new list data is assigned to.
//
****************************************************************/

llist& llist::operator=(const llist &orig)
{
    strncpy(filename, orig.filename, sizeof(filename)-1);
    filename[sizeof(filename) - 1] = '\0';
    
    start = NULL;

    if (orig.start != NULL)
    {
        start = new record;
        start -> accountno = orig.start -> accountno;
        strncpy(start -> name, orig.start -> address, sizeof(start -> address) - 1);
        start -> name[sizeof(start -> address) - 1] = '\0';
        strncpy(start -> address, orig.start -> address, sizeof(start -> address) - 1);
        start -> address[sizeof(start -> address - 1)] = '\0';
        start -> next = NULL;
    }
    
    record *currentSrc = orig.start -> next;
    record *currentDest = start;
    
    while (currentSrc != NULL) 
    {
        currentDest -> next = new record;
        currentDest = currentDest -> next;
        currentDest -> accountno = currentSrc -> accountno;
        strncpy(currentDest -> name, currentSrc-> name, sizeof(currentDest -> name) - 1);
        currentDest -> name[sizeof(currentDest -> name) - 1] = '\0';
        currentDest -> next = NULL;

        currentSrc = currentSrc -> next;   
    }
    return *this;
}

/*****************************************************************
//
//  Function name: friend ostream& operator<<
//
//  DESCRIPTION:   Overload of the << operator in the ostream class
//                 to print all data from the llist. 
//
//  Parameters:    stream (ostream&): The stream being written to.
//                 list (const llist&): The list being printed from.
/y
//  Return Values: ostream&: the stream being written to.
//
****************************************************************/

ostream& operator<<(ostream& stream, const llist& list)
{  
    const record *current = list.start;
    
    if (list.start == NULL)
    {
        stream << "There is currently no accounts in the database.\n\n";
    }

    while (current != NULL)
    {  
        stream << "Account Number: " << current -> accountno << endl; 
        stream << "Name: " << current -> name << endl; 
        stream << "Address: " << endl << current -> address << endl;
        current = current -> next;
    }

    return stream;
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds a record to the list.
//
//  Parameters:    accNo (int): The number of the account
//                 to be added.
//
//                 accName (char[]): A string of the name
//                 of the account to be added.
//
//                 accAddress (char[]): A string of the 
//                 address of the account to be added.
//
//  Return values:  0 : success
//
****************************************************************/

int llist::addRecord (int accNo, char accName[], char accAddress[])
{
    int rv = -1;
    record *currentrecord;
    record *newrecord = NULL;

    if (start == NULL)
    {
         newrecord = new record;
         (newrecord -> next) = NULL;
         start = newrecord;
         rv = 0;
    }

    else
    {
        currentrecord = start;
        while (currentrecord != NULL && (currentrecord -> accountno != accNo) && rv != 0)
        {
            if (accNo > (currentrecord -> accountno))
            {
                newrecord = new record;
                (newrecord -> next) = (currentrecord -> next);
                (currentrecord -> next) = newrecord;
                rv = 0;
            }    
            currentrecord = currentrecord -> next;
        }
    }

    if (newrecord != NULL)
    {
         newrecord -> accountno = accNo;
         strcpy(newrecord -> name, accName);
         strcpy(newrecord -> address, accAddress);
         cout << "Record was successfully addded \n\n";
    }

    if (rv == -1)
    {
        cout << "Account not added: Duplicate ID Exists \n\n";
    }
    return rv;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Prints all records available in the database. 
//
//  Parameters:    None
//
//  Return values: None
//
****************************************************************/

void llist::printAllRecords()
{
    record *current = start;
    
    if (start == NULL)
    {
        cout << "There is currently no accounts in the database.\n\n";
    }
    while (current != NULL)
    {  
        cout << "Account Number: " << current -> accountno << endl;
        cout << "Name: " << current -> name << endl; 
        cout << "Address: " << endl << current -> address << endl;
        current = current -> next;
    }
}
 
/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Finds a record and returns the record
//                 information using the account number to locate.
//
//  Parameters:    accNo (int): The number to use to locate
//                 the account in the database.
//
//  Return values:  0 : Record Successfully found
//                 -1 : No record found with specified ID #
//
****************************************************************/

int llist::findRecord (int accNo)
{
    record *current = start;
    int rv = -1;
    while ( (current != NULL) && (rv != 0) )
    {
        if (current -> accountno == accNo)
        {
            
            cout << "Account Number: " << current -> accountno << "\n" << "Name: " << current -> name << "\n" << "Address: " << endl << current -> address << "\n";
            rv = 0;
        }
        current = current -> next;
    }
    if (rv == -1)
    {
        cout << "No accounts in Database\n\n";
    }
    return rv;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Deletes a record from the database based on the
//                 account number entered.
//
//  Parameters:    accNo (int): The number of the account to
//                 delete in the databse. 
//
//  Return values:  0 : Account successfully deleted
//                 -1 : Account not found
//
****************************************************************/

int llist::deleteRecord (int accNo)
{
    int rv = -1;
    record *current = NULL;
    record *previous = NULL;

    if (start == NULL)
    {  
        rv = -1;
    } 

    else 
    {
        current = start;

        while (current != NULL && rv != 0)
        { 
            if (current -> accountno == accNo)
            {
                rv = 0;
                if (previous == NULL)
                {
                    start = current -> next;
                }
                else
                {
                    previous -> next = current -> next;
                }
                delete current;
                cout << "Account successfully deleted\n\n";
            }
            previous = current;   
            current = current -> next;
        }
    }
    if (rv == -1)
    {
        cout << "Account not found\n\n";
    }
    return rv;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   Takes information from an array of records
//                 and writes them to the specified file. 
//
//  Parameters:    fileName (char[]): Name of the file that 
//                 information will be written to.
//
//  Return values:  0 : All information successfully written to file
//                 -1 : Error while writing the file
//
****************************************************************/

int llist::writefile()
{
    int rv = -1;
    record *current;
    std::ofstream file(filename, ios::out);

    if (!file.is_open())
    {
        rv = -1;
    }
    else
    {
        current = start;
        while (current != NULL)
        {
            file << current -> accountno << endl;
            file << current -> name << endl;
            file << current -> address;
            if (current -> next != NULL)
            {
                file << endl;
            }
            current = current -> next;
            rv = 0;
        }
    }
    file.close();
    return rv;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Reads from a file and stores information
//                 to an array of records. 
//
//  Parameters:    fileName (char []): Name of the file to be
//                 written to.
//
//  Return values:  0 : File successfully read or created
//                 -1 : Error while reading the file
//
****************************************************************/

int llist::readfile()
{
    int rv = 0;
    record *previous;
    record *current;
    char trash[50];
    char line[50];
    fstream file(filename, ios::in | ios::out);

    if (!file.good())
    {
        rv = -1;
    }
  
    else 
    {
        while (file.peek() != EOF)
        {       
            current = new record;
            file >> current -> accountno;
            file.getline(trash, 50);
            file.getline(current -> name, 25);

            do
            {
                file.getline(line, 50);
                if(strlen(line) != 0)
                { 
                    strcat(current -> address, line);
                    strcat(current -> address, "\n");
                }
            }
            while(strlen(line) != 0);
            current -> next = NULL;

            if (start == NULL)
            {
                start = current;
                previous = current;
            }
            else
            {
                previous -> next = current;
            }
        }
        file.close();
    }
    return rv;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   Releases all allocated spaces in heap memory
//                 and sets the start to null
//
//  Parameters:    None
//
//  Return Values: None
//
****************************************************************/

void llist::cleanup()
{
   record *previous;
   record *current;

   if (start != NULL)

   {
       current = start;
       while(current != NULL)
       {  
          previous = current; 
          current = current -> next;
          delete(previous);
       }
   }
   start = NULL;
}

