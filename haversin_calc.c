/*
	C file to implement haversin formula for calculation of distance between 2 co-ordinates

	Author:	Patrick Byrne
	Date:	15-10-25
*/
#include "haversin_calc.h"

typedef struct GPS_Data{
	int lat;
	int lon;
	int dist;
	int hr;
};

typedef struct LL_GPS{
	struct GPS_Data gps;
	struct LL_GPS *next;
};

//When running compiled file ensure to give arg of file to be passed
int main(int argc, char* argv[]){

	// Checking arg for multiple entries ensuring csv file name entered.
	if( argc < 2 ){
		printf("No arg entered on runtime for csv file\n");
		return -1;
	}

	// Opening csv file
	FILE *fp;
	fp = fopen(argv[1], "r");

	// Check if file is opened
	if( fp == NULL ){
		printf("Cannot open file");
		return -2;
	}

	struct LL_GPS *head = NULL;
	char buffer[1000];
	char *data;
	float *lat, *lon, *dist;
	int *hr;
	int length = 0;

	lat = (float*)calloc(sizeof(int), 1);
	lon = (float*)calloc(sizeof(int), 1);
	dist = (float*)calloc(sizeof(int), 1);
	hr = (int*)calloc(sizeof(int), 1);
	// Read in header line
	fgets(buffer, sizeof(buffer), fp);
	printf("%s\n", buffer);

	// Parsing line
	data = strtok(buffer, ",");
	printf("First Token:\t%s\n", data);

	for(int i = 2; i < 29; i++){
		// Use Null to allow strtok to keep using buffer
		data = strtok(NULL, ",");
		printf("Token #%d:\t%s\n", i, data);
	}

	// Read in header line
	fgets(buffer, sizeof(buffer), fp);
	printf("%s\n", buffer);

	// Parsing 2nd line
	data = strtok(buffer, ",");
	printf("First Token:\t%s\n", data);

	// Reading first 20 elements, not needed
	for(int i = 2; i < 20; i++){
		// Use Null to allow strtok to keep using buffer
		data = strtok(NULL, ",");
		printf("Token #%d:\t%s\n", i, data);
	}

	// First elements Read
	data = strtok(NULL, ",");
	lat[length] = atof(data);
	data = strtok(NULL, ",");
	lon[length] = atof(data);
	data = strtok(NULL, ",");
	data = strtok(NULL, ",");
	dist[length] = atof(data);
	data = strtok(NULL, ",");
	hr[length] = atoi(data);

	printf("Latitude\t:%.4f\nLongitude\t:%.4f\nDistance:\t%.4f\nHR:\t\t%d\n", lat[length], lon[length], dist[length], hr[length]);
	length++;

	while( fgets(buffer, sizeof(buffer), fp) ){
		// Print Buffer to terminal
		// printf("%s\n", buffer);

		// Read first 2 elements and discard them
		data = strtok(buffer, ",");
		
		data = strtok(NULL, ",");
		// printf("Latitude:\t%s\n", data);

		data = strtok(NULL, ",");
		// printf("Longitude:\t%s\n", data);

		data = strtok(NULL, ",");

		data = strtok(NULL, ",");
		// printf("Distance:\t%s\n", data);

		data = strtok(NULL, ",");
		// printf("HR:\t%s\n", data);
		length++;
	}
	
	fclose(fp);
	// Return program success
	return EXIT_SUCCESS;
}

/*
 *  Using haversin formula to calculate the distance between 2 gps coordinates
 *  This formula takes into account the curvature of the Earth
 */ 
int haversinCalc(int lon1, int lon2, char we, int lat1, int lat2, char ns){
	int phi1, phi2, delta_phi, delta_lambda;
	// placeholder of PI
	int PI = 3.1415962;
	int PI_RAD = PI/180;
	phi1 = lat1*PI_RAD;
	phi2 = lat2*PI_RAD;

	delta_phi = (phi2-phi1)*PI_RAD;
	delta_lambda = (lon2-lon1)*PI_RAD;

	int delta_p = sin(delta_phi/2);
	int delta_l = sin(delta_lambda/2);

	int a = (delta_p*delta_p)+(cos(phi1)*cos(phi1)*cos(phi2)*delta_l*delta_l);
	int c = 2 * atan2(sqrt(a), sqrt(1-a));
	
	int distance = R*c;
	return distance;
}
