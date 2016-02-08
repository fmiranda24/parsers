// strchk.c: checks the beginning of the buffer for the existence of a particular word
// written by: Martijn Geers
// date: 06-02-2016

#include <stdio.h>
#include <string.h>

int strchk( int size, const char buf[1024], const char *word ) {

	char a[size];								// declare a string with the same size as word
	int i = 1;									// counter
	int indent;									// parameter to store the number of spaces before BOL

	while ( buf[i-1] == ' ') {					// check the number of spaces before BOL
		i++;
	}

	indent = i;									// store number of spaces before BOL

 	for(i = 0; i < size-1; i++) {
		a[i] = buf[i + indent -1];				// fill the new string with the first characters of the buffer, the same length as the search word
	}
	a[size-1] = '\0';							// end the string with NULL terminator

	if( strcmp(a,word) == 0 ) return indent;	// compare the string with the search word, return the indent if they are the same
	else return 0;								// return 0 if word is not the same
}
