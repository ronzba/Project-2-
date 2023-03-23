#ifndef ROUTE-RECORDS_H
#define ROUTE-RECORDS_H
#define MAX_LEN 4
#define MAX_FLIGHTS 7439

typedef struct RouteRecord{
	char origin[MAX_LEN];
	char destination[MAX_LEN];
	char airline[MAX_LEN -1];
	int passengersCount[6];
} RouteRecord;

typedef enum SearchType { ROUTE, ORIGIN, DESTINATION, AIRLINE } SearchType;

#endif
