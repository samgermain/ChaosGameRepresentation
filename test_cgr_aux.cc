//test_aux.cc
//Samuel Germain
//11131725
//sjg970
//Lec Sec 01
//Tut Sec T07

#include "cgr_plot.h"
#include "cgr_aux.h"
#include <assert.h>
using namespace std;

//test_scale_coord: tests if the function scale_coord works correctly
//In: point_t cgrTestPoint
//Out: 
//return: nothing
void test_scale_coord(point_t cgrTestPoint){
	//Test1: testing if scale_coord works correctly when the denominator is equal the border
	cgrTestPoint.x.numer = 2;
	cgrTestPoint.x.denom = maxBitShift;
	cgrTestPoint.x = scale_coord(cgrTestPoint.x);
	assert(cgrTestPoint.x.denom == (maxBitShift>>1));
	
	//Test2: testing if scale_coord works correctly when the denominator is 1 higher than the border
	cgrTestPoint.x.numer = 2;
	cgrTestPoint.x.denom = maxBitShift + 1;
	cgrTestPoint.x = scale_coord(cgrTestPoint.x);
	assert(cgrTestPoint.x.denom >= (maxBitShift+1)>>1);
	
	//Test3: testing if scale_coord works correctly when the denominator is 1 less than the border
	cgrTestPoint.x.numer = 2;
	cgrTestPoint.x.denom = maxBitShift - 1;
	cgrTestPoint.x = scale_coord(cgrTestPoint.x);
	assert(cgrTestPoint.x.denom >= (maxBitShift-1));
}

//test_scale_point: tests if the function scale_point works correctly
//In: point_t cgrTestPoint
//Out: 
//return: nothing
void test_scale_point(point_t cgrTestPoint){
	//Test4: testing if scale_point works when the y point denominator is equal to the border
	cgrTestPoint.y.numer = 2;
	cgrTestPoint.y.denom = maxBitShift;
	cgrTestPoint = scale_point(cgrTestPoint);
	assert(cgrTestPoint.y.denom >= (maxBitShift)>>1);
	
	//Test5: testing if scale_point works when the y point denominator is 1 higher that the border
	cgrTestPoint.y.numer = 2;
	cgrTestPoint.y.denom = maxBitShift+1;
	cgrTestPoint = scale_point(cgrTestPoint);
	assert(cgrTestPoint.y.denom >= (maxBitShift+1)>>1);
	
	//Test6: testing if scale_point works when the y point denominator is 1 lower that the border
	cgrTestPoint.y.numer = 2;
	cgrTestPoint.y.denom = maxBitShift-1;
	cgrTestPoint = scale_point(cgrTestPoint);
	assert(cgrTestPoint.y.denom >= (maxBitShift-1));
	
	//Test7: testing if scale_point works when the x point denominator is equal to the border
	cgrTestPoint.x.numer = 2;
	cgrTestPoint.x.denom = maxBitShift;
	cgrTestPoint = scale_point(cgrTestPoint);
	assert(cgrTestPoint.x.denom >= (maxBitShift)>>1);
	
	//Test8: testing if scale_point works when the x point denominator is 1 higher that the border
	cgrTestPoint.x.numer = 2;
	cgrTestPoint.x.denom = maxBitShift+1;
	cgrTestPoint = scale_point(cgrTestPoint);
	assert(cgrTestPoint.x.denom >= (maxBitShift+1)>>1);
	
	//Test9: testing if scale_point works when the x point denominator is 1 lower that the border
	cgrTestPoint.x.numer = 2;
	cgrTestPoint.x.denom = maxBitShift-1;
	scale_point(cgrTestPoint);
	assert(cgrTestPoint.x.denom >= (maxBitShift-1));
}

//test_determine_midpoint: tests if the function determine_midpoint works correctly
//In: point_t cgrTestPoint
//Out: 
//return: nothing
void test_determine_midpoint(point_t cgrTestPoint, point_t cgrPoint2){
	//Test10: testing determine_midpoint where the point 1 x denominator = point 2 x denominator and point 1 y denominator = point 2 y denominator
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
	
	//Test11: testing determine_midpoint where the point 1 x denominator < point 2 x denominator and point 1 y denominator < point 2 y denominator
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
	
	//Test12: testing determine_midpoint where the point 1 x denominator > point 2 x denominator and point 1 y denominator > point 2 y denominator
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
}

//test_cgr: tests if the function cgr works correctly
//In: point_t cgrTestPoint
//Out: 
//return: nothing
void test_cgr(point_t cgrTestPoint){
	cgrTestPoint.x.numer = 4;
	cgrTestPoint.x.denom = 16;
	cgrTestPoint.y.numer = 2;
	cgrTestPoint.y.denom = 32;
	//Test13: testing cgr for a letter that is not capital or lowercase a,g,c,t
	cgrTestPoint = cgr(cgrTestPoint, 'f');
	assert(cgrTestPoint.x.numer == 4 && cgrTestPoint.x.denom == 16 && cgrTestPoint.y.numer == 2 && cgrTestPoint.y.denom == 32);
	//Test14: testing cgr for lowercase a
	cgrTestPoint = cgr(cgrTestPoint, 'a');
	assert(cgrTestPoint.x.numer == 4 && cgrTestPoint.x.denom == 32 && cgrTestPoint.y.numer == 2 && cgrTestPoint.y.denom == 64);
	assert(PBM_BLACK == Plot[portion_of_scale(cgrTestPoint.y)][portion_of_scale(cgrTestPoint.x)]);
	//Test15: testing cgr for capital A
	cgrTestPoint = cgr(cgrTestPoint, 'A');
	assert(cgrTestPoint.x.numer == 4 && cgrTestPoint.x.denom == 64 && cgrTestPoint.y.numer == 2 && cgrTestPoint.y.denom == 128);
	assert(PBM_BLACK == Plot[portion_of_scale(cgrTestPoint.y)][portion_of_scale(cgrTestPoint.x)]);
	//Test16: testing cgr for lowercase c
	cgrTestPoint = cgr(cgrTestPoint, 'c');
	assert(cgrTestPoint.x.numer == 4 && cgrTestPoint.x.denom == 128 && cgrTestPoint.y.numer == 130 && cgrTestPoint.y.denom == 256);
	assert(PBM_BLACK == Plot[portion_of_scale(cgrTestPoint.y)][portion_of_scale(cgrTestPoint.x)]);
	//Test17: testing cgr for capital C
	cgrTestPoint = cgr(cgrTestPoint, 'C');
	assert(cgrTestPoint.x.numer == 4 && cgrTestPoint.x.denom == 256 && cgrTestPoint.y.numer == 386 && cgrTestPoint.y.denom == 512);
	assert(PBM_BLACK == Plot[portion_of_scale(cgrTestPoint.y)][portion_of_scale(cgrTestPoint.x)]);
	//Test18: testing cgr for lowercase t
	cgrTestPoint = cgr(cgrTestPoint, 't');
	assert(cgrTestPoint.x.numer == 260 && cgrTestPoint.x.denom == 512 && cgrTestPoint.y.numer == 386 && cgrTestPoint.y.denom == 1024);
	assert(PBM_BLACK == Plot[portion_of_scale(cgrTestPoint.y)][portion_of_scale(cgrTestPoint.x)]);
	//Test19: testing cgr for capital T
	cgrTestPoint = cgr(cgrTestPoint, 'T');
	assert(cgrTestPoint.x.numer == 772 && cgrTestPoint.x.denom == 1024 && cgrTestPoint.y.numer == 386 && cgrTestPoint.y.denom == 2048);
	assert(PBM_BLACK == Plot[portion_of_scale(cgrTestPoint.y)][portion_of_scale(cgrTestPoint.x)]);
	//Test20: testing cgr for lowercase g
	cgrTestPoint = cgr(cgrTestPoint, 'g');
	assert(cgrTestPoint.x.numer == 1796 && cgrTestPoint.x.denom == 2048 && cgrTestPoint.y.numer == 2434 && cgrTestPoint.y.denom == 4096);
	assert(PBM_BLACK == Plot[portion_of_scale(cgrTestPoint.y)][portion_of_scale(cgrTestPoint.x)]);
	//Test21: testing cgr for capital G
	cgrTestPoint = cgr(cgrTestPoint, 'G');
	assert(cgrTestPoint.x.numer == 3844 && cgrTestPoint.x.denom == 4096 && cgrTestPoint.y.numer == 6530 && cgrTestPoint.y.denom == 8192);
	assert(PBM_BLACK == Plot[portion_of_scale(cgrTestPoint.y)][portion_of_scale(cgrTestPoint.x)]);
}

//test_is_power_of_2: runs tests for is_power_of_2
//In: nothing
//Out: 
//return: nothing
void test_is_power_of_2(){
	//Test22: testing is_power_of_2 for the lowest power of 2
	assert(true==is_power_of_2(2));
	//Test23: testing is_power_of_2 for 1 below the lowest power of 2
	assert(false==is_power_of_2(1));
	//Test24: testing is_power_of_2 for 0
	assert(false==is_power_of_2(0));
	//Test25: testing is_power_of_w for a negative number
	assert(false==is_power_of_2(-1));
	//Test26: testing is power of 2 for a number that should be a power of 2
	assert(true==is_power_of_2(32));
}


//main: calls all the tests for functions in cgr_aux.cc
//In: nothing
//Out: 
//return: EXIT_SUCCESS if all the functions work correctly
int main(){
	SCALE = 64;
	initialize_plot();
	point_t cgrTestPoint;
	point_t cgrPoint2;
	test_scale_coord(cgrTestPoint);
	test_scale_point(cgrTestPoint);
	test_determine_midpoint(cgrTestPoint, cgrPoint2);
	test_cgr(cgrTestPoint);
	test_is_power_of_2();
	return EXIT_SUCCESS;
}