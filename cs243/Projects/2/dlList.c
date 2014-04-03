/**
 * File: <<TEMPLATE MARK>>
 * <<TEMPLATE MARK>>
 * @author mdl7240 : Mike Lyons
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *prev;
    void *next;
    void *data;
} * DlList_T;

#define _DLL_IMPL_
#include "dlList.h"

DlList_T dll_create( void ) {
    DlList_T new_node = (DlList_T)malloc( sizeof( DlList_T ) );
    
    if( new_node != NULL ) {
        new_node->prev = NULL;
        new_node->next = NULL;
        new_node->data = NULL;
    }

    return new_node;
}

void dll_destroy( DlList_T lst ) {
    while( lst ) {
        DlList_T next = lst->next;

        free( lst->data );
        free( lst );

        lst = next;
    }
}

void dll_clear( DlList_T lst ) {    
    free( lst->data );
    dll_destroy( lst->next ); // Just don't free the first one
}

int dll_size( DlList_T lst ) {
    int counter = 0;
    while( lst ) {
        lst = lst->next;
        counter++;
    }
    return counter;
}

void dll_append( DlList_T lst, void *data ) {

}