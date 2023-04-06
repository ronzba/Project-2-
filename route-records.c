#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route-record.h"


RouteRecord* createRecords(FILE* fp) {
	
	RouteRecord data;
    char line[100];
    int count = 0;
    
    // Count number of records in the file
    while (fgets(line, 100, fp) != NULL)
	{    
        ++count;
    }
    
    count = count - 1;
    
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
   rewind(fp);
    // Return pointer to array of RouteRecord structs
    return records;
}

int fillRecords(RouteRecord* records, FILE* fp){
    char line[100];
    int count = 0;

    // Process each line
    while (fgets(line, 100, fp)){
        if (count != 0){
            sscanf(line, "%*d, %3[^,], %3[^,], %2[^,], %*[^,], %d, %d, %d, %d, %d, %d, %d", records->origin, records->destination, records->airline,
           		&records->passengerCount[0], &records->passengerCount[1],
				&records->passengerCount[2], &records->passengerCount[3],
           		&records->passengerCount[4], &records->passengerCount[5]);
        }
        // Find existing record with same origin, destination, and airline
        int idx = findAirlineRoute(records, count, records->origin, records->destination, records->airline, 0);
        if (idx != -1) { // update existing record
            int i;
            for (i = 0; i < 6; i++) {
                records[idx].passengerCount[i] += records->passengerCount[i];
            }
        } else { // add new record
            strncpy(records[count].origin, records->origin, 3);
            strncpy(records[count].destination, records->destination, 3);
            strncpy(records[count].airline, records->airline, 2);
            int i;
            for (i = 0; i < 6; i++) {
                records[count].passengerCount[i] = records->passengerCount[i];
            }
            count++;
        }
    }
    // Return actual number of records used in array
    return count;
}


int findAirlineRoute(RouteRecord* records, int length, const char* origin, const char* destination, const char* airline, int curIdx){
	if (curIdx >= length){ // basecase
		return -1;
	}
	if (strncmp(records[curIdx].origin, origin, 3) == 0 && strncmp(records[curIdx].destination, destination, 3)== 0 && strncmp(records[curIdx].airline, airline,2) == 0)
	{
		return curIdx;
	}
	
	// Recursive Case
	return findAirlineRoute(records, length, origin, destination, airline, curIdx + 1);
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

void searchRecords(RouteRecord* records, int length, const char* key1, const char* key2, SearchType st) {
    int found = 0;
    int totalPassengers = 0;
    int totalPassengersByMonth[6] = { 0 };
    int matchingRecordsCount = 0;
    
    int i;
    for (i = 0; i < length; i++) {
        RouteRecord record = records[i];
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
