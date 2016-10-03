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
vector<vector<bool> > board;  //vector declared to save data from file
size_t row_size(0), col_size(0); //initial row and column size before getting the vector from file.

size_t max_gen = 0; /* if > 0, fast forward to this generation. */
string wfilename =  "/tmp/gol-world-current"; /* write state here */
FILE* fworld = 0; /* handle to file wfilename. */
string initfilename = "/tmp/gol-world-current"; /* read initial state from here. */

size_t nbrCount(size_t i, size_t j, const vector<vector<bool> >& g);
void update();
int initFromFile(const string& fname);
void mainLoop();
void dumpState(FILE* f);
//extra functions 
void display(vector<vector<bool> >& g );

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

	initFromFile( initfilename );
	mainLoop();
	return 0;
}

void mainLoop() {
	/* update, write, sleep */
	row_size = board.size();	
	col_size = board[0].size();
	string nofilename = "-";
	if ( wfilename == nofilename)
		fworld = fopen(initfilename.c_str(),"wb");

	else fworld = fopen(wfilename.c_str(),"wb");
	
	if ( max_gen > 0 ){
		for ( size_t i = 0; i < max_gen; ++i) {
			update();
		}
		dumpState(fworld);
		display(board);
		fclose(fworld);
	}
	else {
		while ( max_gen == 0 ){
			system("clear");
			display(board);
			dumpState(fworld);
			update();
			sleep(1);
		}
		fclose(fworld);
	}
	
}

size_t nbrCount(size_t i, size_t j, const vector<vector<bool> >& g){

	size_t count = 0;
	count = g[(row_size-1 + i)% row_size][j] +
		g[(row_size-1 + i)% row_size][(col_size -1 +j)%col_size] +    //works perfectly
		g[(row_size-1 + i)% row_size][(col_size +1 +j)%col_size] +	//counts the eight neighbor of a particular cell
		g[(row_size+1 + i)% row_size][j] +				//located at (i,j) position
		g[(row_size+1 + i)% row_size][(col_size -1 +j)%col_size] +
		g[(row_size+1 + i)% row_size][(col_size +1 +j)%col_size] +
		g[i][(col_size -1 +j)%col_size] +
		g[i][(col_size +1 +j)%col_size];
	return count;								//returns the total numbers of neighbor
			
}

void update(){								//works perfectly
	vector<vector<bool> > temp(row_size, vector<bool>(col_size, false));
	size_t total_neighbor = 0;
	for ( size_t i = 0; i < row_size; ++i){
		for ( size_t j = 0; j < col_size; ++j){
			total_neighbor = (nbrCount(i,j, board ));
			if ( (total_neighbor == 2 && board[i][j] == true) || total_neighbor == 3)	// checks the numbers of neighbor of a cell
				temp[i][j] = true;							//if the cell has more than three or less two neighbors, it dies
			else if ( total_neighbor < 2 ||  (total_neighbor ==2 && board[i][j] == false) ||  total_neighbor > 3)	//if a dead cel has exactly three neighbor, it grows,
				temp[i][j] = false;
			
		}
	}
	board = temp;
}
 
 
void display(vector<vector<bool> >& g ){		//works perfectly
 	for ( size_t i = 0; i < row_size; ++i){		// display the vector grid
		for ( size_t j = 0; j < col_size; ++j){
			if ( g[i][j] == true)
 				printf("%c",'O');
		else
				printf("%c",'.');
 			}
		printf("%c",'\n');
	}
}
int initFromFile(const string& fname){			//works perfectly
	FILE* f = fopen(fname.c_str(),"rb");		//opens the file to get input
	if (!f) {					//checks whether the file is opened successfully
	       	exit(1);				//if fails, the programs exits returning int value 1
	}
	vector<bool> temp;
	char c;
	while ( fread(&c,1,1,f)!=0 ) {
		if ( c == '\n' ) {
			board.push_back(temp);		
			temp.clear();
		}
		else {
			if ( c == '.')
				temp.push_back(false);		
			else
				temp.push_back(true);
		}
	}

	fclose(f);
	return 1;
}

void dumpState(FILE* f){
	char c = '.';
	char newline = '\n';
	rewind(f);
	for ( size_t i = 0; i < row_size; ++i){
		for ( size_t j = 0; j < col_size; ++j){
			if ( board[i][j] == true)
 				c = 'O'; 
			else if ( board[i][j] == false)
				c = '.';

			fwrite(&c,1,1,f);
 			}
		fwrite(&newline,1,1,f);
	}
}

