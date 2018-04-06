#include <stdio.h>
#include <stdlib.h>
#include <ctime>    
#include <cstdlib>  
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

#define N 1024

int success = 0;
int idle = 0;
int fail = 0;

int successTotal = 0; 
int idleTotal = 0;
int failTotal = 0; 

int data[N] = { 0 };
vector<vector<int> > splitVec;
int k, stations;

void printVec(vector<int> v){
	for(int i=0;i<v.size();i++)
		cout << v[i] << " ";
	cout << endl;
}

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


void probe(vector<int> vec){
	
	int packets = 0;
	
	for(int i=0;i < vec.size() && packets < 2; i++){
			packets+=vec[i];
	}
	if(packets == 0){
		idle++;
	}else if(packets == 1){
		success++;
	}else {
		fail++;
		vector<int> left;
		vector<int> right;
		int i = 0;
		
		for(;i<vec.size()/2;i++){
			left.push_back(vec[i]);
		} 
		
		for(;i<vec.size();i++){
			right.push_back(vec[i]);
		}
		probe(left);
		probe(right);
	}
}

int main(){

	int firing=0;
	
	cout <<"Enter the number of ready stations(-1 to exit): ";
	
	cin >> stations;
	
	if(stations == -1){
		exit(1);
	}
	
	cout<<"Enter the level where the simulation starts(-1 to exit): ";
	
	cin >> k;
	
	if(k == -1){
		exit(1);
	}

		srand(time(NULL));
		for(int j = 0; j < 100; j++){
			firing = 0;
			int data[N] = { 0 };
			while(firing < stations){
				int index = rand() % N;
				if(data[index] == 0){
					data[index] = 1;
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
			
			for(int i = 0; i < splitVec.size(); i++){	
				probe(splitVec[i]);
			}

			idleTotal = idle; 
			failTotal = fail; 
			successTotal = success; 
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
