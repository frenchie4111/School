/**
 * File: bst.c
 * @author mdl7240 : Mike Lyons
 * $Id$
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bst.h"

// Helper Functions

/**
 * Prints the values in an int array
 *
 * @param int array[] The array to print
 * @param int count The number of elements in the array
 */
void printIntArray( int array[], int count ) {
	for( int i = 0; i < count; i++ ) {
		printf( "%d\n", array[i] );
	}
}

// Major Functions

/**
 * Creates a new tree node (Mallocs it on the heap)
 *
 * @param const int element The value for the new node to have
 */
TreeNode *new_node( const int element ) {
	TreeNode *newNode = (TreeNode *)malloc( sizeof( TreeNode ) );
	newNode->data = element;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

/**
 * Adds a single value to the bst, maintains bst ordering
 *
 * @param TreeNode** root The root pointer of the tree to build
 * @param const int element The value to add to the bst
 */
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

	*currentNode = new_node( element );
}

/**
 * Builds a bst containing the given node
 *
 * @param TreeNode** root The root pointer of the tree to build
 * @param const int elements[] Array of elements to add to bst
 * @param const int count The number of elements in the array
 */
void build_tree( TreeNode** root, const int elements[], const int count ) {
	for( int i = 0; i < count; i++ ) {
		tree_add( root, elements[i] );
	}
}

/**
 * Traverses a tree using postorder ordering
 *
 * @param TreeNode* root The root of the tree to traverse
 */
void preorder_traverse( const TreeNode* root ) {
	printf( "%d\n", root->data );
	if( root->left ) {
		preorder_traverse( root->left );
	}
	if( root->right ) {
		preorder_traverse( root->right );
	}
}

/**
 * Traverses a tree using inorder ordering
 *
 * @param TreeNode* root The root of the tree to traverse
 */
void inorder_traverse( const TreeNode* root ) {
	if( root->left ) {
		inorder_traverse( root->left );
	}
	printf( "%d\n", root->data );
	if( root->right ) {
		inorder_traverse( root->right );
	}
}

/**
 * Traverses a tree using postorder ordering
 *
 * @param TreeNode* root The root of the tree to traverse
 */
void postorder_traverse( const TreeNode* root ) {
	if( root->left ) {
		postorder_traverse( root->left );
	}
	if( root->right ) {
		postorder_traverse( root->right );
	}
	printf( "%d\n", root->data );
}

/**
 * Traverses the tree using the given traversal type
 *
 * @param TreeNode* root The root of the tree to traverse
 * @param TraversalType type The type of traversal to use (PREORDER|INORDER|POSTORDER)
 */
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
		default:
			break;
	}
}

/**
 * Uses postorder traversal to free the nodes of the tree from memory
 *
 *
 * @param TreeNode *root The root of the tree to cleanup
 */
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
 * Takes user input, creates a bst, and prints it in the 3 ordering methods
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
			printf("Input values:\n");
			printIntArray( inputValues, count );

			TreeNode *treeRoot = NULL;
			build_tree( &treeRoot, inputValues, count );

			traverse( treeRoot, PREORDER );
			traverse( treeRoot, INORDER );
			traverse( treeRoot, POSTORDER );

			cleanup_tree( treeRoot );
		}
		else {
			printf("# must be greater than 0\n");
		}
	} else {
		printf("Usage: bst #\n");
	}
}

// $Log$
