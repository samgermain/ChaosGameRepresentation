//cgr.4.cc
//Samuel Germain
//11131725
//sjg970
//Lec Sec 01
//Tut Sec T07

#include <assert.h>
#include <inttypes.h>
#include <iostream>
using namespace std;

const int SCALE = 64;
char Plot[SCALE][SCALE];
const uint64_t maxBitShift = ((uint64_t)1<<63);


//for a pair of values n, q representing the rational number n/q
typedef struct{	
	uint64_t numer;
	uint64_t denom;
}coord_t;
//... ...(coord_t t){
//... t.numer ...
//... t.denom ...
//}

//point_t is a point on the graph, with both a y coordinate and an x coordinate
typedef struct{
	coord_t y;
	coord_t x;
}point_t;
// ... ...(point_t t) {
// ... t.y ...
// ... t.x ...
// }

//a nucleotide is either A G C or T
typedef enum{A, G, C, T}
	ntide_t;
// ... ...(ntide_t ntide, ...) {
// ...
// switch (ntide) {
// case A: ...; break;
// case G: ...; break;
// ...
// return midPoint; break;
// }
// the number of nucleotides is last + 1

//scale_coord: divides numerator and denominator by 2 if denominator has a high order bit set
//In: coord_t old_coord
//Out:
//return: updated structure of coord_t
//else original structure of coord_t if not updated	
coord_t scale_coord( coord_t old_coord ){
	if(old_coord.denom>=maxBitShift){										
		old_coord.denom = old_coord.denom>>1;
		old_coord.numer = old_coord.numer>>1;
	}
	assert(old_coord.denom <= maxBitShift);
	return old_coord;
}

//scale_point: scales either coordinate of old_point if it needs scaling
//In: point_t old_point
//Out:
//return: the resultant point
point_t scale_point( point_t old_point ){
	old_point.x = scale_coord(old_point.x);
	old_point.y = scale_coord(old_point.y);
	return old_point;
}

//print_plot: Outputs the plot stored in the global 2D array plot with bounding box around the plot and labelled vertices
//In: void
//Out:
//return: nothing
void print_plot(){
	cout<<"C+";
	for(int i = 0; i<SCALE; i++){
		cout<<"-";
	}
	cout<<"+G"<<endl;
	for(int i = SCALE-1; i>=0; i--) {
		cout<<" |";
		for(int j=0; j<SCALE; j++) {
			cout<<Plot[j][i];
		}
		cout <<"|"<<endl;
	}
	cout<<"A+";
	for(int i=0; i<SCALE; i++){
		cout<<"-";
	}
	cout<<"+T"<<endl;
}

//portion_of_scale: represents a rational number of numer/denom given coord
//In: coord_t coord where denominator!=0
//Out: 
//return: the integer portion of (SCALE*n/d), a fractional result is rounded down to the nearest integer
int portion_of_scale( coord_t coord ){
	assert(coord.denom!=0);
	while(coord.denom!=SCALE){
		if(coord.denom<SCALE){
			coord.numer = coord.numer*2;
			coord.denom = coord.denom*2;
		}
		if(coord.denom>SCALE){
			coord.numer = coord.numer/2;
			coord.denom = coord.denom/2;
		}
	}
	return coord.numer;
}

//initialize_plot: intializes all the points to be an empty space
//In: nothing
//Out:
//return: nothing
void initialize_plot(){
	for(int i = 0; i<SCALE; i++){
		for(int j=0; j<SCALE; j++){
			Plot[i][j] = ' ';
		}
	}
}
			
//plot_point: using portion_of_scale, scales the two coordinates of point, set Plot[i][j] to '*' assuming the result is (i,j)
//In: point_t point
//Out:
//return: nothing
void plot_point( point_t point ){
	int i = portion_of_scale(point.x);
	int j = portion_of_scale(point.y);
	Plot[i][j] = '*';
}

//determine_midpoint: determine midpoint of pnt1 and pnt2, return value of the new point as a function value
//In: point_t pnt1 and point_t pnt2 where the denominator of neither point is equal to 0 after being multiplied by 2
//Out:
//return: updated points where denominator>= numerator
point_t determine_midpoint( point_t pnt1, point_t pnt2 ){
	assert(pnt1.x.denom != 0);
	assert(pnt2.y.denom !=0);
	assert(pnt1.x.denom*2 != 0);
	assert(pnt2.y.denom*2 !=0);
	scale_point(pnt1);
	scale_point(pnt2);
	point_t midPoint;
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

//cgr: If input character is A,C,G or T then the corresponding vertex is determined, the current point is scaled if necessary, the midpoint of the current point and the corresponding vertex is calculated, the midpoint is used to set the appropriate element in the plot to PBM_BLACK
// converts in_char to uppercase if neccessary 
// In: point_t in_point and char in_char
// Out:
// return: calculated midpoint as the function value if the input character is upper or lower case{A,C,G, or T}
//else: return in_point
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

//main: program entry point
//In: nothing
//Out: 
//return -- EXIT_SUCCESS if program terminates normally,
// EXIT_FAILURE otherwise
int main(){

#ifdef TESTING

	point_t cgrTestPoint;
	point_t cgrPoint2;
	
	//Test1: testing if initialize plot sets all spaces to a blank space
	initialize_plot();
	for(int i = 0; i<SCALE; i++){
		for(int j=0; j<SCALE; j++){
			assert(Plot[i][j] = ' ');
		}
	}	
	
	//Test2: testing if scale_coord works correctly when the denominator is equal the border
	cgrTestPoint.x.numer = 2;
	cgrTestPoint.x.denom = maxBitShift;
	cgrTestPoint.x = scale_coord(cgrTestPoint.x);
	assert(cgrTestPoint.x.denom == (maxBitShift>>1));
	
	//Test3: testing if scale_coord works correctly when the denominator is 1 higher than the border
	cgrTestPoint.x.numer = 2;
	cgrTestPoint.x.denom = maxBitShift + 1;
	cgrTestPoint.x = scale_coord(cgrTestPoint.x);
	assert(cgrTestPoint.x.denom >= (maxBitShift+1)>>1);
	
	//Test4: testing if scale_coord works correctly when the denominator is 1 less than the border
	cgrTestPoint.x.numer = 2;
	cgrTestPoint.x.denom = maxBitShift - 1;
	cgrTestPoint.x = scale_coord(cgrTestPoint.x);
	assert(cgrTestPoint.x.denom >= (maxBitShift-1));
	
	//Test5: testing if scale_point works when the y point denominator is equal to the border
	cgrTestPoint.y.numer = 2;
	cgrTestPoint.y.denom = maxBitShift;
	cgrTestPoint = scale_point(cgrTestPoint);
	assert(cgrTestPoint.y.denom >= (maxBitShift)>>1);
	
	//Test6: testing if scale_point works when the y point denominator is 1 higher that the border
	cgrTestPoint.y.numer = 2;
	cgrTestPoint.y.denom = maxBitShift+1;
	cgrTestPoint = scale_point(cgrTestPoint);
	assert(cgrTestPoint.y.denom >= (maxBitShift+1)>>1);
	
	//Test7: testing if scale_point works when the y point denominator is 1 lower that the border
	cgrTestPoint.y.numer = 2;
	cgrTestPoint.y.denom = maxBitShift-1;
	cgrTestPoint = scale_point(cgrTestPoint);
	assert(cgrTestPoint.y.denom >= (maxBitShift-1));
	
	//Test8: testing if scale_point works when the x point denominator is equal to the border
	cgrTestPoint.x.numer = 2;
	cgrTestPoint.x.denom = maxBitShift;
	cgrTestPoint = scale_point(cgrTestPoint);
	assert(cgrTestPoint.x.denom >= (maxBitShift)>>1);
	
	//Test9: testing if scale_point works when the x point denominator is 1 higher that the border
	cgrTestPoint.x.numer = 2;
	cgrTestPoint.x.denom = maxBitShift+1;
	cgrTestPoint = scale_point(cgrTestPoint);
	assert(cgrTestPoint.x.denom >= (maxBitShift+1)>>1);
	
	//Test10: testing if scale_point works when the x point denominator is 1 lower that the border
	cgrTestPoint.x.numer = 2;
	cgrTestPoint.x.denom = maxBitShift-1;
	scale_point(cgrTestPoint);
	assert(cgrTestPoint.x.denom >= (maxBitShift-1));
	
	//Test11: testing portion_of_scale for when the coord denominator is less that SCALE
	cgrTestPoint.x.numer = 16;
	cgrTestPoint.x.denom = 32;
	int portionTest = portion_of_scale(cgrTestPoint.x);
	assert(portionTest == 32);
	
	//Test12: testing portion_of_scale for when the coord denominator is greater than SCALE
	cgrTestPoint.x.numer = 16;
	cgrTestPoint.x.denom = 128;
	portionTest = portion_of_scale(cgrTestPoint.x);
	assert(portionTest==8);
	
	//Test13: testing portion_of_scale for when the coord denominator is equal to SCALE
	cgrTestPoint.x.numer = 16;
	cgrTestPoint.x.denom = 128;
	portionTest = portion_of_scale(cgrTestPoint.x);
	assert(portionTest==8);
	
	//Test14: testing if plot point plots what it is supposed to 
	cgrTestPoint.x.numer = 4;
	cgrTestPoint.x.denom = 16;
	cgrPoint2.x.numer = 2;
	cgrPoint2.x.denom = 16;
	cgrTestPoint.y.numer = 2;
	cgrTestPoint.y.denom = 32;
	cgrPoint2.y.numer = 16;
	cgrPoint2.y.denom = 32;
	plot_point(cgrTestPoint);
	plot_point(cgrPoint2);
	assert('*' == Plot[16][4] && '*' == Plot[8][32]);
	
	//Test15: testing determine_midpoint where the point 1 x denominator = point 2 x denominator and point 1 y denominator = point 2 y denominator
	cgrTestPoint.x.numer = 4;
	cgrTestPoint.x.denom = 16;
	cgrPoint2.x.numer = 2;
	cgrPoint2.x.denom = 16;
	cgrTestPoint.y.numer = 2;
	cgrTestPoint.y.denom = 32;
	cgrPoint2.y.numer = 16;
	cgrPoint2.y.denom = 32;
	point_t midpoint = determine_midpoint(cgrTestPoint, cgrPoint2);
	assert((midpoint.x.numer==6)&&(midpoint.x.denom==32)&&(midpoint.y.numer==18)&&(midpoint.y.denom==64));
	
	//Test16: testing determine_midpoint where the point 1 x denominator < point 2 x denominator and point 1 y denominator < point 2 y denominator
	cgrTestPoint.x.numer = 4;
	cgrTestPoint.x.denom = 16;
	cgrPoint2.x.numer = 2;
	cgrPoint2.x.denom = 32;
	cgrTestPoint.y.numer = 2;
	cgrTestPoint.y.denom = 32;
	cgrPoint2.y.numer = 16;
	cgrPoint2.y.denom = 64;
	midpoint = determine_midpoint(cgrTestPoint, cgrPoint2);
	assert((midpoint.x.numer==10)&&(midpoint.x.denom==64)&&(midpoint.y.numer==20)&&(midpoint.y.denom==128));
	
	//Test17: testing determine_midpoint where the point 1 x denominator > point 2 x denominator and point 1 y denominator > point 2 y denominator
	cgrTestPoint.x.numer = 4;
	cgrTestPoint.x.denom = 64;
	cgrPoint2.x.numer = 2;
	cgrPoint2.x.denom = 32;
	cgrTestPoint.y.numer = 2;
	cgrTestPoint.y.denom = 128;
	cgrPoint2.y.numer = 16;
	cgrPoint2.y.denom = 64;
	midpoint = determine_midpoint(cgrTestPoint, cgrPoint2);
	assert((midpoint.x.numer==8)&&(midpoint.x.denom==128)&&(midpoint.y.numer==34)&&(midpoint.y.denom==256));
	
	cgrTestPoint.x.numer = 4;
	cgrTestPoint.x.denom = 16;
	cgrTestPoint.y.numer = 2;
	cgrTestPoint.y.denom = 32;
	
	//Test18: testing cgr for a letter that is not capital or lowercase a,g,c,t
	cgrTestPoint = cgr(cgrTestPoint, 'f');
	assert(cgrTestPoint.x.numer == 4 && cgrTestPoint.x.denom == 16 && cgrTestPoint.y.numer == 2 && cgrTestPoint.y.denom == 32);
	
	//Test19: testing cgr for lowercase a
	cgrTestPoint = cgr(cgrTestPoint, 'a');
	assert(cgrTestPoint.x.numer == 4 && cgrTestPoint.x.denom == 32 && cgrTestPoint.y.numer == 2 && cgrTestPoint.y.denom == 64);
	assert('*' == Plot[portion_of_scale(cgrTestPoint.x)][portion_of_scale(cgrTestPoint.y)]);
	
	//Test20: testing cgr for capital A
	cgrTestPoint = cgr(cgrTestPoint, 'A');
	assert(cgrTestPoint.x.numer == 4 && cgrTestPoint.x.denom == 64 && cgrTestPoint.y.numer == 2 && cgrTestPoint.y.denom == 128);
	assert('*' == Plot[portion_of_scale(cgrTestPoint.x)][portion_of_scale(cgrTestPoint.y)]);
	
	//Test21: testing cgr for lowercase c
	cgrTestPoint = cgr(cgrTestPoint, 'c');
	assert(cgrTestPoint.x.numer == 4 && cgrTestPoint.x.denom == 128 && cgrTestPoint.y.numer == 130 && cgrTestPoint.y.denom == 256);
	assert('*' == Plot[portion_of_scale(cgrTestPoint.x)][portion_of_scale(cgrTestPoint.y)]);
	
	//Test22: testing cgr for capital C
	cgrTestPoint = cgr(cgrTestPoint, 'C');
	assert(cgrTestPoint.x.numer == 4 && cgrTestPoint.x.denom == 256 && cgrTestPoint.y.numer == 386 && cgrTestPoint.y.denom == 512);
	assert('*' == Plot[portion_of_scale(cgrTestPoint.x)][portion_of_scale(cgrTestPoint.y)]);
	
	//Test23: testing cgr for lowercase t
	cgrTestPoint = cgr(cgrTestPoint, 't');
	assert(cgrTestPoint.x.numer == 260 && cgrTestPoint.x.denom == 512 && cgrTestPoint.y.numer == 386 && cgrTestPoint.y.denom == 1024);
	assert('*' == Plot[portion_of_scale(cgrTestPoint.x)][portion_of_scale(cgrTestPoint.y)]);
	
	//Test24: testing cgr for capital T
	cgrTestPoint = cgr(cgrTestPoint, 'T');
	assert(cgrTestPoint.x.numer == 772 && cgrTestPoint.x.denom == 1024 && cgrTestPoint.y.numer == 386 && cgrTestPoint.y.denom == 2048);
	assert('*' == Plot[portion_of_scale(cgrTestPoint.x)][portion_of_scale(cgrTestPoint.y)]);
	
	//Test25: testing cgr for lowercase g
	cgrTestPoint = cgr(cgrTestPoint, 'g');
	assert(cgrTestPoint.x.numer == 1796 && cgrTestPoint.x.denom == 2048 && cgrTestPoint.y.numer == 2434 && cgrTestPoint.y.denom == 4096);
	assert('*' == Plot[portion_of_scale(cgrTestPoint.x)][portion_of_scale(cgrTestPoint.y)]);
	
	//Test26: testing cgr for capital G
	cgrTestPoint = cgr(cgrTestPoint, 'G');
	assert(cgrTestPoint.x.numer == 3844 && cgrTestPoint.x.denom == 4096 && cgrTestPoint.y.numer == 6530 && cgrTestPoint.y.denom == 8192);
	assert('*' == Plot[portion_of_scale(cgrTestPoint.x)][portion_of_scale(cgrTestPoint.y)]);
	
	//Test27: testing if print_plot prints what it is supposed to, should only plot 2 points at Plot[16][4] and Plot[8][32]
	initialize_plot();
	cgrTestPoint.x.numer = 4;
	cgrTestPoint.x.denom = 16;
	cgrPoint2.x.numer = 2;
	cgrPoint2.x.denom = 16;
	cgrTestPoint.y.numer = 2;
	cgrTestPoint.y.denom = 32;
	cgrPoint2.y.numer = 16;
	cgrPoint2.y.denom = 32;
	plot_point(cgrTestPoint);
	plot_point(cgrPoint2);
	print_plot();
	
#else	
	
    char nTide;
	point_t cgrPoint;
	cgrPoint.x.numer = 1;
	cgrPoint.x.denom = 2;
	cgrPoint.y.numer = 1;
	cgrPoint.y.denom = 2;
	initialize_plot();
	while(cin >> nTide){
		cgrPoint = cgr(cgrPoint, nTide);
	}

#endif

	print_plot();
}
