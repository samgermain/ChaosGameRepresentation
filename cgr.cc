//cgr.cc
//Samuel Germain
//11131725
//sjg970
//Lec Sec 01
//Tut Sec T07

#include "cgr_plot.h"
#include "cgr_aux.h"
#include <iostream>
using namespace std;
	
int main(int argc, char* argv[]){
	pm_init("cgr", 0);
	if(argc!=2){
		fprintf(stderr, "Usage: %s <N>\n", argv[0]);	//testing if there are not 2 arguments
		return EXIT_FAILURE;
	}
	SCALE = atoi(argv[1]);
	
	if (SCALE>MAX_SCALE){
		fprintf(stderr, "SCALE is too big\n");	//testing if the input scale is over the max limit
		return EXIT_FAILURE;
	}
	if (SCALE<MIN_SCALE){
		fprintf(stderr, "SCALE is too small\n");	// testing if the input scale is less than the minimummlimit
		return EXIT_FAILURE;
	}
	if (!(is_power_of_2(SCALE))){
		fprintf(stderr, "SCALE is not a power of 2\n");	// testing if the input scale is not a power of 2
		return EXIT_FAILURE;
	}
	
    char nTide;
    point_t cgrPoint;		// set as the original mid point in the graph
	cgrPoint.x.numer = 1;		
	cgrPoint.x.denom = 2;
	cgrPoint.y.numer = 1;
	cgrPoint.y.denom = 2;
	initialize_plot();
	
	while(cin >> nTide){
		cgrPoint = cgr(cgrPoint, nTide);		//takes in nucleatides and plots them
	}

	output_plot();
	return EXIT_SUCCESS;
}
