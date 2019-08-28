//cgr_aux.h
//Samuel Germain
//11131725
//sjg970
//Lec Sec 01
//Tut Sec T07

#ifndef _cgrauxh_
#define _cgrauxh_

#include "cgr.h"

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

//is_power_of_2: Determines if an integer is a power of 2
//In: int val
//Out:
//return: true if val is a power of 2
//else return false
bool is_power_of_2( int val );

//scale_coord: divides numerator and denominator by 2 if denominator has a high order bit set
//In: coord_t old_coord
//Out:
//return: updated structure of coord_t
//else original structure of coord_t if not updated	
coord_t scale_coord( coord_t old_coord );

//scale_point: scales either coordinate of old_point if it needs scaling
//In: point_t old_point
//Out:
//return: the resultant point
point_t scale_point( point_t old_point );

//determine_midpoint: determine midpoint of pnt1 and pnt2, return value of the new point as a function value
//In: point_t pnt1 and point_t pnt2 where the denominator of neither point is equal to 0 after being multiplied by 2
//Out:
//return: updated points where denominator>= numerator
point_t determine_midpoint( point_t pnt1, point_t pnt2 );

//cgr: If input character is A,C,G or T then the corresponding vertex is determined, the current point is scaled if necessary, the midpoint of the current point and the corresponding vertex is calculated, the midpoint is used to set the appropriate element in the plot to PBM_BLACK
// converts in_char to uppercase if neccessary 
// In: point_t in_point and char in_char
// Out:
// return: calculated midpoint as the function value if the input character is upper or lower case{A,C,G, or T}
//else: return in_point
point_t cgr( point_t in_point, char in_char );

#endif