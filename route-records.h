#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H

#include <stdio.h>
#include <stdlib.h>
#define MONTHS 6

typedef enum SearchType { ROUTE, ORIGIN, DESTINATION, AIRLINE } SearchType;

typedef struct RouteRecord {
    char origin[4];
    char destination[4];
    char airline[3];
    int passengerCount[6];
} RouteRecord;

RouteRecord* createRecords(FILE* fp);
int fillRecords(RouteRecord* , FILE* fp);
int findAirlineRoute(records, length, origin, destination, airline, curIdx);
void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st);
void printMenu();
void printRecords(RouteRecord* records, int length);


#endif
