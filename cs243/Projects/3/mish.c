/**
 * File: <<TEMPLATE MARK>>
 * <<TEMPLATE MARK>>
 * @author mdl7240 : Mike Lyons
 */
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "dll_mike.h"

#define MAX_ARG (80)

int is_running = 1;
int verbose = 1;
int command_count = 1;
dll history;

void fork_external_command( int argc, char *argv[] )
{
	int pid = fork();

	if( pid == 0 ) {
		if( verbose )
			printf("\texecvp: %s\n", argv[0]);
		execvp( argv[0], argv );

		fprintf(stderr, "%s: No such file or directory\n", argv[0]);
		exit( EXIT_FAILURE );
	} else {
		int status;

		if( verbose )
			printf("\twait for pid %d: %s\n", pid, argv[0]);
		waitpid( pid, &status, 0 );

		if( status != 0 )
			fprintf(stderr,  "command status: %d\n", status );
	}
}

void token_add_to_dll( dll tokens, char *token ) {
	char *tokenCpy = (char *)malloc( strlen( token ) * sizeof( char ) );
	strcpy( tokenCpy, token );
	dll_push( tokens, tokenCpy );
}

dll tokenize_input( char *input )
{
	dll tokens = dll_create();

	int i = 0, curr = 0, in_token = 0, in_quote = 0;
	int c = 0;
	char token[MAX_ARG];
	for( c = input[i]; c != EOF && c != '\0' && c != '\n'; c = input[++i] ) {
		if( c == ' ' ) { // End of token
			if( in_token && !in_quote ) {
				token[curr] = '\0';
				token_add_to_dll( tokens, token );
				
				curr = 0;
				in_token = 0;
				token[0] = '\0';
			} else if( in_quote ) {
				token[curr++] = c;
			}
		} else if( c == '"' ) {
			if( in_quote ) {
				token[curr] = '\0';
				token_add_to_dll( tokens, token );

				curr = 0;
				in_token = 0;
				token[0] = '\0';
			} else {
				in_quote = 1;
			}
		} else {
			token[curr++] = c;
			in_token = 1;
		}
	}
	if( in_token ) {
		token[curr] = '\0';
		token_add_to_dll( tokens, token );
	}
	return tokens;
}

void mish_verbose( int argc, char *argv[] ) {
	if( argc > 1 ) {
		if( !strcmp( argv[1], "on" ) ) {
			verbose = 1;
		} else if( !strcmp( argv[1], "off" ) ) {
			verbose = 0;
		} else {
			fprintf(stderr, "usage: verbose [on|off]\n");
		}
	} else {
		fprintf(stderr, "usage: verbose [on|off]\n");
	}
}

void mish_help( int argc, char *argv[] ) {
	printf("Internal Commands:\n");
	printf("\tVerbose: verbose [on|off] sets verbose mode\n");
	printf("\thelp: shows this help dialog\n");
	printf("\thistory: shows command history\n");
	printf("\tquit: quits mish terminal\n");
}

void mish_history( int argc, char *argv[] ) {
	dll_curs_reset( history );
	int i = 1;
	while( dll_curs_has_next( history ) ) {
		printf("%d: %s\n", i++, dll_curs_next( history ) );
	}
}

void mish_quit( int argc, char *argv[] ) {
	is_running = 0;
}

#define INTERNAL_COMMANDS (4)
void (*internal_commands[INTERNAL_COMMANDS])( int argc, char *argv[] ) = 
    { mish_verbose, mish_help, mish_history, mish_quit };

char *commands[INTERNAL_COMMANDS] = 
    { "verbose", "help", "history", "quit" };

/**
 * Main function
 *
 * @param argc the number of arguments
 * @param argv array of arguments
 * @returns int the error code; 0 if no error
 */
int main( int argc, const char* argv[] ) {
	size_t len = 10;
	char *line = (char *)malloc( sizeof( char ) * len );
	history = dll_create();

	while( is_running ) {
		printf("mish[%d]> ", command_count);
		len = getline( &line, &len, stdin );
		if( feof( stdin ) )
			break;

		char *new_history_item = (char *)malloc( strlen( line ) );
		strcpy( new_history_item, line );
		new_history_item[ strlen( new_history_item ) - 1 ] = '\0';
		dll_push( history, new_history_item );

		if( verbose )
			printf("\tcommand: %s\n\n", line);

		dll tokens = tokenize_input( line );

		int new_argc = dll_count( tokens );
		if( new_argc > 0 ) {
			if( verbose )
				printf("\tinput command tokens:\n");
			char *new_args[ dll_count( tokens ) + 1 ];
			dll_curs_reset( tokens );
			int i = 0;
			while( dll_curs_has_next( tokens ) ) {
				char *token = dll_curs_next( tokens );

				if( verbose )
					printf("\t%d: %s\n", i, token );

				new_args[i++] = token;
			}
			new_args[i] = NULL;

			int command_run = 0;
			for( int i = 0; i < INTERNAL_COMMANDS; i++ ) {
				if( !strcmp( new_args[0], commands[i] ) ) {
					if( verbose )
						printf("\tinternal command: %s\n", new_args[0]);
					internal_commands[i]( new_argc, new_args );
					command_run = 1;
					break;
				}
			}
			if( !command_run ) {
				fork_external_command( new_argc, new_args );
				command_run = 1;
			}

			if( command_run )
				command_count++;
		}

		dll_destroy( tokens );
	}
	free( line );
	dll_destroy(history);
}
