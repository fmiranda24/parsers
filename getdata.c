// getdata.c: takes the data from the XML document and outputs it to console
// written by: Martijn Geers
// date: 06-02-2016

#include <stdio.h>
#include <string.h>

void getdata( const char *buf, char *word, int size) {

	int i;																// counter
	int done = 0;														// integer that helps get rid of comments within data strings

	char eol[] = "\n";													// initialize end of line character
	char eolch[] = "\n";												// define end of line checking character

	char cln[1024-size];												// declare a string, the size is the buffer remainder after taking out the initially detected word

	for(i = 0; i < sizeof(cln)-1; i++) {								// preallocate the entire string with NULL terminators
		cln[i] = '\0';
	}

	for(i = 0; i < sizeof(cln); i++){

		if(buf[size] == 38 && buf[size+1] == 108 && buf[size+2] == 116 && done == 0) { 				// check for &lt
			 if ((buf[size + i] == 38 && buf[size + i + 1] == 103 && buf[size + i + 2] == 116)) {	// check for &gt
				 done  = 1;																			// the text encapsulated by < and > will be skipped after this is set to 1
				 size += i + 5;																		// size parameter adjusted to skip past the text encapsulated by < and >
				 i = -1;																			// repeat the last step at the end of this loop iteration, now with done set to 1
			 }
		}
		else {															// when no &lt is found at BOL, proceed as normally

			if(buf[i+size] == 91 || buf[i+size] == 123) size +=2;		// if the current char is either a { or a [ then skip 2

			cln[i] = buf[i+size];										// copy the current char from buffer to the output line

			eolch[0] = buf[i+size];										// check if the current char is a linebreak

			if(strcmp(eolch,eol) == 0 || buf[i+size] == 93) { 			// check whether EOL or ] is detected
				cln[i] = 34;											// add quotes after data
				break;													// quit the for-loop, all data was extracted
			}
		}
	}

	fputs(cln, stdout);													// output the data to the console

}
