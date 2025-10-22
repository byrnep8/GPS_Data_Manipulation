/*
	C file to implement haversin formula for calculation of distance between 2 co-ordinates

	Author:	Patrick Byrne
	Date:	15-10-25
*/
#include "haversin_calc.h"

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

	// struct LL_GPS *head = NULL;
	char buffer[1000];
	char *data;
	double *lat, *lon, *dist;
	int *hr;
	int length = 0;

	lat = (double*)calloc(sizeof(int), 1);
	lon = (double*)calloc(sizeof(int), 1);
	dist = (double*)calloc(sizeof(int), 1);
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

	// Reading first 20 elements, discarded as not needed
	for(int i = 2; i < 20; i++){
		// Use Null to allow strtok to keep using buffer
		data = strtok(NULL, ",");
		printf("Token #%d:\t%s\n", i, data);
	}

	// Reading of first elements from the file
	data = strtok(NULL, ",");
	lat[length] = atof(data);
	data = strtok(NULL, ",");
	lon[length] = atof(data);
	data = strtok(NULL, ",");
	data = strtok(NULL, ",");
	dist[length] = atof(data);
	data = strtok(NULL, ",");
	hr[length] = atoi(data);

	// printf("Latitude\t:%.4f\nLongitude\t:%.4f\nDistance:\t%.4f\nHR:\t\t%d\n", lat[length], lon[length], dist[length], hr[length]);
	length++;
	
	// Reading the sample data file from the terminal
	while( fgets(buffer, sizeof(buffer), fp) ){
		
		lat = (double*)realloc(lat, sizeof(double) * (length+1));
		lon = (double*)realloc(lon, sizeof(double) * (length+1));
		dist = (double*)realloc(dist, sizeof(double) *(length+1));
		hr = (int*)realloc(hr, sizeof(int) * (length+1));

		// Read first 2 elements and discard them
		data = strtok(buffer, ",");
		
		data = strtok(NULL, ",");
		lat[length] = atof(data);
		// printf("Latitude:\t%s\n", data);

		data = strtok(NULL, ",");
		lon[length] = atof(data);

		// printf("Longitude:\t%s\n", data);
		data = strtok(NULL, ",");

		data = strtok(NULL, ",");
		dist[length] = atof(data);
		// printf("Distance:\t%.4f\n", dist[length]);

		data = strtok(NULL, ",");
		hr[length] = atoi(data);
		// printf("HR:\t%s\n", data);
		length++;
	}

	double new_d = 0;

	// Using GPS Data parsed to calculate distance between 2 points continuously
	for(int i=0; i<length-1; i++)
	{
		new_d += haversinCalc(lon[i], lon[i+1], lat[i], lat[i+1]);

		printf("Calculated distance\t:%.4f\nRecorded Distance\t:%.4f\n", new_d, dist[i+1]);
	}

	// Close file and free memory allocation
	fclose(fp);
	free(lon);
	free(lat);
	free(dist);
	free(hr);

	// Return program success
	return EXIT_SUCCESS;
}

/*
 *  Using haversin formula to calculate the distance between 2 gps coordinates
 *  This formula takes into account the curvature of the Earth
 */ 
double haversinCalc(double lon1, double lon2, double lat1, double lat2){
	// converting latitudes to radians
	double rLat1 = (PI*lat1)/180;
	double rLat2 = (PI*lat2)/180;

	// Longitude distances, conerted to radians
	double theta = lon1 - lon2;
	double rTheta = (PI*theta)/180;

	// Haversin formula for distance along curve
	double distance = (sin(rLat1)*sin(rLat2))+(cos(rLat1)*cos(rLat2)*cos(rTheta));
	distance = acos(distance);
	distance = (distance*180)/PI;

	// Scaling back for kms (1.609344) and further to meters (1000)
	distance = distance*60*1.1515*1.609344*1000;
	
	return distance;
}
