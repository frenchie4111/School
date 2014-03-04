/**
 * File: bannerize.c 
 * bannerize.c creates a banner from input
 * @author mdl7240 : Mike Lyons
 */
#include <stdio.h>
#include <string.h>

/**
 * Takes the border char and the arguments list and prints the proper
 * size border based on the length of the strings in argv
 * @author mdl7240 : Mike Lyons
 *
 * @param argc - the arguments counter from main
 * @param argv - the arguments array from main
 * @param borderChar : char - the character to print for the border
 */
void printBorder( int argc, const char* argv[], char borderChar ) {
	putchar(borderChar);
	for( int i = 1; i < argc; i++ ) {
		putchar(borderChar);
		for( int j = 0; j < strlen( argv[i] ); j++  ) {
			putchar( borderChar );
		}
	}
	printf("%c%c\n", borderChar, borderChar);
}

/**
 * Main function. Takes user input and outputs the borderized text
 *
 * @param argc the number of arguments
 * @param argv array of arguments
 * @returns int the error code; 0 if no error
 */
int main( int argc, const char* argv[] ) {
	if( argc > 1 ) {
		printf("Enter the character for the border:");
		int borderChar = getchar();
		if( borderChar == EOF ) {
			putchar( '\n' );
			return 0;
		}
		printf("\n");
		printBorder( argc, argv, borderChar );	
		printf("%c ", borderChar);
		for( int i = 1; i < argc; i++ ) {
			printf("%s ", argv[i] );
		}
		printf("%c\n", borderChar );
		printBorder( argc, argv, borderChar );
	} else {
		printf("usage: bannerize arguments are the text to bannerize.\n");
	}
}
