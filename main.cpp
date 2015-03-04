/*
NAME: Mitch Worsey
STUDENT ID: 8370927291
*/

#include <cstdlib>
#include <iostream>
#include <sys/time.h>
#include <stdio.h>
#include "Timer.h"
#include <vector>
#include <cmath>
#include <limits>
#include <ctime>

using namespace std;

struct Edge {
    int r, c, depth, jump, parentR, parentC;
    Edge(int row = 0, int col = 0, int dDepth = 0, int jJump = 0, int parR = 0, int parC = 0) :
	 r(row), c(col), depth(dDepth), jump(jJump), parentR(parR), parentC(parC) { }
};

class Grid {
    int height, width;
    vector< vector <int> > tiles;
public:
    Grid(int, int, int**); // construct the grid
    int BFS();
    vector<Edge> reachableBFS();
    vector<Edge> reachingBFS();
};

Grid::Grid(int h, int w, int **puzz){
    height = h;
    width = w;

    tiles.resize(height, vector<int>(width, 0));

    for(int i = 0; i < height; i++)    
        for(int j = 0; j < width; j++) 
            tiles[i][j] = puzz[i][j]; 

}

vector<Edge> Grid::reachableBFS(){
    vector<Edge> reachable;
    vector< vector<int> > origTiles;

    origTiles.resize(height, vector<int>(width, 0));

    for(int i = 0; i < height; i++)    
        for(int j = 0; j < width; j++) 
            origTiles[i][j] = tiles[i][j]; 

    for(int row = 0; row < height; row++){
	for(int col = 0; col < width; col++){
	    if(row != height-1 || col != width-1){
		vector<Edge> openList, closedList;
		for(int i = 0; i < height; i++)    
		    for(int j = 0; j < width; j++) 
			tiles[i][j] = origTiles[i][j];
		openList.push_back(Edge(0, 0));
	        do{
		    closedList.push_back(openList[0]);
		    openList.erase(openList.begin());

		    int r = closedList.back().r;
		    int c = closedList.back().c;
		    int depth = closedList.back().depth; 

		    if(r == row && c == col){
		        reachable.push_back(Edge(r, c, depth, tiles[r][c]));
			break;
		    }

		    int jump = tiles[r][c];
		    tiles[r][c] = 0; 

		    if(r + jump < height && tiles[r+jump][c] != 0){ 
		        openList.push_back(Edge(r+jump, c, depth+1, jump)); 
		    }
		    if(c + jump < width && tiles[r][c+jump] != 0){ 
		        openList.push_back(Edge(r, c+jump, depth+1, jump)); 
		    }
		    if(r - jump > -1 && tiles[r-jump][c] != 0){ 
		        openList.push_back(Edge(r-jump, c, depth+1, jump)); 
		    }
		    if(c - jump > -1 && tiles[r][c-jump] != 0){ 
		        openList.push_back(Edge(r, c-jump, depth+1, jump));
		    }
	        }
	        while(openList.size() > 0);
	    }
	}
    }
    return reachable;    
}

vector<Edge> Grid::reachingBFS(){
    vector<Edge> reaching;
    vector< vector<int> > origTiles;

    origTiles.resize(height, vector<int>(width, 0));

    for(int i = 0; i < height; i++)    
        for(int j = 0; j < width; j++) 
            origTiles[i][j] = tiles[i][j]; 

    for(int row = 0; row < height; row++){
	for(int col = 0; col < width; col++){
	    if(row != height-1 || col != width-1){
		vector<Edge> openList, closedList;
		for(int i = 0; i < height; i++)    
		    for(int j = 0; j < width; j++) 
			tiles[i][j] = origTiles[i][j];
		openList.push_back(Edge(row, col));
	        do{
		    closedList.push_back(openList[0]);
		    openList.erase(openList.begin());

		    int r = closedList.back().r;
		    int c = closedList.back().c;
		    int depth = closedList.back().depth; 

		    if(r == height-1 && c == width-1){
		        reaching.push_back(Edge(row, col));
			break;
		    }

		    int jump = tiles[r][c];
		    tiles[r][c] = 0; 

		    if(r + jump < height && tiles[r+jump][c] != 0){ 
		        openList.push_back(Edge(r+jump, c, depth+1, jump)); 
		    }
		    if(c + jump < width && tiles[r][c+jump] != 0){ 
		        openList.push_back(Edge(r, c+jump, depth+1, jump)); 
		    }
		    if(r - jump > -1 && tiles[r-jump][c] != 0){ 
		        openList.push_back(Edge(r-jump, c, depth+1, jump)); 
		    }
		    if(c - jump > -1 && tiles[r][c-jump] != 0){ 
		        openList.push_back(Edge(r, c-jump, depth+1, jump));
		    }
		    if(r + jump == height - 1 && c == width-1){
	    	        openList.push_back(Edge(r+jump, c, depth+1, jump));
		    }
		    if(c + jump == width - 1 && r == height-1){
		        openList.push_back(Edge(r, c+jump, depth+1, jump));
		    }
	        }
	        while(openList.size() > 0);
	    }
	}
    }
    return reaching;   
}


int Grid::BFS(){
    vector<Edge> openList, closedList;
    openList.push_back(Edge(0, 0));

    do{
        closedList.push_back(openList[0]);
        openList.erase(openList.begin());

        int r = closedList.back().r;
        int c = closedList.back().c;
        int depth = closedList.back().depth; 

        if(r == height-1 && c == width-1){
	    return depth;
	}

        int jump = tiles[r][c];
	//cout << "R="<<r<<" C="<<c<<" val="<<jump<<" depth="<<depth<<endl;
        tiles[r][c] = 0; 

        if(r + jump < height && tiles[r+jump][c] != 0){ 
            openList.push_back(Edge(r+jump, c, depth+1, jump)); 
        }
        if(c + jump < width && tiles[r][c+jump] != 0){ 
	    openList.push_back(Edge(r, c+jump, depth+1, jump)); 
        }
	if(r - jump > -1 && tiles[r-jump][c] != 0){ 
            openList.push_back(Edge(r-jump, c, depth+1, jump)); 
        }
        if(c - jump > -1 && tiles[r][c-jump] != 0){ 
            openList.push_back(Edge(r, c-jump, depth+1, jump));
        }
	if(r + jump == height - 1 && c == width-1){
	    openList.push_back(Edge(r+jump, c, depth+1, jump));
	}
	if(c + jump == width - 1 && r == height-1){
	    openList.push_back(Edge(r, c+jump, depth+1, jump));
	}
    }
    while(openList.size() > 0);

    return 0;
}


class Puzzle {
    int nRows, nCols, minVal, maxVal;
    int solLength, nBHoles, nWHoles, nFFM, nFBM, score;
    bool unique;
    int **puzzle;
public:
    Puzzle(int, int, int, int);
    Puzzle& operator=(Puzzle&);
    void createPuzzle();
    void print();
    int solveAndScore();
    int getScore();
    void setValue(int, int, int);
    int getValue(int, int);
};

Puzzle::Puzzle (int rows, int cols, int min, int max){
    nRows = rows;
    nCols = cols;
    minVal = min;
    maxVal = max;
    puzzle = new int *[nRows];
    for(int i = 0; i < nRows; i++)
	puzzle[i] = new int[nCols];
    solLength = 0;
    nBHoles = 0;
    nWHoles = 0;
    nFFM = 0;
    nFBM = 0;
    score = 0;
    unique = false;
}

Puzzle& Puzzle::operator=(Puzzle& other){
    nRows = other.nRows;
    nCols = other.nCols;
    minVal = other.minVal;
    maxVal = other.maxVal;
    puzzle = new int *[nRows];
    for(int i = 0; i < nRows; i++)
	puzzle[i] = new int[nCols];
    for(int r = 0; r < nRows; r++){
	for(int c = 0; c < nCols; c++){
	    puzzle[r][c] = other.puzzle[r][c];
	}
    }
    //puzzle = other.puzzle;
    solLength = other.solLength;
    nBHoles = other.nBHoles;
    nWHoles = other.nWHoles;
    nFFM = other.nFFM;
    nFBM = other.nFBM;
    score = other.score;
    unique = other.unique;
    return *this;
}

void Puzzle::createPuzzle(){
    for(int r = 0; r < nRows; r++){
	for(int c = 0; c < nCols; c++){
	    if(r == nRows-1 && c == nCols-1)
		puzzle[r][c] = 0;
	    else
		puzzle[r][c] = rand() % (maxVal-minVal+1) + minVal;
	}
    }
}

void Puzzle::print(){
    cout << "Puzzle:" << endl;
    for(int r = 0; r < nRows; r++){
        for(int c = 0; c < nCols; c++){
	    cout << puzzle[r][c] << " ";
	}
    cout << endl;
    }
    cout << endl;
    cout << "Solution: ";
    if(solLength == 0)
	cout << "No" << endl;
    else
	cout << "Yes" << endl;
    cout << "Unique: ";
    if(unique)
	cout << "Yes" << endl;
    else
	cout << "No" << endl;
    cout << "Solution length: " << solLength << endl;
    cout << "# of black holes: " << nBHoles << endl;
    cout << "# of white holes: " << nWHoles << endl;
    cout << "# of forced forward moves: " << nFFM << endl;
    cout << "# of forced backward moves: " << nFBM << endl;
    cout << "Puzzle score: " << score << endl << endl;
}

int Puzzle::solveAndScore(){
    Grid g(nRows, nCols, puzzle);
    Grid gReachable(nRows, nCols, puzzle);
    Grid gReaching(nRows, nCols, puzzle);
    vector<Edge> reachable, reaching;
    nFFM = 0;
    nFBM = 0;
    nBHoles = 0;
    nWHoles = 0;

    solLength = g.BFS();

    reachable = gReachable.reachableBFS();
    reaching = gReaching.reachingBFS();

    if(solLength>0){
    unique = true;
    for(int x = 0; x < reachable.size(); x++){
	vector<Edge> parents;
	for(int y = 0; y < reachable.size(); y++){
	    if(x!=y){
		if(reachable[y].r + reachable[y].jump == reachable[x].r)
		    if(reachable[y].c == reachable[x].c)
			parents.push_back(reachable[y]);
		else if(reachable[y].r - reachable[y].jump == reachable[x].r)
		    if(reachable[y].c == reachable[x].c)
			parents.push_back(reachable[y]);
		else if(reachable[y].c + reachable[y].jump == reachable[x].c)
		    if(reachable[y].r == reachable[x].r)
			parents.push_back(reachable[y]);
		else if(reachable[y].c - reachable[y].jump == reachable[x].c)
		    if(reachable[y].r == reachable[x].r)
			parents.push_back(reachable[y]);
	    }
	}
	if(parents.size()>0){
	    //int parDepth = parents[0].depth;
	    int parDepth = reachable[x].depth-1;
	    int parCount = 0;
	    for(int z = 0; z < parents.size(); z++){
		//cout << "Child r="<<reachable[x].r<<" c="<<reachable[x].c<<" jump="<<reachable[x].jump<<endl;
		//cout << "Parent r="<<parents[z].r<<" c="<<parents[z].c<<" jump="<<parents[z].jump<<endl;
		if(parents[z].depth == parDepth)
		    parCount++;
		if(parents[z].depth <= parDepth && parCount > 1){
		    //cout << "Not Unique r="<<parents[z].r<<" c="<<parents[z].c<<" jump="<<parents[z].jump<<endl;
		    unique = false;
		}
	    }
	}
    }
    }



    for(int x = 0; x < reachable.size(); x++){
	bool match = false;
	for(int y =0; y < reaching.size(); y++){
	    if(reachable[x].r == reaching[y].r && reachable[x].c == reaching[y].c)
		match = true;
	}
	if(!match){
	    //cout << "Black Hole r="<<reachable[x].r<<" c="<<reachable[x].c<<endl;
	    nBHoles++;
	}
    }

    for(int x = 0; x < reaching.size(); x++){
	bool match = false;
	for(int y =0; y < reachable.size(); y++){
	    if(reaching[x].r == reachable[y].r && reaching[x].c == reachable[y].c)
		match = true;
	}
	if(!match){
	    //cout << "White Hole r="<<reaching[x].r<<" c="<<reaching[x].c<<endl;
	    nWHoles++;
	}
    }



    for(int x = 0; x < reachable.size(); x++){
	//cout << "ReachABLE r="<<reachable[x].r<<" c="<<reachable[x].c<<endl;
	int nMoves = 0;
	if(reachable[x].r+reachable[x].jump<nRows)
	    nMoves++;
	if(reachable[x].c+reachable[x].jump<nCols)
	    nMoves++;
	if(reachable[x].r-reachable[x].jump>-1)
	    nMoves++;
	if(reachable[x].c-reachable[x].jump>-1)
	    nMoves++;
	if(nMoves == 1){
	    //cout<<"FFM r="<<reachable[x].r<<" c="<<reachable[x].c<<endl;
	    nFFM++;
	}
    }

	
    for(int x = 0; x < reaching.size(); x++){
	//cout << "ReachING r="<<reaching[x].r<<" c="<<reaching[x].c<<endl;
	int nMoves = 0;
	for(int i = minVal; i <= maxVal; i++){
	    if(reaching[x].r-i>-1){
		if(puzzle[reaching[x].r-i][reaching[x].c]==i){
		    //cout << "This cell: r="<<reaching[x].r<<" c="<<reaching[x].c<<endl;
		   //cout << "Reached by r="<<reaching[x].r-i<<" c="<<reaching[x].c<<" jump="<<puzzle[reaching[x].r-i][reaching[x].c]<<" i="<<i<<endl;
		    nMoves++;
		}
	    }
	    if(reaching[x].r+i<nRows){
		if(puzzle[reaching[x].r+i][reaching[x].c]==i){
		    //cout << "This cell r="<<reaching[x].r<<" c="<<reaching[x].c<<endl;
		    //cout << "Reached by r="<<reaching[x].r+i<<" c="<<reaching[x].c<<" jump="<<puzzle[reaching[x].r+i][reaching[x].c]<<" i="<<i<<endl;
		    nMoves++;
		}
	    }
	    if(reaching[x].c-i>-1){
		if(puzzle[reaching[x].r][reaching[x].c-i]==i){
		    //cout << "This cell r="<<reaching[x].r<<" c="<<reaching[x].c<<endl;
		    //cout << "Reached by r="<<reaching[x].r<<" c="<<reaching[x].c-i<<" jump="<<puzzle[reaching[x].r][reaching[x].c-i]<<" i="<<i<<endl;
		    nMoves++;
		}
	    }
	    if(reaching[x].c+i<nCols){
		if(puzzle[reaching[x].r][reaching[x].c+i]==i){
		    //cout << "This cell r="<<reaching[x].r<<" c="<<reaching[x].c<<endl;
		    //cout << "Reached by r="<<reaching[x].r<<" c="<<reaching[x].c+i<<" jump="<<puzzle[reaching[x].r][reaching[x].c+i]<<" i="<<i<<endl;
		    nMoves++;
		}
	    }
	}
	if(nMoves == 1){
	    //cout<<"FBM r="<<reaching[x].r<<" c="<<reaching[x].c<<endl;
	    nFBM++;
	}
    }
    score = (5*solLength) - (2*(nBHoles+nWHoles)) - (2*(nFFM+nFBM));
    if(unique)
	score += (nRows*nCols);
    return score;



}

int Puzzle::getScore(){
    return score;
}

void Puzzle::setValue(int r, int c, int val){
    puzzle[r][c] = val;
}

int Puzzle::getValue(int r, int c){
    return puzzle[r][c];
}

void hillClimb(Puzzle& puzz, int nRows, int nCols, int minVal, int maxVal, Timer t){
    int bestScore = puzz.solveAndScore();
    //cout << "original" << endl;
    //puzz.print();
    Puzzle tempPuzz (nRows, nCols, minVal, maxVal);

    srand( time (NULL) );

    while(t.GetElapsedTime()<59.9){
	//cout << "temp BEFORE" <<endl;
	//tempPuzz.print();
	tempPuzz = puzz;
	if(t.GetElapsedTime()>14.9 && t.GetElapsedTime()<15.0 ||
		t.GetElapsedTime()>29.9 && t.GetElapsedTime()<30.0 || 
		t.GetElapsedTime()>44.9 && t.GetElapsedTime()<45.0)
	    tempPuzz.createPuzzle();
	//cout << "temp AFTER" <<endl;
	//tempPuzz.print();
	int randRow = rand() % nRows;
	int randCol = rand() % nCols;
	if(randRow != nRows-1 || randCol != nCols-1){
	    int randVal = minVal;
	    while(randVal <= maxVal){
		if(randVal != puzz.getValue(randRow, randCol)){
		    tempPuzz.setValue(randRow, randCol, randVal);
		    int tempScore = tempPuzz.solveAndScore();
		    //cout << "temp" <<endl;
		    //tempPuzz.print();
		    if(tempScore > bestScore){
			bestScore = tempScore;
			puzz = tempPuzz;
			//puzz.setValue(randRow, randCol, randVal);
			//cout << "better" <<endl;
			//puzz.print();
			break;
		     }
		}
		randVal++;
	    }
	    /*int randVal = rand() % (maxVal-minVal+1) + minVal;//minVal;
	    vector<int> checkedVals;
	    checkedVals.push_back(puzz.getValue(randRow, randCol));
	    while(checkedVals.size() < (maxVal-minVal+1)){
		bool alreadyChecked = false;
		for(int ch = 0; ch < checkedVals.size(); ch++){
		    if(randVal == checkedVals[ch])
			alreadyChecked = true;
		}
		if(!alreadyChecked){
		    tempPuzz.setValue(randRow, randCol, randVal);
		    int tempScore = tempPuzz.solveAndScore();
		    //cout << "temp" <<endl;
		    //tempPuzz.print();
		    if(tempScore > bestScore){
			bestScore = tempScore;
			puzz = tempPuzz;
			//puzz.setValue(randRow, randCol, randVal);
			//cout << "better" <<endl;
			//puzz.print();
			//break;
		     }
		     checkedVals.push_back(randVal);
		}
		randVal = rand() % (maxVal-minVal+1) + minVal;
		cout <<"rand "<<randVal<<endl;
	    }
		checkedVals.clear();
		cout << "new rand"<<endl;
*/
	}
    }

    /*
    int imax = numeric_limits<int>::max();

    double numGrids = pow((maxVal-minVal+1), (nRows*nCols));
    cout << "Total number of Grid combinations: " << numGrids << endl;

    if(numGrids > imax)
	numGrids = imax;
    int nGrids =  int (numGrids);
    

    int nGridsAttempted = 1;    

    for(int i = 0; i < nGrids; i++){
	if(t.GetElapsedTime() >59.9 && t.GetElapsedTime() < 60){
	    cout << "Number of Grids attempted: " << nGridsAttempted << endl;
	    break;
	}
	tempPuzz.createPuzzle();
	int tempScore = tempPuzz.solveAndScore();
	//cout << "temp" <<endl;
	//tempPuzz.print();
	if(tempScore > bestScore){
	    bestScore = tempScore;
	    puzz = tempPuzz;
	}
	if(i == nGrids-1)
	    i = 0;
	nGridsAttempted++;
    }*/

}


void GeneratePuzzle(int nRows, int nCols, int minVal, int maxVal, Timer t){
    // YOUR CODE HERE
    Puzzle puzz (nRows, nCols, minVal, maxVal);
    puzz.createPuzzle();
    hillClimb(puzz, nRows, nCols, minVal, maxVal, t);
    puzz.print();
}


int main(int argc, char **argv)
{
	// Process the arguments
	if (argc != 5)
	{
		printf("Please specify the number of rows and columns and the minimum and maximum values for each cell (requires 4 parameters)\n");
		exit(0);
	}
	int nRows = atoi(argv[1]);
	int nColumns = atoi(argv[2]);
	int minVal = atoi(argv[3]);
	int maxVal = atoi(argv[4]);

	// Start the timer
	Timer t;
	t.StartTimer();
  	
	// Generate the puzzle
	printf("Generating a %dx%d puzzle with values in range [%d-%d]\n", nRows, nColumns, minVal, maxVal);
	
	GeneratePuzzle(nRows, nColumns, minVal, maxVal, t);
		
	// Print the elapsed time
    printf("Total time: %.6lf seconds\n", t.GetElapsedTime());

	return 0;
}
