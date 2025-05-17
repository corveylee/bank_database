/*****************************************************************
//  NAME:        Corvey Lee
//
//  HOMEWORK:    Project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        March 26, 2025
//
//  FILE:        database.c
//
//  DESCRIPTION:
//    Database c file that includes functions for manipulating
//    records. Includes an add, printall, find, and delete 
//    functions.
//
****************************************************************/

#include "record.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getaddressfromfile(char[], int, FILE *);

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds a record to the list.
//
//  Parameters:    start (struct record **): Pointer to the 
//                 starting record.
//
//                 accNo (int): The number of the account
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

int addRecord (struct record ** start, int accNo, char accName[], char accAddress[])
{
    int rv = -1;
    struct record *currentrecord;
    struct record *newrecord = NULL;

    if (*start == NULL)
    {
         newrecord = (struct record*)malloc(sizeof(struct record));
         (newrecord -> next) = NULL;
         *start = newrecord;
         rv = 0;
    }

    else
    {
        currentrecord = *start;
        while (currentrecord != NULL && (currentrecord -> accountno != accNo) && rv != 0)
        {
            if (accNo > (currentrecord -> accountno))
            {
                newrecord = (struct record*)malloc(sizeof(struct record));
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
         printf("Record was successfully addded\n\n");
    }

    if (rv == -1)
    {
        printf("Account not added: Duplicate ID Exists \n\n");
    }
    return rv;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Prints all records available in the database. 
//
//  Parameters:    start (struct record *): The starting record
//
//  Return values: none
//
****************************************************************/

void printAllRecords (struct record *current)
{
    if (current == NULL)
    {
        printf("There is currently no accounts in the database.\n\n");
    }
    while (current != NULL)
    {  
        printf("Account Number: %d\nName: %s\nAddress: %s\n\n", (current -> accountno), (current -> name), (current -> address));
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
//  Parameters:    start (struct record *): The starting record to
//                 look at.
//
//                 accNo (int): The number to use to locate
//                 the account in the database.
//
//  Return values:  0 : Record Successfully found
//                 -1 : No record found with specified ID #
//
****************************************************************/

int findRecord (struct record *current, int accNo)
{
    int rv = -1;
    while ( (current != NULL) && (rv != 0) )
    {
        if (current -> accountno == accNo)
        {
            printf("Account Found:\nAccount Number: %d\nName: %s\nAddress: %s\n\n", (current -> accountno), (current -> name), (current -> address));
            rv = 0;
        }
        current = current -> next;
    }
    if (rv == -1)
    {
        printf("Account Not Found\n\n");
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
//  Parameters:    start (struct record **): Pointer to the
//                 address of the starting record.
//
//                 accNo (int): The number of the account to
//                 delete in the databse. 
//
//  Return values:  0 : Account successfully deleted
//                 -1 : Account not found
//
****************************************************************/

int deleteRecord (struct record ** start, int accNo)
{
    int rv = -1;
    struct record *current = NULL;
    struct record *previous = NULL;

    if (start == NULL)
    {  
        rv = -1;
    } 

    else 
    {
        current = *start;

        while (current != NULL && rv != 0)
        { 
            if (current -> accountno == accNo)
            {
                rv = 0;
                if (previous == NULL)
                {
                    *start = current -> next;
                }
                else
                {
                    previous -> next = current -> next;
                }
                free(current);
                printf("Account successfully deleted\n\n");
            }
            previous = current;   
            current = current -> next;
        }
    }
    if (rv == -1)
    {
        printf("Account not found\n\n");
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
//  Parameters:    start (struct record **): Pointer to the
//                 address of the starting record.
//
//                 fileName (char[]): Name of the file that 
//                 information will be written to.
//
//  Return values:  0 : All information successfully written to file
//                 -1 : Error while writing the file
//
****************************************************************/

int writefile(struct record * current, char filename[])
{
    int rv = -1;
    FILE* file;

    file = fopen(filename, "w");
    if (file == NULL)
    {
        rv = -1;
    }
    else
    {
        while (current != NULL)
        {
            fprintf(file, "%d\n", (current -> accountno));
            fputs( (current -> name), file);
            fputs("\n", file);
            fputs( (current -> address), file);
            fputs("\n", file);
            if (current -> next != NULL)
            {
                fputs("\n", file);
            }
            current = current -> next;
            rv = 0;
        }
    }
    return rv;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Reads from a file and stores information
//                 to an array of records. 
//
//  Parameters:    start (struct record **): Pointer to the
//                 starting record.
//
//                 fileName (char []): Name of the file to be
//                 written to.
//
//  Return values:  0 : File successfully read or created
//                 -1 : Error while reading the file
//
****************************************************************/

int readfile(struct record ** start, char fileName[])
{
    int rv = 0;
    FILE* file;
    struct record *previous;
    struct record *current;
    char trash[50];

    file = fopen(fileName, "r");

    if (file == NULL)
    {
        rv = -1;
    }
  
    else 
    {
        while (!feof(file))
        {       
            current = (struct record *)malloc(sizeof(struct record));
            fscanf(file, "%d", &(current -> accountno) );
            fgets(trash, 50, file);
            fgets((current -> name), 25, file);
            current -> name[strlen(current -> name) - 1] = '\0';
            getaddressfromfile(current -> address, 0, file);
            current -> next = NULL;
            
            if (*start == NULL)
            {
                *start = current;
                previous = current;
            }
            else
            {
                previous -> next = current;
            }
        }
        fclose(file);
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
//  Parameters:    start (struct record **): Pointer to the address                     
//                 of the starting record.
//
//  Return Values: None
//
****************************************************************/

void cleanup(struct record ** start)
{
   struct record *previous;
   struct record *current;

   if (start != NULL)
   {
       current = *start;
       while(current != NULL)
       {  
          previous = current; 
          current = current -> next;
          free(previous);
       }
   }
   start = NULL;
}

/*****************************************************************
//
//  Function name: getaddressfromfile
//
//  DESCRIPTION:   Takes a file and writes the address section
//                 into a c style string. 
//
//  Parameters:    address (char[]) : The address to write to
//
//                 pos (int): The starting position of the address
//
//                 file (FILE *): A pointer to the file being read from
//
//  Return values:  None
//
*****************************************************************/ 

void getaddressfromfile(char address[], int pos, FILE* file)
{
    int lines = 0;
    char currentchar;

    while (lines != 2 && !feof(file))
    {
        currentchar = fgetc(file);
        address[pos] = currentchar;
        pos++;
    
        if (currentchar == '\n')
        {
            lines++;
        }
        else
        {
            lines = 0;
        }
    }
    address[pos-1] = '\0';
}
