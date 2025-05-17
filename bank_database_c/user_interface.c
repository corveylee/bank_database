/*****************************************************************
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
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   A user interface implentation for the bank database program.
//   Takes user input and interprets it to send to the functions
//   within the database. 
//
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include "database.h"
#include "record.h"

void getaddress (char [], int);

int debugmode = 0;

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
    struct record * start = NULL;
    int userQuit = -1;
    char userInput[10];
    char trash[100];
    int accountNum;
    char accountName[25];
    char accountAddress[200];
    
    /* Debug mode */
    if(argc > 1)
    {
        if(argc == 2 && (strcmp(argv[1], "debug") == 0))
        {
             debugmode = 1;  /* Debug mode is on */
        }
        else
        {
             debugmode = -1; /* Invalid input when there is more than one argument or 
                                first argument is not 'debug' */
        }
    }

    if(debugmode != -1)
    {
        /* Introductory message */
        printf("\nWelcome to BankSystems EasyDB. This program allows you to modify and search records within\n");
        printf("the bank database. Please follow the prompts given below.\n\n"); 
        
        /* Load all saved record from file */
        readfile(&start, "bankrecords.txt");
    }   

    while(userQuit == -1 && debugmode != -1)
    {
        /* User Selection prompt */ 
        printf("Please type a menu option below. You may shorten the option name, but not add to the option.\n");
        printf("add: Adds a record to the database\n");
        printf("printall: Prints all records in the database\n");
        printf("find: Finds a record by account number and prints the infromation of the record\n");
        printf("delete: Delete a record from a database using account number\n");
        printf("quit: Quit the program\n\n");

        printf("Input menu option: ");
        scanf("%s", userInput);

        /* Detect add */
        if( (strncmp(userInput, "add", strlen(userInput))) == 0 )
        {
            int validInput = -1;

            /* Get account number */
            while(validInput == -1)
            {
                printf("Please input account number: ");
                if( scanf("%d", &accountNum) == 0 )
                {
                    printf("\nError: Please input an integer\n");
                }
                else if( accountNum <= 0 )
                {
                    printf("\nError: Please input a positive integer\n");
                }
                else
                {
                    validInput = 0; /* Input is successful*/
                }
                fgets(trash, 100, stdin);
            }
            
            /* Get account name */
            printf("Enter account name: ");
            fgets(accountName, 25, stdin); 
            accountName[strlen(accountName) - 1] = '\0'; /* Remove the newline */
            
            /* Get address */
            getaddress(accountAddress, 200);
            printf("\n");
            
            /* Call add function */
            addRecord(&start, accountNum, accountName, accountAddress);
            
            /* DEBUG MODE ONLY: Print functions and values */
            if(debugmode == 1)
            {
                printf("Selected function: addRecord\n");
                printf("Account Number: %d\n", accountNum);
                printf("Account Name: %s\n", accountName);
                printf("Account Address: \n%s\n\n", accountAddress);
            }
        }
        
        /* Detect printall */
        else if( (strncmp(userInput, "printall", strlen(userInput))) == 0 )
        {
            /* Call print function */
            printAllRecords(start);
            
            /* DEBUG MODE ONLY: Print function */
            if(debugmode == 1)
            {
                printf("\nSelected function: printAllRecords\n\n");
            }
        }

        /* Detect find */
        else if( (strncmp(userInput, "find", strlen(userInput))) == 0 )
        {
            int validInput = -1;
        
            /* Get account number */
            while(validInput == -1)
            {
                printf("Please input account number: ");
                if( scanf("%d", &accountNum) == 0 )
                {
                    printf("\nError: Please input an integer\n");
                }
                else if( accountNum <= 0 )
                {
                    printf("\nError: Please input a positive integer\n");
                }
                else
                {
                    validInput = 0; /* Input is successful*/
                    printf("\n");
                }
                fgets(trash, 100, stdin);
            }

            /* Call find function */
            findRecord(start, accountNum);

            /* DEBUG MODE ONLY: Print function and values */
            if(debugmode == 1)
            {
                printf("Selected function: findRecord\n");
                printf("Account Number: %d\n\n", accountNum);
            }
        }

        /* Detect delete */
        else if( (strncmp(userInput, "delete", strlen(userInput))) == 0 )
        {
            int validInput = -1;

            /* Get account number */
            while(validInput == -1)
            {
                printf("Please input account number: ");
                if( scanf("%d", &accountNum) == 0 )
                {
                    printf("\nError: Please input an integer\n");
                }
                else if( accountNum <= 0 )
                {
                    printf("\nError: Please input a positive integer\n");
                }
                else
                {
                    validInput = 0; /* Input is successful*/
                    printf("\n");
                }
                fgets(trash, 100, stdin);
            }
            
            /* Call delete function */
            deleteRecord(&start, accountNum);

            /* DEBUG MODE ONLY: Print function and values */
            if(debugmode == 1)
            {
                printf("Selected function: deleteRecord\n");
                printf("Account Number: %d\n\n", accountNum);
            }
        }
        
        /* Detect quit */
        else if( (strncmp(userInput, "quit", strlen(userInput))) == 0 )
        {
            userQuit = 0;
            if(debugmode == 1)
            {
                printf("\nSelected function: quit\n");
            }
            /* Save all records to file */
            writefile(start, "bankrecords.txt");
        }
 
        /* Nothing decteted or invalid option name */
        else
        {
            printf("Error: Invalid option name. Please enter a valid menu option.\n\n");
        }

    }
    cleanup(&start);
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
    char userChar;
    int count = 0;
    printf("Please enter address below. Type '\\[Enter]' when you are finished.\n");

    do
    {
        userChar = getchar();
        if(userChar != '\\')
        {
            address[count] = userChar;
            count++;
        }
       
    }
    while ( userChar != '\\' && count < (limit - 1) );
    address[count] = '\0';
}
