Creator: Mike Lyons (mdl7240@rit.edu)

Design:
	When a command is entered, it is tokenized into a doubl-linked-list of 
	tokens. This is then converted to the appropriate sized array, and used
	for the remainder of the program. The first item in this array of tokens
	is the command name, this is used to determine if the command is internal
	or not. There is an array containing function pointers to all internal 
	commands. The programs loops through to see if the command matches any of
	these internal commands, if it does it runs that command. Otherwise it forks
	and runs the commadn using execvp. It waits for the child fork to be finished
	and reports it's error code if it is not 0.

Known Issues:
	cd commands do not seem to work
