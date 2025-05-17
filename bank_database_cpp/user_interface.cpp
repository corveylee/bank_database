/*****************************************************************
//  NAME:        Corvey Lee
//
//  HOMEWORK:    1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 29, 2025
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   A user interface implentation for the bank database program in
//   c++. Takes user input and interprets it to send to the functions
//   within the database. 
//
//
****************************************************************/

#include <iostream>
#include <cstring>
#include "llist.h"
#include "record.h"

using namespace std;

void getaddress (char [], int);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Displays the user interface on the console. 
//                 Gives an introduction to the program and then
//                 prompts the user to call a function in order to
//                 edit the underlying database. The program continues
//                 until the user enters quit.
//
//  Parameters:    argc (int) : number of arguments
//                 argv (char*[]): array of arguments
//
//  Return values: 0 : success
//
****************************************************************/

int main(int argc, char* argv[])
{
    int debugmode = 0;
    int userQuit = -1;
    char userInput[10];
    char trash[100];
    int accountNum;
    char accountName[25];
    char accountAddress[200];
 
    #ifdef DEBUG
        cout << "Debugmode is activated";
        debugmode = 1;
    #endif

    /* Introductory message */
    cout << "\nWelcome to BankSystems EasyDB. This program allows you to modify and search records within\n";
    cout << "the bank database. Please follow the prompts given below.\n\n"; 
        
    /* Create and load the llist object */
    llist myList;

    while(userQuit == -1)
    {
        /* User Selection prompt */ 
        cout << "Please type a menu option below. You may shorten the option name, but not add to the option.\n";
        cout << "add: Adds a record to the database\n";
        cout << "printall: Prints all records in the database\n";
        cout << "find: Finds a record by account number and prints the infromation of the record\n";
        cout << "delete: Delete a record from a database using account number\n";
        cout << "quit: Quit the program\n\n";

        cout << "Input menu option: ";
        cin >> userInput;

        /* Detect add */
        if( (strncmp(userInput, "add", strlen(userInput))) == 0 )
        {
            int validInput = -1;

            /* Get account number */
            while(validInput == -1)
            {
                cout << "Please input account number: ";
                cin >> accountNum;
                if(cin.fail())
                {
                    cout << "\nError: Please input an integer\n";
                    cin.clear();
                }
                else if( accountNum <= 0 )
                {
                    cout << ("\nError: Please input a positive integer\n");
                }
                else
                {
                    validInput = 0; /* Input is successful*/
                    cout << "\n";
                }
                cin.ignore(100, '\n');
            }
            
            /* Get account name */
            cout << "Enter account name: ";
            cin.getline(accountName, 25); 
            
            
            /* Get address */
            getaddress(accountAddress, 45);
 
            
            /* Call add function */
            myList.addRecord(accountNum, accountName, accountAddress);
            
            /* DEBUG MODE ONLY: Print functions and values */
            if(debugmode == 1)
            {
                cout << "Selected function: addRecord\n";
                cout << "Account Number: " << accountNum << endl;
                cout << "Account Name: " << accountName << endl;
                cout << "Account Address: \n" << accountAddress << endl << endl;
            }
        }
        
        /* Detect printall */
        else if( (strncmp(userInput, "printall", strlen(userInput))) == 0 )
        {
            /* Call print function */
            cout << myList;
            
            /* DEBUG MODE ONLY: Print function */
            if(debugmode == 1)
            {
                cout << "\nSelected function: printAllRecords\n\n";
            }
        }

        /* Detect find */
        else if( (strncmp(userInput, "find", strlen(userInput))) == 0 )
        {
            int validInput = -1;
        
            /* Get account number */
            while(validInput == -1)
            {
                cout << "Please input account number: ";
                cin >> accountNum;
                if(cin.fail())
                {
                    cout << "\nError: Please input an integer\n";
                    cin.clear();
                }
                else if( accountNum <= 0 )
                {
                    cout << "\nError: Please input a positive integer\n";
                }
                else
                {
                    validInput = 0; /* Input is successful*/
                    cout << "\n";
                }
                cin.ignore(100, '\n');
            }

            /* Call find function */
            myList.findRecord(accountNum);

            /* DEBUG MODE ONLY: Print function and values */
            if(debugmode == 1)
            {
                cout << "Selected function: findRecord" << endl;
                cout << "Account Number: " << accountNum << endl << endl;
            }
        }

        /* Detect delete */
        else if( (strncmp(userInput, "delete", strlen(userInput))) == 0 )
        {
            int validInput = -1;

            /* Get account number */
            while(validInput == -1)
            {
                cout << "Please input account number: ";
                cin >> accountNum;
                if(cin.fail())
                {
                    cout << "\nError: Please input an integer\n";
                    cin.clear();
                }
                else if( accountNum <= 0 )
                {
                    cout << "\nError: Please input a positive integer\n";
                }
                else
                {
                    validInput = 0; /* Input is successful*/
                    cout << "\n";
                }
                cin.getline(trash, 100);
            }
            
            /* Call delete function */
            myList.deleteRecord(accountNum);

            /* DEBUG MODE ONLY: Print function and values */
            if(debugmode == 1)
            {
                cout << "Selected function: deleteRecord" << endl;
                cout << "Account Number: " << accountNum << endl << endl;
            }
        }
        
        /* Detect quit */
        else if( (strncmp(userInput, "quit", strlen(userInput))) == 0 )
        {
            userQuit = 0;
            if(debugmode == 1)
            {
                cout << "\nSelected function: quit\n";
            }
        }
 
        /* Nothing decteted or invalid option name */
        else
        {
            cout << "Error: Invalid option name. Please enter a valid menu option.\n\n";
        }

    }
    return 0;
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   Takes a character array and asks the user
//                 to input an address. 
//
//  Parameters:    address (char[]): The array that stores the
//                 address.
//
//                 limit (int): Total characters that may be read,
//                 total size of address.
//
//  Return values: none
//
****************************************************************/

void getaddress(char address[], int limit)
{
    char line[45];
    int count = 0;
    cout << "Please enter address below (Max 45 Characters). Type '[Enter]' twice when you are finished.\n";

    do
    {
        cin.getline(line, 45);
        count = strlen(line) + strlen(address);
        if(count <= limit)
        {
            strcat(address, line);
            if(strlen(line) != 0)
            {
               strcat(address, "\n");
            }
        }
    }
    while (strlen(line) != 0 && count < limit);
}
