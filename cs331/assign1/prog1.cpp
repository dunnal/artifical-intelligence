#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <cmath>
#include <fstream>
#include <queue> 
#include <bits/stdc++.h> 
#include <vector>

using namespace std;

char* output;
FILE* outputfile;
int iddfsCount=0;

struct Problem {
   int   boat_side;     //0 is left, 1 is right
   int   leftBank[2];   //leftBank[0] = # of chickens    	leftBank[1] = # of wolves
   int   rightBank[2];  //rightBank[0] = # of chickens   	rightBank[1] = # of wolves
   
   int   goal_boat_side;     //0 is left, 1 is right
   int   goal_leftBank[2];   //leftBank[0] = # of chickens    	leftBank[1] = # of wolves
   int   goal_rightBank[2];  //rightBank[0] = # of chickens   	rightBank[1] = # of wolves
   
   struct Problem* first;    // Put one chicken in the boat
   struct Problem* second;   // Put two chickens in the boat
   struct Problem* third;    // Put one wolf in the boat
   struct Problem* fourth;   // Put two wolves in the boat
   struct Problem* fifth;    // Put one wolf and one chicken in the boat
   
   struct Problem* parent = NULL;
}; 

struct thing{
    int a;
    struct Problem* b;
    bool operator<(const thing& rhs) const
    {
        return a < rhs.a;
    }
};

//prints out a given node to screen and file
void print_state(struct Problem* prob){

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
	
	fprintf(outputfile,"	left bank\n");
	fprintf(outputfile,"		%d chickens\n", prob->leftBank[0]);
	fprintf(outputfile,"		%d wolves\n", prob->leftBank[1]);
	fprintf(outputfile,"	right bank\n");
	fprintf(outputfile,"		%d chickens\n", prob->rightBank[0]);
	fprintf(outputfile,"		%d wolves\n", prob->rightBank[1]);
	if(prob->boat_side == 1){
		fprintf(outputfile,"		boat is on right bank\n\n");
	} else{
		fprintf(outputfile,"		boat is on left bank\n\n");
	}
		
	printf("\n---------------------------------------------------------\n\n");
	fprintf(outputfile,"\n---------------------------------------------------------\n\n");
}

//checks if a state is a goal state 
	//returns 1 is goal state
	//returns 0 is not goal state
int isgoalstate(struct Problem* prob){
	if(prob->boat_side == prob->goal_boat_side && 
		prob->leftBank[0] == prob->goal_leftBank[0] && prob->leftBank[1] == prob->goal_leftBank[1] && 
		prob->rightBank[0] == prob->goal_rightBank[0] && prob->rightBank[1] == prob->goal_rightBank[1]){
		return 1;
	}
	return 0;
}

//verifies if a succesor is legal
	//return 1 if legal
	//return 0 if illegal
int verifysucc(struct Problem* prob){
//less than 0 chickens on left bank
	if (prob->leftBank[0] < 0){
		return 0;
	}
//less than 0 wolves on left bank
	if(prob->leftBank[1] < 0){
		return 0;
	}
//less than 0 chickens on right bank
	if(prob->rightBank[0] < 0){
		return 0;
	}
//less than 0 wolves on right bank
	if(prob->rightBank[1] < 0){
		return 0;
	}
// more wolves than chickens on left bank
	if(prob->leftBank[0] < prob->leftBank[1] && prob->leftBank[0] != 0){
		return 0;
	}
// more wolves than chickens on right bank
	if(prob->rightBank[0] < prob->rightBank[1] && prob->rightBank[0] != 0){
		return 0;
	}
	
	return 1;
}

//generates succesors for a given node
void makesucc(struct Problem* prob){
//allocate memory for succ
	prob->first = (struct Problem*) malloc(sizeof(struct Problem));
	prob->second = (struct Problem*) malloc(sizeof(struct Problem));
	prob->third = (struct Problem*) malloc(sizeof(struct Problem));
	prob->fourth = (struct Problem*) malloc(sizeof(struct Problem));
	prob->fifth = (struct Problem*) malloc(sizeof(struct Problem));
	
//set parent to current node
	prob->first->parent = prob;
	prob->second->parent = prob;
	prob->third->parent = prob;
	prob->fourth->parent = prob;
	prob->fifth->parent = prob;
	
//copy state information into succ
	prob->first->leftBank[0] = prob->leftBank[0];
	prob->first->leftBank[1] = prob->leftBank[1];
	prob->first->rightBank[0] = prob->rightBank[0];
	prob->first->rightBank[1] = prob->rightBank[1];
	
	prob->second->leftBank[0] = prob->leftBank[0];
	prob->second->leftBank[1] = prob->leftBank[1];
	prob->second->rightBank[0] = prob->rightBank[0];
	prob->second->rightBank[1] = prob->rightBank[1];
	
	prob->third->leftBank[0] = prob->leftBank[0];
	prob->third->leftBank[1] = prob->leftBank[1];
	prob->third->rightBank[0] = prob->rightBank[0];
	prob->third->rightBank[1] = prob->rightBank[1];
	
	prob->fourth->leftBank[0] = prob->leftBank[0];
	prob->fourth->leftBank[1] = prob->leftBank[1];
	prob->fourth->rightBank[0] = prob->rightBank[0];
	prob->fourth->rightBank[1] = prob->rightBank[1];
	
	prob->fifth->leftBank[0] = prob->leftBank[0];
	prob->fifth->leftBank[1] = prob->leftBank[1];
	prob->fifth->rightBank[0] = prob->rightBank[0];
	prob->fifth->rightBank[1] = prob->rightBank[1];
	
	
//copy goal information into succ
	prob->first->goal_boat_side = prob->goal_boat_side;
	prob->first->goal_leftBank[0] = prob->goal_leftBank[0];
	prob->first->goal_leftBank[1] = prob->goal_leftBank[1];
	prob->first->goal_rightBank[0] = prob->goal_rightBank[0];
	prob->first->goal_rightBank[1] = prob->goal_rightBank[1];
	
	prob->second->goal_boat_side = prob->goal_boat_side;
	prob->second->goal_leftBank[0] = prob->goal_leftBank[0];
	prob->second->goal_leftBank[1] = prob->goal_leftBank[1];
	prob->second->goal_rightBank[0] = prob->goal_rightBank[0];
	prob->second->goal_rightBank[1] = prob->goal_rightBank[1];
	
	prob->third->goal_boat_side = prob->goal_boat_side;
	prob->third->goal_leftBank[0] = prob->goal_leftBank[0];
	prob->third->goal_leftBank[1] = prob->goal_leftBank[1];
	prob->third->goal_rightBank[0] = prob->goal_rightBank[0];
	prob->third->goal_rightBank[1] = prob->goal_rightBank[1];
	
	prob->fourth->goal_boat_side = prob->goal_boat_side;
	prob->fourth->goal_leftBank[0] = prob->goal_leftBank[0];
	prob->fourth->goal_leftBank[1] = prob->goal_leftBank[1];
	prob->fourth->goal_rightBank[0] = prob->goal_rightBank[0];
	prob->fourth->goal_rightBank[1] = prob->goal_rightBank[1];
	
	prob->fifth->goal_boat_side = prob->goal_boat_side;
	prob->fifth->goal_leftBank[0] = prob->goal_leftBank[0];
	prob->fifth->goal_leftBank[1] = prob->goal_leftBank[1];
	prob->fifth->goal_rightBank[0] = prob->goal_rightBank[0];
	prob->fifth->goal_rightBank[1] = prob->goal_rightBank[1];

//change data for the 5 possible children
	if(prob->boat_side == 0){ //if boat is on left
		prob->first->boat_side = 1;
		prob->first->leftBank[0]--;
		prob->first->rightBank[0]++;
		
		prob->second->boat_side = 1;
		prob->second->leftBank[0]--;
		prob->second->leftBank[0]--;
		prob->second->rightBank[0]++;
		prob->second->rightBank[0]++;
		
		prob->third->boat_side = 1;
		prob->third->leftBank[1]--;
		prob->third->rightBank[1]++;
		
		prob->fourth->boat_side = 1;
		prob->fourth->leftBank[1]--;
		prob->fourth->leftBank[1]--;
		prob->fourth->rightBank[1]++;
		prob->fourth->rightBank[1]++;
		
		prob->fifth->boat_side = 1;
		prob->fifth->leftBank[0]--;
		prob->fifth->leftBank[1]--;
		prob->fifth->rightBank[0]++;
		prob->fifth->rightBank[1]++;
	} else{ // if boat in on right
		prob->first->boat_side = 0;
		prob->first->leftBank[0]++;
		prob->first->rightBank[0]--;
		
		prob->second->boat_side = 0;
		prob->second->leftBank[0]++;
		prob->second->leftBank[0]++;
		prob->second->rightBank[0]--;
		prob->second->rightBank[0]--;
		
		prob->third->boat_side = 0;
		prob->third->leftBank[1]++;
		prob->third->rightBank[1]--;
		
		prob->fourth->boat_side = 0;
		prob->fourth->leftBank[1]++;
		prob->fourth->leftBank[1]++;
		prob->fourth->rightBank[1]--;
		prob->fourth->rightBank[1]--;
		
		prob->fifth->boat_side = 0;
		prob->fifth->leftBank[0]++;
		prob->fifth->leftBank[1]++;
		prob->fifth->rightBank[0]--;
		prob->fifth->rightBank[1]--;
	}
		
//delete succ who are not legal
	if(verifysucc(prob->first) == 0){
		free(prob->first);
		prob->first = NULL;
	}
	if(verifysucc(prob->second) == 0){
		free(prob->second);
		prob->second = NULL;
	}
	if(verifysucc(prob->third) == 0){
		free(prob->third);
		prob->third = NULL;
	}
	if(verifysucc(prob->fourth) == 0){
		free(prob->fourth);
		prob->fourth = NULL;
	}
	if(verifysucc(prob->fifth) == 0){
		free(prob->fifth);
		prob->fifth = NULL;
	}
}

//checks if node a and b are equivlent
	//return 1 if equivlent
	//return 0 if not equivlent
int issamenode(struct Problem* a, struct Problem* b){
	if(a->boat_side == b->boat_side && 
	   a->leftBank[0] == b->leftBank[0] &&
	   a->leftBank[1] == b->leftBank[1] &&
	   a->rightBank[0] == b->rightBank[0] &&
	   a->rightBank[1] == b->rightBank[1] ){
		   return 1;
	   }
	return 0;
}

//finds if a given node exists within the explored list
	//return 1 if node exists within explored list
	//return 0 if node does not exist within explored list
int isinexplored(struct Problem* prob, vector<struct Problem*>& explored){
	for(int i = 0; i < explored.size(); i++){
		if(issamenode(prob, explored.at(i)) == 1){
			return 1;
		}
	}
	
	return 0;
}

int depth(struct Problem* prob){
	int num=0;
	while(prob->parent != NULL){
		num++;
		prob = prob->parent;
	}
	return num;
}

//uses a bfs to find solution to chicken and wolf problem
void bfs(struct Problem* prob){
	int expanded=0;
	struct Problem* temp = prob;
	struct Problem* temp2;
	vector<struct Problem*> explored;
	prob->first = NULL;
	prob->second = NULL;
	prob->third	= NULL;
	prob->fourth = NULL;
	prob->fifth = NULL;
	
	outputfile = fopen(output, "w");
	
//create queue and explored list and add inital node to them
	queue <struct Problem*> q1; 
	q1.push(prob);
	explored.push_back(prob);
	
	do{
		temp = q1.front();
		q1.pop(); 
		makesucc(temp);
		expanded++;
		
// if succ is legal, add it to the queue
		if(temp->first != NULL && isinexplored(temp->first, explored) == 0){
			q1.push(temp->first);
			explored.push_back(temp->first);
		}
		if(temp->second != NULL && isinexplored(temp->second, explored) == 0){
			q1.push(temp->second);
			explored.push_back(temp->second);
		}
		if(temp->third != NULL && isinexplored(temp->third, explored) == 0){
			q1.push(temp->third);
			explored.push_back(temp->third);
		}
		if(temp->fourth != NULL && isinexplored(temp->fourth, explored) == 0){
			q1.push(temp->fourth);
			explored.push_back(temp->fourth);
		}
		if(temp->fifth != NULL && isinexplored(temp->fifth, explored) == 0){
			q1.push(temp->fifth);
			explored.push_back(temp->fifth);
		}
	} while(isgoalstate(temp)==0);
	
// find the path taken to get to goal node and store in stack
	
	stack <struct Problem*> s1; 
	
	while(temp->parent != NULL){
		s1.push(temp);
		temp = temp->parent;
	}
	
//print out content of stack 
	print_state(prob);	
	
	while (!s1.empty()) 
    { 
        temp = s1.top(); 
        s1.pop(); 
		print_state(temp);
    } 
	
	printf("soultion is %d nodes\n", depth(temp));
	fprintf(outputfile,"soultion is %d nodes\n", depth(temp));
//print the number of nodes explored
	printf("%d nodes explanded in total\n",expanded);
	fprintf(outputfile,"%d nodes explanded in total\n",expanded);
	fclose(outputfile);	
}

void dfs(struct Problem* prob){
	int expanded=0;
	struct Problem* temp = prob;
	struct Problem* temp2;
	vector<struct Problem*> explored;
	prob->first = NULL;
	prob->second = NULL;
	prob->third	= NULL;
	prob->fourth = NULL;
	prob->fifth = NULL;
	
	outputfile = fopen(output, "w");
	
//create stack and explored list and add inital node to them
	stack <struct Problem*> s2; 
	s2.push(prob);
	explored.push_back(prob);
	
	do{
		temp = s2.top();
		s2.pop(); 
		makesucc(temp);
		expanded++;
		
// if succ is legal, add it to the queue
		if(temp->first != NULL && isinexplored(temp->first, explored) == 0){
			s2.push(temp->first);
			explored.push_back(temp->first);
		}
		if(temp->second != NULL && isinexplored(temp->second, explored) == 0){
			s2.push(temp->second);
			explored.push_back(temp->second);
		}
		if(temp->third != NULL && isinexplored(temp->third, explored) == 0){
			s2.push(temp->third);
			explored.push_back(temp->third);
		}
		if(temp->fourth != NULL && isinexplored(temp->fourth, explored) == 0){
			s2.push(temp->fourth);
			explored.push_back(temp->fourth);
		}
		if(temp->fifth != NULL && isinexplored(temp->fifth, explored) == 0){
			s2.push(temp->fifth);
			explored.push_back(temp->fifth);
		}
	} while(isgoalstate(temp)==0);
	
// find the path taken to get to goal node and store in stack
	
	stack <struct Problem*> s1; 
	
	while(temp->parent != NULL){
		s1.push(temp);
		temp = temp->parent;
	}
	
//print out content of stack 
	print_state(prob);	
	
	while (!s1.empty()) 
    { 
        temp = s1.top(); 
        s1.pop(); 
		print_state(temp);
    } 
	
	printf("soultion is %d nodes\n", depth(temp));
	fprintf(outputfile,"soultion is %d nodes\n", depth(temp));
//print the number of nodes explored
	printf("%d nodes explanded in total\n",expanded);
	fprintf(outputfile,"%d nodes explanded in total\n",expanded);
	fclose(outputfile);	
}


int iddfsStart(struct Problem* prob, int maxDepth){
	//int depth = 0;
	
	struct Problem* temp = prob;
	struct Problem* temp2;
	vector<struct Problem*> explored;
	prob->first = NULL;
	prob->second = NULL;
	prob->third	= NULL;
	prob->fourth = NULL;
	prob->fifth = NULL;
	
	outputfile = fopen(output, "w");
	
//create stack and explored list and add inital node to them
	stack <struct Problem*> s2; 
	s2.push(prob);
	explored.push_back(prob);
	
	do{
		temp = s2.top();
		s2.pop(); 
		if(depth(temp) != maxDepth){
			makesucc(temp);
			iddfsCount++;
		
// if succ is legal, add it to the queue
			if(temp->first != NULL && isinexplored(temp->first, explored) == 0){
				s2.push(temp->first);
				explored.push_back(temp->first);
			}
			if(temp->second != NULL && isinexplored(temp->second, explored) == 0){
				s2.push(temp->second);
				explored.push_back(temp->second);
			}
			if(temp->third != NULL && isinexplored(temp->third, explored) == 0){
				s2.push(temp->third);
				explored.push_back(temp->third);
			}
			if(temp->fourth != NULL && isinexplored(temp->fourth, explored) == 0){
				s2.push(temp->fourth);
				explored.push_back(temp->fourth);
			}
			if(temp->fifth != NULL && isinexplored(temp->fifth, explored) == 0){
				s2.push(temp->fifth);
				explored.push_back(temp->fifth);
			}
		
		} else {
			return 0;
		}
	} while(isgoalstate(temp)==0);
	
// find the path taken to get to goal node and store in stack
	
	stack <struct Problem*> s1; 
	
	while(temp->parent != NULL){
		s1.push(temp);
		temp = temp->parent;
	}
	
//print out content of stack 
	print_state(prob);	
	
	while (!s1.empty()) 
    { 
        temp = s1.top(); 
        s1.pop(); 
		print_state(temp);
    } 
	
	printf("soultion is %d nodes\n", depth(temp));
	fprintf(outputfile,"soultion is %d nodes\n", depth(temp));
//print the number of nodes explored
	printf("%d nodes explanded in total\n",iddfsCount);
	fprintf(outputfile,"%d nodes explanded in total\n",iddfsCount);
	fclose(outputfile);	
	return 1;
}


void iddfs(struct Problem* prob){
	int depth=0;
	prob->first = NULL;
	prob->second = NULL;
	prob->third	= NULL;
	prob->fourth = NULL;
	prob->fifth = NULL;
	
	while(true){
		if(iddfsStart(prob,depth) == 0){
			depth++;
		} else {
			break;
		}
	}
	
}

int calchu(int x){
	int count=0;
	while(x != 0){
		x-=2;
		if(x <= 0){
			break;
		}
		count++;
		x+=1;
		count++;
	}
	count++;
	
	return count;
}

int tiebreaker(struct Problem* a, struct Problem* b){
	if(a->rightBank[0] + a->rightBank[1] == b->rightBank[0] + b->rightBank[1] && a->leftBank[0] + a->leftBank[1] == b->leftBank[0] + b->leftBank[1]){
		return 1;
	} else {
		return 0;
	}
}

void astar(struct Problem* prob){
	prob->first = NULL;
	prob->second = NULL;
	prob->third	= NULL;
	prob->fourth = NULL;
	prob->fifth = NULL;
	struct Problem* temp;
	struct thing tempthing;
	struct Problem* temp1;
	struct thing tempthing1;
	int count =0;
	vector<struct Problem*> explored;
	
	outputfile = fopen(output, "w");
	
	std::priority_queue<thing> q1;
	q1.push(thing{calchu(prob->rightBank[0] + prob->rightBank[1]), prob});
	explored.push_back(prob);
	tempthing = q1.top();
	temp = tempthing.b;
	q1.pop();
	
	do{
		makesucc(temp);
				
		if(temp->first != NULL && isinexplored(temp->first, explored) == 0){
				q1.push(thing{-1*calchu(temp->first->rightBank[0] + temp->first->rightBank[1]) - depth(temp->first), temp->first});
		}
		if(temp->second != NULL && isinexplored(temp->second, explored) == 0){
				q1.push(thing{-1*calchu(temp->second->rightBank[0] + temp->second->rightBank[1]) - depth(temp->second), temp->second});
		}

		if(temp->fourth != NULL && isinexplored(temp->fourth, explored) == 0){
				q1.push(thing{-1*calchu(temp->fourth->rightBank[0] + temp->fourth->rightBank[1]) - depth(temp->fourth), temp->fourth});
		}
		if(temp->fifth != NULL && isinexplored(temp->fifth, explored) == 0){
				q1.push(thing{-1*calchu(temp->fifth->rightBank[0] + temp->fifth->rightBank[1]) - depth(temp->fifth), temp->fifth});
		}
		
		if(temp->third != NULL && isinexplored(temp->third, explored) == 0){
				q1.push(thing{-1*calchu(temp->third->rightBank[0] + temp->third->rightBank[1]) - depth(temp->third), temp->third});			
		}

		print_state(temp);
		tempthing = q1.top();
		temp = tempthing.b;
		q1.pop();
		tempthing1 = q1.top();
		temp1 = tempthing1.b;
		while (!q1.empty()){
			q1.pop();
		}
		explored.push_back(temp);
		count++;
	} while(isgoalstate(temp)==0);
	
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

	printf("\n---------------------------------------------------------\n\n");
	
		fprintf(outputfile,"	left bank\n");
	fprintf(outputfile,"		%d chickens\n", prob->goal_leftBank[0]);
	fprintf(outputfile,"		%d wolves\n", prob->goal_leftBank[1]);
	fprintf(outputfile,"	right bank\n");
	fprintf(outputfile,"		%d chickens\n", prob->goal_rightBank[0]);
	fprintf(outputfile,"		%d wolves\n", prob->goal_rightBank[1]);
	if(prob->goal_boat_side == 1){
		fprintf(outputfile,"		boat is on right bank\n");
	} else{
		fprintf(outputfile,"		boat is on left bank\n");
	}

	fprintf(outputfile,"\n---------------------------------------------------------\n\n");
	
	printf("soultion is %d nodes\n", depth(temp));
	fprintf(outputfile,"soultion is %d nodes\n", depth(temp));
	printf("%d nodes explanded in total\n",depth(temp));
	fprintf(outputfile,"%d nodes explanded in total\n",depth(temp));
	
	fclose(outputfile);	
}

int main( int argc, char *argv[] ){
	FILE* myfile;
	int x;
	int y;
	int z;
//checks if the number of arguments is correct
	if(argc != 5){
		printf("incorrect number of arguments\n");
	} else{
		struct Problem* prob;
		prob = (struct Problem*) malloc(sizeof(struct Problem));
		output = argv[4];
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
		
		//print_state(prob);
		
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
	return 0;
}