/**
 * File: dll_mike.c
 * Dll_Mike Library
 * @author mdl7240 : Mike Lyons
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct dll_n dll_n;

struct dll_n {
    dll_n *prev;
    dll_n *next;
    void *data;
};

typedef struct dll_h {
    dll_n *first;
    dll_n *last;
    dll_n *cursor;
    int size;
} dll_h;

typedef dll_h *dll;

#define _DLL_IMPL_
#include "dll_mike.h"

dll dll_create() {
	dll newDll = (dll)malloc( sizeof( dll_h ) );
	if( newDll ) {
		newDll->first = NULL;
		newDll->last = NULL;
		newDll->cursor = NULL;
		newDll->size = 0;
	}
	return newDll;
}

static dll_n *dll_n_create( void *prev, void *next, void *data ) {
	dll_n *newDllN = (dll_n *)malloc( sizeof( dll_n ) );
	if( newDllN ) {
		newDllN->next = next;
		newDllN->prev = prev;
		newDllN->data = data;
	}
	return newDllN;
}

void dll_destroy( dll list ) {
	dll_clear( list );
	free( list );
}

void dll_clear( dll list ) {
	dll_n *node = list->first;

	while( node )
	{
		dll_n *next = node->next;

		free( node->data );
		free( node );

		node = next;
	}
}

void dll_push( dll list, void *data ) {
	if( list->first == NULL || list->last == NULL ) {
		dll_n *new = dll_n_create( NULL, NULL, data );

		list->first = new;
		list->last = new;
	} else {
		dll_n *oldLast = list->last;

		dll_n *new = dll_n_create( oldLast, NULL, data );

		oldLast->next = new;
		list->last = new;
	}

	list->cursor = list->first;
	list->size++;
}

void dll_push_first( dll list, void *data ) {
	if( list->first == NULL || list->last == NULL ) {
		dll_n *new = dll_n_create( NULL, NULL, data );

		list->first = new;
		list->last = new;
	} else {
		dll_n *oldFirst = list->first;

		dll_n *new = dll_n_create( NULL, list->first, data );

		oldFirst->prev = new;
		list->first = new;
	}

	list->cursor = list->first;
	list->size++;
}

void dll_insert( dll list, void *data, int index ) {
	if( index > list->size ) {

	} if( list->first == NULL || list->last == NULL ) {
		dll_n *new = dll_n_create( NULL, NULL, data );

		list->first = new;
		list->last = new;
	} if( index == 0 ) { // Insert at beginning
		dll_n *new = dll_n_create( NULL, list->first, data );

		if( list->first ) {
			list->first->prev = new;
		}
		list->first = new;
	} else {
		dll_n *node = list->first;

		for( int i = 0; i < index && node; i++, node = node->next );

		// node = oldprev
		dll_n *new = dll_n_create( node, node->next, data );

		node->next = new;
		if( new->next )
			new->next->prev = new;

		if( list->last == node )
			list->last = new;
	}

	list->cursor = list->first;
	list->size++;
}


void *dll_first( dll list ) {
	if( list->first )
		return list->first->data;
	return NULL;
}
void *dll_last( dll list ) {
	if( list->last )
		return list->last->data;
	return NULL;
}
void *dll_get( dll list, int index ) {
	dll_n *node = list->first;

	for( int i = 0; i < index && node; i++, node = node->next );

	if( node )
		return node->data;

	return node;
}


void *dll_pop( dll list ) {
	if( list->last ) {
		dll_n *last = list->last;
		void *data = list->last->data;
		if( last->prev ) {
			last->prev->next = NULL;
			list->last = last->prev;
		} else { // List was empty otherwise
			list->first = NULL;
			list->last = NULL;
		}

		free( last );
		list->cursor = list->first;
		list->size--;
		return data;
	}
	return NULL;
}

void *dll_pop_first( dll list ) {
	if( list->first ) {
		dll_n *first = list->first;
		void *data = list->first->data;
		if( first->next ) {
			first->next->prev = NULL;
			list->first = first->next;
		} else { // List was empty otherwise
			list->first = NULL;
			list->last = NULL;
		}

		free( first );
		list->cursor = list->first;
		list->size--;
		return data;
	}
	return NULL;
}

void *dll_remove( dll list, int index ) {
	if( index >= list->size ) {
		return NULL;
	} else {
		dll_n *node = list->first;

		for( int i = 0; i < index && node; i++, node = node->next );

		void *data = node->data;

		if( node->prev )
			node->prev->next = node->next;
		if( node->next )
			node->next->prev = node->prev;

		if( node == list->first )
			list->first = node->next;
		if( node == list->last )
			list->last = node->prev;

		free( node );
		list->cursor = list->first;
		list->size--;
		return data;
	}
}


int dll_count( dll list ) {
	return list->size;
}


void dll_curs_reset( dll list ) {
	list->cursor = list->first;
}

void *dll_curs_next( dll list ) {
	if( list->cursor ) {
		void *data = list->cursor->data;
		list->cursor = list->cursor->next;
		return data;
	}
	return NULL;
}

int dll_curs_has_next( dll list ) {
	return ( list->cursor != NULL );
}


static void dll_n_print( dll_n *node ) {
	if( node ) {
		printf("Node '%s'\n", (char *)node->data);
		if( node->prev ) {
			printf("\tprev '%s'\n", (char *)node->prev->data);
		}
		if( node->next ) {
			printf("\tnext '%s'\n", (char *)node->next->data);
		}
	}
}

void dll_print( dll list ) {
	dll_n *node = list->first;
	printf("count %d\n", list->size);
	if( list->first )
		printf("first '%s'\n", (char *)list->first->data);
	while( node ) {
		dll_n_print( node );

		node = node->next;
	}
	if( list->last )
		printf("last '%s'\n", (char *)list->last->data);
}
