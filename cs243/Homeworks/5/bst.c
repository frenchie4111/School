/**
 * File: bst.c
 * @author mdl7240 : Mike Lyons
 * $Id: 08919f3 Added comments to bst.c $
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

// $Log: $ 
// commit 08919f3420da2adce3c2973c76aa30040e71d096
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Thu Mar 6 10:11:06 2014 -0500
// 
//     Added comments to bst.c
// 
// commit 1f97aba567f9bc0bdac08a2d2fea5fa5331f991f
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Thu Mar 6 10:02:22 2014 -0500
// 
//     Fixed postorder traverse
// 
// commit 904bd272459dc312b957b99e8fefcdc6f918938b
// Merge: f9179f4 8268406
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Thu Mar 6 09:57:15 2014 -0500
// 
//     Merge branch 'master' of https://github.com/frenchie4111/School
//     
//     Conflicts:
//     	cs243/Homeworks/5/bst.c
// 
// commit f9179f4d1cd268718518b39edba828a8fcdfcb7e
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Thu Mar 6 09:56:46 2014 -0500
// 
//     Updated error messages
// 
// commit 82684068bb4f2f9de9117c897b0ed3353ed1e8a8
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Thu Mar 6 09:54:20 2014 -0500
// 
//     Added input.2 and default case statement for traverse
// 
// commit 99c163b485868fb65913eae2e0183fce15b6a3a8
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Thu Mar 6 09:45:36 2014 -0500
// 
//     Fixed Valgrind unitialized error
// 
// commit 4466081ebca5601a16e144ffd0033555da6d3b54
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Thu Mar 6 09:34:17 2014 -0500
// 
//     cs Homework 5 complete
// 
// commit 1f398cf3cb3fd9c8043fc51e658cfdb5a1ddc1dc
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Tue Mar 4 12:22:56 2014 -0500
// 
//     Added stubs for functions from bst.h
// 
// commit 16c706faad1bb7c24d6a00f7de77628753fed8e2
// Author: MICHAEL DOUGLAS LYONS <mdl7240@cs.rit.edu>
// Date:   Tue Mar 4 11:53:25 2014 -0500
// 
//     Initial Commit
// 

