//cgr_aux.cc
//Samuel Germain
//11131725
//sjg970
//Lec Sec 01
//Tut Sec T07

#include "cgr_plot.h"
#include "cgr_aux.h"
#include <assert.h>
using namespace std;


bool is_power_of_2( int val ) {
	if (val <2){
		return false;
	}
	while(0==val%2){
		val = val/2;		//goes down in a loop until the loop reaches one as every power of 2 can be divided by 2 until it reaches 1
	}
	if (1==val){
		return true;
	}else{
		return false;
	}
}

coord_t scale_coord( coord_t old_coord ){
	if(old_coord.denom>=maxBitShift){										
		old_coord.denom = old_coord.denom>>1;
		old_coord.numer = old_coord.numer>>1;	//bit shifts the number if it is larger than the max uint_64 number
	}
	assert(old_coord.denom <= maxBitShift);		
	return old_coord;
}

point_t scale_point( point_t old_point ){
	old_point.x = scale_coord(old_point.x);
	old_point.y = scale_coord(old_point.y);
	return old_point;
}

point_t determine_midpoint( point_t pnt1, point_t pnt2 ){
	assert(pnt1.x.denom != 0);
	assert(pnt2.y.denom !=0);
	assert(pnt1.x.denom*2 != 0);
	assert(pnt2.y.denom*2 !=0);
	scale_point(pnt1);
	scale_point(pnt2);
	point_t midPoint;
	//four loops below bit shift the numbers until they have a common denominator
	if (pnt1.x.denom<pnt2.x.denom){
		while(pnt1.x.denom<pnt2.x.denom){
			pnt1.x.numer = pnt1.x.numer<<1;
			pnt1.x.denom = pnt1.x.denom<<1;
		}
	}
	else if (pnt1.x.denom>pnt2.x.denom){
		while(pnt1.x.denom>pnt2.x.denom){
			pnt2.x.denom = pnt2.x.denom<<1;
			pnt2.x.numer = pnt2.x.numer<<1;
		}
	}
	if (pnt1.y.denom<pnt2.y.denom){
		while(pnt1.y.denom<pnt2.y.denom){
			pnt1.y.numer = pnt1.y.numer<<1;
			pnt1.y.denom = pnt1.y.denom<<1;
		}
	}
	else if (pnt1.y.denom>pnt2.y.denom){
		while(pnt1.y.denom>pnt2.y.denom){
			pnt2.y.denom = pnt2.y.denom<<1;
			pnt2.y.numer = pnt2.y.numer<<1;
		}
	}
	midPoint.x.numer = pnt1.x.numer + pnt2.x.numer;
	midPoint.x.denom = pnt1.x.denom<<1;
	midPoint.y.numer = pnt1.y.numer + pnt2.y.numer;
	midPoint.y.denom = pnt1.y.denom<<1;
	return midPoint;
}

point_t cgr( point_t in_point, char in_char ){
	ntide_t nucleotide;
	if (in_char=='a'||in_char=='A'){
		nucleotide=A;
	}else if(in_char=='g'||in_char=='G'){
		nucleotide=G;
	}else if(in_char=='t'||in_char=='T'){
		nucleotide = T;
	}else if(in_char=='c'||in_char=='C'){
		nucleotide = C;
	}else{
		return in_point;
	}
	point_t correspondingVertex;
	//determines the vertex for the corresponding nucleotide
	switch(nucleotide){
		case A: correspondingVertex.x.numer = 0;
				correspondingVertex.x.denom = 1;
				correspondingVertex.y.numer = 0;
				correspondingVertex.y.denom = 1;
				break;
		case C: correspondingVertex.x.numer = 0;
				correspondingVertex.x.denom = 1;
				correspondingVertex.y.numer = 1;
				correspondingVertex.y.denom = 1;
				break;
		case G: correspondingVertex.x.numer = 1;
				correspondingVertex.x.denom = 1;
				correspondingVertex.y.numer = 1;
				correspondingVertex.y.denom = 1;
				break;
		case T: correspondingVertex.x.numer = 1;
				correspondingVertex.x.denom = 1;
				correspondingVertex.y.numer = 0;
				correspondingVertex.y.denom = 1;
				break;
		default: assert(false);
	}
	in_point = scale_point(in_point);
	assert(in_point.y.denom != maxBitShift);
	point_t midPoint = determine_midpoint(correspondingVertex, in_point);
	plot_point(midPoint);
	return midPoint;
}