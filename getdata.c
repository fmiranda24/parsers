// getdata.c: takes the data from the XML document and outputs it to console
// written by: Martijn Geers
// date: 06-02-2016

#include <stdio.h>
#include <string.h>

void getdata( const char *buf, char *word, int size) {

	int i;																			// counter
	int lt_det = 0;																	// integer that helps get rid of comments within data strings
	int lt_pos;
	char eol[] = "\n";																// initialize end of line character
	char eolch[] = "\n";															// define end of line checking character

	char cln[1024-size];															// declare a string, the size is the buffer remainder after taking out the initially detected word

	for(i = 0; i < sizeof(cln)-1; i++) {											// preallocate the entire string with NULL terminators
		cln[i] = '\0';
	}

	for(i = 0; i < sizeof(cln); i++){												// cycle through all characters in cln

		if(buf[size+i] == 38 && buf[size+i+1] == 108 && buf[size+i+2] == 116 && lt_det == 0) {
			if (i != 0) {															// only add | or space if not at start of data
				if (buf[size+i+4] != 98 && buf[size+i+5] != 114) cln[i] = '|';		// output a | to seperate if no break is found (98 = b and 114 = r)
				else cln[i] = ' ';													// if <br> detected, add a space
			}
			lt_det = 1;																// toggle if a &lt detected
			lt_pos = i;																// store the position where the word stopped adding characters
		}
		else if (lt_det) {															// if a &lt has been detected, do not output until &gt has been detected
			if ((buf[size + i] == 38 && buf[size + i + 1] == 103 && buf[size + i + 2] == 116)) {
				if (lt_pos == 0) {													// if &lt at start of the data:
					size += i + 4 - lt_pos;											// skip past &gt using the size parameter
					i = -1;															// set i to -1 so it will restart at 0 on the next iteration
				}
				else {																// if &lt is not at the start of the data:
					size += i + 3 - lt_pos;											// skip past &gt using the size parameter
					i = lt_pos;														// reset the character position to the one before &lt detection
				}
				lt_pos = 0;		 													// reset lt_det back to zero for another potential detection of &lt
				lt_det = 0;															// reset lt_det back to zero for another potential detection of &lt
				if (buf[size + i + 1] == ' ') size++;								// if data does not directly start after = sign, skip one character further
			}

		}
		else {																		// when no &lt is found, proceed as normally

			if(buf[i+size] == 91 || buf[i+size] == 123) size +=2;					// if the current char is either a { or a [ then skip 2

			cln[i] = buf[i+size];													// copy the current char from buffer to the output line

			eolch[0] = buf[i+size];													// check if the current char is a linebreak

			if(strcmp(eolch,eol) == 0 || buf[i+size] == 93) { 						// check whether EOL or ] is detected
				cln[i] = 34;														// add quotes after data
				break;																// quit the for-loop, all data was extracted
			}
		}
	}

	fputs(cln, stdout);																// output the data to the console

}
