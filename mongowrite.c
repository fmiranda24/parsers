// mongowrite.c: streamlines the checking and writing process
// written by: Martijn Geers
// date: 06-02-20

#include <stdio.h>
#include <string.h>
#include "strchk.h"
#include "getdata.h"
#include "sizechk.h"

int mongowrite( const char* wordlist[], const char* buf, int entry, int check) {

	int wordlength;										// int to hold the length of the word
	int i;												// counter
	int indent;

	wordlength = sizechk(wordlist, entry) + 2;			// calculate the wordlength, add room for 2 characters: | at BOL and = at EOL

	char chkword[wordlength+1];							// declare the word to check against
	char prntword[wordlength-1];						// declare the word to print to output

	chkword[0] = 124;									// the first character to look for is |

	for(i = 1; i < wordlength+2; i++) {					// fill in both strings
		chkword[i] = wordlist[entry][i-1];				// the checkword should look like "|checkword"
		prntword[i-1] = wordlist[entry][i-1];			// the printword should look like "checkword"
	}

	chkword[wordlength-1] = 61;							// the last character to look for is =

	if(indent = strchk(wordlength+1,buf,chkword)) {				// check if the buffer contains the checkword at BOL
		if(check) {										// if there was a line before this one in the same document...
			fputs(",\n",stdout);						// ...end last line with a ,
		}
		fputs("    ",stdout);							// add spacing before printing the printword
		fputs(prntword, stdout);						// print the printword
		fputs(": \"",stdout);							// add a : followed by a space followed by "
		getdata(buf,chkword,wordlength+indent-1);		// use getdata to write the data into the newly created mongofield, accounting for the indenting in the source
		check = 1;										// indicate that a line has been written
	}
	return check;										// return the linewrite indicator

}
