/**
 * File: <<TEMPLATE MARK>>
 * <<TEMPLATE MARK>>
 * @author mdl7240 : Mike Lyons
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dlList.h"

// Assumes all data is char *
void dll_print( DlList_T test ) {
    printf("dll fowards:\n");
    dll_move_to( test, 0 );
    while( dll_has_next( test ) ) {
        printf( "\t%s\n", (char *)dll_next( test ) );
    }
}

void dll_backwards( DlList_T test ) {
    printf("dll backwards:\n");
    dll_move_to( test, dll_size( test ) -1  );
    while( dll_has_next( test ) ) {
        printf( "\t%s\n", (char *)dll_prev( test ) );
    }
}

/**
 * Main function
 *
 * (a) Tests insert and delete operations.
 * (b) Tests move forward beyond last element.
 * (c) Tests move back beyond ﬁrst element.
 * (d) Tests cursor absolute and relative positioning.
 * (e) Tests cursor state
 * 
 * @param argc the number of arguments
 * @param argv array of arguments
 * @returns int the error code; 0 if no error
 */
int main( int argc, const char* argv[] ) {
    DlList_T test = dll_create();

    printf("Adding test1\n");
    char *str = (char *)malloc( sizeof( char ) * 6 );
    strcpy( str, "test1" );
    dll_append( test, str );

    printf("Adding test2\n");
    char *str2 = (char *)malloc( sizeof( char ) * 6 );
    strcpy( str2, "test2" );
    dll_append( test, str2 );

    printf("Adding test3\n");
    char *str3 = (char *)malloc( sizeof( char ) * 6 );
    strcpy( str3, "test3" );
    dll_append( test, str3 );

    dll_print( test );

    printf("Injecting at 2\n");
    char *inj = (char *)malloc( sizeof( char ) * 6 );
    strcpy( inj, "injec" );

    dll_insert_at( test, 2, inj );
    dll_backwards( test );

    printf("Testing get 2: ");
    char *ret = (char *)dll_get( test, 2 );
    printf( "%s\n", (ret)?ret:"NULL" );

    printf("Testing get 5: ");
    char *ret2 = (char *)dll_get( test, 5 );
    printf( "%s\n", (ret2)?ret2:"NULL" );

    printf("Testing set 2, 'set2'\n");
    char *setstr = (char *)malloc( sizeof( char ) * 6 );
    strcpy( setstr, "set2" );
    free( dll_set( test, 2, setstr ) );
    dll_print( test );
    dll(test);

    dll( test );
    printf("Testing Pop 2: ");
    void *popped = dll_pop( test, 2 );
    printf( "popp %s\n", (char *) ((popped)?popped:"NULL") );
    dll( test );
    dll_print( test );
    dll_backwards( test );

    printf("index 'test2' = %d\n", dll_index( test, str2 ) );

    printf("dllempty %d\n", dll_empty( test ));

    dll_destroy( test );
}
