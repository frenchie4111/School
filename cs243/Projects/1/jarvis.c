/**
 * File: jarvis.c
 * 
 * @author mdl7240 : Mike Lyons
 */
#include <stdio.h>
#include <string.h>

#include "points.h"

/**
 * Finds the convex hull of given points using the jarvis algorithm
 *
 * @arg struct Point points[] The points to find the convex hull of
 * @arg int count How many points there is in points
 * @arg struct Point answer[] The array to put the results in
 * 		This array will be populated with the results of the algorithm
 *
 * @return int The number of result points
 */
int jarvis( struct Point points[], int count, struct Point answer[] ) {
	struct Point pointOnHull = leftmostPoint( points, count );	
	struct Point endpoint;
	int i = 0;
	while( !equal( endpoint, answer[0] ) ) {
		answer[i] = pointOnHull;
		endpoint = points[0];
		for( int j = 0; j < count; j++ ) {
			if( equal( pointOnHull, endpoint ) ||
			    ccw( answer[i], endpoint, points[j] ) > 0 ) {
				endpoint = points[j];
			} 
		}
		i = i + 1;
		pointOnHull = endpoint;
	}
	return i;
}

/**
 * Main function
 *
 * Takes user input and finds/prints the convex hull using
 * jarvis algorithm.
 *
 * @param argc the number of arguments
 * @param argv array of arguments
 * @returns int the error code; 0 if no error
 */
int main( int argc, const char* argv[] ) {
	struct Point points[MAX_POINTS];
	int numPoints = readPoints( points );
	
	struct Point results[numPoints];
	int numResults = jarvis( points, numPoints, results );

	printf("Convex hull:\n");
	displayPoints( results, numResults );
}
