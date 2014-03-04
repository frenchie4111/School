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

void tree_add( TreeNode** root, const int element ) {
	TreeNode *currentNode = *root;
	while( currentNode ) {
		if( element <= currentNode->data ) {
			currentNode = currentNode->left;
		}
		else {
			currentNode = currentNode->right;
		}
	}
}

void build_tree( TreeNode** root, const int elements[], const int count ) {
	for( int i = 0; i < count; i++ ) {
		tree_add( root, elements[i] );
	}
}

void traverse( const TreeNode* root, const TraversalType type ) {

}

void cleanup_tree( TreeNode* root ) {

}

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
