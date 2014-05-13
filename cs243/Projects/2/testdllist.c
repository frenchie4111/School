/**
 * File: <<TEMPLATE MARK>>
 * <<TEMPLATE MARK>>
 * @author mdl7240 : Mike Lyons
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dlList.h"
#include "dlList-extra.h"

// Assumes all data is char *
void dll_print( DlList_T test ) {
    printf("dll fowards:\n");
    dll_first( test );
    void *cur;
    while( (cur = dll_next( test ) ) != NULL ) {
        printf( "\t%s\n", (char *)cur );
    }
}

void dll_backwards( DlList_T test ) {
    printf("dll backwards:\n");
    dll_last( test );
    void *cur;
    while( (cur = dll_prev( test ) ) != NULL ) {
        printf( "\t%s\n", (char *)cur );
    }
}

DlList_T test;

void testInsertAndDelete() {
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

    printf("Injecting at 2\n");
    char *inj2 = (char *)malloc( sizeof( char ) * 6 );
    strcpy( inj2, "inje2" );
    dll_insert_at( test, 0, inj2 );
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

    printf("Testing Pop 2: ");
    void *popped = dll_pop( test, 2 );
    printf( "popp %s\n", (char *) ((popped)?popped:"NULL") );
    dll_print( test );
    dll_backwards( test );

    printf("index 'test2' = %d\n", dll_index( test, str2 ) );

    printf("dllempty %d\n", dll_empty( test ));
}

void testCursor() {
    dll_print( test );

    dll_next( test );
    printf( "%s\n", (char *)dll_current( test ) );
    dll_prev( test );
    printf( "%s\n", (char *)dll_current( test ) );

    while( dll_next(test) );
    printf( "last %s\n", (char *)dll_current( test ) );

    while( dll_prev(test) );
    printf( "first %s\n", (char *)dll_current( test ) );

    dll_move_to( test, 1 );
    printf( "index 1 %s\n", (char *)dll_current( test ) );    
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
    test = dll_create();

    testInsertAndDelete();
    testCursor();

    dll_destroy( test );
}

// $Log: $ 
// commit f6a06bb03cf1a4ec0a799f56396cbe1621263ae3
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Fri Apr 18 19:30:03 2014 -0400
// 
//     Added comments
// 
// commit 6097520aa427064a9c2fb9b6ab46d2a2e45b8cbc
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Wed Apr 16 22:56:21 2014 -0400
// 
//     Trying to match output with try
// 
// commit 582e0c65b60e06b271c974fe094ae5537f6e9e0b
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Wed Apr 16 20:53:32 2014 -0400
// 
//     Code complete. Working with valgrind
// 
// commit 6b8365017b2e8e0560808e84cbd07e1982011557
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Fri Apr 11 18:31:28 2014 -0400
// 
//     dlList done. Started mrEd
// 
// commit 9bc47e7e8e68609d8cb5b17200da6e9488f86e11
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Thu Apr 3 10:49:51 2014 -0400
// 
//     Updated makefile, added template code to testdllis
// 
// commit 15f77a29d0ef65a98ebd52366ebc6c5ab0003171
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Tue Apr 1 11:56:22 2014 -0400
// 
//     Initial Commit of mrEd
// 


