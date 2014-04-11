/**
 * File: <<TEMPLATE MARK>>
 * <<TEMPLATE MARK>>
 * @author mdl7240 : Mike Lyons
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct DlList_Node DlList_Node;

struct DlList_Node {
    DlList_Node *prev;
    DlList_Node *next;
    void *data;
};

typedef struct DlList_Head {
    DlList_Node *first;
    DlList_Node *cursor;
    int size;
} DlList_Head;

typedef DlList_Head *DlList_T;

#define _DLL_IMPL_
#include "dlList.h"

static DlList_Node *dll_node_create( void *data, DlList_Node *prev, DlList_Node *next ) {
    DlList_Node *new_node = ( DlList_Node * )malloc( sizeof( DlList_Node ) );
    
    if( new_node != NULL ) {
        new_node->prev = prev;
        new_node->next = next;
        new_node->data = data;
    }

    return new_node;
}

DlList_T dll_create( void ) {
    DlList_T new_node = ( DlList_T )malloc( sizeof( DlList_Head ) );
    
    if( new_node != NULL ) {
        new_node->first = NULL;
        new_node->cursor = NULL;
        new_node->size = 0;
    }

    return new_node;
}

void dll_destroy( DlList_T lst ) {
    dll_clear( lst );
    free( lst );
}

void dll_clear( DlList_T lst ) {    
    DlList_Node *current_node = lst->first;
    while( current_node ) {
        DlList_Node *next = current_node->next;

        free( current_node->data ); 
        free( current_node );

        current_node = next;
    }
}

bool dll_move_to( DlList_T lst, int index ) {
    if( index >= lst->size || index < 0 )
        return 0;

    // Reset cursor to beginning
    lst->cursor = lst->first;
    for( int i = 0; i < index; i++ ) {
        // Move cursor to index
        dll_next( lst );
    }
    return 1;
}

int dll_has_next( DlList_T lst ) {
    return lst->cursor != NULL;
}

void *dll_next( DlList_T lst ) {
    void *data = lst->cursor->data;
    lst->cursor = lst->cursor->next;
    return data;
}

void *dll_prev( DlList_T lst ) {
    void *data = lst->cursor->data;
    lst->cursor = lst->cursor->prev;
    return data;
}

int dll_size( DlList_T lst ) {
    return lst->size;
}

void dll_append( DlList_T lst, void *data ) {
    lst->size++;
    
    DlList_Node **current = &(lst->first);
    DlList_Node *prev = NULL;

    while( *current != NULL ) {
        prev = (*current);
        current = &((*current)->next);
    }

    *current = dll_node_create( data, prev, NULL );
    lst->cursor = (*current);
}

void dll_print_node( DlList_Node *node ) {
    printf( "Node: %s\n", (char *)node->data );

}

void dll_print_node_children( DlList_Node *node ) {
    if( node->prev != NULL ) {
        printf("\t\t");
        dll_print_node( node->prev );
    }
    else {
        printf("\t\tNULL\n");
    }

    if( node->next != NULL ) {
        printf("\t\t");
        dll_print_node( node->next );
    }
    else {
        printf("\t\tNULL\n");
    }
}

void dll_insert_at( DlList_T lst, int indx, void *data ) {
    if( indx >= dll_size( lst ) )
        return;
    lst->size++;
    
    DlList_Node **current = &(lst->first);
    DlList_Node *prev = NULL;

    for( int i = 0; i < indx && *current != NULL; i++ ) {
        prev = (*current);
        current = &((*current)->next);
    }

    DlList_Node *old = *current;

    *current = dll_node_create( data, prev, *current );

    old->prev = *current;

    lst->cursor = (*current);
}

void *dll_get( DlList_T lst, int indx ) {
    DlList_Node *current = lst->first;

    for( int i = 0; i < indx - 1 && current != NULL; i++, current = current->next );

    if( current ) {
        return current->data;
    }
    return NULL;
}

void *dll_set( DlList_T lst, int indx, void *data ) {
    DlList_Node *current = lst->first;

    for( int i = 0; i < indx && current != NULL; i++, current = current->next );

    if( current ) {
        void *old = current->data;
        current->data = data;
        return old;
    }
    return NULL;
}

void *dll_pop( DlList_T lst, int indx ) {
    DlList_Node *current = lst->first;

    for( int i = 0; i < indx && current != NULL; i++, current = current->next );

    dll_print_node( current );

    if( current ) {
        void *data = current->data;

        if( current->prev )
            current->prev->next = current->next;
        if( current->next )
            current->next->prev = current->prev;

        if( lst->cursor == current ) {
            lst->cursor = ((current->next != NULL)?(current->next):
                          ((current->prev != NULL)?(current->prev):
                          NULL));
        }

        if( lst->first == current ) {
            lst->first = current->next;
        }

        free( current );

        lst->size--;

        return data;
    }
    return NULL;
}

int dll_index( DlList_T lst, void *data ) {
    DlList_Node *current = lst->first;
    int counter;
    while( current != NULL ) {
        if( current->data == data )
            return counter;
        counter++;

        current = current->next;
    }
    return -1;
}

bool dll_empty( DlList_T lst ) {
    return lst->first == NULL;
}

// Remove these before submit

void dll( DlList_T lst ) {
    DlList_Node *current = lst->first;

    printf("Node structure:\n");
    while( current != NULL ) {
        printf("\t");
        dll_print_node( current );

        dll_print_node_children( current );

        current = current->next;
    }

    printf("Cursor: ");
    if( lst->cursor ) {
        dll_print_node( lst->cursor );
    } else {
        printf("NULL\n");
    }
}