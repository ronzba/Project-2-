#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "route-record.h"

int main(int argc, char *argv[]) {
    /* 1. Declare variables here */
    FILE *fp;
    RouteRecord *records = NULL;
    int numRecords, actualRecords;
    char key1[4], key2[4];
    SearchType st;
    int choice;
    int count = 7000;

    /* 2. Check command line arguments here. If a command line argument (for the file name) is missing, print out the following: ERROR: Missing file name and end the program */
    if (argc != 2) {
        printf("ERROR: Missing file name\n");
        return 1;
    }
    
    /* 3. Attempt to open the file. Print out Opening <filename>... before you call fopen(). */
    printf("Opening %s...\n", argv[1]);
    fp = fopen(argv[1], "r");
    
    /* 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program. */
    if (fp == NULL) {
        printf("ERROR: Could not open file\n");
        return 1;
    }
    
    /* 5. Do the following to load the records into an array of RouteRecords */
    
    /* 5.1 Call createRecords(), which will read through the file once to find the total number of lines/records in the file. Use this count, to dynamically allocate memory for an array of RouteRecords. It returns a pointer to that array. Don't forget to rewind the file pointer. */
    numRecords = createRecords(fp);
    records = (RouteRecord *) malloc(numRecords * sizeof(RouteRecord));
    rewind(fp);
    
    /* 5.2 Call fillRecords() to go through the CSV file again to fill in the values. It will then return the actual number of items the array has. Recall that not all records in the original CSV file will be entered into the array. Print the number of unique routes operated by different airlines: Unique routes operated by airlines: ??? */
    actualRecords = fillRecords(records, fp);
    printf("Unique routes operated by airlines: %d\n", countUniqueRoutes(records, actualRecords));
    
    /* 5.3 Close the the file. */
    fclose(fp);
    
     /* 6. Create an infinite loop that will do the following: */
    while (1) {
        /* 6.1 Call printMenu() */
        printMenu();
        
        /* 6.2 Ask the user to input a value for the menu */
        printf("Enter a menu option: ");
        if (scanf("%d", &choice) != 1) { /* 6.3 Handle the case in which a non-integer value is entered */
            printf("Invalid input\n");
            while (getchar() != '\n'); /* clear input buffer */
            continue;
        }
    switch (choice) {
        case 1: // search by ROUTE
            printf("Enter Origin airport code (3 letters): ");
            scanf("%3s", key1);
            printf("Enter Destination airport code (3 letters): ");
            scanf("%3s", key2);
            st = ROUTE;
            searchRecords(records, count, key1, key2, st);
            break;
        case 2: // search by ORIGIN
            printf("Enter Origin airport code (3 letters): ");
            scanf("%3s", key1);
            st = ORIGIN;
            searchRecords(records, count, key1, NULL, st);
            break;
        case 3: // search by DESTINATION
            printf("Enter Destination airport code (3 letters): ");
            scanf("%3s", key1);
            st = DESTINATION;
            searchRecords(records, count, key1, NULL, st);
            break;
        case 4: // search by AIRLINE
            printf("Enter Airline name (max 30 characters): ");
            scanf("%30s", key1);
            st = AIRLINE;
            searchRecords(records, count, key1, NULL, st);
            break;
        case 5: // quit
            printf("\nQuitting...\n");
            free(records);
            break;
        default:
            printf("\nInvalid choice. Please choose a number from the menu.\n");
            break;
    }
} while (choice != 5);

  return 0;
}
