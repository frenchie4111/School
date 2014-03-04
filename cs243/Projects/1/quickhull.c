/**
 * File: <<TEMPLATE MARK>>
 * <<TEMPLATE MARK>>
 * @author mdl7240 : Mike Lyons
 */
#include <stdio.h>
#include <string.h>

#include "points.h"

/**
 * Recursive function for quickhull algorithm. Calculates convex hull
 *
 * @arg struct Point points[] Array of points to analyze to find convext hull
 * 		This array is updated with results points after excecution
 * @arg int count Number of points in the array
 * @arg struct Point l The left point of the line that is currently being analyzed
 * @arg struct Point r The right point of the line that is currently beinga analyzed
 *
 * @return int Number of results in points array
 */
int quickHullRec( struct Point points[], int count, struct Point l, struct Point r ) {
	if( count > 0 ) {
		struct Point f = furthestLeftPoint( l, r, points, count );
		struct Point L[count];
		int leftCount = leftPointSet( l, f, points, count, L );
		struct Point R[count];
		int rightCount = leftPointSet( f, r, points, count, R );

		int leftCallCount = quickHullRec( L, leftCount, l, f );
		int rightCallCount = quickHullRec( R, rightCount, f, r );

		int replacementIndex = 0;
		
		for( int i = 0; i < leftCallCount; i++ ) {
			points[replacementIndex] = L[i];
			replacementIndex++;
		}
		points[replacementIndex] = f;
		replacementIndex++;
		for( int i = 0; i < rightCallCount; i++ ) {
			points[replacementIndex] = R[i];
			replacementIndex++;
		}
		return replacementIndex;
	}
	return 0;
}

/**
 * Main function for quickhull algorithm. Invokes recursive algorithm in
 * order to find the convex hull of the given points
 *
 * @arg struct Point points[] The points to find the convex hull of
 * 		This array is updated with results points after excecution
 * @arg int count How many points there is in the array
 *
 * @return Returns the number of result points in the points[] array
 */
int quickHull( struct Point points[], int count ) {
	struct Point l = leftmostPoint( points, count );
	struct Point r = rightmostPoint( points, count );
	struct Point L[count];
	int leftCount = leftPointSet( l, r, points, count, L );
	struct Point R[count];
	int rightCount = leftPointSet( r, l, points, count, R );

	int leftCallCount = quickHullRec( L, leftCount, l, r );
	int rightCallCount = quickHullRec( R, rightCount, r, l );

	int replacementIndex = 0;
	
	points[replacementIndex] = l;
	replacementIndex++;
	for( int i = 0; i < leftCallCount; i++ ) {
		points[replacementIndex] = L[i];
		replacementIndex++;
	}
	points[replacementIndex] = r;
	replacementIndex++;
	for( int i = 0; i < rightCallCount; i++ ) {
		points[replacementIndex] = R[i];
		replacementIndex++;
	}
	return replacementIndex;
}

/**
 * Main function
 *
 * @param argc the number of arguments
 * @param argv array of arguments
 * @returns int the error code; 0 if no error
 */
int main( int argc, const char* argv[] ) {
	struct Point points[MAX_POINTS];
	int numPoints = readPoints( points );
	
	struct Point l = leftmostPoint( points, numPoints );
	struct Point r = rightmostPoint( points, numPoints );
	struct Point L[ numPoints ];
	int leftCount = leftPointSet( l, r, points, numPoints, L );
	struct Point R[ numPoints ];
	int rightCount = leftPointSet( r, l, points, numPoints, R );

	int numResults = quickHull( points, numPoints );
	printf("Convex hull:\n");
	displayPoints( points, numResults );
}
