/**
 * File: bst.c
 * @author mdl7240 : Mike Lyons
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bst.h"

// Helper Functions

void printIntArray( int array[], int count ) {
	for( int i = 0; i < count; i++ ) {
		printf( "%d\n", array[i] );
	}
}

// Major Functions

void tree_add( TreeNode** root, const int element ) {
	TreeNode **currentNode = root;

	while( (*currentNode) ) {
		if( element <= (*currentNode)->data ) {
			currentNode = &((*currentNode)->left);
		}
		else {
			currentNode = &((*currentNode)->right);
		}
	}

	*currentNode = (TreeNode *)malloc( sizeof( TreeNode ) );
	(*currentNode)->data = element;
}

void build_tree( TreeNode** root, const int elements[], const int count ) {
	for( int i = 0; i < count; i++ ) {
		tree_add( root, elements[i] );
	}
}

void preorder_traverse( const TreeNode* root ) {
	printf( "%d\n", root->data );
	if( root->left ) {
		preorder_traverse( root->left );
	}
	if( root->right ) {
		preorder_traverse( root->right );
	}
}

void inorder_traverse( const TreeNode* root ) {
	if( root->left ) {
		inorder_traverse( root->left );
	}
	printf( "%d\n", root->data );
	if( root->right ) {
		inorder_traverse( root->right );
	}
}

void postorder_traverse( const TreeNode* root ) {
	if( root->left ) {
		inorder_traverse( root->left );
	}
	if( root->right ) {
		inorder_traverse( root->right );
	}
	printf( "%d\n", root->data );
}

void traverse( const TreeNode* root, const TraversalType type ) {
	switch( type ) {
		case PREORDER:
			printf("Preorder:\n");
			preorder_traverse( root );
			break;
		case INORDER:
			printf("Inorder:\n");
			inorder_traverse( root );
			break;
		case POSTORDER:
			printf("Postorder:\n");
			postorder_traverse( root );
			break;
	}
}

void cleanup_tree( TreeNode* root ) {
	if( root->left ) {
		cleanup_tree( root->left );
	}
	if( root->right ) {
		cleanup_tree( root->right );
	}
	free( root );
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
		if( count > 0 ) {
			int inputValues[ count ];
			printf("Enter %d integer values to place in tree:\n", count);
			for( int i = 0; i < count; i++ ) {
				int inputNumber = 0;
				scanf( "%d", &inputNumber );
				inputValues[ i ] = inputNumber;	
			}
			printf("Input Values:\n");
			printIntArray( inputValues, count );

			TreeNode *treeRoot = NULL;
			build_tree( &treeRoot, inputValues, count );

			traverse( treeRoot, PREORDER );
			traverse( treeRoot, INORDER );
			traverse( treeRoot, POSTORDER );

			cleanup_tree( treeRoot );
		}
		else {
			printf("# must be greater than 0\n")
		}
	} else {
		printf("Usage: bst #\n");
	}
}
