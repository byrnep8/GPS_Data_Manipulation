#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define R 6371000

int main(int argc, char* argv[]){

	//Sample running of haversin formula for calculating distance
	
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
	int PI_RAD = 3.141592/180;
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
