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
    
    // Rewind file pointer
   rewind(fp);
    // Return pointer to array of RouteRecord structs
    return records;
}

int fillRecords(RouteRecord* r, FILE* fileIn){
   char buffer[LENGTH];
   int routeCount = 0;
   int i;
   int passengers[MONTHS] = {0, 0, 0, 0, 0, 0};

   fgets(buffer, LENGTH, fileIn);

   while(fgets(buffer, LENGTH, fileIn) != NULL){
      int month;
      char airline[3];
      char origin[4];
      char destination[4];
      char dummy[10];
      int passNum;

      sscanf(buffer, "%d,%[^,],%[^,],%[^,],%[^,],%d", &month, origin, destination, airline, dummy, &passNum);
      passengers[month - 1] += passNum;

      int routeIdx = findAirlineRoute(r, routeCount, origin, destination, airline, 0);

      if(routeIdx >= 0){
         for (i = 0; i < MONTHS; i++){
            r[routeIdx].passengerCount[i] += passengers[i];
         }
         }

      else{
         strcpy(r[routeCount].origin, origin);
         strcpy(r[routeCount].destination, destination);
         strcpy(r[routeCount].airline, airline);

         for (i = 0; i < MONTHS; i++){
            r[routeCount].passengerCount;
            }

      routeCount += 1;
      }
   }
   return routeCount;
}


int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx){
    // base case: if current index is greater than or equal to length, return -1
    if (curIdx >= length) {
        return -1;
    }
    // check if current record matches the given origin, destination, and airline
    if (strncmp(r[curIdx].origin, origin, 3) == 0 && strncmp(r[curIdx].destination, destination, 3) == 0 && strncmp(r[curIdx].airline, airline, 2) == 0) {
        return curIdx; // return current index if there is a match
    }
    // recursive case: search the remaining records
    return findAirlineRoute(r, length, origin, destination, airline, curIdx + 1);
}




	// Print records FOR DEBUGGGING
	void printRecords(RouteRecord* records, int length){
    int i, j;
    for (i = 0; i < 10; i++){
        printf("Record %d:\n", i+1);
        printf("\tOrigin: %s\n", records[i].origin);
        printf("\tDestination: %s\n", records[i].destination);
        printf("\tAirline: %s\n", records[i].airline);
        printf("\tPassenger Count:\n");
        for (j = 0; j < 6; j++){
            printf("\t\Month %d: %d\n", j+1, records[i].passengerCount[j]);
        }
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
