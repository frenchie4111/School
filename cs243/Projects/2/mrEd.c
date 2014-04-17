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

#include "dlList.h"
#include "dlList-extra.h"

#define MAX_LINE (80)

char *getLine( FILE *f );

int isRunning = 1;
int changed = 0;
char fileName[MAX_LINE] = "";

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

void next( DlList_T fileList ) {
    void *data = dll_next( fileList );
    if( data ) {
        printf("%s\n", (char *)dll_current( fileList ));
    } else {
        printf("?\n");
    }
}

void prev( DlList_T fileList ) {
    void *data = dll_prev( fileList );
    if( data ) {
        printf("%s\n", (char *)dll_current( fileList ));
    } else {
        printf("?\n");
    }
}

void last( DlList_T fileList ) {
    dll_move_to( fileList, dll_size( fileList ) - 1 );
    printLine( fileList );
}

void jump_to( DlList_T fileList, int line ) {
    if( line - 1 < dll_size( fileList ) && line - 1 > -1 ) {
        dll_move_to( fileList, line - 1 );
        printLine( fileList );
    } else {
        printf("?\n");
    }
}

void delete( DlList_T fileList ) {
    changed = 1;
    free( dll_pop_cursor( fileList ) );
}

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

void currLineNum( DlList_T fileList ) {
    printf("%d\n", dll_get_cursor_index( fileList ) + 1 );
}

void size( DlList_T fileList ) {
    printf("%d\n", dll_size( fileList ));
}

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

void forceQuit( DlList_T fileList ) {
    isRunning = 0;
}

char *getLine( FILE *f ) {
        char *line = calloc( sizeof( char ), MAX_LINE + 1);
	int c = ' ';
	int curr = 0;
	for( int i = 0; i < MAX_LINE && (( c = getc(f) ) != '\n') && c != '\0' && c != EOF; i++, line[curr++] = c );

	return line;
}

// will be 14
#define NUM_COMMANDS (12)
void (*commandFunctions[NUM_COMMANDS])(DlList_T fileList) = { quit, printLine, next, prev, last, delete, insert, currLineNum, size, printAll, forceQuit, insertAfter };
char *commands[NUM_COMMANDS] = { "q", ".", "+", "-", "$", "d", "i", ".=", "$=", "p", "Q", "a" };

DlList_T readFile( const char *filename ) {
    DlList_T fileList = dll_create();

    FILE *f = fopen( filename, "r" );

    if( !f ) {
	    fprintf( stderr, "could not read file '%s'", filename );
    	return NULL;
    }

    do {
	char *line = getLine( f );
	dll_append( fileList, line );
    } while( !feof( f ) );

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
    DlList_T fileList;

    if( argc > 1 ) {
        DlList_T fileList = readFile( argv[1] );
	if( !fileList )
            return 0;
    } else {
        printf("no file supplied.\n");
        fileList = dll_create();
    }

    while( isRunning ) {
        char *line = getLine( stdin );
        int ranCommand = 0;
        for( int i = 0; i < NUM_COMMANDS; i++ ) {
            if( !strcmp( line, commands[i] ) ) {
                commandFunctions[i]( fileList );
                ranCommand = 1;
                break;
            }
        }
        if( !ranCommand ) {
            int value;
            if( sscanf( line, "%d", &value ) == 1 ) {
                jump_to( fileList, value );
                ranCommand = 1;
            }
        }
        if( !ranCommand ) {
            if( line[0] == 'w' ) {
                int spaces = 2;
                if( line[1] == 'q' ) {
                    spaces = 3;
                    isRunning = 0;
                }

                char newFileName[MAX_LINE];
                memcpy( newFileName, &line[spaces], strlen( line ) );
                newFileName[ strlen( line ) - spaces ] = '\0';

                if( strlen( newFileName ) == 0 ) {
                    if( strlen( fileName ) > 0 ) {
                        memcpy( newFileName, fileName, strlen( fileName ) );
                    } else {
                        printf("?\n");
                        continue;
                    }
                } else {
                    memcpy( fileName, newFileName, strlen( newFileName ) );
                }

                FILE *fp = fopen( newFileName, "w" );

                if( !fp ) {
                    perror("open failed: ");
                }
                dll_first( fileList );
                void *data;
                while( (data = dll_next( fileList )) != NULL ) {
                    fprintf(fp, "%s\n", (char *)data);
                }
                fprintf(fp, "%s", (char *)dll_current( fileList ));
                dll_last( fileList );

                fclose( fp );

                printf("filename: '%s'\n", newFileName);
                ranCommand = 1;
                changed = 0;
            }
        }
        if( !ranCommand ) {
            printf("?\n");
        }
        free( line );
    }

    printf("\nBye\n");
    dll_destroy( fileList );
}
