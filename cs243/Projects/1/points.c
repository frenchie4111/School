#include <stdio.h>
#include <stdlib.h>

#include "points.h"

int ccw(struct Point p, struct Point q, struct Point r) {
	return( (q.x - p.x)*(r.y - p.y) - (q.y - p.y)*(r.x - p.x) );
}

void displayPoint( struct Point p ) {
	printf("%c: (%d,%d)\n", p.label, p.x, p.y);
}

void displayPoints( struct Point points[], int count ) {
	for( int i = 0; i < count; i++ ) {
		displayPoint( points[i] );
	}
}

int equal( struct Point p1, struct Point p2 ) {
	if( p1.x == p2.x && p1.y == p2.y ) {
		return 1;
	}
	return 0;
}

int indexOf( struct Point p, struct Point points[], int numPoints ) {
	for( int i = 0; i < numPoints; i++ ) {
		if( equal( points[i], p ) ) {
			return i;
		}
	}
	return -1;
}

struct Point leftmostPoint( struct Point points[], int numPoints ) {
	struct Point leftMost = points[0];
	for( int i = 0; i < numPoints; i++ ) {
		if( points[i].x < leftMost.x ) {
			leftMost = points[i];
		}
	}
	return leftMost;
}

struct Point rightmostPoint( struct Point points[], int numPoints ) {
	struct Point rightMost = points[0];
	for( int i = 0; i < numPoints; i++ ) {
		if( points[i].x > rightMost.x ) {
			rightMost = points[i];
		}
	}
	return rightMost;
}

struct Point furthestLeftPoint( struct Point a, struct Point z, struct Point points[], int numPoints) {
	struct Point furthestLeft = points[0];
	int furthestLeftCcw = ccw( a, z, furthestLeft );
	for( int i = 0; i < numPoints; i++ ) {
		int currentCcw = ccw( a, z, points[i] );
		if( currentCcw > furthestLeftCcw ) {
			furthestLeftCcw = currentCcw;
			furthestLeft = points[i];
		}
	}
	return furthestLeft;
}

int leftPointSet( struct Point a, struct Point z, struct Point points[], int numPoints, struct Point lps[]) {
	int numLps = 0;
	for( int i = 0; i < numPoints; i++ ) {
		if( ccw( a, z, points[i] ) > 0 ) {
			lps[numLps] = points[i];
			numLps++;
		}
	}
	return numLps;
}

struct Point lowestPoint( struct Point points[], int numPoints ) {
	struct Point lowest = points[0];
	for( int i = 0; i < numPoints; i++ ) {
		if( points[i].y < lowest.y ) {
			lowest = points[i];
		}	
	}
	return lowest;
}

int readPoints( struct Point points[] ) {
	char buff[MAX_LINE];

	int numPoints = 0;
	// First input is number of points
	printf("Number of points(3-100):");
	fgets( buff, MAX_LINE, stdin );
	if( feof( stdin ) ) {
		printf("Error reading number of points.\n");
		return 0;
	}
	numPoints = atoi( buff );
	if( numPoints < 3 || numPoints > 100 ) {
		printf("Number of points must be between 3 and 100.\n");
		return 0;	
	}

	for( int i = 0; i < numPoints; i++ ) {
		// Character that represents the string
		printf("Enter label (character):");
		fgets( buff, MAX_LINE, stdin );
		if( feof( stdin ) ) {
			printf("Error reading point label.\n");
			return 0;
		}
		points[i].label = buff[0];

		// X Value
		printf("Enter x (int):");
		fgets( buff, MAX_LINE, stdin);
		if( feof( stdin ) ) {
			printf("Error reading x coordinate.\n");
			return 0;
		}
		points[i].x = atoi( buff );

		// Y Value
		printf("Enter y (int):");
		fgets( buff, MAX_LINE, stdin);
		if( feof( stdin ) ) {
			printf("Error reading y coordinate.\n");
			return 0;
		}
		points[i].y = atoi( buff );
	}
	
	printf("Set of points:\n");
	displayPoints( points, numPoints );	
	return numPoints;
}

void swap( int a, int b, struct Point points[], int numPoints ) {
	if( a < numPoints && b < numPoints ) {
		struct Point temp = points[a];
		points[a] = points[b];
		points[b] = temp;
	}
}
