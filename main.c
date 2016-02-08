// getdata.c: main body of the xml parser
// written by: Martijn Geers
// date: 06-02-20

#include <stdio.h>
#include <string.h>

int main( int argc, char ** argv ) {

	// declarations
	int check = 0;											// integer to help track whether printed line is the last one within the document
	int i;													// counter
	int wnr;												// number of words within list
	const char * fn = "countries.xml";							// file name
	const static int maxString = 1024;						// read buffer size
	char buf[maxString];									// read buffer

	// read the file
	FILE * fr = fopen(fn, "r");								// open the file in read mode

	char *rc;

	// list of words to include data on from XML file * always finish with NULL terminator \0 !!! *
	char* wordlist[] = {"name\0",
						"official_languages\0",
						"languages\0",
						"conventional_long_name\0",
						"common_name\0",
						"religion\0",
						"native_name\0",
						"leader_title1\0",
						"leader_name1\0",
						"leader_title2\0",
						"leader_name2\0",
						"leader_title3\0",
						"leader_name3\0",
						"leader_title4\0",
						"leader_name4\0",
						"capital\0",
						"currency_code\0",
						"currency\0",
						"sovereignty_type\0",
						"government_type\0",
						"latd\0",
						"demonym\0",
						"time_zone\0",
						"time_zone_DST\0",
						"largest_city\0"
						};


	wnr = sizeof(wordlist)/sizeof(wordlist[0]);					// calculate the number of words in the list

	while(( rc = fgets(buf, maxString, fr) )) {					// fill up buffer while not yet at EOF

		// check for XML indicating start of new wiki page
		char a[] = "<page>";									// tag indicating page start
		if(strchk(sizeof(a),buf,a) != 0) {							// check buffer for existence of tag at BOL
			fputs("{\n", stdout);								// output the { to herald the start of a new document to console
		}

		// check for XML indicating end of new wiki page
		char b[] = "</page>";									// tag indicating page end
		if(strchk(sizeof(b),buf,b) != 0) {							// check buffer for existence of tag at BOL
			fputs("\n},\n", stdout);							// output the } followed by , to herald the end of the doc and be ready for the next
			check = 0;											// reset check back to 0, no comma at the end of the next line
		}

		for(i = 0; i < wnr; i++) {								// cycle through wordlist
			check = mongowrite(wordlist,buf,i,check);			// use mongowrite to detect a wordmatch and output data
		}

	}
	fclose(fr);													// close the XML document

	return 0;
}
