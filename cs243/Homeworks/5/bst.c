/**
 * File: bst.c
 * @author mdl7240 : Mike Lyons
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Helper Functions

void printIntArray( int array[], int count ) {
	for( int i = 0; i < count; i++ ) {
		printf( "%d\n", array[i] );
	}
}

// Major Functions



/**
 * Main function
 *
 * @param argc the number of arguments
 * @param argv array of arguments
 * @returns int the error code; 0 if no error
 */
int main( int argc, const char* argv[] ) {
	if( argc == 2 ) {
		int count = atoi( argv[1] );	
		int inputValues[ count ];
		printf("Number of arguments: %d\n", count );
		for( int i = 0; i < count; i++ ) {
			int inputNumber = 0;
			scanf( "%d", &inputNumber );
			inputValues[ i ] = inputNumber;	
		}
		printIntArray( inputValues, count );
	} else {
		printf("Invalid Arguments");
	}
}
