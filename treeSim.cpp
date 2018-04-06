#include <stdio.h>
#include <stdlib.h>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

#define N 1024
#define START 10
int success = 0;
int idle = 0;
int fail = 0;

int successTotal = 0; 
int idleTotal = 0;
int failTotal = 0; 

int data[N] = { 0 };
vector<vector<int> > splitVec;
int k, stations;

void split(vector<int>vec, int level){
	if(vec.size() ==1){
		splitVec.push_back(vec);
	}else if(level == 0){
		splitVec.push_back(vec);
	}else{
		vector<int> left;
		vector<int> right;
		int i = 0;
		for(;i<vec.size()/2;i++){
			left.push_back(vec[i]);
		} 
		for(;i<vec.size();i++){
			right.push_back(vec[i]);
		}

		split(left, level-1);
		split(right, level-1);
	}
}

void printVec(vector<int> v){
	for(int i=0;i<v.size();i++)
		cout << v[i] << " ";
	cout << endl;
}

void probe(vector<int> vec){
	int packets = 0;
	cout <<"loop"<<endl;
	//success = 0;
	//idle = 0;
	//fail = 0;
	
	for(int i=0;i < vec.size() && packets < 2; i++){
			packets+=vec[i];
	}
	if(packets == 0){
		//cout << "idle with ";
		//printVec(vec);
		idle++;
	}else if(packets == 1){
		success++;
		//cout << "success with ";
		//printVec(vec);
	}else {
		fail++;
		//cout << "fail with ";
		//printVec(vec);
		vector<int> left;
		vector<int> right;
		int i = 0;
		for(;i<vec.size()/2;i++){
			left.push_back(vec[i]);
		} 
		for(;i<vec.size();i++){
			right.push_back(vec[i]);
		}
		//printVec(right);
		probe(left);
		probe(right);
	}
}

int main(){
	//Define array
	int firing=0;
	cout<<"Enter the level where the simulation starts:(-1 to exit) ";
	cin >> k;
	if(k == -1){
		exit(1);
	}
	cout <<"Enter the number of ready stations: ";
	cin >> stations;


		for(int j = 0; j < 1; j++){
			srand(time(NULL));
			while(firing < stations){
				if(data[rand() % N] == 0){
					data[rand() % N] = 1;
					firing++;
				}else{
					//Do nothing
				}
			}
			vector<int> vec;
			for(int v = 0 ; v < N; v++){
				vec.push_back(data[v]);
			}
			split(vec, k);
			printf("INPUT\n");
			printVec(vec);
			
			for(int i = 0; i < splitVec.size(); i++){	
				probe(splitVec[i]);
			}
			printf("Idle before:| %d \n", idle);
			printf("Fail before :( %d\n", fail);
			printf("Success! before :) %d \n", success);
			idleTotal += idle; 
			failTotal += fail; 
			successTotal += success; 
			idle = 0;
			fail = 0;
			success = 0; 

		}
		printf("Level: %d\n", k);
		printf("Idle :| %d \n", idleTotal);
		printf("Fail :( %d\n", failTotal);
		printf("Success! :) %d \n", successTotal);

	return 0;
}
