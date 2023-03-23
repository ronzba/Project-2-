

// This function creates the array of RouteRecord's and initializes it. The function takes in a file pointer
RouteRecord* createRecords(FILE* fileIn){
	
	// open file
	FILE *file = fopen("data.csv", "r");
	if (file == NULL) {
		printf("ERROR FILE DID NOT OPEN\n");
		return 1;
	}
	
	// Allocate Memory for array
	RouteRecord *routeRecord = malloc(sizeof(RouteRecord) * MAX_FLIGHTS);
	
	// Initialize each array value to 0
	struct RouteRecord RouteRecordStruct;
	int i;
	for (i = 0; i < 6; i++) {
		myStruct.passengerCount[1] = 0;
	}
	
	// Rewind File
	rewind(file);
}
