//test_plot.cc
//Samuel Germain
//11131725
//sjg970
//Lec Sec 01
//Tut Sec T07

#include "cgr_plot.h"
#include <assert.h>
using namespace std;

//test_portion_of_scale: tests if the function portion_of_scale functions as it should
//In: point_t cgrTestPoint
//Out: 
//return: nothing
void test_portion_of_scale(point_t cgrTestPoint){
	//Test1: testing portion_of_scale for when the coord denominator is less that SCALE
	cgrTestPoint.x.numer = 16;
	cgrTestPoint.x.denom = 32;
	int portionTest = portion_of_scale(cgrTestPoint.x);
	assert(portionTest == 32);
	
	//Test2: testing portion_of_scale for when the coord denominator is greater than SCALE
	cgrTestPoint.x.numer = 16;
	cgrTestPoint.x.denom = 128;
	portionTest = portion_of_scale(cgrTestPoint.x);
	assert(portionTest==8);
	
	//Test3: testing portion_of_scale for when the coord denominator is equal to SCALE
	cgrTestPoint.x.numer = 16;
	cgrTestPoint.x.denom = 128;
	portionTest = portion_of_scale(cgrTestPoint.x);
	assert(portionTest==8);
}

//test_plot_point: tests if the function plot_point functions as it should
//In: point_t cgrTestPoint and point_t cgrPoint2
//Out: 
//return: nothing
void test_plot_point(point_t cgrTestPoint, point_t cgrPoint2){
	//Test4: testing if plot point plots what it is supposed to 
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
	assert(PBM_BLACK == Plot[4][16] && PBM_BLACK == Plot[32][8]);
}

//main: tests all the functions in cgr_plot.cc
//In: nothing
//Out: 
//return: EXIT_SUCCESS if all the functions work correctly
int main(){
	pm_init("cgr", 0);
	SCALE = 64;
	initialize_plot();
	point_t cgrTestPoint;
	point_t cgrPoint2;
	test_portion_of_scale(cgrTestPoint);
	test_plot_point(cgrTestPoint, cgrPoint2);
	return EXIT_SUCCESS;
}
