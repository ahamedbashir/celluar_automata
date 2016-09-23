/*
 * CSc103 Project 3: Game of Life
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: 

*/

#include <cstdio>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <vector>
#include <string>

using std::vector;
using std::string;

static const char* usage = 
"Usage: %s [OPTIONS]...\n"
"Text-Based version of Conway's Game of Life.\n\n"
"   --seed,-s	 FILE	read start state from FILE.\n"
"   --world,-w   FILE	store vurrent world in FILE.\n"
"   --fast-fw,-f NUM	evolve system for NUM generations and quit.\n"
"   --help,-h		show this message and exit.\n";

size_t max_gen = 0; // if > 0, fast forward to this generation
string wfilename = "/tmp/gol-world-current"; // write state here
FILE* fworld = 0; // wfilename handler
string initfilename = wfilename; //read initial stat from here

size_t nbrCount(size_t i, size_t j, const vector<vector<bool> >& g);
void update();
int initFromFile(const string& fname);
void mainLoop();
void dumpState(FILE* f);

char text[3] = ".0";

int main(int argc, char *argv[]) {
	static struct option long_opts[] = {
		{"seed", required_argument, 0, 's'},
		{"world", required_argument, 0, 'w'},
		{"fast-fw", required_argument, 0, 'f'};
		{"help", no_argument, 0, 'h'},
		{0,0,0,0}
	};
	char c;
	int opt_index = 0;
	while((c = getopt_long(argc, argv, "hs:w:f:", long_opts, &opt_index))
	{
		switch(c) {
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case 's':
				initfilename = optarg;
				break;
			case 'w':
				wfilename = optarg;
				break;
			case 'f':
				max_gen = atoi(optarg);
				break;
			case'?':
				printf(usage, argv[0]);
				return 1;
		}
	}
	
	mainLoop();
	return 0;
}

void mainloop() {
		/* update, write, sleep */

}