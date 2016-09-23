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
#include <stdlib.h> // for exit();
#include <getopt.h> // to parse long arguments.
#include <unistd.h> // sleep
#include <vector>
using std::vector;
#include <string>
using std::string;

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Text-based version of Conway's game of life.\n\n"
"   --seed,-s     FILE     read start state from FILE.\n"
"   --world,-w    FILE     store current world in FILE.\n"
"   --fast-fw,-f  NUM      evolve system for NUM generations and quit.\n"
"   --help,-h              show this message and exit.\n";

size_t max_gen = 0; /* if > 0, fast forward to this generation. */
string wfilename =  "/tmp/gol-world-current"; /* write state here */
FILE* fworld = 0; /* handle to file wfilename. */
string initfilename = "/tmp/gol-world-current"; /* read initial state from here. */

size_t nbrCount(size_t i, size_t j, const vector<vector<bool> >& g);
void update();
int initFromFile(const string& fname);
/*FILE* f = fopen(fname, "rb");
	int i = 0;
	int j = 0;
	char c;
	while((c = getc(f))!= EOF) {
		switch(c) {
			case '.': grid[i][j] = false; ++i; break;
			case 'O': grid[i][j] = true; ++i; break;
			case '\n': ++j; i = 0; break;
		}
	}
	for(int i = 0; i < 10; ++i){
		for(int j = 0; j < 20; ++j) {
			if(grid[j][i])
				cout << "O";
			else cout << ".";
		}
		cout << endl;
	}
	cout << endl;
	fclose(f);
	return 1;
}
*/
void mainLoop();
void dumpState(FILE* f);

char text[3] = ".O";

int main(int argc, char *argv[]) {
	// define long options
	static struct option long_opts[] = {
		{"seed",    required_argument, 0, 's'},
		{"world",   required_argument, 0, 'w'},
		{"fast-fw", required_argument, 0, 'f'},
		{"help",    no_argument,       0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "hs:w:f:", long_opts, &opt_index)) != -1) {
		switch (c) {
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
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}

	mainLoop();
	return 0;
}

void mainLoop() {
	/* update, write, sleep */
}

size_t nbrCount(size_t i, size_t j, const vector<vector<bool> >& g{

		size_t row_size = g.size();
		size_t col_size = g[i].size();
		for ( i = 0; i < row_size; ++i)
			for ( j = 0; j < col_size; ++j){
				size_t count = 0;
				if ( g[(row_size-1 + i)% row_size][j] == true )
					count++;
				if ( g[(row_size-1 + i)% row_size][j-1] == true )
					count++;
				if ( g[(row_size-1 + i)% row_size][j+1] == true )
					count++;
				if ( g[(row_size+1 + i)% row_size][j] == true )
					count++;
				if ( g[(row_size+1 + i)% row_size][j-1] == true )
					count++;
				if ( g[(row_size+1 + i)% row_size][j+1] == true )
					count++;
				if ( g[i][(col_size -1 +j)%col_size] == true )
					count++;
				if ( g[i][(col_size +1 +j)%col_size] == true )
					count++;

				return count;

		}
}
