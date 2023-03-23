

// This function creates the array of RouteRecord's and initializes it. The function takes in a file pointer
RouteRecord* createRecords(FILE* fileIn){
	
	// open file
	FILE *file = fopen("data.csv", "r");
	if (file == NULL) {
		printf("ERROR FILE DID NOT OPEN\n");
		return 1;
	}
	
	// Count the records
	int read = 0;
	int records = 0;
	do
	{
		read = fscanf(file,
		            "%d,%3[^,],%3[^,],%2[^,],%10[^,],%d"
					 &RouteRecord[records].month);
					 RouteRecord[records].origin);
					 RouteRecord[records].destination);
					 RouteRecord[records].airline);
					 &RouteRecord[records].passengerCount);
		records++;
		
		if (ferror(file)){
			printf("Error Reading File");
			return 1;
		}
		            
	} while (!foef(file));
	
	//output records read
	printf("\n Records: ", records);
	
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
// close file at somepoint
