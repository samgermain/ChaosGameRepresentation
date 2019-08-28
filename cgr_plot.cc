//cgr_plot.cc
//Samuel Germain
//11131725
//sjg970
//Lec Sec 01
//Tut Sec T07

#include "cgr_aux.h"
#include <assert.h>
#include <netpbm/pbm.h>
using namespace std;

int SCALE;
bit** Plot;

void initialize_plot(){
	Plot = pbm_allocarray(SCALE, SCALE);
}

void output_plot(){
	pbm_writepbminit(stdout, SCALE, SCALE, false);
	for(int i = SCALE-1; i>=0; i--){	
		pbm_writepbmrow(stdout, Plot[i], SCALE, false);
	}
}

int portion_of_scale( coord_t coord ){
	assert(coord.denom!=0);
	while(coord.denom!=(uint64_t)SCALE){
		if(coord.denom<(uint64_t)SCALE){
			coord.numer = coord.numer*2;
			coord.denom = coord.denom*2;
		}
		if(coord.denom>(uint64_t)SCALE){
			coord.numer = coord.numer/2;
			coord.denom = coord.denom/2;
		}
	}
	return coord.numer;
}

void plot_point( point_t point ){
	int i = portion_of_scale(point.x);
	int j = portion_of_scale(point.y);
	Plot[j][i] = PBM_BLACK;
}