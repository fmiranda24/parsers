// sizechk.c: checks the size of the word
// written by: Martijn Geers
// date: 06-02-20

#include <stdio.h>
#include <string.h>

int sizechk( const char* wordlist[], int entry ) {

	int i;							// counter

	char c = '\0';					// initialize the checking character
	char ch = '\0';					// declare the character to look out for

	for(i = 0; i < 100; i++) {		// assuming no word will be longer than 100 characters, cycle through a 100
		c = wordlist[entry][i]; 	// copy the character from the wordlist
		if(c == 0) break;			// check if it's a NULL terminator, if so, end the loop
	}

	return i;						// return the number of cycles from the loop, this is the wordlength
}
