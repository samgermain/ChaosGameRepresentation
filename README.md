# chaosgamerepresentation

Chaos Game Representation(CGR) is a novel holistic approach for plotting nucleotide sequences.

The project models cgr on a 2-dimensional grid with each corner representing a nucleotide. The first point in plotted in the corner of the the letter that matches the first nucleotide. Each point after that is plotted halfway between the letter that corresponds to the next nucleotide and the previous point plotted.

Ex. A cgr display for the sequence AC

C+----------------------------------------------------------------+G
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |        *                                                       |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
 |                *                                               |
 |                                                                |
 |                                                                |
 |                                                                |
 |                                                                |
A+----------------------------------------------------------------+T

For an in depth explanation of chaos game representation(cgr) please read the explanation at http://www.lifenscience.com/bioinformatics/chaos-game-representation

cgr_aux.h 
Imported Headers
cgr.h - include for use of coord_t and point_t datatypes

GLOBAL ADT's
ntide_t - an enum that assures that a nucleotide is either A, G, C, or T

FUNCTIONS
is_power_of_2
Takes in an integer
Determines if a number is a power of 2
Returns true if the number is a power of 2, false if the number is not

scale_coord:
Takes in a coordinate.
Bit shifts numerator and denominator of a coordinate once to the right if the denominator has a high order bit set.
Returns the coordinate.

scale_point:
Takes in a point.
If either coordinate of the point has a high order bit set the numerator and denominator of that point are bit shifted once to the right by calling scale_coord on each coordinate of the point.
Returns the scaled point. 

determine_midpoint:
Takes in 2 points.
Finds the middle point between both points.
Returns the middle point.

cgr:
Takes in a point and character.
Determines the corresponding vertex of the character(which would be a symbol for a nucleotide), scales the in_point using scale_point, finds the midpoint between the corresponding vertex and point given using determine_midpoint and plots that midpoint using plot_point.
Returns the midpoint that it finds.




cgr_plot.h
IMPORTED HEADERS
netpbm/pbm.h - include for use of PBM functions and datatypes
cgr.h - included for use of point_t and coord_t datatypes

GLOBAL VARIABLES
const int MIN_SCALE - determines the minimum int that scale can be sent to
const int MAX_SCALE - determines the maximum int that scale can be sent to
extern int SCALE - is used to depict the size of the plot 
extern bit** Plot - a 2 dimentional array that holds the information that the cgr function produces
const uint64_t maxBitShift - is used to depict the maximum 64 bit integer number

FUNCTIONS
output_plot: 
Takes in no parameters.
Outputs the plot stored in the 2D array plot with bounding box around the plot and labelled vertices.
Returns nothing.

portion_of_scale:
Takes in a coordinate.
Creates a rational number of the numerator/denominator.
Returns the rational number that it makes.

initialize_plot: 
Takes in no parameters.
intializes all the points by calling pbm_allocarray
Returns nothing.

plot_point: 
Takes in a point .
Sets that point to be PBM_BLACK after scaling the coordinates.
Returns nothing.

cgr.h
IMPORTED HEADERS
inttypes.h - included for use of uint64_t

GLOBAL ADTS
coord_t - a struct that sets the numerator and denominator of either an x or y coordinate
point_t - a struct that sets the x and y coordinate of a point on the Plot




cgr_aux.cc
IMPORTED HEADERS
#include "cgr_plot.h" - is included for use of methods in cgr_plot.cc
#include "cgr_aux.h" - included for use of function headers
#include <assert.h> - include for use of assert function

FUNCTIONS
is_power_of_2
Takes in an integer
Determines if a number is a power of 2
Returns true if the number is a power of 2, false if the number is not

scale_coord:
Takes in a coordinate.
Bit shifts numerator and denominator of a coordinate once to the right if the denominator has a high order bit set.
Returns the coordinate.

scale_point:
Takes in a point.
If either coordinate of the point has a high order bit set the numerator and denominator of that point are bit shifted once to the right by calling scale_coord on each coordinate of the point.
Returns the scaled point. 

determine_midpoint:
Takes in 2 points.
Finds the middle point between both points.
Returns the middle point.

cgr:
Takes in a point and character.
Determines the corresponding vertex of the character(which would be a symbol for a nucleotide), scales the in_point using scale_point, finds the midpoint between the corresponding vertex and point given using determine_midpoint and plots that midpoint using plot_point.
Returns the midpoint that it finds.




cgr_plot.cc
IMPORTED HEADERS
#include "cgr_aux.h" - included for use of function in cgr_aux.cc
#include <assert.h> - included for use of assert funciton
#include <netpbm/pbm.h> - included for use of pbm functions and pbm_black

GLOBAL VARIABLES
int SCALE - is used to depict the size of the plot 
bit** Plot - a 2 dimentional array that holds the information that the cgr function produces

FUNCTIONS
output_plot: 
Takes in no parameters.
Outputs the plot stored in the 2D array plot with bounding box around the plot and labelled vertices.
Returns nothing.

portion_of_scale:
Takes in a coordinate.
Creates a rational number of the numerator/denominator.
Returns the rational number that it makes.

initialize_plot: 
Takes in no parameters.
intializes all the points by calling pbm_allocarray
Returns nothing.

plot_point: 
Takes in a point .
Sets that point to be PBM_BLACK after scaling the coordinates.
Returns nothing.




cgr.cc
IMPORTED HEADERS
cgr_plot.h - included for use of cgr_plot functions
cgr_aux.h - included for use of cgr_aux functions
iostream - included for use of cin

FUNCTIONS
main:
Takes in a series of characters as standard input, and continually calls cgr for each character given in order to plot the midpoints determined by the characters and the midpoints returned by cgr.
Prints the plot of all the points plotted use output_plot.




test_cgr_plot.cc
IMPORTED HEADERS
cgr_plot.h - included for use of cgr_plot functions
assert.h - included for use of assert function

FUNCTIONS
test_portion_of_scale:
takes in a point_t 
tests if the function portion_of_scale functions as it should
returns nothing

test_plot_point:
takes in 2 point_t's
tests if the function plot_point functions as it should
returns nothing

main:
takes in nothing
tests all the functions in cgr_plot.cc
returns nothing

TESTS
Test1: testing portion_of_scale for when the coord denominator is less that SCALE.
Test2: testing portion_of_scale for when the coord denominator is greater than SCALE.
Test3: testing portion_of_scale for when the coord denominator is equal to SCALE.
Test4: testing if plot point plots what it is supposed to.




test_cgr_aux.cc
IMPORTED HEADERS
cgr_plot.h - included for use of cgr_plot functions
cgr_aux.h - included for use of cgr_aux functions
assert.h - included for use of assert function

FUNCTIONS
test_scale_coord:
takes in nothing
tests if the function scale_coord works correctly
returns nothing

test_scale_point
takes in nothing
tests if the function scale_point works correctly
returns nothing

test_determine_midpoint
takes in nothing
tests if the function determine_midpoint works correctly
returns nothing

test_cgr
takes in nothing
tests if the function cgr works correctly
returns nothing

test_is_power_of_2
takes in nothing
tests if the function is_power_of_2 works correctly
returns nothing

main
takes in nothing
calls all the tests for functions in cgr_aux.cc
returns nothing

TESTS
Test1: testing if scale_coord works correctly when the denominator is equal the border.
Test2: testing if scale_coord works correctly when the denominator is 1 higher than the border.
Test3: testing if scale_coord works correctly when the denominator is 1 less than the border.
Test4: testing if scale_point works when the y point denominator is equal to the border.
Test5: testing if scale_point works when the y point denominator is 1 higher that the border.
Test6: testing if scale_point works when the y point denominator is 1 lower that the border.
Test7: testing if scale_point works when the x point denominator is equal to the border.
Test8: testing if scale_point works when the x point denominator is 1 higher that the border.
Test9: testing if scale_point works when the x point denominator is 1 lower that the border.
Test10: testing determine_midpoint where the point 1 x denominator = point 2 x denominator and point 1 y denominator = point 2 y denominator.
Test11: testing determine_midpoint where the point 1 x denominator < point 2 x denominator and point 1 y denominator < point 2 y denominator.
Test12: testing determine_midpoint where the point 1 x denominator > point 2 x denominator and point 1 y denominator > point 2 y denominator.
Test13: tests cgr for invalid character input.
Test14: tests cgr for when in_char=='a' is true. Also check for when nucleotide is case A.
Test15: tests cgr for when in_char=='A' is true.
Test16: tests cgr for when in_char=='g' is true. Also check for when nucleotide is case G.
Test17: tests cgr for when in_char=='G' is true.
Test18: tests cgr for when in_char=='t' is true. Also check for when nucleotide is case T.
Test19: tests cgr for when in_char=='T' is true.
Test20: tests cgr for when in_char=='c' is true.Also check for when nucleotide is case C.
Test21: tests cgr for when in_char=='C' is true.
Test22: testing is_power_of_2 for the lowest power of 2
Test23: testing is_power_of_2 for 1 below the lowest power of 2
Test24: testing is_power_of_2 for 0
Test25: testing is_power_of_w for a negative number
Test26: testing is power of 2 for a number that should be a power of 2
