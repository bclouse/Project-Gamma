#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>
#include <random>
#include <iomanip>
#include <cmath>

using namespace std;

#define ZERO_TO_ONE (float)rand()/RAND_MAX
#define RADIANS (double)3.1415926535897/180

#ifndef CLASSES_H
#define CLASSES_H

//===============================
//	Cities Struct
//===============================

struct City {
	float x, y;
	int num;
};

//===============================
//	Agent Class
//===============================

class Agent {
private:
	vector<vector<City>> policy;
	vector<float> fitness;
	int start;
	int policies;
	int cities;
public:
	Agent(float,int,int,bool);
	void p_random();
	void display();
	void action(float**,int);
	void evaluate();
	void down_select();
	void repopulate();
	void mutate(vector<City>*);
	void log_data(float**,int);
	void path();
};

//===============================
//	Functions
//===============================

float distance(City, City);

#endif