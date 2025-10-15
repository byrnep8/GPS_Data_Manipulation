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

	char row[MAX_CHAR];
	// Parse through every row of the file until end is reached
	while(feof(fp) != true)
	{
		fgets(row, MAX_CHAR, fp);
		printf(row);
		
	}
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
