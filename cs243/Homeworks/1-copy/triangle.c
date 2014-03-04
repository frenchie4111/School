// 
// File: triangle.c 
// 
// A program to print out multiple triangles "right-up" triangles.
// of the form
//    *
//   **
//  ***
// ****
// 
// @author mdl7240 : Michael Lyons
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

#include <stdlib.h>
#include <stdio.h>

/**
 *  Function: drawTriangle
 *
 *  Description: function to draw a triangle whose height/width is "size"
 * 
 *  @param size  the size of the triangle to draw
 */

void drawTriangle( int degree ) {
	int i;
	for( i = 1; i <= degree; i++ ) {
		int j = 0;
		for( ; j < (degree - i); j++ ) {
			printf( " " );	
		}
		for( ; j < degree; j++ ) {
			printf( "*" );
		}
		printf("\n");
	}
}

/**
 *  Function: main 
 *
 *  Description: program to draw 3 triangles of size 2, 4, and 6.
 *
 *  @author mdl7240 : Michael Lyons
 * 
 *  @param argc  number of command line arguments, including program name
 *  @param argv  supplied command line arguments, including program name
 *  @returns errorCode  error Code; EXIT_SUCCESS if no error
 */

int main() {
	drawTriangle( 2 );
	drawTriangle( 4 );
	drawTriangle( 6 );
	return( EXIT_SUCCESS );
}

// // // // // // // // // // // // // // // // // // // // // // // // 
// Version: 
// $Id$ 
// 
// Revisions: 
// $Log$ 
