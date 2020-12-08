/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <queue> 
#include <vector>
#include "MinimaxPlayer.h"

using std::vector;
MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

struct MinimaxTree {
   MinimaxTree* parent;
   OthelloBoard arr;
   MinimaxTree* succ[100];
   int num_succ=0;
   int value;
   int col;
   int row;
   char mysymb;
}; 

MinimaxTree* gametree;
int x=0;
int y=0;


int min_value(MinimaxTree* tree);
int max_value(MinimaxTree* tree);

int depth(MinimaxTree* tree){
	int num=0;
	while(tree->parent != NULL){
		num++;
		tree = tree->parent;
	}
	return num;
}

bool isequal(MinimaxTree* a, MinimaxTree* b){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(a->arr.get_cell(i,j) != b->arr.get_cell(i,j)){
				return false;
			}
		}
	}
	
	return true;
}

void generateSucc(MinimaxTree* tree, char symb){
	if(!tree->arr.has_legal_moves_remaining(tree->mysymb)){
		return;
	}


	struct MinimaxTree* temp = (MinimaxTree*) malloc(sizeof(MinimaxTree));
	temp->arr = tree->arr; 



	 for(int i=0; i<4;i++){
		 for(int j=0; j<4;j++){
			 if(tree->arr.is_legal_move(i, j, tree->mysymb)){
				 temp->arr.play_move(i, j, tree->mysymb);
				 temp->col = i;
				 temp->row = j;
				 temp->parent = tree;
				 
				 temp->value = temp->arr.count_score('X');
				 
				 
				temp->num_succ=0; 

				if(tree->mysymb == 'X'){
					temp->mysymb = 'O';
				} else {
					temp->mysymb = 'X';
				}

				 tree->succ[tree->num_succ] = temp; 
				 tree->num_succ++;
				 temp = NULL;
				 temp = (MinimaxTree*) malloc(sizeof(MinimaxTree));
				 temp->arr = tree->arr;
			 }
		 }
	 }	 
}

bool inexpl(MinimaxTree* a, vector<struct MinimaxTree*>& explored){
	for(int i = 0; i < explored.size(); i++){
		if(isequal(a, explored.at(i))){
			return true;
		}
	}
	
	return false;
}


void create_tree(MinimaxTree* tree, char symb){
	int expan=0;
	char tempsymb = symb;
	struct MinimaxTree* temp;
	std::queue <struct MinimaxTree*> q1; 
	q1.push(tree);
	
	tree->mysymb='O';
	do{
	
		temp = q1.front();
		q1.pop(); 
		expan++;
		
		generateSucc(temp, tree->mysymb);
		for(int i=0;i<temp->num_succ;i++){
			q1.push(temp->succ[i]);
		}
	} while(!q1.empty());
}

int max_value(MinimaxTree* tree){
	if(tree->num_succ == 0){
		return tree->value;
	}
	int val = -99999;
	for(int i=0;i<tree->num_succ;i++){
			val =std::max(val, min_value(tree->succ[i]));
	}
	return val;
}

int min_value(MinimaxTree* tree){
	if(tree->num_succ == 0){
		return tree->value;
	}
	int val = 99999;
	for(int i=0;i<tree->num_succ;i++){
		val = std::min(val, max_value(tree->succ[i]));
	}
	return val;
}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
	MinimaxTree* tree;
		tree = (MinimaxTree*) malloc(sizeof(MinimaxTree));	
	
		tree->arr = *b;
		create_tree(tree, symbol);
		
	if(tree->num_succ < 0){
		col = x;
		row = y;
		x++;
		if(x==16){
			if(y==15){
				y=0;
				x=0;
			} else{
				x=0;
				y++;
			}
		}
	} else {
	if(symbol == 'X'){
		int temp=-9999;
	for(int i=0;i<tree->num_succ;i++){
		if(min_value(tree->succ[i]) < temp){
			col = tree->succ[i]->col;
			row = tree->succ[i]->row;
			temp = min_value(tree->succ[i]);
		}
	}
	
	 } else if (symbol == 'O'){
		int temp=9999;
		for(int i=0;i<tree->num_succ;i++){
			if(max_value(tree->succ[i]) < temp){
				col = tree->succ[i]->col;
				row = tree->succ[i]->row;
				temp = max_value(tree->succ[i]);
			}
		}
	 }
	
	
	
	}
	
	free(tree);
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
