#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route-record.h"

#define MAX_RECORDS 8000

RouteRecord* createRecords(FILE* fileIn) {
    char line[100];
    int count = 0;
    // Count number of records in the file
    while (fgets(line, 100, fileIn)) {
        if (count != 0) { // ignore header
            count++;
        }
    }
    // Allocate memory for array of RouteRecord structs
    RouteRecord* records = malloc(count * sizeof(RouteRecord));
    // Initialize passenger count to 0 for each month
    int i,j;
    
    for (i = 0; i < count; i++) {
        for (j = 0; j < 6; j++) {
            records[i].passengerCount[j] = 0;
        }
    }
    // Rewind file pointer
    rewind(fileIn);
    // Return pointer to array of RouteRecord structs
    return records;
}

int fillRecords(RouteRecord* r, FILE* fileIn) {
    char line[100];
    int count = 0;
    // Process each line in the file
    while (fgets(line, 100, fileIn)) {
        if (count != 0) { // ignore header
            // Parse CSV line
            char* origin = strtok(line, ",");
            char* destination = strtok(NULL, ",");
            char* airline = strtok(NULL, ",");
            int passengers[6];
            int i;
            for (i = 0; i < 6; i++) {
                passengers[i] = atoi(strtok(NULL, ","));
            }
            // Find existing record with same origin, destination, and airline
            int idx = findAirlineRoute(r, count, origin, destination, airline, 0);
            if (idx != -1) { // update existing record
            int i;
                for (i = 0; i < 6; i++) {
                    r[idx].passengerCount[i] += passengers[i];
                }
            } else { // add new record
                strncpy(r[count].origin, origin, 3);
                strncpy(r[count].destination, destination, 3);
                strncpy(r[count].airline, airline, 3);
                int i;
                for (i = 0; i < 6; i++) {
                    r[count].passengerCount[i] = passengers[i];
                }
                count++;
            }
        }
    }
    // Return actual number of records used in array
    return count;
}

int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx) {
    if (curIdx >= length) { // base case: record not found
        return -1;
    }
    if (strncmp(r[curIdx].origin, origin, 3) == 0 &&
        strncmp(r[curIdx].destination, destination, 3) == 0 &&
        strncmp(r[curIdx].airline, airline, 3) == 0) { // base case: record found
        return curIdx;
    }
    // Recursive case: check next record
    return findAirlineRoute(r, length, origin, destination, airline, curIdx + 1);
}

void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st) {
    int found = 0;
    int totalPassengers = 0;
    int totalPassengersByMonth[6] = { 0 };
    int matchingRecordsCount = 0;
    
    int i;
    for (i = 0; i < length; i++) {
        RouteRecord record = r[i];
        int matchesKey = 0;
        
        switch (st) {
            case ROUTE:
                if (strcmp(record.origin, key1) == 0 && strcmp(record.destination, key2) == 0) {
                    matchesKey = 1;
                }
                break;
            case ORIGIN:
                if (strcmp(record.origin, key1) == 0) {
                    matchesKey = 1;
                }
                break;
            case DESTINATION:
                if (strcmp(record.destination, key1) == 0) {
                    matchesKey = 1;
                }
                break;
            case AIRLINE:
                if (strcmp(record.airline, key1) == 0) {
                    matchesKey = 1;
                }
                break;
        }
        
        if (matchesKey) {
            found = 1;
            matchingRecordsCount++;
            printf("Airline: %s, Route: %s-%s\n", record.airline, record.origin, record.destination);
            
            int j;
            for (j = 0; j < 6; j++) {
                totalPassengersByMonth[j] += record.passengerCount[j];
                totalPassengers += record.passengerCount[j];
            }
        }
    }
    
    if (found) {
        printf("Total number of passengers on all matching records: %d\n", totalPassengers);
        printf("Total number of passengers by month for all matching records: ");
        int i;
        for (i = 0; i < 6; i++) {
            printf("%d ", totalPassengersByMonth[i]);
        }
        printf("\n");
        printf("Average number of passengers per month: %.2f\n", (float)totalPassengers / (matchingRecordsCount * 6));
    } else {
        printf("No matching records found.\n");
    }
}

void printMenu()
{
	printf( "\n\n######### Airline Route Records Database MENU #########\n" );
	printf( "1. Search by Route\n" );
	printf( "2. Search by Origin Airport\n" );
	printf( "3. Search by Destination Airport\n" );
	printf( "4. Search by Airline\n" );
	printf( "5. Quit\n" );
	printf( "Enter your selection: " );
}

