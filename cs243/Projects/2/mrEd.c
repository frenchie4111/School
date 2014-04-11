/**
 * File: <<TEMPLATE MARK>>
 * <<TEMPLATE MARK>>
 * @author mdl7240 : Mike Lyons
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dlList.h"

 #define MAX_LINE (80)

int isRunning = 1;

/**
 * Prints the line at the cursor position
 * @param DlList_T list/cursor to print
 */
void printLine( DlList_T fileList ) {
    printf("%s", (char *)dll_next( fileList ));
    dll_prev( fileList );
}

// will be 14
void (*func_ptr[1])(DlList_T fileList) = { printLine };
char *functionNames = { "." };

DlList_T readFile( const char *filename ) {
    DlList_T fileList = dll_create();
    size_t size = MAX_LINE;
    ssize_t read;

    FILE *f = fopen( filename, "r" );

    do {
        char *line = malloc( sizeof( char ) * MAX_LINE );
        read = getline( &line, &size, f );
        if( read != -1 )
        {
            dll_append( fileList, line );
        }
    } while( read != -1 );

    fclose( f );
    return fileList;
}

/**
 * Main function
 *
 * @param argc the number of arguments
 * @param argv array of arguments
 * @returns int the error code; 0 if no error
 */
int main( int argc, const char* argv[] ) {
    if( argc > 1 ) {
        printf("File %s\n", argv[1]);
        DlList_T fileList = readFile( argv[1] );

        while( isRunning ) {
            
        }

        dll_destroy( fileList );
    }
}
