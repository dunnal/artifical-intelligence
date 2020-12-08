#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue> 
#include <bits/stdc++.h> 
#include <vector>
#include <string.h>
#include <stdio.h>

using namespace std;


int existinmod(string x, vector<string>& bag){
	//printf("bag size is %d\n", bag.size());
	for(int i = 0; i < bag.size(); i++){
		if(x == bag[i]){
			return i;
		}
	}
	
	return 0;
}



int existin(string x, vector<string>& bag){
	for(int i = 0; i < bag.size(); i++){
		if(x == bag[i]){
			return 1;
		}
	}
	
	return 0;
}


int main (){
	// string line;
	// char rating;
	string rating;
	// ifstream myfile ("trainingSet.txt");
	// getline(myfile,line);

	// cout << line << endl;
	// rating = line[line.length()-3];
	// line[line.length()-6] = '\0';
	
	// cout << line << endl;
	
	
	
	
	
	// myfile.close();
	
	
	
	
	
	
	
	
	
	
	
	
	FILE* myfile;
	char x[300];
	char line[1000];
	char linef[1000];
	char y;
	char rate;
	vector<string> bag;
	vector<string> sentences[500];
	vector<string> sentences1[500];
	vector<string> lookup[501];
	int sentenceCount=0;
	//string y;
	int acurate=0;
	int acuratesum=0;
	myfile = fopen("trainingSet.txt", "r");
	int flag = 0;
	int counterp=0;
		int poscount = 0;
		int negcount = 0;
while(true){
	do {
		if(fscanf(myfile,"%s",x) == EOF){
			flag = 1;
			//printf("glag is %d\n", flag);
			break;
		}
		
		if(strcmp("1",x) != 0 && strcmp("0",x) != 0){
			strcat(line, " ");
			strcat(line,x);
		} else{
			rate = x[0];
		}
	} while(strcmp("1",x) != 0 && strcmp("0",x) != 0);
	
	if(flag == 1){
	//	printf("break\n");
		break;
	}
	counterp++;
	if(counterp == 312){
	//	printf("312: %s\n",line);
		strcat(line," one");
		do {
		if(fscanf(myfile,"%s",x) == EOF){
			flag = 1;
			//printf("glag is %d\n", flag);
			break;
		}
		
		if(strcmp("1",x) != 0 && strcmp("0",x) != 0){
			strcat(line, " ");
			strcat(line,x);
		} else{
			rate = x[0];
		}
	} while(strcmp("1",x) != 0 && strcmp("0",x) != 0);
	//	printf("312: %s\n",line);
	}
	//printf("%s\n",line);
	//printf("rate is %c",rate);
	
	for(int c = 0; line[c] != '\0';c++){
		if(line[c] > 64 && line[c] < 91){
			line[c] += 32;
		} else if(line[c] < 60 || line[c] > 123){
			if(line[c] != 32){
				line[c] = 94;
			}
		}
	}
	
	//printf("%s\n",line);
	
	int counter=0;
	for(int c = 0; c < 1000;c++){
		if(line[c] != 94){
			linef[counter] = line[c];
			counter++;
		}
	}
	
	//printf("%s		%c\n",linef, rate);
	//printf("\n");
	
	char temp[100];
	int count=0;
	for(int c = 1; c < 1000; c++){
	//	if(linef[c] != 32){
			temp[count] = linef[c];
			count++;
			
		if(linef[c] == 32 || linef[c] == 0){
	//		printf("	temp is %s\n",temp);
			if(temp[count-1] == ' '){
				temp[count-1] = '\0';
			}
				
			string that = temp;
		//	printf("push into it\n");
			sentences[sentenceCount].push_back(that);
		//	printf("pushed\n");
			if(existin(that,bag) == 0){
				bag.push_back(that);
			}
			memset(temp,0,100);
			count = 0;
			if(linef[c] == 0){
				break;
			}
		}
	}
	rating = rate;
	if(rating == "1"){
		poscount++;
	} else if (rating == "0"){
		negcount++;
	}
	sentences[sentenceCount].push_back(rating);
	memset(linef,0,1000);
	memset(line,0,1000);
	sentenceCount++;
}
		
	printf("count is %d\n",counterp);
	fclose(myfile);
	
	sort(bag.begin(), bag.end()); 
	
//	for(int i=0;i<bag.size();i++){
//		cout << bag[i] << "\n";
//	}
	
	for(int i=0; i<bag.size();i++){
		if(bag[i] == ""){
			bag.erase(bag.begin() + i);
		}
	}
	
		printf("done with %d words\n",bag.size());
	// for(int i=0; i<bag.size();i++){
		// cout << i << ": " << bag[i] << "\n";
	// }
	
	ofstream outfile ("preprocessed_train.txt");
	
	

	for(int i=0; i<bag.size()-1;i++){
		outfile << bag[i] << ",";
	}
	outfile << bag.back() << "\n";

	for(int i=0; i < bag.size(); i++){
		lookup[0].push_back(bag[i]);
	}
	lookup[0].push_back("classlabel");
	
	
	
	for(int j=0; j < 499; j++){
	for(int i=0; i < bag.size(); i++){
		if(existin(bag[i], sentences[j]) == 1){
			outfile << "1,";
			lookup[j+1].push_back("1");
		} else {
			outfile << "0,";
			lookup[j+1].push_back("0");
		}
	}
	
	lookup[j+1].push_back(sentences[j].back());
	outfile << sentences[j].back() << "\n" ;
	}
	
	 outfile.close();
	 
	
	
	//for(int i=0;i<500;i++){
	//	if(lookup[i+1].back() == "1"){
	//		poscount++;
	//	}
	//}
	
	//printf("pos is %d neg is %d\n",poscount,negcount);
	
	vector<int> probs[bag.size()];
	
	//lookup[0]
	
	//for(int i=0; i< lookup[0].size();i++){
	//	cout << lookup[i][5] << "\n";
	//}
	
	
	
	// int lookupcountpos=0;
	// int lookupcountneg=0;
	// for(int j=0; j<500; j++){
		// for(int i=0;i<lookup[j+1].size()-1;i++){
			// if(lookup[j+1][i] == "1"){
				// if(lookup[j+1].back() == "1"){
					// lookupcountpos++;
				// } else{
					// lookupcountneg++;
				// }
			// }
		// }
		// probs[j].push_back(lookupcountpos);
		// probs[j].push_back(lookupcountneg);
		// lookupcountpos=0;
		// lookupcountneg=0;
	// }
	
	int tempo=0;
	int tempn=0;
	for(int j=0; j< bag.size(); j++){
	for(int i=0;i<500;i++){
		if(lookup[i][j] == "1"){
			if(lookup[i].back() == "1"){
				tempo++;
			} else {
				tempn++;
			}
		} 
	}
		probs[j].push_back(tempo);
		probs[j].push_back(tempn);
	//	cout << lookup[0][j] << " pos: " << probs[j][0] << " neg: " << probs[j][1] << "\n";
		tempo=0;
		tempn=0;

	}
	
	//probs 0 is positive, probs 1 is negative
	
//	cout << " pos: " << probs[0][0] << " neg: " << probs[0][1] << "\n";
	
	int numpos=0; // total positive
	int numneg=0; // total negative
	
	for(int i=0;i<500; i++){
		if(lookup[i].back() == "1"){
			numpos++;
		} else {
			numneg++;
		}
	}
	
	//printf("num pos: %d, neg: %d\n", numpos, numneg);
	//printf("testinf this %d\n", probs[0][0]);
	
//	float temper = numpos;
//	float helper = (probs[0][0]+1) / (temper+2.0);
	
//	printf("test %f\n",log(helper));
	
	float tempneg=0;
	float temppos=0;
	
	float negsum=0;
	float possum=0;
	string airating;
	
	for(int j=0; j < 499; j++){
	for(int i=0; i < sentences[j].size(); i++){
		if(existin(sentences[j][i],lookup[0]) > 0){
			int area = existinmod(sentences[j][i],lookup[0]);
		//	printf("area is %d\n", area);
		//	cout << sentences1[j][i] << "\n";
			float temper = numpos + 2.0;
			float helper = (probs[area][0]+1) / (temper);
			temppos = helper;
		//	cout << "     probs pos: " << probs[area][0] << " neg: " << probs[area][1] << "\n";
			temper = numneg + 2.0;
			helper = (probs[area][1]+1) / (temper);
			tempneg = helper;
		//	printf("	test pos: %f neg: %f\n",temppos, tempneg);
			if(negsum == 0){
				negsum += tempneg;
				possum += temppos;
			} else{
				negsum *= tempneg;
				possum *= temppos;
			}
		}
	}
//	printf("sum pos: %f neg: %f\n",log(possum), log(negsum));
	//float temper = numpos / 499;
	//possum *= possum/499;
	//negsum *= negsum/499;
	
	float whatamidoing = possum + negsum;
	possum /= whatamidoing;
	negsum /= whatamidoing;
	
	//printf("sum pos: %f neg: %f\n",possum, negsum );
	
	if(possum > negsum){
		airating = "1";
	} else {
		airating = "0";
	}
	
	
	//cout << "gussed rating is " << airating << " and actual is " << sentences[j].back() << "\n";
	//printf("sum pos: %f neg: %f\n\n",possum, negsum );
	//printf("gussed rating is %s and actual is %d\n", airating,sentences[j].back())
	if(airating == sentences[j].back()){
		acurate++;
	}
	acuratesum++;
	
	negsum=0;
	possum=0;
	}
	
	float welp = acuratesum;
	float thisthat = acurate / welp;
	
	outfile.open("results.txt");
	
	printf("training accuracy is %f\n",thisthat);
	outfile << "training accuracy is " << thisthat << "\n";
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	myfile = fopen("testSet.txt", "r");
	
	flag=0;
	memset(linef,0,1000);
	memset(line,0,1000);
	sentenceCount=0;
	while(true){
		do {
		if(fscanf(myfile,"%s",x) == EOF){
			flag = 1;
			//printf("glag is %d\n", flag);
			break;
		}
		
		if(strcmp("1",x) != 0 && strcmp("0",x) != 0){
			strcat(line, " ");
			strcat(line,x);
		} else{
			rate = x[0];
		}
	} while(strcmp("1",x) != 0 && strcmp("0",x) != 0);
	
	if(flag == 1){
	//	printf("break\n");
		break;
	}
	counterp++;
	//printf("%s",line);
	//printf("  rate is %c\n",rate);
	
	for(int c = 0; line[c] != '\0';c++){
		if(line[c] > 64 && line[c] < 91){
			line[c] += 32;
		} else if(line[c] < 60 || line[c] > 123){
			if(line[c] != 32){
				line[c] = 94;
			}
		}
	}
	
	//printf("%s\n",line);
	
	int counter=0;
	for(int c = 0; c < 1000;c++){
		if(line[c] != 94){
			linef[counter] = line[c];
			counter++;
		}
	}
	
	//printf("%s		%c\n",linef, rate);
	//printf("\n");
	
	char temp[100];
	int count=0;
	for(int c = 1; c < 1000; c++){
	//	if(linef[c] != 32){
			temp[count] = linef[c];
			count++;
			
		if(linef[c] == 32 || linef[c] == 0){
	//		printf("	temp is %s\n",temp);
			if(temp[count-1] == ' '){
				temp[count-1] = '\0';
			}
				
			string that = temp;
		//	printf("push into it\n");
			sentences1[sentenceCount].push_back(that);
		//	printf("pushed\n");
			if(existin(that,bag) == 0){
				bag.push_back(that);
			}
			memset(temp,0,100);
			count = 0;
			if(linef[c] == 0){
				break;
			}
		}
	}
	rating = rate;
	if(rating == "1"){
		poscount++;
	} else if (rating == "0"){
		negcount++;
	}
	sentences1[sentenceCount].push_back(rating);
	memset(linef,0,1000);
	memset(line,0,1000);
	sentenceCount++;
}


 //myfile.close();
	int testcount = 498;
	
	tempneg=0;
	temppos=0;
	
	negsum=0;
	possum=0;

	
	for(int j=0; j < testcount; j++){
	for(int i=0; i < sentences1[j].size(); i++){
		if(existin(sentences1[j][i],lookup[0]) > 0){
			int area = existinmod(sentences1[j][i],lookup[0]);
		//	printf("area is %d\n", area);
		//	cout << sentences1[j][i] << "\n";
			float temper = numpos + 2.0;
			float helper = (probs[area][0]+1) / (temper);
			temppos = helper;
		//	cout << "     probs pos: " << probs[area][0] << " neg: " << probs[area][1] << "\n";
			temper = numneg + 2.0;
			helper = (probs[area][1]+1) / (temper);
			tempneg = helper;
		//	printf("	test pos: %f neg: %f\n",temppos, tempneg);
			if(negsum == 0){
				negsum += tempneg;
				possum += temppos;
			} else{
				negsum *= tempneg;
				possum *= temppos;
			}
		}
	}
//	printf("sum pos: %f neg: %f\n",log(possum), log(negsum));
	//float temper = numpos / 499;
	//possum *= possum/499;
	//negsum *= negsum/499;
	
	float whatamidoing = possum + negsum;
	possum /= whatamidoing;
	negsum /= whatamidoing;
	
	//printf("sum pos: %f neg: %f\n",possum, negsum );
	
	if(possum > negsum){
		airating = "1";
	} else {
		airating = "0";
	}
	
	
	//cout << "gussed rating is " << airating << " and actual is " << sentences[j].back() << "\n";
	//printf("sum pos: %f neg: %f\n\n",possum, negsum );
	//printf("gussed rating is %s and actual is %d\n", airating,sentences[j].back())
	if(airating == sentences[j].back()){
		acurate++;
	}
	acuratesum++;
	
	negsum=0;
	possum=0;
	}
	
	welp = acuratesum;
	thisthat = acurate / welp;
	
	printf("test accuracy is %f\n",thisthat);
	outfile << "test accuracy is " << thisthat << "\n";
	
	outfile << "\n" << "we used the training data as traning, and then tested it on both the traningSet and testSet, with accuracy as you see above" << "\n";
	
	
	outfile.close();
	
	
	
	
	
	
	
	
	
	
	return 0;
}