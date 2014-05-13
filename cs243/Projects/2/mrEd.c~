/**
 * File: <<TEMPLATE MARK>>
 * <<TEMPLATE MARK>>
 * @author mdl7240 : Mike Lyons
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include "dlList.h"
#include "dlList-extra.h"

#define MAX_LINE (80)

char *getLine( FILE *f );

int isRunning = 1;
int changed = 0;
char fileName[MAX_LINE] = "";

/**
 * Quits the running program if not recently changed. Otherwise
 * prints "? buffer dirty."
 * @param fileList Only here so that it matches the proper signature
 */
void quit( DlList_T fileList ) {
    if( !changed ) {
        isRunning = 0;
    } else {
        printf("? buffer dirty.\n");
    }
}

/**
 * Prints the line at the cursor position
 * @param DlList_T list/cursor to print
 */
void printLine( DlList_T fileList ) {
    if( dll_current( fileList ) ) {
        printf("%s\n", (char *)dll_current( fileList ));
    } else {
        printf("?\n");
    }
}

/**
 * mrEd next. Moves the editing cursor to next line
 * @param fileList fileList the fileList that the editor is currently
 *                 working on
 */
void next( DlList_T fileList ) {
    void *data = dll_next( fileList );
    if( data ) {
        printf("%s\n", (char *)dll_current( fileList ));
    } else {
        printf("?\n");
    }
}

/**
 * mrEd prev. Moves the editing cursor to previous line
 * @param fileList fileList the fileList that the editor is currently
 *                 working on
 */
void prev( DlList_T fileList ) {
    void *data = dll_prev( fileList );
    if( data ) {
        printf("%s\n", (char *)dll_current( fileList ));
    } else {
        printf("?\n");
    }
}

/**
 * mrEd last. Moves the editing cursor to last line
 * @param fileList fileList the fileList that the editor is currently
 *                 working on
 */
void last( DlList_T fileList ) {
    dll_move_to( fileList, dll_size( fileList ) - 1 );
    printLine( fileList );
}

/**
 * mrEd jump_to. Moves the editing cursor to the specified line
 * @param fileList fileList the fileList that the editor is currently
 *                 working on
 */
void jump_to( DlList_T fileList, int line ) {
    if( line - 1 < dll_size( fileList ) && line - 1 > -1 ) {
        dll_move_to( fileList, line - 1 );
        printLine( fileList );
    } else {
        printf("?\n");
    }
}

/**
 * mrEd delete. Deletes the current line
 * @param fileList fileList the fileList that the editor is currently
 *                 working on
 */
void delete( DlList_T fileList ) {
    changed = 1;
    free( dll_pop_cursor( fileList ) );
}

/**
 * mrEd isnert. Inserts before the cursor
 * @param fileList fileList the fileList that the editor is currently
 *                 working on
 */
void insert( DlList_T fileList ) {
    changed = 1;
    int current = dll_get_cursor_index( fileList );
    do {
        char *line = getLine( stdin );

        if( !strcmp( line, "." ) )
        {
            free( line );
            break;
        }
        dll_insert_at( fileList, current, line );
        current++;
    } while( !feof( stdin ) );
}

/**
 * mrEd insertAfter. Inserts after the cursor
 * @param fileList fileList the fileList that the editor is currently
 *                 working on
 */
void insertAfter( DlList_T fileList ) {
    changed = 1;
    int current = dll_get_cursor_index( fileList );
    if( dll_size( fileList ) > 0 )
	current++;
    do {
        char *line = getLine( stdin );

        if( !strcmp( line, "." ) )
            break;

        dll_insert_at( fileList, current, line );
        current++;
    } while( !feof( stdin ) );
}

/**
 * mrEd currLineNum. Prints the current line number
 * @param fileList fileList the fileList that the editor is currently
 *                 working on
 */
void currLineNum( DlList_T fileList ) {
    if( dll_size( fileList ) == 0 ) {
        printf("0\n");
    } else {
        printf("%d\n", dll_get_cursor_index( fileList ) + 1 );
    }
}

/**
 * mrEd size. Prints the total size
 * @param fileList fileList the fileList that the editor is currently
 *                 working on
 */
void size( DlList_T fileList ) {
    if( dll_size( fileList ) == 0 ) {
        printf("?\n");
    } else {
        printf("%d\n", dll_get_cursor_index( fileList ) + 1 );
    }
}

/**
 * mrEd printAll. Prints the total size
 * @param fileList fileList the fileList that the editor is currently
 *                 working on
 */
void printAll( DlList_T fileList ) {
    if( dll_empty( fileList ) ) {
        printf("?\n");
    } else {
        dll_first( fileList );
        void *data;
        while( (data = dll_next( fileList )) != NULL ) {
            printf("%s\n", (char *)data);
        }
        printLine( fileList );
        dll_last( fileList );
    }
}

/**
 * Quits the running program even if recently changed. 
 * @param fileList Only here so that it matches the proper signature
 */
void forceQuit( DlList_T fileList ) {
    isRunning = 0;
}

/**
 * Get's line from the given stream
 * @param  f File holder
 * @return   Returns a line of text stored on heap. Is not responsible for the 
 *                   new line
 */
char *getLine( FILE *f ) {
        char *line = calloc( sizeof( char ), MAX_LINE + 1);
	int c = ' ';
	int curr = 0;
	for( int i = 0; 
        i < MAX_LINE && (( c = getc(f) ) != '\n') && c != '\0' && c != EOF; 
        i++, line[curr++] = c );

	return line;
}

// will be 14
#define NUM_COMMANDS (12)
void (*commandFunctions[NUM_COMMANDS])(DlList_T fileList) = 
    { quit, printLine, next, prev, last, delete, insert, 
      currLineNum, size, printAll, forceQuit, insertAfter };

char *commands[NUM_COMMANDS] = 
    { "q", ".", "+", "-", "$", "d", "i", 
      ".=", "$=", "p", "Q", "a" };

/**
 * Reads a file and returns a DlList_T containing the file
 * If file is failed to open returns NULL instead
 * @param  filename The name of the file to open
 * @return          The DlList_T that represents the file contents
 */
DlList_T readFile( const char *filename ) {
    DlList_T fileList = dll_create();

    FILE *f = fopen( filename, "r+" );

    if( !f ) {
        perror("open failed");
	    fprintf( stderr, "could not read file '%s'\n", filename );
    	return NULL;
    }

    do {
	    char *line = getLine( f );
	    dll_append( fileList, line );
    } while( !feof( f ) );

    fclose( f );

    memcpy( fileName, filename, strlen( filename ) );
    return fileList;
}

/**
 * Main function
 * Opens the given filename (First argument)
 *
 * Enters run loop, accepting commands to modify/print
 *     file contents
 *
 * Saves file when write command given
 *
 * @param argc the number of arguments
 * @param argv array of arguments
 * @returns int the error code; 0 if no error
 */
int main( int argc, const char* argv[] ) {
    DlList_T fileList;

    if( argc > 1 ) { // File name specified
        fileList = readFile( argv[1] );

        if( !fileList ) { // Read File failed, probably unreadable
            fileList = dll_create();
        } 
    }
    else { // No filename specified
        printf("no file supplied.\n");
        fileList = dll_create();
    }

    while( isRunning ) { // Enter command loops
        char *line = getLine( stdin );
        int ranCommand = 0;
        // printf("Responding to command '%s': ", line);
        for( int i = 0; i < NUM_COMMANDS; i++ ) { // Check if command is basic
            if( !strcmp( line, commands[i] ) ) {
                commandFunctions[i]( fileList );
                ranCommand = 1;
                break;
            }
        }
        if( !ranCommand ) { // If not check if it is the jump_to command (A number)
            int value;
            if( sscanf( line, "%d", &value ) == 1 ) {
                jump_to( fileList, value );
                ranCommand = 1;
            }
        }
        if( !ranCommand ) { // If not check if it is the write command
            if( line[0] == 'w' ) {
                int spaces = 2;
                if( line[1] == 'q' ) { // Check for q (Write & Quit)
                    spaces = 3;
                    isRunning = 0;
                }

                char newFileName[ MAX_LINE ]; // Get the filename
                memset(newFileName, 0, sizeof(char) * MAX_LINE);
                memcpy( newFileName, &line[spaces], strlen( line ) );
                newFileName[ strlen( line ) - spaces ] = '\0';

                if( strlen( newFileName ) == 0 ) { // Use old filename
                    memcpy( newFileName, fileName, strlen( fileName ) );
                } else {
                    memcpy( fileName, newFileName, strlen( newFileName ) );
                }

                FILE *fp = fopen( newFileName, "w" );

                if( !fp ) { // Open failed for writing, oopsie
                    perror("open failed");
	                fprintf( stderr, "could not read file '%s'\n", newFileName );
                    continue;
                }
                dll_first( fileList );
                void *data;
                while( (data = dll_next( fileList )) != NULL ) { // Write file
                    fprintf(fp, "%s\n", (char *)data);
                }
                fprintf(fp, "%s\n", (char *)dll_current( fileList ));
                dll_last( fileList );

                fclose( fp );

                printf("filename: '%s'\n", newFileName);
                ranCommand = 1;
                changed = 0;
            }
        }
        if( !ranCommand ) { // Command not found
            printf("?\n");
        }
        free( line );
    }

    printf("\nBye\n");
    dll_destroy( fileList );
}


// $Log: $ 
// commit f6a06bb03cf1a4ec0a799f56396cbe1621263ae3
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Fri Apr 18 19:30:03 2014 -0400
// 
//     Added comments
// 
// commit 4a72678e88adb1a9f2f7f68943d8f1680a846d77
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Fri Apr 18 19:04:48 2014 -0400
// 
//     Almost matches try output. Still having error on 13
// 
// commit 6097520aa427064a9c2fb9b6ab46d2a2e45b8cbc
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Wed Apr 16 22:56:21 2014 -0400
// 
//     Trying to match output with try
// 
// commit 4adc3bafb611d97c3e62a67e2d5068a6c6c31edb
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Wed Apr 16 21:21:53 2014 -0400
// 
//     Removed getline, it was causing valgrind leaks
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
// commit c33e63b78db935584771561b8dabafcd710e574e
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Tue Apr 1 12:01:46 2014 -0400
// 
//     Added .gitignore and Makefile (generated with gmakemake)
// 
// commit 15f77a29d0ef65a98ebd52366ebc6c5ab0003171
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Tue Apr 1 11:56:22 2014 -0400
// 
//     Initial Commit of mrEd
// 

