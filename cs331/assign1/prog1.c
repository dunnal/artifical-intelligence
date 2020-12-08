#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Problem {
   int   boat_side;     //0 is left, 1 is right
   int   leftBank[2];   //leftBank[0] = # of chickens    	leftBank[1] = # of wolves
   int   rightBank[2];  //rightBank[0] = # of chickens   	rightBank[1] = # of wolves
   
   int   goal_boat_side;     //0 is left, 1 is right
   int   goal_leftBank[2];   //leftBank[0] = # of chickens    	leftBank[1] = # of wolves
   int   goal_rightBank[2];  //rightBank[0] = # of chickens   	rightBank[1] = # of wolves
   
   struct Problem* first;
   struct Problem* second;
   struct Problem* third;
   struct Problem* fourth;
   struct Problem* fifth;
   
   struct Problem* parent = this;
}; 

int isgoalstate(struct Problem* prob){
	if(prob->boat_side == prob->goal_boat_side && 
		prob->leftBank[0] == prob->goal_leftBank[0] && prob->leftBank[1] == prob->goal_leftBank[1] && 
		prob->rightBank[0] == prob->goal_rightBank[0] && prob->rightBank[1] == prob->goal_rightBank[1]){
		return 1;
	}
	return 0;
}

void bfs(struct Problem* prob){
	printf("bfs\n");
	prob->first = NULL;
	prob->second = NULL;
	prob->third	= NULL;
	prob->fourth = NULL;
	prob->fifth = NULL;
	
	
}

void dfs(struct Problem* prob){
	printf("dfs\n");
	prob->first = NULL;
	prob->second = NULL;
	prob->third	= NULL;
	prob->fourth = NULL;
	prob->fifth = NULL;
}

void iddfs(struct Problem* prob){
	printf("iddfs\n");
	prob->first = NULL;
	prob->second = NULL;
	prob->third	= NULL;
	prob->fourth = NULL;
	prob->fifth = NULL;
}

void astar(struct Problem* prob){
	printf("astar\n");
	prob->first = NULL;
	prob->second = NULL;
	prob->third	= NULL;
	prob->fourth = NULL;
	prob->fifth = NULL;
}

void print_state(struct Problem* prob){
	printf("start:\n");
	printf("	left bank\n");
	printf("		%d chickens\n", prob->leftBank[0]);
	printf("		%d wolves\n", prob->leftBank[1]);
	printf("	right bank\n");
	printf("		%d chickens\n", prob->rightBank[0]);
	printf("		%d wolves\n", prob->rightBank[1]);
	if(prob->boat_side == 1){
		printf("		boat is on right bank\n\n");
	} else{
		printf("		boat is on left bank\n\n");
	}
		
		
	printf("goal:\n");
	printf("	left bank\n");
	printf("		%d chickens\n", prob->goal_leftBank[0]);
	printf("		%d wolves\n", prob->goal_leftBank[1]);
	printf("	right bank\n");
	printf("		%d chickens\n", prob->goal_rightBank[0]);
	printf("		%d wolves\n", prob->goal_rightBank[1]);
	if(prob->goal_boat_side == 1){
		printf("		boat is on right bank\n");
	} else{
		printf("		boat is on left bank\n");
	}
}

void main( int argc, char *argv[] ){
	FILE* myfile;
	int x;
	int y;
	int z;
//checks if the number of arguments is correct
	if(argc != 5){
		printf("incorrect number of arguments\n");
	} else{
		struct Problem* prob;
		prob = malloc(sizeof(struct Problem));
		
//reading in the start file		
		myfile = fopen(argv[1], "r");
		fscanf(myfile,"%d,%d,%d", &x,&y,&z);
		prob->leftBank[0] = x;
		prob->leftBank[1] = y;
		
		fscanf(myfile,"%d,%d,%d", &x,&y,&z);
		prob->rightBank[0] = x;
		prob->rightBank[1] = y;
		
		if(z == 1){
			prob->boat_side = 1;
		} else{
			prob->boat_side = 0;
		}
		fclose(myfile);
		
//reading in the goal file		
		myfile = fopen(argv[2], "r");
		fscanf(myfile,"%d,%d,%d", &x,&y,&z);
		prob->goal_leftBank[0] = x;
		prob->goal_leftBank[1] = y;
		
		fscanf(myfile,"%d,%d,%d", &x,&y,&z);
		prob->goal_rightBank[0] = x;
		prob->goal_rightBank[1] = y;
		
		if(z == 1){
			prob->goal_boat_side = 1;
		} else{
			prob->goal_boat_side = 0;
		}
		fclose(myfile);	
		
		print_state(prob);
		
//find what mode you're working in, and call the functions

		if(!strcmp(argv[3], "bfs")){
			bfs(prob);
		} else if(!strcmp(argv[3], "dfs")){
			dfs(prob);
		} else if(!strcmp(argv[3], "iddfs")){
			iddfs(prob);
		} else if(!strcmp(argv[3], "astar")){
			astar(prob);
		} else {
			printf("invalid mode\n");
		}
	}
}
