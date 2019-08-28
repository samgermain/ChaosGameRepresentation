//cgr.h
//Samuel Germain
//11131725
//sjg970
//Lec Sec 01
//Tut Sec T07

#ifndef _cgrh_
#define _cgrh_

#include <inttypes.h>

//for a pair of values numer, denom representing the rational number numer/denom
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

#endif //cgrh