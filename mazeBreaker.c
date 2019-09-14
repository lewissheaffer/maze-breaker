#include <stdio.h>
#include <ncurses.h> 
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h> 
 
int rows, columns, area, startX, startY, endX, endY, randValue;

char fileName[20];

void delay(int milliseconds);

void generateRandomMaze(char maze[rows][columns]);

void generateMazeFromFile(char maze[rows][columns]);

void drawMaze(char maze[rows][columns]);

bool depthSolver(int x, int y, char maze[rows][columns]);

bool isWalkable(int row, int col, char maze[rows][columns]);

int main (int argc, char *argv[]) {
	setlocale(LC_ALL, "");
	initscr();
    refresh();
	
	if(strcmp(argv[1], "Random") == 0) {
		sscanf(argv[2], "%d", &randValue);
		sscanf(argv[3], "%d", &rows);
		sscanf(argv[4], "%d", &columns);
	}
	else if(strcmp(argv[1], "File") == 0) {
		strcpy(fileName, argv[2]);
		char line[200];
		FILE *file = fopen(fileName,"r");
		
		if(file != NULL) {
			while(fgets(line,sizeof(line),file)!=NULL) {
				if(columns<strlen(line)) {
					columns = strlen(line); 
				}
				rows++; 
			}
			fclose(file);
		}
		else {
		endwin();
		perror(fileName);
		exit;
		} 
	}
	else {
		endwin(); 
		printf("Must include maze type (Random or File)");
		exit;
	} 

	char maze[rows][columns];

	if(strcmp(argv[1], "File") == 0) {
		generateMazeFromFile(maze);
	}
	else {
		generateRandomMaze(maze);
	}
	
	drawMaze(maze);
	
	if(!depthSolver(startX, startY, maze)) {
		mvprintw(0, columns+1, "No Solution"); 
	}
	else {
		mvprintw(0, columns+1, "Solution Found!!");
	}

	refresh(); 
	while(true){
	}
	endwin();
}

void draw_character(int x, int y, char use)
{
    mvaddch(y,x,use);
    refresh();
}

void generateRandomMaze(char maze[rows][columns]) {
	srand(time(0));
	for(int i = 0; i<rows; i++) {	
		for(int j=0; j<columns; j++) {
			if((i == 0 || j == columns-1)||(j == 0 || i == rows-1)) {
				maze[i][j] = 1;
			}
			else if(rand()% 100< randValue) {
					maze[i][j] = 1;
			}
			else {
					maze[i][j] = 0;
			}
		}
	}
	
	startX = rand()%(columns-2)+1;
	startY = rand()%(rows-2)+1;
	endX = rand()%(columns-2)+1;
	endY = rand()%(rows-2)+1;
	maze[startY][startX] = 'S'; 
	maze[endY][endX] = 'E'; 
}


void generateMazeFromFile(char maze[rows][columns]) {
	FILE *file = fopen(fileName,"r");
	char line[200];
	int row = 0;
	while(fgets(line,sizeof(line),file) != NULL) {
		for(int i = 0; i<strlen(line); i++) {
			if(line[i] == 'S' || line[i] == 's' ) {
				maze[row][i] = toupper(line[i]);
				startX = i;
				startY = row;
			}
			else if(line[i] == 'E' || line[i] == 'e') {
				maze[row][i] = toupper(line[i]);
				endX = i;
				endY = row;
			}
			else if(line[i] == '#'){
				maze[row][i] = 1;
			}
			else{
				maze[row][i] = 0;
			}
		}
		row++;
	}
	fclose(file);
}


void drawMaze(char maze[rows][columns]) {
	for(int i = 0; i<rows; i++) {	
		for(int j=0; j<columns; j++) {
			if(maze[i][j] == 1) {
				attron(ACS_CKBOARD);
				draw_character(j,i,ACS_CKBOARD);
				attroff(ACS_CKBOARD);
			}
			else if(maze[i][j] == 'S' || maze[i][j] == 'E') {
				draw_character(j,i, maze[i][j]);
			}
		}
	}
}

bool depthSolver(int x, int y, char maze[rows][columns]) {
	if(x == endX && y == endY) {
		return true; 
	}
	//Up, Left, Down, Right
	int direction[4][2] ={{0, -1} , {-1,0}, {0,1}, {1,0}};
	for(int i = 0; i<4; i++) {
		int nextX = direction[i][0]+x;
		int nextY = direction[i][1]+y;
		if(isWalkable(nextY, nextX, maze)) {
			maze[nextY][nextX] = 1; 
			attron(ACS_DARROW);
			if(!(nextX == endX && nextY == endY)) {
				switch(i) {
					case 0: 
						draw_character(nextX, nextY, ACS_UARROW);
						break;
					case 1:
						draw_character(nextX, nextY, ACS_LARROW);
						break;
					case 2:
						draw_character(nextX, nextY, ACS_DARROW);
						break;
					case 3:
						draw_character(nextX, nextY, ACS_RARROW);
						break;
				}
			}
			attroff(ACS_DARROW);
			delay(50); 
			if(depthSolver(nextX, nextY, maze)) {
				return true; 
			}
			draw_character(nextX, nextY, ' ');
		} 
	}
	//No solution is found
	return false;
}

bool isWalkable(int row, int col, char maze[rows][columns]) {
	return((maze[row][col] == 0)||(maze[row][col] == 'E'));
}

void delay(int milliseconds) {
    long pause;
    clock_t now,then;
    pause = milliseconds * (CLOCKS_PER_SEC/1000);
    now = then = clock(); 
    while((now-then) < pause)
        now = clock();
}




