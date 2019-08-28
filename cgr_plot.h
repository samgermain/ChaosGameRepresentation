//cgr_plot.h
//Samuel Germain
//11131725
//sjg970
//Lec Sec 01
//Tut Sec T07

#ifndef _cgrploth_
#define _cgrploth_

#include "cgr.h"
#include <netpbm/pbm.h>
const int MIN_SCALE = 32;
const int MAX_SCALE = 4096;
extern int SCALE;
extern bit** Plot;
const uint64_t maxBitShift = ((uint64_t)1<<63);

//initialize_plot: intializes all the points by calling pbm_allocarray
//In: nothing
//Out:
//return: nothing
void initialize_plot();

//output_plot: Outputs the plot stored in the global 2D array plot with bounding box around the plot and labelled vertices
//In: void
//Out:
//return: nothing
void output_plot();

//portion_of_scale: represents a rational number of numer/denom given coord
//In: coord_t coord where denominator!=0
//Out: 
//return: the integer portion of (SCALE*n/d), a fractional result is rounded down to the nearest integer
int portion_of_scale( coord_t coord );

//plot_point: using portion_of_scale, scales the two coordinates of point, set Plot[i][j] to PMB_BLACK assuming the result is (i,j)
//In: point_t point
//Out:
//return: nothing
void plot_point( point_t point );

#endif //cgrploth